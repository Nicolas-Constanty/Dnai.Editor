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
 * ENTITY
 */
BinaryStream    &operator <<(BinaryStream &stream, core::ENTITY value);
BinaryStream    &operator >>(BinaryStream &stream, core::ENTITY &value);
JSONStream      &operator <<(JSONStream &stream, core::ENTITY value);
JSONStream      &operator >>(JSONStream &stream, core::ENTITY &value);

/*
 * VISIBILITY
 */
BinaryStream    &operator <<(BinaryStream &stream, core::VISIBILITY value);
BinaryStream    &operator >>(BinaryStream &stream, core::VISIBILITY &value);
JSONStream      &operator <<(JSONStream &stream, core::VISIBILITY value);
JSONStream      &operator >>(JSONStream &stream, core::VISIBILITY &value);

/*
 * INSTRUCTION
 */
BinaryStream    &operator <<(BinaryStream &stream, core::INSTRUCTION value);
BinaryStream    &operator >>(BinaryStream &stream, core::INSTRUCTION &value);
JSONStream      &operator <<(JSONStream &stream, core::INSTRUCTION value);
JSONStream      &operator >>(JSONStream &stream, core::INSTRUCTION &value);

#endif // CORESERIALOPERATIONS_H
