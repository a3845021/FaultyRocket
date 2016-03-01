#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "cocos2d.h"
#include "Rocket.h"

USING_NS_CC;

class Asteroid : public Node {
private:
	Size _visibleSize;
	Vec2 _visibleOrigin;

	Sprite* _sprite;
#if (COCOS2D_DEBUG)
	DrawNode* _debugLine;
#endif
#if (COCOS2D_DEBUG_BODIES)
	DrawNode* _debugCircle;
#endif

	Vec2 _velocity;
	Point _nextPosition;

	Action* _rotationTween;
	float _radius;

public:
	Asteroid();
	bool init();
	CREATE_FUNC(Asteroid);

	void update(float dt);
	void recycle();
	void launch();

	bool checkCollision(Rocket* rocket);

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

#endif // __ASTEROID_H__
