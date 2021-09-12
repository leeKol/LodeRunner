#pragma once

#include "GameObject.h"

class StaticObject : public GameObject
{
public:
    //c-tor:
	using GameObject::GameObject;

    //handleCollision functions:
    virtual void handleCollision(Player&) override {};
    virtual void handleCollision(Enemy&) override {};
    virtual void handleCollision(Floor&) override {};
    virtual void handleCollision(Ladder&) override {};
    virtual void handleCollision(Rope&) override {};
    virtual void handleCollision(Coin&) override {};
    virtual void handleCollision(TimePresent&) override {};
    virtual void handleCollision(BadPresent&) override {};
    virtual void handleCollision(ScorePresent&) override {};
    virtual void handleCollision(LifePresent&) override {};
    virtual void handleCollision(ShieldPresent&) override {};
    virtual void handleCollision(Hole&) override {};
    virtual void handleCollision(GameObject&) override;
};