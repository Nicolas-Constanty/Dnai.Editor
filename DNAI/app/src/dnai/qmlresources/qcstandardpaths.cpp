/* QuickCross Project
 * License: APACHE-2.0
 * Author: Ben Lau
 * Project Site: https://github.com/benlau/quickcross
 *
 */

#include <QtCore>
#include <QStandardPaths>
#include "dnai/qmlresources/qcstandardpaths.h"

/*!
 * \qmltype StandardPaths
 * \instantiates QCStandardPaths
 *
 * \brief QML Wrapper of QStandardPaths
 *
 * It is a singleton component
 *
 */

/*!
 \qmlproperty enumeration StandardPaths::stanardLocation
 It is equivalent to QStandardPaths::standardLocation()
  \code
    enum StandardLocation {
        DesktopLocation,
        DocumentsLocation,
        FontsLocation,
        ApplicationsLocation,
        MusicLocation,
        MoviesLocation,
        PicturesLocation,
        TempLocation,
        HomeLocation,
        DataLocation,
        CacheLocation,
        GenericDataLocation,
        RuntimeLocation,
        ConfigLocation,
        DownloadLocation,
        GenericCacheLocation,
        GenericConfigLocation,
        AppDataLocation,
        AppConfigLocation,
        AppLocalDataLocation = DataLocation
    };
  \endcode
Example:
\code
console.log(StandardPaths.standardLocations(StandardPaths.ConfigLocation)); // Get standard location patsh of config.
\endcode
 */

QCStandardPaths::QCStandardPaths(QObject *parent) : QObject(parent)
{

}

QCStandardPaths::~QCStandardPaths()
{
    qDebug() << "QCStandardPath";
}

/*!
    \qmlmethod array StandardPaths::standardLocations(int standardLocation)
    It is equivalent to QStandardPaths::standardLocations()
 */

QStringList QCStandardPaths::standardLocations(int standardLocation)
{
    return QStandardPaths::standardLocations((QStandardPaths::StandardLocation) standardLocation);
}

/*!
    \qmlmethod string StandardPaths::writableLocation(int standardLocation)
    It is equivalent to QStandardPaths::writableLocation()
 */

QString QCStandardPaths::writableLocation(int standardLocation)
{
    return QStandardPaths::writableLocation((QStandardPaths::StandardLocation) standardLocation);
}

/*!
    \qmlmethod string StandardPaths::displayName(int standardLocation)
    It is equivalent to QStandardPaths::displayName()
 */

QString QCStandardPaths::displayName(int standardLocation)
{
    return QStandardPaths::displayName((QStandardPaths::StandardLocation) standardLocation);
}
