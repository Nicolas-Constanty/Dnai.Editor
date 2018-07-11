#include "dnai/models/ml/dataset.h"

namespace dnai {
namespace models {
namespace ml {

Dataset::Dataset(QObject *parent) : QObject(parent) {}

Dataset::~Dataset() {}

QString Dataset::name() const
{
    return m_data["name"].toString();
}

QString Dataset::path() const
{
    return m_data["path"].toString();
}

int Dataset::samples() const
{
    return m_data["samples"].toInt();
}

int Dataset::training() const
{
    return m_data["training"].toInt();
}

int Dataset::test() const
{
    return m_data["test"].toInt();
}

bool Dataset::autoGenerateCsv() const
{
    return m_data["autoGenerateCsv"].toBool();
}

bool Dataset::shuffleData() const
{
    return m_data["shuffleData"].toBool();
}

QString Dataset::csvPath() const
{
    return m_data["csvPath"].toString();
}

utils::IterableQQmlPropertyMap *Dataset::labels()
{
    return &m_labels;
}

void Dataset::setName(const QString &name)
{
    if (m_data["name"].toString() == name)
        return;

    m_data["name"] = name;
    emit nameChanged(name);
}

void Dataset::setPath(const QString &path)
{
    if (m_data["path"].toString() == path)
        return;

    m_data["path"] = path;
    emit pathChanged(path);
}

void Dataset::setSamples(int samples)
{
    if (m_data["samples"].toInt() == samples)
        return;

    m_data["samples"] = samples;
    emit samplesChanged(samples);
}

void Dataset::setTraining(int training)
{
    if (m_data["training"].toInt() == training)
        return;

    m_data["training"] = training;
    emit trainingChanged(training);
}

void Dataset::setTest(int test)
{
    if (m_data["test"].toInt() == test)
        return;

    m_data["test"] = test;
    emit testChanged(test);
}

void Dataset::setAutoGenerateCsv(bool autoGenerateCsv)
{
    if (m_data["autoGenerateCsv"].toBool() == autoGenerateCsv)
        return;

    m_data["autoGenerateCsv"] = autoGenerateCsv;
    emit autoGenerateCsvChanged(autoGenerateCsv);
}

void Dataset::setShuffleData(bool shuffleData)
{
    if (m_data["shuffleData"].toBool() == shuffleData)
        return;

    m_data["shuffleData"] = shuffleData;
    emit shuffleDataChanged(shuffleData);
}

void Dataset::setCsvPath(const QString &csvPath)
{
    if (m_data["csvPath"].toString() == csvPath)
        return;

    m_data["csvPath"] = csvPath;
    emit csvPathChanged(csvPath);
}

void Dataset::setLabels(utils::IterableQQmlPropertyMap *labels)
{
    for (auto key : (*labels).keys())
        m_labels[key] = (*labels)[key];
    emit labelsChanged(&m_labels);
}

void Dataset::setData(QQmlPropertyMap *data)
{
    for (auto key : (*data).keys())
        m_data[key] = (*data)[key];
    emit dataChanged(&m_data);
}

void Dataset::serialize(QJsonObject &obj) const
{
    for (auto key : m_data.keys())
        obj.insert(key, QJsonValue::fromVariant(m_data[key]));
}

QQmlPropertyMap *Dataset::data()
{
    return &m_data;
}

void Dataset::_deserialize(const QJsonObject &obj)
{
    for (auto key : obj.keys())
        m_data.insert(key, QVariant::fromValue(obj[key]));
}

Label::Label(QObject *parent) : QObject(parent) {}

Label::~Label() {}

QString Label::path() const
{
    return m_path;
}

QString Label::value() const
{
    return m_value;
}

void Label::setPath(QString path)
{
    if (m_path == path)
        return;

    m_path = path;
    emit pathChanged(m_path);
}

void Label::setValue(QString value)
{
    if (m_value == value)
        return;

    m_value = value;
    emit valueChanged(m_value);
}

}
}
}
