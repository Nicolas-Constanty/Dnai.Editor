#ifndef DNAI_INTERFACES_SERIALIZABLE_H
#define DNAI_INTERFACES_SERIALIZABLE_H
#include <QJsonObject>
#include <QJsonArray>

namespace dnai {
    namespace interfaces {
	    /**
		 * \brief Allow inherited class to serialize and deserialize itself
		 */
        class ISerializable
        {
        public:
            virtual ~ISerializable() = default;
	        /**
             * \brief Implement this function to serialize into QJsonObject
             * \param obj 
             */
            virtual void serialize(QJsonObject &obj) const = 0;
		protected:
	        /**
			 * \brief Implement this function in order to use deserialize(const QJsonObject &obj)
			 * \param obj 
			 */
			virtual void _deserialize(const QJsonObject &obj) = 0;
        };

		/**
		* \brief Allow inherited class to serialize and deserialize itself
		* \tparam T
		*/
		template <class T>
		class ASerializable : ISerializable
		{
		public:
			virtual ~ASerializable() = default;
			virtual void serialize(QJsonObject &obj) const override = 0;

			template<class DataType>
			QJsonArray serializeList(const QList<DataType *> &datalist) const
			{
				QJsonArray tmp;
				foreach(const auto data, datalist) {
					QJsonObject var;
					data->serialize(var);
					tmp.append(var);
				}
				return tmp;
			}

			/**
			* \brief This function deserialize into a new instance of type T *
			* \param obj
			* \return
			*/
			/*static T *deserialize(const QJsonObject &obj)
			{
				auto n = dynamic_cast<ASerializable *>(new T);
				if (n == nullptr)
					return nullptr;
				n->_deserialize(obj);
				return dynamic_cast<T *>(n);
			}*/

            template<typename ... Args>
            static T *deserialize(const QJsonObject &obj, Args& ... args)
            {
                auto n = dynamic_cast<ASerializable *>(new T(args...));
                if (n == nullptr)
                    return nullptr;
                n->_deserialize(obj);
                return dynamic_cast<T *>(n);
            }
		protected:
			virtual void _deserialize(const QJsonObject &obj) override = 0;
		};
    }
}


#endif //DNAI_INTERFACES_SERIALIZABLE_H
