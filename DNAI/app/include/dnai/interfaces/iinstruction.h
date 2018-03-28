#ifndef DNAI_INTERFACES_IINSTRUCTION_H
#define DNAI_INTERFACES_IINSTRUCTION_H

#include "dnai/models/gui/input.h"
#include "dnai/models/gui/output.h"
#include "dnai/models/gui/flow.h"

namespace dnai
{
	namespace interfaces
	{
		class IInstruction
		{
		public:
			virtual ~IInstruction() = default;

			virtual QList<models::gui::Input*> inputs() const = 0;
			virtual bool setInputs(const QList<models::gui::Input*> &inputs) = 0;

			virtual QList<models::gui::Output*> outputs() const = 0;
			virtual bool setOutputs(const QList<models::gui::Output*> &outputs) = 0;

			virtual models::gui::Flow* flowIn() const = 0;
			virtual bool setFlowIn(models::gui::Flow* flow) = 0;

			virtual models::gui::Flow* flowOut() const = 0;
			virtual bool setFlowOut(models::gui::Flow* flow) = 0;
		};
	}
}

#endif //DNAI_INTERFACES_IINSTRUCTION_H