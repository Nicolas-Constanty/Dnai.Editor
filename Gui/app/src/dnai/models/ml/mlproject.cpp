#include "dnai/models/ml/mlproject.h"

namespace dnai {
namespace models {
namespace ml {

MlProject::MlProject(QObject *parent) : QObject(parent) {}

QList<Dataset *> MlProject::datasets() const
{
    return m_datasets;
}

Model *MlProject::model()
{
    return &m_model;
}

}
}
}
