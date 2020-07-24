#pragma once

#include "Animation.h"

class FiniteAnimation : public virtual Animation {
private:
    bool done{false};
public:
    bool isDone() const {
        return done;
    }
};
