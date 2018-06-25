#include "dnai/controllers/inputcontroller.h"
#include "dnai/controllers/outputcontroller.h"
#include "dnai/views/beziercurve.h"
#include "dnai/views/output.h"
#include "dnai/link.h"
#include "dnai/views/input.h"
#include "dnai/app.h"

#include <QQmlProperty>

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
					if (!m_links.empty())
					{
						if (auto input = dynamic_cast<dnai::views::Input *>(parent()))
							input->unlinkAll();
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

        Link *InputController::asyncConnect(interfaces::ALinkable *linkable)
        {
            const auto li = dynamic_cast<controllers::OutputController *>(linkable);
            if (li != nullptr && li->getType() == getType())
            {
                auto l = getLink(linkable);
                if (l == nullptr)
                {
                    if (!m_links.empty())
                    {
                        if (auto input = dynamic_cast<dnai::views::Input *>(parent()))
                            input->unlinkAll();
                    }
                    if (const auto input = dynamic_cast<dnai::views::Input *>(parent()))
                    {
                        const auto output = dynamic_cast<dnai::views::Output *>(li->parent());
                        emit input->linked(output->property("name"), output->getNode()->property("instruction_model"));
                    }
                }
            }
            return nullptr;
        }
	}
}
