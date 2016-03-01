#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class MenuScene : public Layer {
private:
	Size _visibleSize;
	Vec2 _visibleOrigin;

public:
	static Scene* createScene();
	bool init();
	CREATE_FUNC(MenuScene);

	static void startGame(Ref* sender);
};

#endif // __MENU_SCENE_H__
