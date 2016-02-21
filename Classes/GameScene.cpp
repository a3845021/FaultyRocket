#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

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

	Vec2 visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto spritecache = SpriteFrameCache::getInstance();

	// adding spritesheets
	spritecache->addSpriteFramesWithFile("rockets.plist");

	auto rocket = Sprite::createWithSpriteFrameName("rocket-0.png");
	rocket->setPosition(visibleSize.x / 2 + origin.x, visibleSize.y / 2 + origin.y);
	this->addChild(rocket);

	return true;
}
