#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>
#include <QVariant>
#include "imodel.h"

namespace dnai {
namespace models {
class Property : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
public:
	explicit Property(QObject *parent = nullptr);
	explicit Property(QObject * model, QObject *parent = nullptr);
	explicit Property(const QString &m_name, const QVariant &m_value, QObject * model, QObject *parent = nullptr);

    virtual ~Property();

signals:
    void nameChanged(const QString &name);
    void valueChanged(const QVariant &value);

public:
    const QString &name() const;
    void setName(const QString &name);
    const QVariant &value() const;
    void setValue(const QVariant &value);

private:
    QString m_name;
    QVariant m_value;
	QObject *m_model;
};
}
}

#endif // PROPERTY_H
