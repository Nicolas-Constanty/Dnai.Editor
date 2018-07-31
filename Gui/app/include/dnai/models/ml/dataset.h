#ifndef  DNAI_MODELS_ML_DATASET_H
#define  DNAI_MODELS_ML_DATASET_H

#include <QObject>
#include <QQmlPropertyMap>

#include "dnai/interfaces/iserializable.h"
#include "dnai/utils/iterableqqmlpropertymap.h"

namespace dnai {
namespace models {
namespace ml {
class Label : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

    QString m_path;

    QString m_value;

public:
    Label(QObject *parent = nullptr);
    virtual ~Label();
    QString path() const;
    QString value() const;

public slots:
    void setPath(QString path);
    void setValue(QString value);

signals:
    void pathChanged(QString path);
    void valueChanged(QString value);
};
class Dataset : public QObject, public interfaces::ASerializable<Dataset>
{
    Q_OBJECT
    Q_PROPERTY(QQmlPropertyMap *data READ data WRITE setData NOTIFY dataChanged)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(int samples READ samples WRITE setSamples NOTIFY samplesChanged)
    Q_PROPERTY(int training READ training WRITE setTraining NOTIFY trainingChanged)
    Q_PROPERTY(int test READ test WRITE setTest NOTIFY testChanged)
    Q_PROPERTY(bool autoGenerateCsv READ autoGenerateCsv WRITE setAutoGenerateCsv NOTIFY autoGenerateCsvChanged)
    Q_PROPERTY(bool shuffleData READ shuffleData WRITE setShuffleData NOTIFY shuffleDataChanged)
    Q_PROPERTY(QString csvPath READ csvPath WRITE setCsvPath NOTIFY csvPathChanged)
    Q_PROPERTY(dnai::utils::IterableQQmlPropertyMap *labels READ labels WRITE setLabels NOTIFY labelsChanged)

public:
    Dataset(QObject *parent = nullptr);
    virtual ~Dataset();

    QString name() const;

    QString path() const;

    int samples() const;

    int training() const;

    int test() const;

    bool autoGenerateCsv() const;

    bool shuffleData() const;

    QString csvPath() const;

    utils::IterableQQmlPropertyMap *labels();

public slots:
    void setName(const QString & name);

    void setPath(const QString & path);

    void setSamples(int samples);

    void setTraining(int training);

    void setTest(int test);

    void setAutoGenerateCsv(bool autoGenerateCsv);

    void setShuffleData(bool shuffleData);

    void setCsvPath(const QString & csvPath);

    void setLabels(utils::IterableQQmlPropertyMap *labels);

    void setData(QQmlPropertyMap * data);

signals:
    void nameChanged(const QString &name);

    void pathChanged(const QString & path);

    void samplesChanged(int samples);

    void trainingChanged(int training);

    void testChanged(int test);

    void autoGenerateCsvChanged(bool autoGenerateCsv);

    void shuffleDataChanged(bool shuffleData);

    void csvPathChanged(const QString & csvPath);

    void labelsChanged(utils::IterableQQmlPropertyMap *labels);

    void dataChanged(QQmlPropertyMap * data);

private:
    QQmlPropertyMap m_data;
    utils::IterableQQmlPropertyMap m_labels;


    // ISerializable interface
public:
    void serialize(QJsonObject &obj) const;

    QQmlPropertyMap * data();

protected:
    void _deserialize(const QJsonObject &obj);
};
}
}
}


#endif // DNAI_MODELS_ML_DATASET_H
