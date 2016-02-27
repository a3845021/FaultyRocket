#include "GameScene.h"
#include "GameLayer.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	auto scene = Scene::createWithPhysics();
	
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

	auto game = GameScene::create();
	game->_setPhysicsWorld(scene->getPhysicsWorld());

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

	// boundaries
	auto edgeBody = PhysicsBody::createEdgeBox(_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(_visibleSize.width * 0.5f + _visibleOrigin.x,
	                            _visibleSize.height * 0.5f + _visibleOrigin.y));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

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
	_layer->addAsteroids();
	_rocket->wobble();
	_state = State::Playing;
}

void GameScene::update(float dt) {
	// state playing
	// _rocket->update(dt);
	_layer->update(dt);

	// check boundaries
	// if (_layer->checkTopBoundary(_rocket)) {
	// 	_rocket->setNextPosition(Point(_rocket->getNextPosition().x,
	// 	                               _visibleSize.height + _visibleOrigin.y));
	// }
	// auto checkLeftRightBoundaries = _layer->checkLeftRightBoundaries(_rocket);
	// if (checkLeftRightBoundaries == 1) {
	// 	_rocket->setNextPosition(Point(_visibleOrigin.x,
	// 	                               _rocket->getNextPosition().y));
	// } else if (checkLeftRightBoundaries == 2) {
	// 	_rocket->setNextPosition(Point(_visibleSize.width + _visibleOrigin.x,
	// 	                               _rocket->getNextPosition().y));
	// }

	// _rocket->place();
	// ... check collision
	// ...
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













