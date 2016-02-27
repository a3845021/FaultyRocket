#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "cocos2d.h"

USING_NS_CC;

class Asteroid : public Node {
private:
	Sprite* _sprite;
	
	float _angularVelocity;
	Vec2 _velocity;

public:
	Asteroid();
	bool init();

	void update(float dt);

	CREATE_FUNC(Asteroid);
};

#endif // __ASTEROID_H__
