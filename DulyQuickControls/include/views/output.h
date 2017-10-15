#ifndef OUTPUT_H
#define OUTPUT_H

#include "io.h"

namespace duly_gui
{
	namespace views
	{
		class Output : public Io
		{

		public:
			explicit Output(QQuickItem *parent = nullptr);

			/**
			* \brief Refresh BackendIO for Output
			*/
			virtual void refreshBackendIo() override;

			/**
			* \brief Override componentComplete, and init some values
			*/
			virtual void componentComplete() override;

			/**
			* \brief Override findIo, return the IO under the point p of the Node n
			* \param n
			* \param p
			* \return Io *
			*/
			virtual LinkableBezierItem *findLinkableBezierItem(GenericNode* n, const QPointF& p) override;

			virtual void updateLink() override;

		private:

		};
	}
}

#endif // OUTPUT_H
