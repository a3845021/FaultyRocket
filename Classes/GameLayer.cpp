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

	return true;
}

void GameLayer::addAsteroids() {
	// ...
}

void GameLayer::update(float dt) {
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