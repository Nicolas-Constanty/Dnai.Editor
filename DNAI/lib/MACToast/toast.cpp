#include "toast.h"
#include <QtMac>
#include "MacToast.h"

Toast::Toast()
{

}

void Toast::show(QString const &title, QString const &info) {
    MacToast toast;
 //   QtMac mac;

    //QPixmap(const QString &fileName
    toast.notification(title, info);
}
