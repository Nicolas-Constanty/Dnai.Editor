#include <QJsonObject>

#include "dnai/models/ml/hyperparameters.h"

namespace dnai {
namespace models {
namespace ml {

HyperParameters::HyperParameters() {}

HyperParameters::~HyperParameters() {}

QQmlPropertyMap *HyperParameters::data()
{
    return &m_data;
}

int HyperParameters::epoch() const
{
    return m_data["epoch"].toInt();
}

int HyperParameters::batchSize() const
{
    return m_data["batchSize"].toInt();
}

float HyperParameters::customLoss() const
{
    return m_data["customLoss"].toFloat();
}

QString HyperParameters::lossFunction() const
{
    return m_data["customLoss"].toString();
}

QString HyperParameters::optimizerNam() const
{
    return m_data["customLoss"].toString();
}

float HyperParameters::learningRate() const
{
    return m_data["customLoss"].toFloat();
}

float HyperParameters::epsilon() const
{
    return m_data["customLoss"].toFloat();
}

float HyperParameters::decay() const
{
    return m_data["customLoss"].toFloat();
}

float HyperParameters::rho() const
{
    return m_data["customLoss"].toFloat();
}

void HyperParameters::setData(QQmlPropertyMap *parameters)
{
    for (auto key : (*parameters).keys())
        m_data[key] = (*parameters)[key];
    emit dataChanged(&m_data);
}

void HyperParameters::setEpoch(int epoch)
{
    if (m_data["epoch"].toInt() == epoch)
        return;

    m_data["epoch"] = epoch;
    emit epochChanged(epoch);
}

void HyperParameters::setBatchSize(int batchSize)
{
    if (m_data["batchSize"].toInt() == batchSize)
        return;

    m_data["batchSize"] = batchSize;
    emit batchSizeChanged(batchSize);
}

void HyperParameters::setCustomLoss(float customLoss)
{
    if (m_data["customLoss"].toFloat() == customLoss)
        return;

    m_data["customLoss"] = customLoss;
    emit customLossChanged(customLoss);
}

void HyperParameters::setLossFunction(const QString &lossFunction)
{
    if (m_data["lossFunction"].toString() == lossFunction)
        return;

    m_data["lossFunction"] = lossFunction;
    emit lossFunctionChanged(lossFunction);
}

void HyperParameters::setoptimizerNam(const QString &optimizer)
{
    if (m_data["optimizer"].toString() == optimizer)
        return;

    m_data["lossFunction"] = optimizer;
    emit optimizerNamChanged(optimizer);
}

void HyperParameters::setLearningRate(float learningRate)
{
    if (m_data["learningRate"].toFloat() == learningRate)
        return;

    m_data["learningRate"] = learningRate;
    emit learningRateChanged(learningRate);
}

void HyperParameters::setEpsilon(float epsilon)
{
    if (m_data["epsilon"].toFloat() == epsilon)
        return;

    m_data["epsilon"] = epsilon;
    emit epsilonChanged(epsilon);
}

void HyperParameters::setDecay(float decay)
{
    if (m_data["decay"].toFloat() == decay)
        return;

    m_data["decay"] = decay;
    emit decayChanged(decay);
}

void HyperParameters::setRho(float rho)
{
    if (m_data["rho"].toFloat() == rho)
        return;

    m_data["rho"] = rho;
    emit rhoChanged(rho);
}

void HyperParameters::serialize(QJsonObject &obj) const
{
    for (auto key : m_data.keys())
        obj.insert(key, QJsonValue::fromVariant(m_data[key]));
}

void HyperParameters::_deserialize(const QJsonObject &obj)
{
    for (auto key : obj.keys())
        m_data.insert(key, QVariant::fromValue(obj[key]));
}
}
}
}
