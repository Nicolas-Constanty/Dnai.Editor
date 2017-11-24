#include "controllers/outputcontroller.h"
#include "controllers/inputcontroller.h"

namespace duly_gui
{
	namespace controllers
	{
        OutputController::OutputController(IoType type, QQuickItem* parent)
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
