#include "View.h"

#include "Solengine/ResourceManager.h"

#include <iostream>
#include <glm/glm.hpp>
#include "UIIcon.h"

View::View() {}

View::~View() {}

void View::Init(Solengine::ICamera* cam, Solengine::ICamera* uiCam,
	int screenwidth, int screenheight)
{
	//Creates window
	m_SOL_window.Create("DQ", screenwidth, screenheight, 0);

	//Initialises the shader programs
	m_SOL_shaderProgram.CompileShaders("Shaders/colourShading.vert",
		"Shaders/colourShading.frag");
	m_SOL_shaderProgram.AddAttribute("vertexPosition");
	m_SOL_shaderProgram.AddAttribute("vertexColour");
	m_SOL_shaderProgram.AddAttribute("vertexUV");
	m_SOL_shaderProgram.LinkShaders();

	//Obtain the cameras from the scene and intiialise/position them
	p_SOL_cam = cam;
	cam->Init(screenwidth, screenheight);
	p_SOL_uiCam = uiCam;
	uiCam->Init(screenwidth, screenheight);

	p_SOL_uiCam->SetPosition({ -screenwidth / 2, 0});

	//Stores the screen dimensions
	m_screenHeight = screenheight;
	m_screenWidth = screenwidth;
}

void View::Update(std::vector<Drawable*> worldDrawables,
	std::vector<std::pair<Drawable*, Drawable*>> visualEffectDrawables,
	std::vector<Drawable*> overlayDrawables)
{
	p_SOL_cam->Update();
	drawGame(worldDrawables, visualEffectDrawables, overlayDrawables);
}

void View::drawGame(std::vector<Drawable*> worldDrawables,
	std::vector<std::pair<Drawable*, Drawable*>> visualEffectDrawables,
	std::vector<Drawable*> overlayDrawables)
{
	//Set base depth
	glClearDepth(1.0);
	//Clear colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//start the shader program
	m_SOL_shaderProgram.Use();
	//DrawCode, optional? Tells it to use texture unit 0
	glActiveTexture(GL_TEXTURE0);
	//Shader uses texture 0
	GLint textureUniform = m_SOL_shaderProgram.GetUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// NTS: anything that changes/moves must be redrawn. 
	// Otherwise we simply rerender.

	drawToCamera(worldDrawables, p_SOL_cam);
	drawToCamera(visualEffectDrawables, p_SOL_cam);
	drawToCamera(overlayDrawables, p_SOL_uiCam);

	m_SOL_shaderProgram.Unuse();
	m_SOL_window.SwapBuffer();
}

void View::drawToCamera(std::vector<Drawable*> drawables,
	Solengine::ICamera* cam)
{
	glm::mat4 projectionMatrix = cam->GetCameraMatrix();
	GLint pUniform = m_SOL_shaderProgram.GetUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	for (size_t i = 0; i < drawables.size(); i++)
		if (drawables[i] != nullptr) drawables[i]->Draw();
}

void View::drawToCamera(std::vector<std::pair<Drawable*, Drawable*>> drawablePairs,
	Solengine::ICamera* cam)
{
	glm::mat4 projectionMatrix = cam->GetCameraMatrix();
	GLint pUniform = m_SOL_shaderProgram.GetUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	for (size_t i = 0; i < drawablePairs.size(); i++)
	{
		if (drawablePairs[i].first != nullptr)
			drawablePairs[i].first->Draw();
		if (drawablePairs[i].second != nullptr)
			drawablePairs[i].second->Draw();
	}
}

////
////




