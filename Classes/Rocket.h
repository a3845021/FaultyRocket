#ifndef __ROCKET_H__
#define __ROCKET_H__

#include "cocos2d.h"

USING_NS_CC;

class Rocket : public Sprite {
private:
	Size _visibleSize;
	Vec2 _visibleOrigin;

#if (COCOS2D_DEBUG_BODIES)
	DrawNode* _debugCircle;
#endif

	Vec2 _velocity;
	Point _nextPosition;
	Size _contentSize;

	Action* _wobbleTween;
	float _speedBoost;
	bool _isBoosting;
	float _radius;

public:
	Rocket();
	bool init();
	CREATE_FUNC(Rocket);

	void update(float dt);
	void boost();
	void wobble();
	void die();

	inline float getRadius() {
		return _radius;
	}

	Point getNextPosition() {
		return _nextPosition;
	};
	inline void setNextPosition(Point position) {
		_nextPosition = position;
	};
	inline virtual void place() {
		setPosition(_nextPosition);
	};
};

#endif // __ROCKET_H__
