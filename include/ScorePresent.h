#pragma once

#include "Present.h"

class ScorePresent : public Present 
{
public:
    //c-tor:
    using Present::Present;

    //handleCollision functions:
    using Present::handleCollision;
    virtual void handleCollision(GameObject&) override;
};