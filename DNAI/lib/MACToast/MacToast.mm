#include "MacToast.h"
#include <QDebug>
#include <QString>
#include <Foundation.h>

void MacToast::notification(QString const &title, QString const &info) {
  NSUserNotification *userNotification = [[[NSUserNotification alloc] init] autorelease];
  userNotification.title = [NSString stringWithUTF8String:title.toStdString().c_str()];//"My Great Title";
  userNotification.informativeText = [NSString stringWithUTF8String:info.toStdString().c_str()];//"Blah Blah Blah";
  [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:userNotification];

}
