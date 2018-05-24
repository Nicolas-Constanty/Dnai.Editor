#include <QDebug>

#include "dnai/app.h"
#include "dnai/api/api.h"
#include "dnai/settings.h"
#include "dnai/exceptions/exceptionmanager.h"
#include "dnai/exceptions/guiexception.h"

namespace dnai
{
    AppSettings::AppSettings(QObject* parent) : QObject(parent),
	 m_apiSettings("apiSettings", QSettings::IniFormat)
    {
#ifdef QT_DEBUG
        m_settings.clear();
#endif
		const auto theme = m_settings.value("themes/selected").toString();
        m_isInit = theme != "";
	    dynamic_cast<App *>(App::instance())->registerSettings(this);
	}

	AppSettings::~AppSettings()
	{
        qDebug() << "~" << "AppSetting";
	}
	
	void AppSettings::init()
	{
		const auto defaultPath = m_settings.value("themes/selected").toString();

		const auto path = QGuiApplication::applicationDirPath() + "/settings/themes";
		QDir dir(path);

		const auto themePaths = dir.entryList(QDir::Files);
		for (const auto& themePath : themePaths)
		{
			const auto f = QFileInfo(themePath);
			const auto basename = f.baseName();
			m_themes.append(basename);
			m_themesPath[basename] = dir.absoluteFilePath(themePath);
			const auto settingPath = "themes/" + basename;
			if (m_settings.value(settingPath).toString().isEmpty())
			{
				loadFromJson(m_themesPath[basename]);
				m_settings.setValue(settingPath, m_theme);
			}
		}
		m_isInit = defaultPath != "";
		if (!m_isInit && m_themes.count() != 0)
		{
			loadFromJson(m_themesPath[m_themes[0]]);
		}
		else {
			loadFromJson(m_themesPath[defaultPath]);
		}

		QVariant value = m_apiSettings.value(api::settings_key);
		//  qDebug() << value.value<api::User>().id;
		api::setUser(value.value<api::User>());
		qDebug() << "API ID: " << api::getId();
	}

	void AppSettings::loadFromJson(const QString &path)
    {
		auto file = new QFile(path);

		if (!file->open(QIODevice::ReadOnly)) {
			qWarning("Couldn't open file.");
			return;
		}

		const QByteArray data = file->readAll();

		try {
			const QJsonObject obj(QJsonDocument::fromJson(data).object());
			m_theme = obj.toVariantMap();
		}
		catch (std::exception &e) {
			Q_UNUSED(e)
			exceptions::ExceptionManager::throwException(exceptions::GuiExeption("Error : Corrupted file"));
			qWarning("Couldn't parse file.");
		}
		file->close();
    }

	const QVariantMap& AppSettings::theme() const
	{
		return m_theme;
	}

	void AppSettings::setTheme(const QVariantMap& map)
	{
		m_theme = map;
		emit themeChanged(map);
	}

	QString AppSettings::currentTheme() const
	{
        return m_settings.value("themes/selected").toString();
    }

	QString AppSettings::getEntityColor(int identifier) const
	{
		const auto id = static_cast<core::ENTITY>(identifier);
		const auto json = QJsonObject::fromVariantMap(m_theme);
		switch (id)
		{
		case ENTITY::UNDEFINED: return "";
		case ENTITY::CONTEXT: return json["entities"].toObject()["context"].toObject()["color"].toString();
		case ENTITY::VARIABLE: return json["entities"].toObject()["variable"].toObject()["color"].toString();
		case ENTITY::FUNCTION: return json["entities"].toObject()["function"].toObject()["color"].toString();
		case ENTITY::DATA_TYPE: return json["entities"].toObject()["data_type"].toObject()["color"].toString();
		case ENTITY::ENUM_TYPE: return json["entities"].toObject()["enum_type"].toObject()["color"].toString();
		case ENTITY::OBJECT_TYPE: return json["entities"].toObject()["object_type"].toObject()["color"].toString();
		case ENTITY::LIST_TYPE: return json["entities"].toObject()["list_type"].toObject()["color"].toString();
		default: ;
		}
		return "";
	}

