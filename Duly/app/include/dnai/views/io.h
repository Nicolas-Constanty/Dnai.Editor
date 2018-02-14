#ifndef IO_H
#define IO_H

#include <QtQuick/qsgnode.h>

#include "dnai/baseio.h"
#include "dnai/eventutilities.h"
#include "beziercurve.h"
#include "genericnode.h"
#include "linkablebezieritem.h"
#include "iscalable.h"

#include "dnai/qmlresources/iotype.h"

namespace dnai
{
	namespace views
	{
		class Io : public LinkableBezierItem, public IScalable
		{
			Q_OBJECT

			Q_PROPERTY(uint nbSegments READ nbSegments WRITE setNbSegments NOTIFY nbSegmentsChanged)
            Q_PROPERTY(dnai::qmlresources::IoTypeRessouce::IoType type READ type WRITE setType NOTIFY typeChanged)

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
            qmlresources::IoTypeRessouce::IoType type() const { return m_type; }

		public:
			void setNbSegments(uint n);
            void setType(qmlresources::IoTypeRessouce::IoType type);

		signals:
			void nbSegmentsChanged(uint n);
            void typeChanged(qmlresources::IoTypeRessouce::IoType type);

		protected:
			uint m_nbSegments;

            qmlresources::IoTypeRessouce::IoType m_type;

		protected:
			bool m_holdClick;

			virtual void setHover() override;

			virtual void setLink(Link *l) override;

		};
	}
}

#endif // IO_H
