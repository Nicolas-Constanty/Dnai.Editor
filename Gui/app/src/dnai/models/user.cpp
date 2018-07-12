#include "dnai/models/user.h"

namespace dnai {
    namespace models {

       User::User(): QObject(nullptr)
       {}

       User::~User()
       {}

       QString User::name() const
       {
           return m_name;
       }

       void User::setName(const QString &name)
       {
           m_name = name;
       }

       QString User::profile_url() const
       {
           return m_profile_url;
       }

       void User::setProfile_url(const QString &profile_url)
       {
           m_profile_url = profile_url;
       }

       QJsonArray User::files() const
       {
           return m_files;
       }

       void User::setFiles(const QJsonArray &files)
       {
           m_files = files;
       }

       QJsonObject User::currentFileData() const
       {
           return m_currentFileData;
       }

       void User::setCurrentFileData(const QJsonObject &currentFileData)
       {
           m_currentFileData = currentFileData;
       }
    }
}
