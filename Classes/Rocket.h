#ifndef __ROCKET_H__
#define __ROCKET_H__

#include "cocos2d.h"

USING_NS_CC;

class Rocket : public Sprite {
private:
	Size _visibleSize;
	Vec2 _visibleOrigin;

	Vec2 _velocity;
	Point _nextPosition;

	Action* _wobbleTween;
	float _speedBoost;
	bool _isBoosting;

public:
	Rocket();
	bool init();

	void update(float dt);
	void boost();
	void wobble();

	Point getNextPosition() {
		return _nextPosition;
	};
	inline void setNextPosition(Point position) {
		_nextPosition = position;
	};
	inline virtual void place() {
		setPosition(_nextPosition);
	};

	CREATE_FUNC(Rocket);
};

#endif // __ROCKET_H__
