#include "Rocket.h"
#include "Definitions.h"

USING_NS_CC;

Rocket::Rocket()
	: _visibleSize(Director::getInstance()->getVisibleSize())
	, _visibleOrigin(Director::getInstance()->getVisibleOrigin()) {

}

bool Rocket::init() {
	if (!Sprite::initWithSpriteFrameName("rocket-0.png")) {
		return false;
	}

	_velocity = Vec2(0.0f, 0.0f);
	_nextPosition = Point(0.0f, 0.0f);
	_speedBoost = 0.0f;
	_isBoosting = false;

	setAnchorPoint(Point(0.5f, 0.5f));

	_body = PhysicsBody::createBox(Size(ROCKET_WIDTH, ROCKET_HEIGHT));
	setPhysicsBody(_body);

	float start = ROCKET_WOBBLE_LIMIT / 2;
	_wobbleTween = RepeatForever::create(Sequence::create(
	                   EaseInOut::create(RotateTo::create(ROCKET_WOBBLE_DELAY, start), 1.0f),
	                   EaseInOut::create(RotateTo::create(ROCKET_WOBBLE_DELAY, -start), 1.0f),
	                   nullptr
	               ));
	_wobbleTween->retain();
	_wobbleTween->setTag(ROCKET_WOBBLE);

	// _body->setVelocity(Vec2(40.0f, 0.0f));

	return true;
}

void Rocket::update(float dt) {
	auto rotation = getRotation();
	auto position = getPosition();

	if (_speedBoost > 50.0f) {
		// boost
		_speedBoost -= 15.0f;
		_velocity.x = sin(CC_DEGREES_TO_RADIANS(rotation)) * _speedBoost;
		_velocity.y = cos(CC_DEGREES_TO_RADIANS(-rotation)) * _speedBoost;
	} else {
		// resume actions
		// resume();
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

	_body->applyForce(_velocity);
}

void Rocket::boost() {
	if (!_isBoosting) {
		_speedBoost = ROCKET_SPEED_BOOST;
		// pause actions
		// pause();
		_isBoosting = true;
	}
}

void Rocket::wobble() {
	setRotation(-ROCKET_WOBBLE_LIMIT / 2);
	runAction(_wobbleTween);
}