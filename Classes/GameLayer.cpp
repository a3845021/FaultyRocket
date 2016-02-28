#include "GameLayer.h"
#include "Definitions.h"

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

	auto asteroidsLoopCallback = CallFunc::create([&]() {
		GameLayer::addAsteroid();
	});
	_asteroidsLoop = RepeatForever::create(Sequence::create(
	        DelayTime::create(ASTEROID_DELAY / _visibleSize.width),
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
	if (_asteroids.size() < 5) {
		auto asteroid = Asteroid::create();
		addChild(asteroid);
		_asteroids.push_back(asteroid);
	}
}

void GameLayer::update(float dt) {
	for (size_t i = 0; i < _asteroids.size(); ++i) {
		// ...
	}
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