#ifndef DNAI_SOLUTION_H
#define DNAI_SOLUTION_H

#include "interfaces/isolution.h"
#include "interfaces/iserializable.h"
#include <QAbstractListModel>

namespace dnai
{
	class Solution : public QAbstractListModel, public interfaces::ISolution, public interfaces::ASerializable<Solution>
	{
		Q_OBJECT
	public:
		enum ROLES
		{
			ITEM = Qt::UserRole + 1,
			NAME,
			DESCRIPTION
		};

		Solution();
		void save() override;
		void load(const QString& path) override;
		void close() override;
		const QString& version() const override;
		void setVersion(const QString& version) override;
		const QString& name() const override;
		void setName(const QString& name) override;
		const QString& description() const override;
		void setDescription(const QString& desc) override;
		const QJsonObject& jsonData() const override;
		const QList<IProject*>& projects() const override;
		void addProject(IProject*) override;
		IProject *seletedProject() const override;
		bool selectProject(IProject*) override;
		void serialize(QJsonObject& obj) const override;
		const QString& fileName() const override;
		void setFileName(const QString& name) override;
		Q_INVOKABLE int getRoleKey(QString rolename) const;

	protected:
		void _deserialize(const QJsonObject& obj) override;

	public:
		int rowCount(const QModelIndex& parent) const override;
		QVariant data(const QModelIndex& index, int role) const override;

	private:
		IProject* m_selectedProject;
		QList<IProject*> m_projects;
		QJsonObject m_data;
		QString m_description;
		QString m_name;
		QString m_version;
		QFile *m_file;
		QString m_filename;
		virtual QHash<int, QByteArray> roleNames() const override;

	};
}

#endif //DNAI_SOLUTION_H