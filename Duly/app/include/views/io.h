#ifndef IO_H
#define IO_H

#include <QtQuick/qsgnode.h>

#include "baseio.h"
#include "resourcesnode.h"
#include "beziercurve.h"
#include "eventutilities.h"
#include "genericnode.h"
#include "linkablebezieritem.h"

namespace duly_gui
{
	namespace views
	{
		class Io : public LinkableBezierItem, public IScalable
		{
			Q_OBJECT

			Q_PROPERTY(uint nbSegments READ nbSegments WRITE setNbSegments NOTIFY nbSegmentsChanged)
            Q_PROPERTY(IoType type READ type WRITE setType NOTIFY typeChanged)

		public:
			static BaseIo *CurrentHover;

		public:
			explicit Io(QQuickItem *parent = nullptr);
			~Io();

			/**
			* \brief Refresh BackendIo
			*/
			virtual void refreshBackendIo();

			/**
			* \brief return the current BaseIO
			* \return BaseIO*
			*/

			/**
			* \brief Override updatePaintNode and draw a beautifull IO
			* \return
			*/
			virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

			virtual QPointF getCanvasPos() const override;

			virtual GenericNode *getNode() const override;

			//Interface implementation
		public:
			virtual qreal scaleFactor() const override;
			virtual QPointF scalePos() const override;
			virtual QPointF realPos() const override;

		public:
			uint nbSegments() const { return m_nbSegments; }
            IoType type() const { return m_type; }

		public:
			void setNbSegments(uint n);
            void setType(IoType type);

		signals:
			void nbSegmentsChanged(uint n);
            void typeChanged(IoType type);

		protected:
			uint m_nbSegments;

            IoType m_type;

		protected:
			bool m_holdClick;

			virtual void setHover() override;

			virtual void setLink(Link *l) override;

		};
	}
}

#endif // IO_H
