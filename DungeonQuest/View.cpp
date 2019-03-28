#include "View.h"

#include "Solengine/ResourceManager.h"

#include <iostream>
#include <glm/glm.hpp>

View::View()
{
}

View::~View()
{
	//Since we called new for this, we call delete
	delete p_SOL_spriteFont;
}

//View needs a reference to everything we want to draw. we'll pass them all with init. We'll also create a window and initialise shader/spritebatch/camera here.
void View::init(Solengine::Camera2D* cam, Solengine::Camera2D* uiCam, int screenwidth, int screenheight)
{
	//Creates window
	m_SOL_window.create("DQ", screenwidth, screenheight, 0);

	//Initialises the shader programs
	m_SOL_shaderProgram.compileShaders("Shaders/colourShading.vert", "Shaders/colourShading.frag");
	m_SOL_shaderProgram.addAttribute("vertexPosition");
	m_SOL_shaderProgram.addAttribute("vertexColour");
	m_SOL_shaderProgram.addAttribute("vertexUV");
	m_SOL_shaderProgram.linkShaders();

	//Initialises sprite batches
	m_SOL_agentSpriteBatch.init();
	m_SOL_uiBackgroundSpriteBatch.init();
	m_SOL_uiSpriteBatch.init();

	//Grab the font from the TTF
	p_SOL_spriteFont = new Solengine::Font("Fonts/Roboto-Regular.ttf", 64);

	//Obtain the cameras from the scene and intiialise/position them
	p_SOL_cam = cam;
	cam->init(screenwidth, screenheight);
	p_SOL_uiCam = uiCam;
	uiCam->init(screenwidth, screenheight);
	

	//Stores the screen dimensions
	m_screenHeight = screenheight;
	m_screenWidth = screenwidth;

	//Creates the User Interface background panel
	glm::vec4 destRect(20, 0, m_screenWidth, 150);
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	m_SOL_uiBackgroundSpriteBatch.begin();
	m_SOL_uiBackgroundSpriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, Solengine::ColourRGBA8{ 255, 255, 255, 255 });
	m_SOL_uiBackgroundSpriteBatch.end();
}

void View::update(std::vector<Level*>& levels, std::vector<Unit*>& units)
{
	p_SOL_cam->update();
	p_SOL_uiCam->update();
	p_SOL_uiCam->setPosition(glm::vec2(m_screenWidth / 2, m_screenHeight / 2));
	drawGame(levels, units);
}

void View::drawGame(std::vector<Level*>& levels, std::vector<Unit*>& units)
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
	drawUnits(units);
	m_SOL_agentSpriteBatch.end();

	m_SOL_agentSpriteBatch.renderBatch();

	drawUI(units);

	m_SOL_shaderProgram.unuse();
	m_SOL_window.swapBuffer();
}


void View::drawUnits(std::vector<Unit*>& units)
{
	glm::vec2 agentDims(AGENT_RADIUS * 2.0f);

	//Draw humans
	for (size_t i = 0; i < units.size(); i++)
	{
		//Frustrum culling
		if (p_SOL_cam->isBoxInView(units[i]->getPosition(), agentDims))
		{
			units[i]->draw(m_SOL_agentSpriteBatch);
		}
	}
}


// Ideally: We only modify the uiSpriteBatch when we modify the contents of the information.
// Otherwise, we just want to call renderBatch. In order to do this, we'll have to routinely tell it to update its information.
// For now we can let it do it every frame.
void View::drawUI(std::vector<Unit*>& units)
{
	//char buffer[256];
	//Grab camera matrix
	glm::mat4 projectionMatrix = p_SOL_uiCam->getCameraMatrix();
	GLint pUniform = m_SOL_shaderProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	updateUIText(units);

	//background
	m_SOL_uiBackgroundSpriteBatch.renderBatch();
	//Text
	m_SOL_uiSpriteBatch.renderBatch();
}

// Create a better lower panel UI?
// What information do we want to see?
void View::updateUIText(std::vector<Unit*>& units)
{
	m_SOL_uiSpriteBatch.begin();

	p_SOL_spriteFont->draw(m_SOL_uiSpriteBatch, ("Name: " + units[0]->getName()).c_str(), glm::vec2(40, 100), glm::vec2(0.5f), 0.0f, Solengine::ColourRGBA8{ 255, 255, 255, 255 });
	p_SOL_spriteFont->draw(m_SOL_uiSpriteBatch, ("Health: " + std::to_string(units[0]->getHealth())).c_str(), glm::vec2(40, 60), glm::vec2(0.5f), 0.0f, Solengine::ColourRGBA8{ 255, 255, 255, 255 });
	p_SOL_spriteFont->draw(m_SOL_uiSpriteBatch, ("Energy: " + std::to_string(units[0]->getEnergy())).c_str(), glm::vec2(40, 20), glm::vec2(0.5f), 0.0f, Solengine::ColourRGBA8{ 255, 255, 255, 255 });

	
	m_SOL_uiSpriteBatch.end();
}