#include "dnai/session.h"
#include "dnai/http/response.h"
#include "dnai/api/api.h"
#include "dnai/project.h"
#include <QFileInfo>

namespace dnai {

Session::Session(QObject *parent) : QObject(parent), m_user(nullptr)
{
}

models::User *Session::user() const
{
    return m_user;
}

void Session::setUser(models::User *user)
{
    if (user == m_user)
        return;
    m_user = user;
    emit userChanged(user);
}

void Session::signin(const QString &username, const QString &password)
{
    api::signin(username, password).map([this](Response response) -> Response {
        getCurrentUser();
        return response;
    },
    [this](Response response) -> Response {
        emit apiErrors();
        return response;
    });
}

void Session::getCurrentUser()
{
    api::get_current_user().map([this](Response response) -> Response {
        m_user = new models::User();
        m_user->setName(response.body["first_name"].toString() + " " + response.body["last_name"].toString());
        m_user->setProfile_url("../Images/default_user.png");
        updateCurentUserFiles();
        emit userChanged(m_user);
        return response;
    });
}

bool Session::uploadFile(const QString &path)
{
    auto file = new QFile(QUrl(path).toLocalFile());
    if (!file->open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        return false;
    }
    api::post_file(QFileInfo(file->fileName()).fileName(), file).map([this](Response response) -> Response {
        updateCurentUserFiles();
        return response;
    });
    return true;
}

void Session::updateCurentUserFiles()
{
    api::get_files().map([this](Response response) -> Response {
        if (m_user != nullptr) {
            m_user->setFiles(response.body["results"].toArray());
            emit userChanged(m_user);
        }
        return response;
    });
}

void Session::logout()
{
    api::logout();
    delete m_user;
    setUser(nullptr);
}

void Session::downloadProjectData(uint index, const QString &id)
{
    api::get_raw_file(id).map([this, index](Response response) -> Response {
         QFile emptyFile("empty");
         auto project = Project::loadProject(response.body, emptyFile);
         if (project != nullptr) {
             m_user->setCurrentFileData(project->data());
             emit userChanged(m_user);
         }
         return response;
     });
}

}
