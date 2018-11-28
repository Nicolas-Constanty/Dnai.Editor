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
