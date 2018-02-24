#ifndef MODELS_ICLONE_H
#define MODELS_ICLONE_H

namespace dnai {
namespace models {
class IClone {
public:
    virtual IClone* clone() const = 0;
};
}
}

#endif // MODELS_ICLONE_H
