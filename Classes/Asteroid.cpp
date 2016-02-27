#include "Asteroid.h"
#include "Definitions.h"

USING_NS_CC;

Asteroid::Asteroid() {

}

bool Asteroid::init() {
	if (!Node::init()) {
        return false;
    }

    // _velocity = Vec2(0.0f, 0.0f);

    // _sprite = Sprite::createWithSpriteFrameName("asteroid-0.png");
    // _sprite->setAnchorPoint(Point(0.5f, 0.5f));
    // addChild(_sprite);

    // _angularVelocity = (CCRANDOM_0_1() - 0.5) * 10;

    // ...

	return true;
}

// void Asteroid::update(float dt) {
	
// }