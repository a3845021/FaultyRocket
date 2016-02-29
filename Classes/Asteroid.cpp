#include "Definitions.h"
#include "Asteroid.h"

USING_NS_CC;

Asteroid::Asteroid()
	: _visibleSize(Director::getInstance()->getVisibleSize())
	, _visibleOrigin(Director::getInstance()->getVisibleOrigin())
	, _radius(ASTEROID_RADIUS)
	, _velocity(Vec2::ZERO) {

}

bool Asteroid::init() {
	if (!Node::init()) {
		return false;
	}

	_sprite = Sprite::createWithSpriteFrameName("asteroid-0.png");
	_sprite->setAnchorPoint(Point::ANCHOR_MIDDLE);
	addChild(_sprite);

#if (COCOS2D_DEBUG)
	_debugLine = DrawNode::create();
	_debugLine->drawLine(Vec2::ZERO, Vec2(_visibleSize.width, 0.0f), Color4F::ORANGE);
	addChild(_debugLine);
#endif
#if (COCOS2D_DEBUG_BODIES)
	_debugCircle = DrawNode::create();
	_debugCircle->drawCircle(Vec2::ZERO, _radius, CC_DEGREES_TO_RADIANS(90), CIRCLE_NUMBER_SEGMENTS, false, Color4F::ORANGE);
	addChild(_debugCircle);
#endif

	// rotation
	_rotationTween = RepeatForever::create(Sequence::create(
	        RotateBy::create(4.0f, 180.0f),
	        nullptr
	                                       ));
	_rotationTween->retain();

	_sprite->runAction(_rotationTween);

	return true;
}

void Asteroid::launch() {
	Asteroid::recycle();
	_velocity.y = -ASTEROID_SPEED;
}

// ... set animations

void Asteroid::update(float dt) {
	auto position = getPosition();
	_nextPosition = position;

	// ...

	_nextPosition += _velocity * dt;
}

void Asteroid::recycle() {
	auto position = Point(CCRANDOM_0_1() * _visibleSize.width + _visibleOrigin.x,
	                      _visibleOrigin.y + _visibleSize.height + ASTEROID_MARGIN);
	setPosition(position);
}