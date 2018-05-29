#ifndef DNAI_INTERFACES_IINSTRUCTION_H
#define DNAI_INTERFACES_IINSTRUCTION_H

#include "dnai/models/gui/flow.h"
namespace dnai
{
    namespace models {
        class Entity;
    }
	namespace interfaces
	{
		class IInstruction
		{
		public:
			virtual ~IInstruction() = default;

            virtual const QList<models::Entity*> &inputs() const = 0;
			virtual bool setInputs(const QList<models::Entity*> &inputs) = 0;

			virtual const QList<models::Entity*> &outputs() const = 0;
			virtual bool setOutputs(const QList<models::Entity*> &outputs) = 0;

			virtual models::gui::Flow* flowIn() const = 0;
			virtual bool setFlowIn(models::gui::Flow* flow) = 0;

			virtual models::gui::Flow* flowOut() const = 0;
			virtual bool setFlowOut(models::gui::Flow* flow) = 0;
		};
	}
}

#endif //DNAI_INTERFACES_IINSTRUCTION_H
