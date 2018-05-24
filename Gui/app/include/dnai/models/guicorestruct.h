#ifndef DNAI_MODELS_GUI_CORE_STRUCT_H
#define DNAI_MODELS_GUI_CORE_STRUCT_H

namespace dnai
{
	namespace models
	{
		template <class GuiModel, class CoreModel>
		class GuiCoreStruct
		{
		private:
			GuiModel m_guimodel;
			CoreModel m_coreModel;
		};
	}
}

#endif //DNAI_MODELS_GUI_CORE_STRUCT_H
