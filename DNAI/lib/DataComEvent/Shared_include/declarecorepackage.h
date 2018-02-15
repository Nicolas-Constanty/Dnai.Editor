#ifndef DECLARECOREPACKAGE_H
#define DECLARECOREPACKAGE_H

#include <QString>
#include "packagecore.h"

PACKED(
struct DeclareCorePackageInterface {
    PackageDataCom::ENTITYCORE entityType;
    qint32 containerID;
    qint32 p_sizeName;
    PackageDataCom::VISIBILITYCORE visibility;
}
);

typedef struct DeclareCorePackage {
    PackageDataCom::ENTITYCORE entityType;
    qint32 containerID;
    QString name;
    PackageDataCom::VISIBILITYCORE visibility;
} DeclareCorePackage;

typedef struct EntityDeclareCorePackage {
    PackageDataCom::ENTITYCORE entityType;
    qint32 containerID;
    QString name;
    PackageDataCom::VISIBILITYCORE visibility;
    qint32 id;
} EntityDeclareCorePackage;

#define SIZE_PACKAGE_DECLARE(sizeName) (sizeof(DeclareCorePackageInterface) + sizeName)

#endif // DECLARECOREPACKAGE_H
