#include "Definitions.h"
#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MenuScene::createScene() {
	auto scene = Scene::create();
	auto menu = MenuScene::create();

	scene->addChild(menu);

	return scene;
}

bool MenuScene::init() {
	if ( !Layer::init() ) {
		return false;
	}

	_visibleSize = Director::getInstance()->getVisibleSize();
	_visibleOrigin = Director::getInstance()->getVisibleOrigin();

	// ... replace node play
	auto menu = Menu::create(
	                MenuItemSprite::create(
	                    Sprite::createWithSpriteFrameName("play-0.png"),
	                    nullptr,
	                    MenuScene::startGame
	                ),
	                nullptr
	            );

	menu->setPosition(Point(_visibleSize.width * 0.5f + _visibleOrigin.x,
	                        _visibleSize.height * 0.5f + _visibleOrigin.y));
	addChild(menu, 1);

	return true;
}

void MenuScene::startGame(Ref* sender) {
	auto gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}