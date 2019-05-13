#include "View.h"

#include "Solengine/ResourceManager.h"

#include <iostream>
#include <glm/glm.hpp>
#include "UIIcon.h"

View::View() {}

View::~View() {}

void View::init(Solengine::Camera2D* cam, Solengine::Camera2D* uiCam,
	int screenwidth, int screenheight)
{
	//Creates window
	m_SOL_window.create("DQ", screenwidth, screenheight, 0);

	//Initialises the shader programs
	m_SOL_shaderProgram.compileShaders("Shaders/colourShading.vert",
		"Shaders/colourShading.frag");
	m_SOL_shaderProgram.addAttribute("vertexPosition");
	m_SOL_shaderProgram.addAttribute("vertexColour");
	m_SOL_shaderProgram.addAttribute("vertexUV");
	m_SOL_shaderProgram.linkShaders();

	//Obtain the cameras from the scene and intiialise/position them
	p_SOL_cam = cam;
	cam->init(screenwidth, screenheight);
	p_SOL_uiCam = uiCam;
	uiCam->init(screenwidth, screenheight);

	//Stores the screen dimensions
	m_screenHeight = screenheight;
	m_screenWidth = screenwidth;

}

void View::update(std::vector<Drawable*> worldDrawables, 
	std::vector<Drawable*> visualEffectDrawables,
    std::vector<Drawable*> overlayDrawables)
{
	p_SOL_cam->update();
	p_SOL_uiCam->update();
    p_SOL_uiCam->setPosition(glm::vec2(m_screenWidth / 2, m_screenHeight / 2));
	drawGame(worldDrawables, visualEffectDrawables, overlayDrawables);
}

void View::drawGame(std::vector<Drawable*> worldDrawables, 
    std::vector<Drawable*> visualEffectDrawables,
	std::vector<Drawable*> overlayDrawables)
{
	//Set base depth
	glClearDepth(1.0);
	//Clear colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//start the shader program
	m_SOL_shaderProgram.use();
	//DrawCode, optional? Tells it to use texture unit 0
	glActiveTexture(GL_TEXTURE0);
	//Shader uses texture 0
	GLint textureUniform = m_SOL_shaderProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// NTS: anything that changes/moves must be redrawn. 
	// Otherwise we simply rerender.

	drawToCamera(worldDrawables, p_SOL_cam);
	drawToCamera(visualEffectDrawables, p_SOL_cam);
	drawToCamera(overlayDrawables, p_SOL_uiCam);

	m_SOL_shaderProgram.unuse();
	m_SOL_window.swapBuffer();
}

void View::drawToCamera(std::vector<Drawable*> drawables, 
    Solengine::Camera2D* cam)
{
	glm::mat4 projectionMatrix = cam->getCameraMatrix();
	GLint pUniform = m_SOL_shaderProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	for (size_t i = 0; i < drawables.size(); i++)
		if (drawables[i] != nullptr) drawables[i]->draw();
}



