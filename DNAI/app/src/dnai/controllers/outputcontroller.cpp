#include "dnai/controllers/outputcontroller.h"
#include "dnai/controllers/inputcontroller.h"

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
				return BaseIo::connect(linkable, curve);
			}
			return nullptr;
		}
	}
}
