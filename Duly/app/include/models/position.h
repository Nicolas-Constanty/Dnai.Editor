#ifndef MODEL_POSITION_H
#define MODEL_POSITION_H

#include <QVector2D>
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Position: virtual public IModel
        {
        public:
            Position(QVector2D const &);

        private:
            QVector2D m_position;

        public:
            QVector2D position() const;
            void setPosition(const QVector2D &);

            // IClone interface
        private:
            IClone *clone() const;
            virtual void declare() const;

            // IModel interface
        public:
            void serialize(QJsonObject &) const;
        };
    }
}

#endif // MODEL_POSITION_H
