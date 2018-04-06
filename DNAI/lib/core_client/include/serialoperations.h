#ifndef CORESERIALOPERATIONS_H
#define CORESERIALOPERATIONS_H

#include <QString>

#include "Cerealizer/Binary/BinaryStream.hpp"
#include "Cerealizer/JSON/JSONStream.hpp"
#include "core.h"

/*
 * QString
 */
Cerealization::Cerealizer::BinaryStream    &operator <<(Cerealization::Cerealizer::BinaryStream &stream, QString const & value);
Cerealization::Cerealizer::BinaryStream    &operator >>(Cerealization::Cerealizer::BinaryStream &stream, QString &value);
Cerealization::Cerealizer::JSONStream      &operator <<(Cerealization::Cerealizer::JSONStream &stream, QString const &value);
Cerealization::Cerealizer::JSONStream      &operator >>(Cerealization::Cerealizer::JSONStream &stream, QString &value);

/*
 * ENTITY
 */
Cerealization::Cerealizer::BinaryStream    &operator <<(Cerealization::Cerealizer::BinaryStream &stream, core::ENTITY value);
Cerealization::Cerealizer::BinaryStream    &operator >>(Cerealization::Cerealizer::BinaryStream &stream, core::ENTITY &value);
Cerealization::Cerealizer::JSONStream      &operator <<(Cerealization::Cerealizer::JSONStream &stream, core::ENTITY value);
Cerealization::Cerealizer::JSONStream      &operator >>(Cerealization::Cerealizer::JSONStream &stream, core::ENTITY &value);

/*
 * VISIBILITY
 */
Cerealization::Cerealizer::BinaryStream    &operator <<(Cerealization::Cerealizer::BinaryStream &stream, core::VISIBILITY value);
Cerealization::Cerealizer::BinaryStream    &operator >>(Cerealization::Cerealizer::BinaryStream &stream, core::VISIBILITY &value);
Cerealization::Cerealizer::JSONStream      &operator <<(Cerealization::Cerealizer::JSONStream &stream, core::VISIBILITY value);
Cerealization::Cerealizer::JSONStream      &operator >>(Cerealization::Cerealizer::JSONStream &stream, core::VISIBILITY &value);

/*
 * INSTRUCTION
 */
Cerealization::Cerealizer::BinaryStream    &operator <<(Cerealization::Cerealizer::BinaryStream &stream, core::INSTRUCTION value);
Cerealization::Cerealizer::BinaryStream    &operator >>(Cerealization::Cerealizer::BinaryStream &stream, core::INSTRUCTION &value);
Cerealization::Cerealizer::JSONStream      &operator <<(Cerealization::Cerealizer::JSONStream &stream, core::INSTRUCTION value);
Cerealization::Cerealizer::JSONStream      &operator >>(Cerealization::Cerealizer::JSONStream &stream, core::INSTRUCTION &value);

#endif // CORESERIALOPERATIONS_H
