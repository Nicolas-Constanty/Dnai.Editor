#ifndef DNAI_MODELS_ML_HYPERPARAMETERS_H
#define DNAI_MODELS_ML_HYPERPARAMETERS_H

#include <QObject>
#include <QQmlPropertyMap>

#include "dnai/interfaces/iserializable.h"

namespace dnai {
namespace models {
namespace ml {
class HyperParameters : public QObject, public interfaces::ASerializable<HyperParameters>
{
    Q_OBJECT
    Q_PROPERTY(QQmlPropertyMap *data READ data WRITE setData NOTIFY dataChanged)

    Q_PROPERTY(int epoch READ epoch WRITE setEpoch NOTIFY epochChanged)
    Q_PROPERTY(int batchSize READ batchSize WRITE setBatchSize NOTIFY batchSizeChanged)
    Q_PROPERTY(float customLoss READ customLoss WRITE setCustomLoss NOTIFY customLossChanged)
    Q_PROPERTY(QString lossFunction READ lossFunction WRITE setLossFunction NOTIFY lossFunctionChanged)
    Q_PROPERTY(QString optimizer READ optimizerNam WRITE setoptimizerNam NOTIFY optimizerNamChanged)
    Q_PROPERTY(float learningRate READ learningRate WRITE setLearningRate NOTIFY learningRateChanged)
    Q_PROPERTY(float epsilon READ epsilon WRITE setEpsilon NOTIFY epsilonChanged)
    Q_PROPERTY(float decay READ decay WRITE setDecay NOTIFY decayChanged)
    Q_PROPERTY(float rho READ rho WRITE setRho NOTIFY rhoChanged)

private:
    QQmlPropertyMap m_data;

public:
    HyperParameters();
    virtual ~HyperParameters();

public:
    QQmlPropertyMap *data();

    int epoch() const;

    int batchSize() const;

    float customLoss() const;

    QString lossFunction() const;

    QString optimizerNam() const;

    float learningRate() const;

    float epsilon() const;

    float decay() const;

    float rho() const;

public slots:
    void setData(QQmlPropertyMap *parameters);

    void setEpoch(int epoch);

    void setBatchSize(int batchSize);

    void setCustomLoss(float customLoss);

    void setLossFunction(const QString &lossFunction);

    void setoptimizerNam(const QString &optimizer);

    void setLearningRate(float learningRate);

    void setEpsilon(float epsilon);

    void setDecay(float decay);

    void setRho(float rho);

signals:
    void dataChanged(QQmlPropertyMap *parameters);

    void epochChanged(int epoch);

    void batchSizeChanged(int batchSize);

    void customLossChanged(float customLoss);

    void lossFunctionChanged(QString lossFunction);

    void optimizerNamChanged(QString optimizer);

    void learningRateChanged(float learningRate);

    void epsilonChanged(float epsilon);

    void decayChanged(float decay);

    void rhoChanged(float rho);

    // ISerializable interface
public:
    void serialize(QJsonObject &obj) const;

protected:
    void _deserialize(const QJsonObject &obj);
};

}
}
}

#endif // DNAI_MODELS_ML_HYPERPARAMETERS_H
