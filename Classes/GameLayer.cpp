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