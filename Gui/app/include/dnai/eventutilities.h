#ifndef EVENTUTILITIES_H
#define EVENTUTILITIES_H

#include <QInputEvent>

namespace dnai
{
	class EventUtilities
	{
	public:
		EventUtilities();

		/**
		* \brief Checl if a Mouse is hover RectF
		* \param r
		* \param e
		* \return
		*/
		static bool isHoverRectF(const QRectF &r, QMouseEvent *e);

		/**
		* \brief Checl if a Mouse is hover Rect
		* \param r
		* \param e
		* \return
		*/
		static bool isHoverRect(const QRect &r, QMouseEvent *e);

		/**
		* \brief Checl if a Mouse is hover Circle of radius ra
		* \param ra
		* \param e
		* \return
		*/
		static bool isHoverCircle(const qreal ra, QMouseEvent *e);

	};
}

#endif // EVENTUTILITIES_H
