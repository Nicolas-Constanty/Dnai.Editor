#ifndef LINK_H
#define LINK_H

#include "dnai/interfaces/ilinkable.h"

namespace dnai
{
	class Link
	{
	public:
        interfaces::ALinkable *L1;
        interfaces::ALinkable *L2;

	public:
        Link(interfaces::ALinkable *l1, interfaces::ALinkable *l2);
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
