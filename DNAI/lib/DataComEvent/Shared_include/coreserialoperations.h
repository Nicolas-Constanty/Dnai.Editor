#ifndef CORESERIALOPERATIONS_H
#define CORESERIALOPERATIONS_H

#include <QString>

#include "Cerealizer/Binary/Binary.hpp"
#include "packagecore.h"

/*
 * QString
 */
BinaryStream    &operator <<(BinaryStream &stream, QString const & value);
BinaryStream    &operator >>(BinaryStream &stream, QString &value);

/*
 * PackageDataCom::ENTITY_CORE
 */
BinaryStream    &operator <<(BinaryStream &stream, PackageDataCom::ENTITY_CORE value);
BinaryStream    &operator >>(BinaryStream &stream, PackageDataCom::ENTITY_CORE &value);

/*
 * PackageDataCom::VISIBILITYCORE
 */
BinaryStream    &operator <<(BinaryStream &stream, PackageDataCom::VISIBILITYCORE value);
BinaryStream    &operator >>(BinaryStream &stream, PackageDataCom::VISIBILITYCORE &value);

#endif // CORESERIALOPERATIONS_H
