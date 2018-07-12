#ifndef DNAI_MODELS_ML_MODEL_H
#define DNAI_MODELS_ML_MODEL_H

#include <QObject>

namespace dnai {
namespace models {
namespace ml {
class Model : public QObject
{
    Q_OBJECT
public:
    Model() {}
    virtual ~Model() {}
};
}
}
}

#endif //  DNAI_MODELS_ML_MODEL_H
