#ifndef MODEL_USER_H
#define MODEL_USER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

namespace dnai {
namespace models {
class User: public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString profile_url READ profile_url WRITE setProfile_url NOTIFY profile_urlChanged)
    Q_PROPERTY(QJsonArray files READ files WRITE setFiles NOTIFY filesChanged)
    Q_PROPERTY(QJsonObject currentFileData READ currentFileData WRITE setCurrentFileData NOTIFY currentFileDataChanged)
public:
    User();
    ~User();

    QString name() const;
    void setName(const QString &name);

    QString profile_url() const;
    void setProfile_url(const QString &profile_url);

    QJsonArray files() const;
    void setFiles(const QJsonArray &files);

    QJsonObject currentFileData() const;
    void setCurrentFileData(const QJsonObject &currentFileData);

private:
    QString m_name;
    QString m_profile_url;
    QJsonArray m_files;
    QJsonObject m_currentFileData;

signals:
    void nameChanged(QString &);
    void profile_urlChanged(QString &);
    void filesChanged(QJsonArray &);
    void currentFileDataChanged(QJsonObject &);
};
}
}

#endif // MODEL_USER_H
