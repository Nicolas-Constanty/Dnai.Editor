#ifndef DNAI_IENTITY_H
#define DNAI_IENTITY_H

namespace dnai
{
	namespace models
	{
		template <class T>
		class IEntity
		{
		public:
			virtual ~IEntity() = default;
			virtual const T& data() const = 0;
			virtual bool setData(const T& data) = 0;
		};
	}
}

#endif //DNAI_IENTITY_H