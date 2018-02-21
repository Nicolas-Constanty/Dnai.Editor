#ifndef LISTNODE_H
#define LISTNODE_H

#include <QAbstractListModel>

namespace dnai
{
	namespace models
	{
		class ListNode : public QAbstractListModel
		{
			Q_OBJECT
				enum Roles {
				ITEM = Qt::UserRole + 1,
				NAME,
                INSTRUCTION_ID,
                MENU_NAME
			};
		public:
			explicit ListNode(QObject *parent = nullptr);
			ListNode(const ListNode &other, QObject *parent = nullptr);
			virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
			virtual QVariant data(const QModelIndex& index, int role) const override;
			void operator<<(QObject *value);
			ListNode &operator=(const ListNode &other);
			QObject *operator[](const int i) const;
		protected:
			virtual QHash<int, QByteArray> roleNames() const override;

		private:
			QList<QObject *> m_nodes;
		};
	}
}

#endif // LISTNODE_H
