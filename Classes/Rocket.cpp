#include "Definitions.h"
#include "Rocket.h"

USING_NS_CC;

Rocket::Rocket()
	: _visibleSize(Director::getInstance()->getVisibleSize())
	, _visibleOrigin(Director::getInstance()->getVisibleOrigin())
	, _radius(ROCKET_RADIUS)
	, _velocity(Vec2::ZERO)
	, _nextPosition(Point::ZERO)
	, _speedBoost(0.0f)
	, _isBoosting(false) {
	setAnchorPoint(Point::ANCHOR_MIDDLE);
}

bool Rocket::init() {
	if (!Sprite::initWithSpriteFrameName("rocket-0.png")) {
		return false;
	}

	_contentSize = getContentSize();
	_nextPosition = getPosition();

#if (COCOS2D_DEBUG_BODIES)
	_debugCircle = DrawNode::create();
	_debugCircle->drawCircle(Vec2(_contentSize.width * 0.5f, _contentSize.height * 0.5f),
	                         _radius,
	                         CC_DEGREES_TO_RADIANS(90),
	                         CIRCLE_NUMBER_SEGMENTS,
	                         false,
	                         Color4F::MAGENTA);
	_debugCircle->setAnchorPoint(Point::ANCHOR_MIDDLE);
	addChild(_debugCircle);
#endif

	float start = ROCKET_WOBBLE_LIMIT / 2;
	_wobbleTween = RepeatForever::create(Sequence::create(
	        EaseSineInOut::create(RotateTo::create(ROCKET_WOBBLE_DELAY, start)),
	        EaseSineInOut::create(RotateTo::create(ROCKET_WOBBLE_DELAY, -start)),
	        nullptr
	                                     ));
	_wobbleTween->retain();

	return true;
}

void Rocket::update(float dt) {
	auto rotation = getRotation();
	auto position = getPosition();

	_nextPosition = position;

	if (_speedBoost > 100.0f) {
		// boost
		_speedBoost -= 30.0f;
		_velocity.x = sin(CC_DEGREES_TO_RADIANS(rotation)) * _speedBoost;
		_velocity.y = cos(CC_DEGREES_TO_RADIANS(-rotation)) * _speedBoost;
	} else {
		// resume actions
		resume();
		_isBoosting = false;
		// wobble
		_velocity.x = sin(CC_DEGREES_TO_RADIANS(rotation)) * ROCKET_SPEED;
		// lower boundary
		if (position.y < _visibleSize.height * ROCKET_BOTTOM) {
			_velocity.y = 0;
		} else {
			_velocity.y = -ROCKET_SPEED_RETURN;
		}
	}

	_nextPosition += _velocity * dt;
}

void Rocket::boost() {
	if (!_isBoosting) {
		_speedBoost = ROCKET_SPEED_BOOST;
		// pause actions
		pause();
		_isBoosting = true;
	}
}

void Rocket::die() {
	CCLOG("Die!");
	setVisible(false);
	stopAllActions();
}

void Rocket::wobble() {
	setRotation(-ROCKET_WOBBLE_LIMIT / 2);
	runAction(_wobbleTween);
}