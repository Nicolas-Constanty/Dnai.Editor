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
			explicit GuiExeption(const std::string& _Message)
				: Exception(_Message, "Gui")
			{
			}
		};
	}
}

#endif //DNAI_EXECPTIONS_GUIEXEPTION_H#pragma once
