#include "Asteroid.h"
#include "Definitions.h"

USING_NS_CC;

Asteroid::Asteroid() {

}

bool Asteroid::init() {
	if (!Node::init()) {
        return false;
    }

    // ...

	return true;
}