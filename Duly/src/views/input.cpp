#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

#include "link.h"
#include "views/output.h"
#include "views/input.h"
#include "views/genericnode.h"
#include "views/dulycanvas.h"
#include "controllers/inputcontroller.h"

namespace duly_gui
{
	namespace views
	{
		Input::Input(QQuickItem *parent) :
			Io(parent)
		{
			m_linkable = new controllers::InputController(m_type, this);
		}

		void Input::refreshBackendIo()
		{
			m_linkable = new controllers::InputController(m_type, this);
		}

		void Input::componentComplete()
		{
			QQuickItem::componentComplete();
			auto n = dynamic_cast<GenericNode *>(parentItem()->parentItem()->parentItem()->parentItem()->parentItem());
			n->inputs().registerItem(this);
		}

		LinkableBezierItem* Input::findLinkableBezierItem(GenericNode* n, const QPointF& p)
		{
			auto qlist = n->outputs().findFocused(p);
			return (qlist.size() != 0) ? dynamic_cast<Io*>(qlist.at(0)) : nullptr;
		}

		void Input::updateLink()
		{
			auto list = m_linkable->links();
			for (auto i = 0; i < list.size(); i++)
			{
				const auto l = list.at(i);
				l->curve()->setRealPosition(getCanvasPos());
				const auto io = dynamic_cast<Output *>(dynamic_cast<BaseIo *>(l->L1 != m_linkable ? l->L1 : l->L2)->parent());
				l->curve()->setP4(io->getCanvasPos());
			}
		}

		void Input::afterRealease(Link *l)
		{
			if (l == nullptr)
				unlinkAll();
		}
	}
}
