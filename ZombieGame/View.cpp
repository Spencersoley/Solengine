#include "View.h"

#include <iostream>

#include "Zombie.h"

View::View()
{
}

View::~View()
{
}

void View::init(std::vector<Level*>* levels, std::vector<Human*>* humans, std::vector<Zombie*>* zombies, std::vector<Bullet>* bullets, Player* player, float screenwidth, float screenheight)
{
	_SOL_window.create("Zom", screenwidth, screenheight, 0);

	_SOL_shaderProgram.compileShaders("Shaders/colourShading.vert", "Shaders/colourShading.frag");
	_SOL_shaderProgram.addAttribute("vertexPosition");
	_SOL_shaderProgram.addAttribute("vertexColour");
	_SOL_shaderProgram.addAttribute("vertexUV");
	_SOL_shaderProgram.linkShaders();

	_SOL_agentSpriteBatch.init();

	_SOL_cam.init(screenwidth, screenheight);

	//game object pointers
	_levels = levels;
	_humans = humans;
	_zombies = zombies;
	_bullets = bullets;
	_player = player;
}

void View::update(glm::vec2 playerPos)
{
	//Camera follows player

	_SOL_cam.setPosition(playerPos);

	_SOL_cam.update();

	drawGame();
}

void View::drawGame()
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
	(*_levels)[_currentLevel]->draw();

	_SOL_agentSpriteBatch.begin();

	glm::vec2 agentDims(AGENT_RADIUS * 2.0f);

	//Draw humans
	for (size_t i = 0; i < _humans->size(); i++)
	{
		if (_SOL_cam.isBoxInView((*_humans)[i]->getPosition(), agentDims))
		{
			(*_humans)[i]->draw(_SOL_agentSpriteBatch);
		}
	}
	
	//Draw zombies
	for (size_t i = 0; i < _zombies->size(); i++)
	{
		if (_SOL_cam.isBoxInView((*_zombies)[i]->getPosition(), agentDims))
		{
			(*_zombies)[i]->draw(_SOL_agentSpriteBatch);
		}
	}

	//Draw bullets
	for (size_t i = 0; i < _bullets->size(); i++)
	{
		(*_bullets)[i].draw(_SOL_agentSpriteBatch);
	}

	// called agent sprite batch but not just for agents
	_SOL_agentSpriteBatch.end();

	_SOL_agentSpriteBatch.renderBatch();

	_SOL_shaderProgram.unuse();

	_SOL_window.swapBuffer();
}
