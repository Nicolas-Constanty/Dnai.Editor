#ifndef MODEL_COMMON_H
#define MODEL_COMMON_H

#include <QObject>
#include <QString>

#include "dnai/models/imodel.h"

namespace dnai {
enum ModelTypes {
    Common = -1,
    Context,
    Class,
    Function,
    Variable,
    Input,
    Output
};
namespace models {
class Common: public QObject, virtual public IModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(int listIndex READ listIndex WRITE setListIndex NOTIFY listIndexChanged)
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
public:
    Common(QString const &, QString const &, QString const &, int index, int listindex, QObject * = nullptr);
    virtual ~Common();

    QString uid() const;
    void setUid(const QString &uid);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    int index() const { return m_index; }
    void setIndex(int i);

    int listIndex() const { return m_listindex; }
    void setListIndex(int i);

    int type() const { return m_type; }
    void setType(int t);

    Q_INVOKABLE void select(bool s);
    Q_INVOKABLE bool isSelect() const { return m_select; }

private:
    QString m_uid;
    QString m_name;
    QString m_description;
    int m_index;
    int m_listindex;
    bool m_select;

signals:
    void nameChanged();
    void descriptionChanged();
    void indexChanged(int i);
    void listIndexChanged(int i);
    void typeChanged(int t);

    // IModel interface
public:
    virtual void serialize(QJsonObject &) const;
    virtual void declare() const;

    // IClone interface
private:
    IClone *clone() const;

protected:
    int m_type;
};
}
}

#endif // MODEL_COMMON_H
