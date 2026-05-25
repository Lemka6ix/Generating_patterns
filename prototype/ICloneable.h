#ifndef ICLONEABLE_H
#define ICLONEABLE_H

class ICloneable {
public:
    virtual ~ICloneable() = default;
    virtual ICloneable* clone() const = 0;
};

#endif