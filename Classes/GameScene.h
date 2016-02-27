#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene : public Layer {
private:
	Size _visibleSize;
	Vec2 _visibleOrigin;

	enum class State {
		Starting,
		Playing,
		Gameover
	};

	PhysicsWorld* _sceneWorld;

	State _state;
	GameLayer* _layer;

	Rocket* _rocket;

	void _setPhysicsWorld(PhysicsWorld* world) {
		_sceneWorld = world;
	}

public:
	static Scene* createScene();
	bool init();
	CREATE_FUNC(GameScene);

	void startPlay();

	void update(float dt);

	// ...

	bool onTouchBegan(Touch* touch, Event* event);
};

#endif // __GAME_SCENE_H__
