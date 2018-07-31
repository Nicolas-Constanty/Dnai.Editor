#ifndef DNAI_MODELS_ML_ML_PROJECT_H
#define DNAI_MODELS_ML_ML_PROJECT_H

#include <QObject>
#include "dataset.h"
#include "model.h"

namespace dnai {
namespace models {
namespace ml {
class MlProject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<Dataset*> datasets READ datasets CONSTANT)
    Q_PROPERTY(dnai::models::ml::Model *model READ model CONSTANT)

public:
    MlProject(QObject *parent = nullptr);

    QList<Dataset*> datasets() const;

    dnai::models::ml::Model *model();

private:
    QList<Dataset*> m_datasets;
    dnai::models::ml::Model m_model;
};
}
}
}

#endif //DNAI_MODELS_ML_ML_PROJECT_H
