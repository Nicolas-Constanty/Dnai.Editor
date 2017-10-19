#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

namespace duly_gui {
    class Project
    {
    public:
        Project(const QString &, const QString &);
        virtual ~Project();

    //public:
    //    static Project *create(const QString &, const QString &);
    //    static Project *load(const QString &);

    public:
        void save();

    private:
        const QString &_name;
        const QString &_path;
    };
}

#endif // PROJECT_H
