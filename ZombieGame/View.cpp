#include "View.h"

#include <iostream>

#include "Zombie.h"

View::View()
{
}

View::~View()
{
}

void View::initShaders()
{
	_SOL_shaderProgram.compileShaders("Shaders/colourShading.vert", "Shaders/colourShading.frag");
	_SOL_shaderProgram.addAttribute("vertexPosition");
	_SOL_shaderProgram.addAttribute("vertexColour");
	_SOL_shaderProgram.addAttribute("vertexUV");
	_SOL_shaderProgram.linkShaders();
}

void View::drawGame(std::vector<Level*> levels, std::vector<Human*> humans, std::vector<Zombie*> zombies, std::vector<Bullet> bullets)
{
	
	//Set base depth
	glClearDepth(1.0);
	//Clear colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_SOL_shaderProgram.use();

	//DrawCode, optional? Tells it to use texture unit 0
	glActiveTexture(GL_TEXTURE0);

	//Shader uses texture 0
	GLint textureUniform = _SOL_shaderProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	//Grab camera matrix
	glm::mat4 projectionMatrix = _SOL_cam.getCameraMatrix();
	GLint pUniform = _SOL_shaderProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//Draw level
	levels[_currentLevel]->draw();


	_SOL_agentSpriteBatch.begin();

	glm::vec2 agentDims(AGENT_RADIUS * 2.0f);

	//Draw humans
	for (size_t i = 0; i < humans.size(); i++)
	{
		if (_SOL_cam.isBoxInView(humans[i]->getPosition(), agentDims))
		{
			humans[i]->draw(_SOL_agentSpriteBatch);
		}
	}
	
	//Draw zombies
	for (size_t i = 0; i < zombies.size(); i++)
	{
		if (_SOL_cam.isBoxInView(zombies[i]->getPosition(), agentDims))
		{
			zombies[i]->draw(_SOL_agentSpriteBatch);
		}
	}

	//Draw bullets
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].draw(_SOL_agentSpriteBatch);
	}

	// called agent sprite batch but not just for agents
	_SOL_agentSpriteBatch.end();

	_SOL_agentSpriteBatch.renderBatch();

	_SOL_shaderProgram.unuse();

	_SOL_window.swapBuffer();
}
