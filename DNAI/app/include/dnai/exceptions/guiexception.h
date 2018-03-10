#ifndef DNAI_EXECPTIONS_GUIEXEPTION_H
#define DNAI_EXECPTIONS_GUIEXEPTION_H
#include "exception.h"

namespace dnai
{
	namespace exceptions
	{
		class GuiExeption : public Exception
		{
		public:
			/**
			* \brief Use this class with exception manager in order to throw a dialog exception. Use this class for gui model exception
			* \param _Message
			*/
			explicit GuiExeption(const std::string& _Message)
				: Exception(_Message, "Gui")
			{
			}
		};
	}
}

#endif //DNAI_EXECPTIONS_GUIEXEPTION_H#pragma once
