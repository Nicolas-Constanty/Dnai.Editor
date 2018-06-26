#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

#include "dnai/link.h"
#include "dnai/views/output.h"
#include "dnai/views/input.h"
#include "dnai/views/genericnode.h"
#include "dnai/controllers/inputcontroller.h"

namespace dnai
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
            GenericNode *n = nullptr;
			auto parent = parentItem();
            while (n == nullptr && parent != nullptr)
            {
                n = dynamic_cast<GenericNode *>(parent);
                if (n)
                    n->inputs().registerItem(this);
                parent = parent->parentItem();
            }
		}

		LinkableBezierItem* Input::findLinkableBezierItem(GenericNode* n, const QPointF& p)
		{
			auto qlist = n->outputs().findFocused(p);
			return (!qlist.empty()) ? dynamic_cast<Io*>(qlist.at(0)) : nullptr;
		}

		void Input::updateLink()
		{
			auto list = m_linkable->links();
			for (auto l : list)
			{
				l->curve()->setRealPosition(getCanvasPos());
				const auto io = dynamic_cast<Output *>(dynamic_cast<BaseIo *>(l->L1 != m_linkable ? l->L1 : l->L2)->parent());
                l->curve()->setP4(io->getCanvasPos());
			}
		}

		void Input::unlinkAll()
        {
            LinkableBezierItem::unlinkAll();
        }

        void Input::asyncUnlinkAll()
        {
            for (auto link : m_linkable->links())
            {
                const auto lb = dynamic_cast<Output *>(dynamic_cast<BaseLinkable *>(link->L1 == m_linkable ? link->L2 : link->L1)->parent());
                emit unlinked(lb->property("name"), lb->getNode()->property("instruction_model"));
            }
        }

		void Input::afterRealease(Link *l)
		{
			if (l == nullptr)
			{
				unlinkAll();
			}
		}
	}
}
