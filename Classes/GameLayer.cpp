#include "Definitions.h"
#include "GameLayer.h"

USING_NS_CC;

GameLayer::GameLayer()
	: _speed(150)
	, _visibleSize(Director::getInstance()->getVisibleSize())
	, _visibleOrigin(Director::getInstance()->getVisibleOrigin()) {

}

bool GameLayer::init() {
	if ( !Layer::init() ) {
		return false;
	}

	// ... sprite background

	// define asterodis parameters
	_asteroidsDelay = ASTEROID_DELAY / _visibleSize.width;

	auto asteroidsLoopCallback = CallFunc::create([&]() {
		GameLayer::addAsteroid();
	});
	_asteroidsLoop = RepeatForever::create(Sequence::create(
	        DelayTime::create(_asteroidsDelay),
	        asteroidsLoopCallback,
	        nullptr
	                                       ));
	_asteroidsLoop->retain();

	return true;
}

void GameLayer::startAsteroids() {
	runAction(_asteroidsLoop);
}

void GameLayer::addAsteroid() {
	for (size_t i = 0; i < _asteroids.size(); ++i) {
		auto asteroid = _asteroids[i];
		if (asteroid->getPositionY() < _visibleOrigin.y - ASTEROID_MARGIN) {
			// use created asteroid
			asteroid->recycle();
			return;
		}
	}
	// create new asteroid
	auto asteroid = Asteroid::create();
	addChild(asteroid);
	asteroid->launch();
	_asteroids.push_back(asteroid);
}

void GameLayer::update(float dt) {
	for (size_t i = 0; i < _asteroids.size(); ++i) {
		_asteroids[i]->update(dt);
	}

	// ...
}

void GameLayer::place() {
	for (size_t i = 0; i < _asteroids.size(); ++i) {
		_asteroids[i]->place();
	}

	// ...
}

bool GameLayer::checkTopBoundary(Rocket* rocket) {
	return rocket->getNextPosition().y > _visibleSize.height + _visibleOrigin.y;
}

int GameLayer::checkLeftRightBoundaries(Rocket* rocket) {
	if (rocket->getNextPosition().x < _visibleOrigin.x) {
		// left boundary
		return 1;
	} else if (rocket->getNextPosition().x > _visibleSize.width + _visibleOrigin.x) {
		// right boundary
		return 2;
	}
	return 0;
}