#include "controllers/inputcontroller.h"
#include "controllers/outputcontroller.h"
#include "views/beziercurve.h"
#include "views/output.h"
#include "link.h"

namespace duly_gui
{
	namespace controllers
	{
        InputController::InputController(qmlresources::IoTypeRessouce::IoType t, QQuickItem *parent)
			: BaseIo(t, parent)
		{
		}

		Link *InputController::connect(ALinkable *linkable, views::BezierCurve *curve)
		{
            const auto li = dynamic_cast<controllers::OutputController *>(linkable);
			if (li != nullptr && li->getType() == getType())
			{
				auto l = getLink(linkable);
				if (l == nullptr)
				{
					if (m_links.size() > 0)
					{
						unlinkAll();
					}
					l = new Link(this, linkable);
					l->setCurve(curve);
					return l;
				}
				//TODO INSERT DEBUG "Link already exist"
				return nullptr;
			}
			return nullptr;
		}
	}
}
