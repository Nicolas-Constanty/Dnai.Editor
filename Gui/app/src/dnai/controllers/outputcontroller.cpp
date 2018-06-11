#include "dnai/controllers/outputcontroller.h"
#include "dnai/controllers/inputcontroller.h"
#include "dnai/views/output.h"

namespace dnai
{
	namespace controllers
	{
        OutputController::OutputController(enums::IoTypeRessouce::IoType type, QQuickItem* parent)
			: BaseIo(type, parent)
		{
		}

		Link *OutputController::connect(ALinkable *linkable, views::BezierCurve *curve)
		{
			const auto li = dynamic_cast<InputController *>(linkable);

			if (li != nullptr && li->getType() == getType())
			{
				li->unlinkAll();
				const auto link = BaseIo::connect(linkable, curve);
				if (const auto output = dynamic_cast<dnai::views::Output *>(parent()))
					emit output->linked(link);
				return link;
			}
			return nullptr;
		}
	}
}
