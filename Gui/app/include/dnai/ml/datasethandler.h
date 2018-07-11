#ifndef DNAI_ML_DATASET_HANDLER_H
#define DNAI_ML_DATASET_HANDLER_H

#include <QObject>
#include "dnai/models/ml/dataset.h"

namespace dnai {
namespace ml {
class DatasetHandler : public QObject
{
    Q_OBJECT
public:
    DatasetHandler(QObject *parent = nullptr);

    Q_INVOKABLE int open(const QString &path);
    Q_INVOKABLE dnai::models::ml::Dataset *createFromPath(const QString &path);
};
}
}

#endif //DNAI_ML_DATASET_HANDLER_H
