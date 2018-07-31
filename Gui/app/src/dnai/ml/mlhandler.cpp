#include "dnai/ml/mlhandler.h"

namespace dnai {
namespace ml {

MlHandler::MlHandler(QObject *parent) : QObject(parent)
{

}

DatasetHandler *MlHandler::dataset()
{
    return &m_dataset;
}

DatasetHandler &MlHandler::Dataset()
{
    return m_dataset;
}

}
}
