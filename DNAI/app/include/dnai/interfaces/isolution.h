#ifndef DNAI_INTERFACES_ISOLUTION_H
#define DNAI_INTERFACES_ISOLUTION_H

#include "iproject.h"

namespace dnai
{
	namespace interfaces
	{
		class ISolution : public IProject
		{
		public:
			virtual ~ISolution() = default;
			virtual const QList<IProject *> &projects() const = 0;
			virtual void addProject(IProject *) = 0;
			virtual IProject *seletedProject() const = 0;
			virtual bool selectProject(IProject *) = 0;
		};
	}
}

#endif //DNAI_INTERFACES_ISOLUTION_H