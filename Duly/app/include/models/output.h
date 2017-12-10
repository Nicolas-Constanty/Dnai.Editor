#ifndef MODEL_OUTPUT_H
#define MODEL_OUTPUT_H

#include "models/variable.h"
#include "models/identity.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Output: public Variable, Identity, virtual public IModel
        {
        public:
            Output(QString const &, QString const &, QString const &, QString const &, bool, QString const &, QObject *parent = nullptr);
            virtual ~Output();

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

#endif // MODEL_OUTPUT_H
