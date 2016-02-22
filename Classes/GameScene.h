#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "Rocket.h"

class GameScene : public cocos2d::Layer {
private:
	cocos2d::Size _screenSize;
	cocos2d::Size _visibleSize;
	cocos2d::Vec2 _visibleOrigin;

	cocos2d::PhysicsWorld *_sceneWorld;

	cocos2d::SpriteFrameCache *_spriteCache;
	// cocos2d::Sprite *_rocket;

	Rocket _rocket;

	void _setPhysicsWorld(cocos2d::PhysicsWorld *world) {
		_sceneWorld = world;
	}

	void _spawnRocket();

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_SCENE_H__
