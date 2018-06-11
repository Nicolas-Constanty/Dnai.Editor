#include "dnai/controllers/inputcontroller.h"
#include "dnai/controllers/outputcontroller.h"
#include "dnai/views/beziercurve.h"
#include "dnai/views/output.h"
#include "dnai/link.h"
#include "dnai/views/input.h"

namespace dnai
{
	namespace controllers
	{
        InputController::InputController(enums::IoTypeRessouce::IoType t, QQuickItem *parent)
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
					if (const auto input = dynamic_cast<dnai::views::Input *>(parent()))
						emit input->linked(l);
					return l;
				}
				//TODO INSERT DEBUG "Link already exist"
				return nullptr;
			}
			return nullptr;
		}
	}
}
