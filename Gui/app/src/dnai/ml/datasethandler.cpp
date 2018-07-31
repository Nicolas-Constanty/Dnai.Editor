#include <QDir>
#include <QUrl>
#include <QDebug>
#include <QVariantMap>

#include "dnai/ml/datasethandler.h"
#include "dnai/models/ml/dataset.h"

namespace dnai {
namespace ml {

DatasetHandler::DatasetHandler(QObject *parent) : QObject(parent)
{

}

int DatasetHandler::open(const QString &path)
{
    return 0;
}

models::ml::Dataset *DatasetHandler::createFromPath(const QString &path)
{
    const auto realPath = QUrl(path).toLocalFile();
    QDir directory(realPath);
    if (!directory.exists())
    {
        return nullptr;
    }
    auto dataset = new models::ml::Dataset();
    const auto dirs = directory.entryList(QDir::Dirs);
    auto label = 0;
    auto totalCount = 0;
    for (const auto dir : dirs)
    {
        if (dir != "." && dir != "..")
        {
            QVariantMap m;
            QDir tmp(realPath + "/" + dir);
            const auto infos = tmp.entryInfoList(QDir::Files);

            m["value"] = QString::number(label);
            m["count"] = infos.count();
            m["selected"] = true;
            dataset->labels()->insert(dir, m);
            totalCount += infos.count();
            label++;
        }
    }
    dataset->setName(QUrl(path).fileName());
    dataset->setPath(path);
    dataset->setAutoGenerateCsv(true);
    dataset->setShuffleData(true);
    dataset->data()->insert("totalCount", totalCount);
    return dataset;
}

}
}
