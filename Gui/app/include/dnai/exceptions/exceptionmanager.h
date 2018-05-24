#ifndef DNAI_EXEPTIONS_EXEPTION_MANAGER_H
#define DNAI_EXEPTIONS_EXEPTION_MANAGER_H

#include <QString>
#include <QDebug>
#include "exception.h"

namespace dnai
{
	namespace exceptions
	{
		class ExceptionManager
		{
		public:
			/**
			 * \brief Allow to output error in log and display it in a dialog box
			 * \param exception 
			 */
			static void throwException(const Exception &exception)
			{
				try
				{
					throw exception;
				}
				catch (const Exception& error)
				{
					qDebug() << error.what();
					//TODO ADD CALL TO VIEW POPUP
				}
			}
		};



	}
}

#endif //DNAI_EXEPTIONS_EXEPTION_MANAGER_H