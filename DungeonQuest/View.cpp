#include "View.h"

#include <iostream>

#include <glm/glm.hpp>

View::View()
{
}

View::~View()
{
}

//View needs a reference to everything we want to draw. we'll pass them all with init. We'll also create a window and initialise shader/spritebatch/camera here.
void View::init(Solengine::Camera2D* cam, Solengine::Camera2D* uiCam, int screenwidth, int screenheight)
{
	m_SOL_window.create("Zom", screenwidth, screenheight, 0);

	m_SOL_shaderProgram.compileShaders("Shaders/colourShading.vert", "Shaders/colourShading.frag");
	m_SOL_shaderProgram.addAttribute("vertexPosition");
	m_SOL_shaderProgram.addAttribute("vertexColour");
	m_SOL_shaderProgram.addAttribute("vertexUV");
	m_SOL_shaderProgram.linkShaders();

	m_SOL_agentSpriteBatch.init();
	m_SOL_uiSpriteBatch.init();

	p_SOL_spriteFont = new Solengine::Font("Fonts/Roboto-Regular.ttf", 64);

	p_SOL_cam = cam;
	cam->init(screenwidth, screenheight);

	p_SOL_uiCam = uiCam;
	uiCam->init(screenwidth, screenheight);

	m_screenHeight = screenheight;
	m_screenWidth = screenwidth;
}

void View::update(std::vector<Level*>& levels)
{
	//Camera follows player
	p_SOL_cam->setPosition(glm::vec2(m_screenWidth / 2, m_screenHeight / 2));
	p_SOL_cam->update();
	p_SOL_uiCam->update();
	p_SOL_uiCam->setPosition(glm::vec2(m_screenWidth / 2, m_screenHeight / 2));
	drawGame(levels);
}

void View::drawGame(std::vector<Level*>& levels)
{
	//Set base depth
	glClearDepth(1.0);
	//Clear colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_SOL_shaderProgram.use();

	//DrawCode, optional? Tells it to use texture unit 0
	glActiveTexture(GL_TEXTURE0);

	//Shader uses texture 0
	GLint textureUniform = m_SOL_shaderProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	//Grab camera matrix
	glm::mat4 projectionMatrix = p_SOL_cam->getCameraMatrix();
	GLint pUniform = m_SOL_shaderProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//Draw level
	levels[m_currentLevel]->draw();

	m_SOL_agentSpriteBatch.begin();

	//draw entities


	// called agent sprite batch but not just for agents
	m_SOL_agentSpriteBatch.end();

	m_SOL_agentSpriteBatch.renderBatch();

	drawUI();

	m_SOL_shaderProgram.unuse();

	m_SOL_window.swapBuffer();
}

void View::drawUI()
{
	char buffer[256];
	//Grab camera matrix
	glm::mat4 projectionMatrix = p_SOL_uiCam->getCameraMatrix();
	GLint pUniform = m_SOL_shaderProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_SOL_uiSpriteBatch.begin();

	sprintf_s(buffer, "GameName");
	p_SOL_spriteFont->draw(m_SOL_uiSpriteBatch, buffer, glm::vec2(30, 56), glm::vec2(0.5f), 0.0f, Solengine::ColourRGBA8{ 255, 255, 255, 255 });

	m_SOL_uiSpriteBatch.end();
	m_SOL_uiSpriteBatch.renderBatch();
}