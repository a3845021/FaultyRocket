#include "Definitions.h"
#include "AppDelegate.h"
#include "MenuScene.h"

USING_NS_CC;

typedef struct tagResource {
	cocos2d::Size size;
	char directory[100];
} Resource;

static Resource ultraResource = { cocos2d::Size(1536, 2048), "res/HDR" };
static Resource hiResource = { cocos2d::Size(768, 1024), "res/HD" };
static Resource stdResource = { cocos2d::Size(384, 512), "res/SD" };
static Size designResolutionSize = Size(DESIGN_WIDTH, DESIGN_HEIGHT);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs() {
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

	GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages() {
	return 0; //flag for packages manager
}

void AppDelegate::_initDirector() {
	auto director = Director::getInstance();
	director->setAnimationInterval(1.0 / 60);
	director->setDisplayStats(true);
}

void AppDelegate::_initOpenGL() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("FaultyRocket", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("FaultyRocket");
#endif
		director->setOpenGLView(glview);
	}
}

void AppDelegate::_initMultiResolution() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	// set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

	// multi resolution
	std::vector<std::string> searchPaths;
	float scaleFactor = 1.0f;
	Size frameSize = glview->getFrameSize();

	// portrait: width
	// landscape: height
	if (frameSize.width > hiResource.size.width) {
		CCLOG("Usage resolution textures: HDR");
		searchPaths.push_back(ultraResource.directory);
		scaleFactor = ultraResource.size.width / designResolutionSize.width;
	} else if (frameSize.width > stdResource.size.width) {
		CCLOG("Usage resolution textures: HD");
		searchPaths.push_back(hiResource.directory);
		scaleFactor = hiResource.size.width / designResolutionSize.width;
	} else {
		CCLOG("Usage resolution textures: SD");
		searchPaths.push_back(stdResource.directory);
		scaleFactor = stdResource.size.width / designResolutionSize.width;
	}

	director->setContentScaleFactor(scaleFactor);
	FileUtils::getInstance()->setSearchPaths(searchPaths);
}

void AppDelegate::_createAndRunScene() {
	auto menuScene = MenuScene::createScene();
	Director::getInstance()->runWithScene(menuScene);
}

bool AppDelegate::applicationDidFinishLaunching() {
	_initOpenGL();
	_initDirector();
	_initMultiResolution();
	register_all_packages();

	// preload
	preloadSpriteCache();

	_createAndRunScene();

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::preloadSpriteCache() {
	auto spriteCache = SpriteFrameCache::getInstance();

	spriteCache->addSpriteFramesWithFile("ui.plist");
	spriteCache->addSpriteFramesWithFile("rockets.plist");
	spriteCache->addSpriteFramesWithFile("asteroids.plist");
}