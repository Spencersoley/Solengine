#pragma once

#include <Solengine/GLSLProgram.h>
#include <Solengine/Camera2D.h>
#include <Solengine/SpriteBatch.h>
#include <Solengine/Window.h>
#include <Solengine/Font.h>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

#include "Drawable.h"

class View
{
public:
	View();
	~View();

	void init(Solengine::Camera2D* cam, Solengine::Camera2D* uiCam, 
		      int screenWidth, int screenHeight);
    void update(std::vector<Drawable*> worldDrawables, 
		        std::vector<Drawable*> overlayDrawables);

private:
	void drawGame(std::vector<Drawable*> worldDrawables, 
		          std::vector<Drawable*> overlayDrawables);
	void drawToCamera(std::vector<Drawable*> drawables, 
		              Solengine::Camera2D* cam);

	Solengine::Camera2D* p_SOL_cam = nullptr;
	Solengine::Camera2D* p_SOL_uiCam = nullptr;

	Solengine::GLSLProgram m_SOL_shaderProgram;
	Solengine::Window m_SOL_window;

	Solengine::Font* p_SOL_spriteFont;
	
	int m_screenHeight;
	int m_screenWidth;
};

