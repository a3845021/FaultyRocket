#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "Rocket.h"
#include "Asteroid.h"

USING_NS_CC;

class GameLayer : public Layer {
private:
	Size _visibleSize;
	Vec2 _visibleOrigin;

	float _speed;

	std::vector<Asteroid*> _asteroids;

public:
	GameLayer();
	bool init();

	void addAsteroids();
	void update(float dt);

	bool checkTopBoundary(Rocket* rocket);
	int checkLeftRightBoundaries(Rocket* rocket);

	CREATE_FUNC(GameLayer);
};

#endif // __GAME_LAYER_H__
