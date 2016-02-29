#include "Definitions.h"
#include "GameScene.h"
#include "GameLayer.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	auto scene = Scene::create();

	auto game = GameScene::create();

	scene->addChild(game);

	return scene;
}

bool GameScene::init() {
	if ( !Layer::init() ) {
		return false;
	}

	CCLOG("Game scene initialize...");

	_state = State::Starting;

	_visibleSize = Director::getInstance()->getVisibleSize();
	_visibleOrigin = Director::getInstance()->getVisibleOrigin();

	CCLOG("Visible size: %fx%f", _visibleSize.width, _visibleSize.height);

	// layer
	_layer = GameLayer::create();
	addChild(_layer, 0);

	// create rocket
	_rocket = Rocket::create();
	_rocket->setPosition(Point(_visibleSize.width * 0.5f + _visibleOrigin.x,
	                           _visibleSize.height * ROCKET_BOTTOM + _visibleOrigin.y));
	addChild(_rocket, 1);

	// touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// start update
	schedule(schedule_selector(GameScene::update));

	return true;
}

void GameScene::startPlay() {
	_layer->startAsteroids();
	_rocket->wobble();
	_state = State::Playing;
}

void GameScene::update(float dt) {
	// state playing
	_rocket->update(dt);
	_layer->update(dt);

	// check boundaries
	if (_layer->checkTopBoundary(_rocket)) {
		_rocket->setNextPosition(Point(_rocket->getNextPosition().x,
		                               _visibleSize.height + _visibleOrigin.y));
	}
	auto checkLeftRightBoundaries = _layer->checkLeftRightBoundaries(_rocket);
	if (checkLeftRightBoundaries == 1) {
		_rocket->setNextPosition(Point(_visibleOrigin.x,
		                               _rocket->getNextPosition().y));
	} else if (checkLeftRightBoundaries == 2) {
		_rocket->setNextPosition(Point(_visibleSize.width + _visibleOrigin.x,
		                               _rocket->getNextPosition().y));
	}

	_rocket->place();
	_layer->place();
}

bool GameScene::onTouchBegan(Touch* touch, Event* event) {
	if (_state == State::Starting) {
		startPlay();
		return true;
	} else if (_state == State::Playing) {
		_rocket->boost();
		return true;
	}

	return false;
}













