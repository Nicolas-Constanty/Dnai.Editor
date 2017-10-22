#ifndef LINK_H
#define LINK_H

#include "ilinkable.h"

namespace duly_gui
{
	class Link
	{
	public:

		ALinkable *L1;
		ALinkable *L2;

	public:
		Link(ALinkable *l1, ALinkable *l2);
		~Link();
		/**
		* \brief Assign the visual object to the link
		* \param curve
		*/
        void setCurve(views::BezierCurve *curve) { m_bezierCurve = curve; }
        views::BezierCurve *curve() const { return m_bezierCurve; }
		void ClearLink();

	private:
		Link();
        views::BezierCurve *m_bezierCurve;
	};
}

#endif // LINK_H
