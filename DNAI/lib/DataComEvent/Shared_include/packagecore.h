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
    LIST_TYPE = 6,
    ENTITY_INT_MIN_SENTINEL_DO_NOT_USE_ = -0x7FFFFFFF - 1,
    ENTITY_INT_MAX_SENTINEL_DO_NOT_USE_ = 0x7FFFFFFF
};

enum VISIBILITYCORE {
  PRIVATE = 0,
  PUBLIC = 1,
  VISIBILITY_INT_MIN_SENTINEL_DO_NOT_USE_ = -0x7FFFFFFF - 1,
  VISIBILITY_INT_MAX_SENTINEL_DO_NOT_USE_ = 0x7FFFFFFF
};

}

#endif // PACKAGECORE_H
