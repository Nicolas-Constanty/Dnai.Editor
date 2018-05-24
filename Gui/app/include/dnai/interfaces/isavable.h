#ifndef DNAI_INTERFACES_ISAVABLE_H
#define DNAI_INTERFACES_ISAVABLE_H

namespace dnai
{
	namespace interfaces
	{
		class ISavable
		{
		public:
			virtual ~ISavable() = default;
			virtual void save() = 0;
		};
	}
}

#endif //DNAI_INTERFACES_ISAVABLE_H