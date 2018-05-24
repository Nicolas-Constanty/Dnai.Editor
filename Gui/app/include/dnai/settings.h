#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>
#include <qquickitem.h>

namespace dnai {
class AppSettings : public QObject
{
    Q_OBJECT

public:
	Q_PROPERTY(QVariantMap theme READ theme WRITE setTheme NOTIFY themeChanged)
    explicit AppSettings(QObject *parent = nullptr);
    ~AppSettings();

    static const QString settings_extension;
signals:
	void themeChanged(const QVariantMap &theme);
private:
    QSettings m_settings;
    QSettings m_apiSettings;
    QStringList m_themes;
    QStringList m_families;
    QMap<QString, QString> m_themesPath;
    QMap<QString, QColor> m_loadedColors;
    QMap<QString, QObject *> m_loadedObjects;
    QMap<QString, qreal> m_loadedNumbers;
	QVariantMap m_theme;

public:
    QString const &currentVersionAPI() const  { return m_currentVersionAPI; }
	void loadFromJson(const QString &);
	const QVariantMap &theme() const;
	void setTheme(const QVariantMap &map);
	Q_INVOKABLE void loadTheme(const QString &);
	Q_INVOKABLE void init();
	Q_INVOKABLE QStringList getThemes() const;
	Q_INVOKABLE bool isSettingsLoad() const;
	Q_INVOKABLE bool isNewVersionAvailable() const;
	Q_INVOKABLE QString currentTheme() const;
	Q_INVOKABLE QString getEntityColor(int identifier) const;
	Q_INVOKABLE QString getEntityIcon(int identifier) const;

	Q_INVOKABLE qreal getSettingNumber(const QString &path);
	void setVersion(QString const &);
	void setAPIVersion(QString const &);
	void onNotifyVersionChanged();

	QVariant getValue(const QString &key);
	QVariant getValue(const QString &key, QVariant defaultValue);
	void setValue(const QString &path, const QVariant &value);
	void setAPIValue(const QString &path, const QVariant &value);

private:
	bool m_isInit;
	QString m_currentVersionAPI;
};
}

#endif // APPSETTINGS_H
