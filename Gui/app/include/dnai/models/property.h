#ifndef DNAI_MODELS_PROPERTY_H
#define DNAI_MODELS_PROPERTY_H

#include <QAbstractTableModel>

namespace dnai {
namespace models {

	class Entity;

class Property : public QAbstractTableModel
{
	Q_OBJECT
public:
	enum ROLES
	{
		NAME = Qt::UserRole + 1,
		VALUE,
		ITEM
	};
	explicit Property(const QList<QPair<QObject *, QString>> &editableprops);
	int rowCount(const QModelIndex& parent) const override;
	int columnCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	void addProperty(QObject *obj, const QString &pname);
	Q_INVOKABLE void setProp(int row, const QVariant& value);
	Q_INVOKABLE QString getPropName(int row) const;
	Q_INVOKABLE dnai::models::Entity *model() const;

private:
	QHash<int, QByteArray> roleNames() const override;
	QList<QPair<QObject *, QString>> m_editableIndex;
	QObject *m_obj;
};

}
}

#endif // DNAI_MODELS_PROPERTY_H
