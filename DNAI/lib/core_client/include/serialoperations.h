#ifndef CORESERIALOPERATIONS_H
#define CORESERIALOPERATIONS_H

#include <QString>

#include "Cerealizer/Binary/Binary.hpp"
#include "Cerealizer/JSON/JSON.hpp"
#include "core.h"

/*
 * QString
 */
BinaryStream    &operator <<(BinaryStream &stream, QString const & value);
BinaryStream    &operator >>(BinaryStream &stream, QString &value);
JSONStream      &operator <<(JSONStream &stream, QString const &value);
JSONStream      &operator >>(JSONStream &stream, QString &value);

/*
 * PackageDataCom::ENTITY_CORE
 */
BinaryStream    &operator <<(BinaryStream &stream, core::ENTITY value);
BinaryStream    &operator >>(BinaryStream &stream, core::ENTITY &value);
JSONStream      &operator <<(JSONStream &stream, core::ENTITY value);
JSONStream      &operator >>(JSONStream &stream, core::ENTITY &value);

/*
 * PackageDataCom::VISIBILITYCORE
 */
BinaryStream    &operator <<(BinaryStream &stream, core::VISIBILITY value);
BinaryStream    &operator >>(BinaryStream &stream, core::VISIBILITY &value);
JSONStream      &operator <<(JSONStream &stream, core::VISIBILITY value);
JSONStream      &operator >>(JSONStream &stream, core::VISIBILITY &value);

#endif // CORESERIALOPERATIONS_H
