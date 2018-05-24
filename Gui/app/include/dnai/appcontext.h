#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QObject>

namespace dnai {
class AppContext : public QObject
{
public:
	explicit AppContext(QObject *parent = nullptr);
};
}

#endif // APPCONTEXT_H
