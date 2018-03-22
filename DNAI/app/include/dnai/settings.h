#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>
#include <QFontDatabase>
#include <QColor>
#include <qquickitem.h>
#include "models/settingsmodel.h"

namespace dnai {
class AppSettings : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(dnai::models::SettingsModel *style READ style WRITE setStyle NOTIFY styleChanged)
    explicit AppSettings(QObject *parent = nullptr);
    ~AppSettings();

    static const QString settings_extension;

signals:
    void styleChanged(models::SettingsModel *m);

private:
    QSettings m_settings;
    QStringList m_themes;
    QStringList m_families;
    QMap<QString, QString> m_themesPath;
    QMap<QString, QColor> m_loadedColors;
    QMap<QString, QObject *> m_loadedObjects;
    QMap<QString, qreal> m_loadedNumbers;
    models::SettingsModel *m_style;

public:
    models::SettingsModel *style() const { return m_style; }
    void setStyle(models::SettingsModel *m);
    Q_INVOKABLE void loadTheme(const QString &);
    Q_INVOKABLE void init();
    Q_INVOKABLE QStringList getThemes() const;
    Q_INVOKABLE bool isSettingsLoad() const;
    Q_INVOKABLE void updateProperty(const QString& path, const QVariant &variant);
    Q_INVOKABLE void registerStyle(models::SettingsModel *);
    QPair<QQuickItem*, QString> getFinalProperty(QQuickItem* item, const QString& path) const;

    Q_INVOKABLE qreal getSettingNumber(const QString &path);

    QVariant getValue(const QString &key);
    void setValue(const QString &path, const QVariant &value);
private:
    static QPair<QStringList, QList<QVariant>> findObject(QJsonObject obj, const QString root);
    bool m_isInit;
};
}

#endif // APPSETTINGS_H
