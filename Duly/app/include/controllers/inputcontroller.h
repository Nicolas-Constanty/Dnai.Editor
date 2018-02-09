#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include "baseio.h"

namespace duly_gui
{
	namespace controllers
	{
		class InputController : public BaseIo
		{
        public:
            explicit InputController(qmlresources::IoTypeRessouce::IoType t, QQuickItem *parent);

			/**
			* \brief Connect linkable together, create a link, and keep a reference on the visual curve
			* \param linkable
			* \param curve
			* \return Link *
			*/
			Link *connect(ALinkable *linkable, views::BezierCurve *curve) override;
		};

	}
}

#endif // INPUTCONTROLLER_H
