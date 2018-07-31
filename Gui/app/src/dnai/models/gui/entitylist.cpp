#include "dnai/models/gui/entitylist.h"
#include "dnai/models/entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			EntityList::EntityList(QList<models::Entity*>*l) : QAbstractListModel(nullptr)
			{
				m_list = l;
			}

			EntityList::EntityList(const QList<models::Entity*>& l)
			{
				m_list = new QList<models::Entity*>();
				*m_list = l;
			}

			int EntityList::rowCount(const QModelIndex& parent) const
			{
                Q_UNUSED(parent)
				if (!m_list) return 0;
				return m_list->count();
			}

			QVariant EntityList::data(const QModelIndex& index, const int role) const
			{
				if (!index.isValid() || !m_list)
					return QVariant();
				if (role == Name)
					return QVariant::fromValue(m_list->at(index.row())->name());
				else if (role == Type)
					return QVariant::fromValue(dynamic_cast<gui::declarable::Variable*>(m_list->at(index.row())->guiModel())->varType());
				else if (role == Entity)
					return QVariant::fromValue(m_list->at(index.row()));
				return QVariant();
			}

			void EntityList::append(models::Entity *var)
			{
				if (!m_list) return;
				beginInsertRows(QModelIndex(), m_list->length(), m_list->length());
				m_list->append(var);
				endInsertRows();
			}

			void EntityList::moveUp(const int index)
			{
				if (index < 0 || !m_list)
					return;
				const auto start = index % m_list->length();
				const auto end = (start <= 0) ? m_list->length() - 1 : start - 1;
				beginMoveRows(QModelIndex(), start, start, QModelIndex(), start == 0 ? m_list->length() : end);
				m_list->swap(start, end);
				endMoveRows();
			}

			void EntityList::moveDown(const int index)
			{
				if (index < 0 || !m_list)
					return;
				const auto start = index % m_list->length();
				const auto end = (start + 1) % m_list->length();
				beginMoveRows(QModelIndex(), start, start, QModelIndex(), end == 0 ? 0 : end + 1);
				m_list->swap(start, end);
				endMoveRows();
			}

			void EntityList::remove(const QString& name)
			{
				if (!m_list) return;
				auto index = 0;
				for (auto i : *m_list)
				{
					if (i->name() == name)
						break;
					index++;
				}
				beginRemoveRows(QModelIndex(), index, index);
				m_list->removeAt(index);
				endRemoveRows();
			}

			bool EntityList::setData(const QModelIndex& index, const QVariant& value, int role)
			{
				if (!m_list) return false;
				auto result = false;
				if (role == Name)
				{
					m_list->at(index.row())->setName(value.toString());
					result = true;
				}
				else if (role == Type)
                    result = dynamic_cast<models::gui::declarable::Variable*>(m_list->at(index.row())->guiModel())->setVarType(value.toString());
				if (result)
					emit dataChanged(index, index);

				return result;
			}

			bool EntityList::setData(const int index, const QVariant& value, int role)
			{
				return setData(createIndex(index, 0), value, role);
			}

			QHash<int, QByteArray> EntityList::roleNames() const {
				QHash<int, QByteArray> roles;
				roles[Name] = "name";
				roles[Type] = "varType";
				roles[Entity] = "entity";
				return roles;
			}
		}
	}
}
