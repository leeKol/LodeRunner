#pragma once

#include "Present.h"

class BadPresent : public Present
{
public:
    //c-tor:
    using Present::Present;

    //handleCollision functions:
    using Present::handleCollision;
    virtual void handleCollision(GameObject&) override;
};