	QString AppSettings::getEntityIcon(int identifier) const
	{
		const auto id = static_cast<core::ENTITY>(identifier);
		const auto json = QJsonObject::fromVariantMap(m_theme);
		switch (id)
		{
		case ENTITY::UNDEFINED: return "";
		case ENTITY::CONTEXT: return json["entities"].toObject()["context"].toObject()["icon"].toString();
		case ENTITY::VARIABLE: return json["entities"].toObject()["variable"].toObject()["icon"].toString();
		case ENTITY::FUNCTION: return json["entities"].toObject()["function"].toObject()["icon"].toString();
		case ENTITY::DATA_TYPE: return json["entities"].toObject()["data_type"].toObject()["icon"].toString();
		case ENTITY::ENUM_TYPE: return json["entities"].toObject()["enum_type"].toObject()["icon"].toString();
		case ENTITY::OBJECT_TYPE: return json["entities"].toObject()["object_type"].toObject()["icon"].toString();
		case ENTITY::LIST_TYPE: return json["entities"].toObject()["list_type"].toObject()["icon"].toString();
		default:;
		}
		return "";
	}

	void AppSettings::loadTheme(const QString&path)
	{
		loadFromJson(m_themesPath[path]);
		m_settings.setValue("themes/selected", path);
		emit themeChanged(m_theme);
	}

	QStringList AppSettings::getThemes() const
    {
		return  m_themes;
	}

	bool AppSettings::isSettingsLoad() const
	{
		return m_isInit;
    }

    bool AppSettings::isNewVersionAvailable() const {
        QStringList currentVersionList = Editor::instance().version().split('.');
        QStringList currentVersionAPIList = m_currentVersionAPI.split('.');
        int i = 0;

        while (i < currentVersionAPIList.length() && i < currentVersionList.length()) {
            if (currentVersionAPIList[i].toInt() > currentVersionList[i].toInt()) {
                return true;
            }
            ++i;
        }
        return false;
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

    void AppSettings::setVersion(QString const &ver) {
        Editor::instance().setVersion(ver);
    }

    void AppSettings::setAPIVersion(QString const &ver) {
        m_currentVersionAPI = ver;
    }

    void AppSettings::onNotifyVersionChanged() {
        if (isNewVersionAvailable()) {
            Editor::instance().notifyInformation("Switch to new version " + m_currentVersionAPI, [this]() {
                App::currentInstance()->processManager()->launchUpdater(Editor::instance().version(), m_currentVersionAPI);
            });
            /*Editor::instance().notifyError("Switch to new version " + m_currentVersionAPI, [this]() {
                App::currentInstance()->processManager()->launchUpdater(Editor::instance().version(), m_currentVersionAPI);
            });
            Editor::instance().notifySuccess("Switch to new version " + m_currentVersionAPI, [this]() {
                App::currentInstance()->processManager()->launchUpdater(Editor::instance().version(), m_currentVersionAPI);
            });
            Editor::instance().notifyWarning("Switch to new version " + m_currentVersionAPI, [this]() {
                App::currentInstance()->processManager()->launchUpdater(Editor::instance().version(), m_currentVersionAPI);
            });*/
        }
    }

    void AppSettings::setValue(const QString &path, const QVariant &value)
    {
        m_settings.setValue(path, value);
    }

    void AppSettings::setAPIValue(const QString &path, const QVariant &value) {
        m_apiSettings.setValue(path, value);
    }

    QVariant AppSettings::getValue(const QString &key)
    {
        return m_settings.value(key);
    }

    QVariant AppSettings::getValue(const QString &key, QVariant defaultValue)
    {
        return m_settings.value(key, defaultValue);
    }
}
