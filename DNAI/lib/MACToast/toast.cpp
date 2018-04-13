#include "toast.h"
#include <QtMac>
#include "MacToast.h"

ToastMac::ToastMac()
{

}

void ToastMac::show(QString const &title, QString const &info) {
    MacToast toast;
 //   QtMac mac;

    //QPixmap(const QString &fileName
    toast.notification(title, info);
}
