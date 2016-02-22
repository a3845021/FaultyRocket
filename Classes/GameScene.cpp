#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->_setPhysicsWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init() {
	// super init first
	if ( !Layer::init() ) {
		return false;
	}

	CCLOG("Game scene initialize...");

	_screenSize = Director::getInstance()->getWinSize();
	_visibleSize = Director::getInstance()->getVisibleSize();
	_visibleOrigin = Director::getInstance()->getVisibleOrigin();

	_spriteCache = SpriteFrameCache::getInstance();
	// adding spritesheets
	_spriteCache->addSpriteFramesWithFile("rockets.plist");

	// edge world
	auto edgeBody = PhysicsBody::createEdgeBox(_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(_visibleSize.width * 0.5f + _visibleOrigin.x,
	                            _visibleSize.height * 0.5f + _visibleOrigin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	// spawn rocket
	GameScene::_spawnRocket();

	// this->schedule(schedule_selector(GameScene::_spawnRocket), ROCKET_SPAWN_FREQUENCY * _visibleSize.height);

	// _rocket = Sprite::createWithSpriteFrameName("rocket-0.png");
	// _rocket->setPosition(_screenSize.width * 0.5f, _screenSize.height * 0.1f);
	// this->addChild(_rocket);

	return true;
}

void GameScene::_spawnRocket() {
	_rocket.spawn(this);
}