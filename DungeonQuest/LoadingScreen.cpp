#include "LoadingScreen.h"

#include "UIIcon.h"
#include "UIText.h"
#include <vector>

LoadingScreen::LoadingScreen(int screenWidth, int screenHeight, View* view)
{
	UIIcon* loadScreen = new UIIcon({ -screenWidth / 16, 0 }, screenWidth / 8, screenWidth / 8,
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/icon_flame.png").textureID,
		{ 255, 50, 0, 255 });

	//Set current health
	UIText* loadText = new UIText({ -screenWidth / 3.5f, -screenWidth / 8 }, 1.4f,
		new Solengine::Font("Fonts/Px437_VGA_SquarePx.ttf", 64),
		"Welcome to DUNGEONQUEST!", { 255, 100, 0, 255 });
	loadText->updateText(" ");

	view->update(std::vector<Drawable*> {}, std::vector<std::pair<Drawable*, Drawable*>> {}, 
		std::vector<Drawable*> {loadScreen, loadText});

	delete loadText;
	delete loadScreen;
}

LoadingScreen::~LoadingScreen()
{
}
