#ifndef DNAI_ML_ML_HANDLER_H
#define DNAI_ML_ML_HANDLER_H

#include <QObject>

#include "datasethandler.h"

namespace dnai {
namespace ml {
class MlHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DatasetHandler *dataset READ dataset CONSTANT)

public:
    MlHandler(QObject *parent = nullptr);

    /*
     * QML Properties
     */
public:
    DatasetHandler *dataset();

    /*
     * Inner c++ properties
     */
public:
    DatasetHandler &Dataset();

private:
    DatasetHandler m_dataset;
};
}
}

#endif // DNAI_ML_ML_HANDLER_H
