#include <QJsonDocument>

#include "dnai/solution.h"
#include "dnai/editor.h"
#include "dnai/exceptions/guiexception.h"
#include "dnai/project.h"
#include "dnai/exceptions/exceptionmanager.h"

namespace dnai
{
	Solution::Solution(): m_selectedProject(nullptr), m_file(nullptr)
    {
    }

    Solution::Solution(const QString filename)
    {
        m_filename = filename;
        m_file = new QFile(QUrl(m_filename).toLocalFile());
    }

    Solution::~Solution()
    {
        while (!m_projects.isEmpty()) {
            delete m_projects.takeFirst();
        }
        qDebug() << "~ Solution";
    }

	void Solution::save()
	{
		QJsonObject obj;
		serialize(obj);

		for (auto p : m_projects)
			p->save();
		m_file->open(QIODevice::WriteOnly);
        m_file->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
		m_file->close();
	}

    QString Solution::path() const {
        QFileInfo fi(m_file->fileName());
        return fi.absolutePath();
    }

	void Solution::load(const QString& path)
	{
		m_filename = path;

        qDebug() << "File url: " << m_filename;
        qDebug() << "File path: " << QUrl(m_filename).toLocalFile();

		m_file = new QFile(QUrl(m_filename).toLocalFile());

        if (!m_file->open(QIODevice::ReadOnly)) {
            qWarning() << "Couldn't open file: " << m_file->errorString();
			return;
		}

		const QByteArray data = m_file->readAll();

		try {
			const QJsonObject obj(QJsonDocument::fromJson(data).object());
			_deserialize(obj);
			m_data = obj;
			if (!m_projects.isEmpty())
				m_selectedProject = m_projects[0];
		}
		catch (std::exception &e) {
			Q_UNUSED(e)
            exceptions::ExceptionManager::throwException(exceptions::GuiExeption("Error : Corrupted Solution file"));
            qWarning("Couldn't parse file.");
		}
		m_file->close();
	}

	void Solution::close()
	{
		for (const auto proj : m_projects)
			proj->close();
	}

	const QString& Solution::version() const
	{
		return m_version;
	}

	void Solution::setVersion(const QString& version)
	{
		if (m_version == version)
			return;
		m_version = version;
	}

	const QString& Solution::name() const
	{
		return m_name;
	}

	void Solution::setName(const QString& name)
	{
		if (name == m_name)
			return;
		m_name = name;
	}

	const QString& Solution::description() const
	{
		return m_description;
	}

	void Solution::setDescription(const QString& desc)
	{
		if (m_description == desc)
			return;
		m_description = desc;
	}

	const QJsonObject& Solution::jsonData() const
	{
		return m_data;
	}

	const QList<interfaces::IProject*>& Solution::projects() const
	{
		return m_projects;
	}

	void Solution::addProject(IProject *proj)
	{
        beginInsertRows(QModelIndex(), m_projects.length(), m_projects.length());
		if (!m_projects.contains(proj))
			m_projects.append(proj);
        endInsertRows();
	}

	interfaces::IProject *Solution::seletedProject() const
	{
		return m_selectedProject;
	}

	bool Solution::selectProject(IProject *proj)
	{
		if (proj == m_selectedProject)
			return false;
		m_selectedProject = proj;
		return true;
	}

	void Solution::serialize(QJsonObject& obj) const
	{
		QJsonArray arr;
		for (auto p : m_projects)
		{
			const QStringRef subString(&m_filename, 0, m_filename.lastIndexOf("/") + 1);
			auto s = p->fileName();
			const QJsonValue v = s.replace(subString.toString(), "");
			qDebug() << v.toString();
			arr.append(v);
		}
		obj["name"] = name();
		obj["description"] = description();
		obj["projects"] = arr;
        obj["version"] = Editor::instance().version();
	}

	const QString& Solution::fileName() const
	{
		return m_filename;
	}

	void Solution::setFileName(const QString& name)
	{
		if (m_filename == name)
			return;
		m_filename = name;
	}


	int Solution::getRoleKey(QString rolename) const
	{
		return roleNames().key(rolename.toLatin1());
	}

	bool Solution::selectProject(Project* p)
	{
		return selectProject(static_cast<IProject*>(p));
	}

	Project* Solution::selectedProject() const
	{
		return dynamic_cast<Project*>(m_selectedProject);
	}

	void Solution::_deserialize(const QJsonObject& obj)
	{
		if (obj["version"].toString() != Editor::instance().version())
			qWarning() << "Warning this solution file (" << m_filename << ") wasn't created with the same editor's version (" << obj["version"].toString() << "!= current" << Editor::instance().version() << ")";

		m_name = obj["name"].toString();
		m_description = obj["description"].toString();
		for (const auto projfilename : obj["projects"].toArray())
		{
			const QStringRef subString(&m_filename, 0, m_filename.lastIndexOf("/"));
			const auto proj = new Project();
			proj->load(subString + "/" + projfilename.toString());
			m_projects.append(proj);
			qDebug() << "Successfully load the project :" << subString + "/" + projfilename.toString();
			if (m_selectedProject == nullptr)
				selectProject(proj);
		}
	}

	int Solution::rowCount(const QModelIndex& parent) const
	{
        Q_UNUSED(parent)
		return m_projects.count();
	}

	QVariant Solution::data(const QModelIndex& index, int role) const
	{
		if (!index.isValid())
			return QVariant();
		const auto proj = dynamic_cast<Project *>(m_projects.at(index.row()));
		if (proj)
		{
			switch (role)
			{
			case ITEM:
				return QVariant::fromValue(proj);
			case NAME:
			case Qt::DisplayRole:
				return QVariant::fromValue(proj->name());
			case DESCRIPTION:
				return QVariant::fromValue(proj->description());
			default:
				return QVariant();
			}
		}
        return QVariant();
    }

	QHash<int, QByteArray> Solution::roleNames() const
	{
		QHash<int, QByteArray> roles;
		roles[ROLES::ITEM] = "item";
		roles[ROLES::NAME] = "name";
		roles[ROLES::DESCRIPTION] = "description";
		return roles;
	}
}
