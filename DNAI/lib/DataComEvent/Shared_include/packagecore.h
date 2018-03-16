#ifndef PACKAGECORE_H
#define PACKAGECORE_H

#include <QObject>

#ifdef __GNUC__
#define PACKED( class_to_pack ) class_to_pack __attribute__((__packed__))
#else
#define PACKED( class_to_pack ) __pragma( pack(push, 1) ) class_to_pack __pragma( pack(pop) )
#endif

namespace PackageDataCom {

enum class ENTITY_CORE : qint32 {
    CONTEXT_D = 0,
    VARIABLE = 1,
    FUNCTION = 2,
    DATA_TYPE = 3,
    ENUM_TYPE = 4,
    OBJECT_TYPE = 5,
    LIST_TYPE = 6
};

enum class VISIBILITYCORE : qint32 {
  PRIVATE = 0,
  PUBLIC = 1
};

using EntityID = uint32_t;

}

#endif // PACKAGECORE_H
