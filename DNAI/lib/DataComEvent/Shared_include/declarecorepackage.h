#ifndef DECLARECOREPACKAGE_H
#define DECLARECOREPACKAGE_H

#include <QString>
#include "packagecore.h"

PACKED(
struct DeclareCorePackageInterface {
    PackageDataCom::ENTITY_CORE entityType;
    qint32 containerID;
    qint32 p_sizeName;
    PackageDataCom::VISIBILITYCORE visibility;
}
);

typedef struct DeclareCorePackage {
    PackageDataCom::ENTITY_CORE entityType;
    qint32 containerID;
    QString name;
    PackageDataCom::VISIBILITYCORE visibility;
} DeclareCorePackage;

typedef struct EntityDeclareCorePackage {
    PackageDataCom::ENTITY_CORE entityType;
    qint32 containerID;
    QString name;
    PackageDataCom::VISIBILITYCORE visibility;
    qint32 id;
} EntityDeclareCorePackage;

#define SIZE_PACKAGE_DECLARE(sizeName) (sizeof(DeclareCorePackageInterface) + sizeName)

#endif // DECLARECOREPACKAGE_H
