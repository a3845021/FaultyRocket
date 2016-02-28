#include "Asteroid.h"
#include "Definitions.h"

USING_NS_CC;

Asteroid::Asteroid()
	: _visibleSize(Director::getInstance()->getVisibleSize())
	, _visibleOrigin(Director::getInstance()->getVisibleOrigin()) {

}

bool Asteroid::init() {
	if (!Node::init()) {
		return false;
	}

	_velocity = Vec2::ZERO;

	_sprite = Sprite::createWithSpriteFrameName("asteroid-0.png");
	_sprite->setAnchorPoint(Point::ANCHOR_MIDDLE);
	addChild(_sprite);

	Asteroid::recycle();

	_rotationTween = RepeatForever::create(Sequence::create(
	        RotateBy::create(4.0f, 180.0f),
	        nullptr
	                                       ));
	_rotationTween->retain();

	auto asteroidEndCallback = CallFunc::create([&]() {
		Asteroid::recycle();
	});
	float duration = (ASTEROID_DELAY / _visibleSize.width) * floor(_visibleSize.height / ASTEROID_VELOCITY + 0.5);
	_fallTween = RepeatForever::create(Sequence::create(
	                                       MoveBy::create(duration, Vec2(0, -_visibleSize.height - 200.0f)),
	                                       asteroidEndCallback,
	                                       nullptr
	                                   ));
	_fallTween->retain();

	runAction(_rotationTween);
	runAction(_fallTween);

	return true;
}

// ... set animations

void Asteroid::update(float dt) {
    // auto position = getPosition();
    // _nextPosition = position;

	// ...

	// _nextPosition += _velocity * dt;
}

void Asteroid::recycle() {
	auto position = Point(CCRANDOM_0_1() * _visibleSize.width + _visibleOrigin.x,
	                      _visibleSize.height + _visibleOrigin.y + 100.0f);
	setPosition(position);
}