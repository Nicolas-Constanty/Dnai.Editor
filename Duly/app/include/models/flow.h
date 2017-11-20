#ifndef MODEL_FLOW_H
#define MODEL_FLOW_H

#include "models/identity.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Flow: public Identity, virtual public IModel
        {
        public:
            Flow(QString const &, QString const &);
            virtual ~Flow();

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;

            // IClone interface
        private:
            IClone *clone() const;
        };
    }
}

#endif // MODEL_FLOW_H
