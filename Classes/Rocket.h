#ifndef __ROCKET_H__
#define __ROCKET_H__

#include "cocos2d.h"

USING_NS_CC;

class Rocket : public Sprite {
private:
	Size _visibleSize;
	Vec2 _visibleOrigin;

	Action* _wobbleTween;
	Vec2 _velocity;
	float _speedBoost;

public:
	Rocket();
	bool init();

	void update(float dt);
	void boost();
	void wobble();

	CREATE_FUNC(Rocket);
};

#endif // __ROCKET_H__
