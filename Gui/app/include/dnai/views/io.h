#ifndef IO_H
#define IO_H

#include <QtQuick/qsgnode.h>

#include "dnai/baseio.h"
#include "dnai/eventutilities.h"
#include "beziercurve.h"
#include "genericnode.h"
#include "linkablebezieritem.h"
#include "dnai/interfaces/iscalable.h"

#include "dnai/enums/iotype.h"

namespace dnai
{
	namespace views
	{
        class Io : public LinkableBezierItem, public interfaces::IScalable
		{
			Q_OBJECT

			Q_PROPERTY(uint nbSegments READ nbSegments WRITE setNbSegments NOTIFY nbSegmentsChanged)
            Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
            Q_PROPERTY(bool isLink READ isLink WRITE setIsLink NOTIFY isLinkChanged)
            Q_PROPERTY(bool isHover READ isHover WRITE setIsHover NOTIFY isHoverChanged)

            bool m_isLink;

            bool m_isHover;

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

			virtual GenericNode *getNode() override;

			//Interface implementation
		public:
			virtual qreal scaleFactor() const override;
			virtual QPointF scalePos() const override;
			virtual QPointF realPos() const override;

		public:
			uint nbSegments() const { return m_nbSegments; }
            int type() const { return m_type; }

		public:
			void setNbSegments(uint n);
            void setType(int type);

            bool isLink() const;

            bool isHover() const;

        public slots:
            virtual void setIsLink(bool isLink) override;

            virtual void setIsHover(bool isHover) override;

        signals:
			void nbSegmentsChanged(uint n);
            void typeChanged(int type);
			void linked(const QVariant &name, const QVariant &instructionModel);
			void unlinked(const QVariant &name, const QVariant &instructionModel);

            void isLinkChanged(bool isLink);

            void isHoverChanged(bool isHover);

        protected:
			uint m_nbSegments;

            enums::IoTypeRessouce::IoType m_type;
			GenericNode *m_genericNode{};

		protected:
			bool m_holdClick{};

//			virtual void setHover() override;

//			virtual void setLink(Link *l) override;

		};
	}
}

#endif // IO_H
