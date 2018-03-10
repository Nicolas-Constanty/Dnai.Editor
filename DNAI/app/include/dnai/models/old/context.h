#ifndef DNAI_MODELS_CONTEXT_H
#define DNAI_MODELS_CONTEXT_H
#include "entitycore.h"


namespace dnai {
	namespace models {
		class ContextCore : public EntityCore 
		{
		public:
			~ContextCore() override;
			std::map<qint32, commands::EntityCommand*> initCommands() const override;
		};
	}
}

#endif // DNAI_MODELS_CONTEXT_H
