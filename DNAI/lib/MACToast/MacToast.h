#ifndef MACTOAST_H
#define MACTOAST_H

#include <QObject>

class MacToast {
public:
  void notification(QString const &title, QString const &info);
};

#endif
