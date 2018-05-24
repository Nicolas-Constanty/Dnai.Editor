#ifndef DNAI_IENTITY_H
#define DNAI_IENTITY_H

namespace dnai
{
	namespace interfaces
	{
		template <class T>
		class IModelData
		{
		public:
			virtual ~IModelData() = default;

			/**
			 * \brief Return the data component
			 * \return const T& data
			 */
			virtual const T& data() const = 0;
			/**
			 * \brief set the data component of this object
			 * \param data 
			 * \return true if the value is successuffy updated, false otherwise
			 */
			virtual bool setData(const T& data) = 0;
		};
	}
}

#endif //DNAI_IENTITY_H