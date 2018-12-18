#include <QProcess>
#include <QDir>
#include <QGuiApplication>
#include "dnai/core/resourcehandler.h"
#include "dnai/interfaces/isolution.h"
#include "dnai/editor.h"

namespace dnai
{
    namespace gcore
    {
        void ResourceHandler::setDirectory(QString directory)
        {

        }

        QString ResourceHandler::copyResource(QUrl filePath)
        {
            QFile resource(filePath.toLocalFile());
            interfaces::ISolution *solution = Editor::instance().solution();

            if (resource.exists())
            {
                QFileInfo resourceInfo(filePath.toLocalFile());

                if (!QFile::exists(solution->path()))
                {
                    Editor::instance().notifyError("No such target directory: " + solution->path());
                }
                else
                {
                    QString newPath = solution->path() + "/";

                    while (QFile::exists(newPath + resourceInfo.fileName()))
                    {
                        newPath += "copy_";
                    }

                    newPath += resourceInfo.fileName();

                    if (resource.copy(newPath))
                    {
                        convertModels(newPath);
                        return QFileInfo(newPath).fileName();
                    }
                    else
                    {
                        Editor::instance().notifyError("Couldn't copy file: " + resource.errorString());
                    }
                }
            }
            else
            {
                Editor::instance().notifyError("No such file " + filePath.toLocalFile());
            }

            return QString();
        }

        void ResourceHandler::convertModels(const QString &path)
        {
            QList<QProcess *> converters;

            auto pythonPath = QGuiApplication::applicationDirPath() + "/pythonBackend";
            //Keras to cntk
            auto kerasToCntk = new QProcess();
            kerasToCntk->setProgram(pythonPath + "/python.exe");
            kerasToCntk->setArguments(QStringList({ pythonPath + "/KerasToCntk.py", "-m", path}));
            //Keras to tensorflow
            auto kerasToTensorflow = new QProcess();
            kerasToTensorflow->setProgram(pythonPath + "/python.exe");
            kerasToTensorflow->setArguments(QStringList({  pythonPath + "/KerasToTensorflow.py", "-m", path}));

            converters << kerasToCntk << kerasToTensorflow;
            for (auto converter : converters)
            {
                converter->start();
                if (!converter->waitForStarted())
                    Editor::instance().notifyError("Couldn't start process: " + converter->errorString());
            }

            for (auto converter : converters)
            {
                converter->waitForFinished();
            }

            for (auto i = 0; i < converters.length(); i++)
            {
                delete converters[i];
            }
        }

        bool ResourceHandler::deleteResource(QString value)
        {
            QFile file(Editor::instance().solution()->path() + "/" + value);

            if (file.exists())
            {
                return file.remove();
            }

            Editor::instance().notifyError("Couldn't delte resource file (not found): " + file.fileName());
            return false;
        }
    }
}
