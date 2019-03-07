#include "View.h"

#include <iostream>

#include "Zombie.h"
#include <glm/glm.hpp>

View::View()
{
}

View::~View()
{
}

//View needs a reference to everything we want to draw. we'll pass them all with init. We'll also create a window and initialise shader/spritebatch/camera here.
void View::init(Player* player, int screenwidth, int screenheight)
{
	m_SOL_window.create("Zom", screenwidth, screenheight, 0);

	m_SOL_shaderProgram.compileShaders("Shaders/colourShading.vert", "Shaders/colourShading.frag");
	m_SOL_shaderProgram.addAttribute("vertexPosition");
	m_SOL_shaderProgram.addAttribute("vertexColour");
	m_SOL_shaderProgram.addAttribute("vertexUV");
	m_SOL_shaderProgram.linkShaders();

	m_SOL_agentSpriteBatch.init();

	m_SOL_cam.init(screenwidth, screenheight);

	p_player = player;

	p_player->setCamera(&m_SOL_cam);
}

void View::update(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets)
{
	//Camera follows player
	m_SOL_cam.setPosition(p_player->getPosition());

	m_SOL_cam.update();

	drawGame(humans, zombies, levels, bullets);
}

void View::drawGame(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets)
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
	glm::mat4 projectionMatrix = m_SOL_cam.getCameraMatrix();
	GLint pUniform = m_SOL_shaderProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//Draw level
	levels[m_currentLevel]->draw();

	m_SOL_agentSpriteBatch.begin();

	glm::vec2 agentDims(AGENT_RADIUS * 2.0f);

	//Draw humans
	for (size_t i = 0; i < humans.size(); i++)
	{
		if (m_SOL_cam.isBoxInView(humans[i]->getPosition(), agentDims))
		{
			humans[i]->draw(m_SOL_agentSpriteBatch);
		}
	}
	
	//Draw zombies
	for (size_t i = 0; i < zombies.size(); i++)
	{
		if (m_SOL_cam.isBoxInView(zombies[i]->getPosition(), agentDims))
		{
			zombies[i]->draw(m_SOL_agentSpriteBatch);
		}
	}

	//Draw bullets
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].draw(m_SOL_agentSpriteBatch);
	}

	// called agent sprite batch but not just for agents
	m_SOL_agentSpriteBatch.end();

	m_SOL_agentSpriteBatch.renderBatch();

	m_SOL_shaderProgram.unuse();

	m_SOL_window.swapBuffer();
}

void View::scale(float scaleSpeed)
{
	m_SOL_cam.setScale(m_SOL_cam.getScale() + scaleSpeed);
}
