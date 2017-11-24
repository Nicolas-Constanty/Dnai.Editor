#ifndef DULYSETTINGS_H
#define DULYSETTINGS_H

#include <QSettings>
#include <QFontDatabase>
#include <QColor>
#include <qquickitem.h>
#include "dulysettingsmodel.h"


namespace duly_gui {
class DulySettings : public QObject
{
    Q_OBJECT

public:
	Q_PROPERTY(DulySettingsModel *style READ style WRITE setStyle NOTIFY styleChanged)
	explicit DulySettings(QObject *parent = nullptr);
    virtual ~DulySettings();

    static const QString settings_extension;

signals:
	void styleChanged(DulySettingsModel *m);

private:
    QSettings m_settings;
	QStringList m_themes;
	QStringList m_families;
	QMap<QString, QString> m_themesPath;
	QMap<QString, QColor> m_loadedColors;
	QMap<QString, QObject *> m_loadedObjects;
	QMap<QString, qreal> m_loadedNumbers;
	DulySettingsModel *m_style;

public:
	DulySettingsModel *style() const { return m_style; }
	void setStyle(DulySettingsModel *m);
    Q_INVOKABLE void loadTheme(const QString &);
    Q_INVOKABLE void init();
	Q_INVOKABLE QStringList getThemes() const;
	Q_INVOKABLE bool isSettingsLoad() const;
	Q_INVOKABLE void updateProperty(const QString& path, const QVariant &variant);
	Q_INVOKABLE void registerStyle(DulySettingsModel *);
	QPair<QQuickItem*, QString> getFinalProperty(QQuickItem* item, const QString& path) const;

	Q_INVOKABLE qreal getSettingNumber(const QString &path);

private:
	static QPair<QStringList, QList<QVariant>> findObject(QJsonObject obj, const QString root);
	bool m_isInit;
};
}

#endif // DULYSETTINGS_H
