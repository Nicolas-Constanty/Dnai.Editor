#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include <QtQuick/qsgnode.h>
#include "customshape.h"

namespace duly_gui
{
	namespace views
	{
		class RoundedRectangle : public CustomShape
		{
			Q_OBJECT

				Q_PROPERTY(bool topLeft READ topLeft WRITE setTopLeft NOTIFY topLeftChanged)
				Q_PROPERTY(bool topRight READ topRight WRITE setTopRight NOTIFY topRightChanged)
				Q_PROPERTY(bool bottomLeft READ bottomLeft WRITE setBottomLeft NOTIFY bottomLeftChanged)
				Q_PROPERTY(bool bottomRight READ bottomRight WRITE setBottomRight NOTIFY bottomRightChanged)

				Q_PROPERTY(uint roundedSegments READ roundedSegments WRITE setRoundedSegments NOTIFY roundedSegmentsChanged)

		public:
			RoundedRectangle(QQuickItem *parent = nullptr);

			/**
			* \brief Override updatePaintNode and draw a magnificient rounded rectangle
			* \return QSGNode *
			*/
			virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

		public:
			bool topLeft() const { return m_topLeft; }
			bool topRight() const { return m_topRight; }
			bool bottomLeft() const { return m_bottomLeft; }
			bool bottomRight() const { return m_bottomRight; }

			int roundedSegments() const { return m_nbSegments; }

		public:
			void setTopLeft(bool value);
			void setTopRight(bool value);
			void setBottomLeft(bool value);
			void setBottomRight(bool value);

			void setRoundedSegments(uint segments);

		signals:
			void topLeftChanged(bool value);
			void topRightChanged(bool value);
			void bottomLeftChanged(bool value);
			void bottomRightChanged(bool value);

			void roundedSegmentsChanged(uint segments);

		private:
			bool m_topLeft;
			bool m_topRight;
			bool m_bottomLeft;
			bool m_bottomRight;

			uint m_nbSegments;

		private:
			/**
			* \brief return the number of rounded corner
			* \return int
			*/
			int getNumberRoundedCorner() const;

		};
	}
}


#endif // ROUNDEDRECTANGLE_H
