#ifndef MODEL_AREGISTER_H
#define MODEL_AREGISTER_H

#include <QList>

namespace duly_gui {
    namespace models {
        template <class T>
        class ARegister {
        public:
            ARegister() {}
            virtual ~ARegister() {}

        public:
            void addView(T *view) {
                m_views.push_back(view);
            }

            bool removeView(T *view) {
                return m_views.removeOne(view);
            }
        private:
            QList<T*> m_views;
        };
    }
}

#endif // MODEL_AREGISTER_H
