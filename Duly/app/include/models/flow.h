#ifndef MODEL_FLOW_H
#define MODEL_FLOW_H

#include "models/identity.h"
#include "models/imodel.h"
#include "models/common.h"

namespace duly_gui {
    namespace models {
        class Flow: public Common, public Identity, virtual public IModel
        {
        public:
            Flow(QString const &, QString const &, QString const &, QString const &, QObject *parent = nullptr);
            virtual ~Flow();

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;
            virtual void declare() const;

            // IClone interface
        private:
            IClone *clone() const;
        };
    }
}

#endif // MODEL_FLOW_H
