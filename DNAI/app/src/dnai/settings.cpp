#include <QDebug>
#include <QQuickItem>
#include <QGuiApplication>
#include <QJsonDocument>
#include <QJsonObject>

#include "dnai/app.h"
#include "dnai/api/api.h"
#include "dnai/settings.h"

namespace dnai
{
	AppSettings::AppSettings(QObject* parent) : QObject(parent)
    {
//        m_settings.clear();
        m_style = new models::SettingsModel(nullptr);
		const auto theme = m_settings.value("themes/current/theme").toString();
		m_isInit = theme != "";
	}

	AppSettings::~AppSettings()
	{
        delete m_style;
        qDebug() << "~" << "AppSetting";
	}

    void AppSettings::setStyle(models::SettingsModel* m)
	{
		if (m == m_style)
			return;
		m_style = m;
		emit styleChanged(m);
	}

	void AppSettings::loadTheme(const QString&path)
	{
//        if (m_settings.value("themes/current/theme").toString() == path)
//            return;
		m_loadedColors.clear();
		m_loadedNumbers.clear();
        QFile file(m_themesPath[path]);

        if (!file.open(QIODevice::ReadOnly)) {
            return;
        }

		const auto data = file.readAll();
		const auto obj(QJsonDocument::fromJson(data).object());
		const auto pair = findObject(obj, "");
		const auto loadThemeName = "themes/" + path;
		const auto currentThemeName = "themes/current";
		for (auto i = 0; i < pair.first.count(); i++)
		{
			const auto key = pair.first[i];
            const auto value = pair.second[i];
			if (!m_isInit)
			{
				m_settings.setValue(currentThemeName + key, value);
				m_settings.setValue(loadThemeName + key, value);
            }
			if (m_style)
			{
                updateProperty(key.mid(1), value);
			}
		}
		m_settings.setValue("themes/current/theme", path);
	}

	void AppSettings::init()
    {
		const auto theme = m_settings.value("themes/current/theme").toString();
#ifdef Q_OS_MAC
    QString path = QGuiApplication::applicationDirPath() + "/settings/themes";
#else
    QString path = "settings/themes";
#endif
        QDir dir(path);

		const auto list = dir.entryList(QDir::Files);
		for (auto i = list.begin(); i!= list.end(); ++i)
		{
			const auto f = QFileInfo(*i);
			const auto basename = f.baseName();
			m_themes.append(basename);
			m_themesPath[basename] = dir.absoluteFilePath(*i);
			
		}
		m_isInit = theme != "";
		if (!m_isInit && m_themes.count() != 0)
		{
			m_settings.clear();
			loadTheme(m_themes[0]);
		}
		else
			loadTheme(theme);
		static_cast<App *>(App::instance())->registerSettings(this);

        QVariant value = m_settings.value(api::settings_key);
        api::setUser(value.value<api::User>());
	}

	QStringList AppSettings::getThemes() const
    {
		return  m_themes;
	}

	bool AppSettings::isSettingsLoad() const
	{
		return m_isInit;
    }

	void AppSettings::updateProperty(const QString &path, const QVariant &variant)
	{
		const auto pair = getFinalProperty(m_style, path);
        QFontDatabase database;
		QString family = "";

		if (pair.second == "family")
		{
            for (auto i = 0; i < m_families.count(); i++)
            {
                if (database.hasFamily(m_families[i]))
                    family = m_families[i];
            }
            if (family == "")
            {
                const auto id = QFontDatabase::addApplicationFont(variant.toString());
                family = QFontDatabase::applicationFontFamilies(id).at(0);
                m_families.append(family);
            }
            pair.first->setProperty(pair.second.toLatin1().data(), family);
		}
		else
        {
			pair.first->setProperty(pair.second.toLatin1().data(), variant);
		}
	}

    void AppSettings::registerStyle(models::SettingsModel *style)
	{
		m_style = style;
	}

	QPair<QQuickItem*, QString> AppSettings::getFinalProperty(QQuickItem *item, const QString &path) const
	{
		QPair<QQuickItem*, QString> pair;
        auto list = path.split("/");
        QByteArray *qb = new QByteArray(list[0].toLatin1());
        if (list.count() > 1)
        {
            const auto newPath = path.section('/', 1, -1);
            const auto prop = item->property(qb->constData());
            item = qvariant_cast<QQuickItem *>(prop);
            pair = getFinalProperty(item, newPath);
        }
        else
        {
            pair.first = item;
			pair.second = list[0];
            return pair;
        }
		return pair;
	}

	qreal AppSettings::getSettingNumber(const QString &path)
	{
		
		if (m_loadedNumbers.contains(path))
		{

			return m_loadedNumbers[path];
		}
		const auto s = m_settings.value(path).toReal();
		m_loadedNumbers[path] = s;
		return m_loadedNumbers[path];
	}

	QPair<QStringList, QList<QVariant>> AppSettings::findObject(QJsonObject obj, const QString root)
	{
		QPair<QStringList, QList<QVariant>> pair;
		for (auto it = obj.begin(); it != obj.end(); ++it) {
			const auto key = it.key();
			const auto value = it.value();

			if (value.isObject())
			{
				const auto p = findObject(value.toObject(), root + "/" + key);
				pair.first.append(p.first);
				pair.second.append(p.second);
			}
			else
			{
				pair.first.append(root + "/" + key);
				pair.second.append(value.toVariant());
			}
		}
		return pair;
	}
    void AppSettings::setValue(const QString &path, const QVariant &value)
    {
        m_settings.setValue(path, value);
    }

    QVariant AppSettings::getValue(const QString &key)
    {
        return m_settings.value(key);
    }
}
