#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ICamera.h"

#include <unordered_map>

namespace Solengine
{
	class Camera2D : public ICamera
	{
	public:
		Camera2D();
		~Camera2D();

		void Init(int screenWidth, int screenHeight);
		void Update();

		glm::vec2 ScreenToWorld(glm::vec2 screenCoords);

		bool IsBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

		//Setters
		void SetPosition(const glm::vec2& newPosition) { glm::vec2 adjust = { 20.0f, 20.0f }; m_pos = newPosition + adjust; m_needsMatrixUpdate = true; }
		void SetScale(float newScale) { if (newScale > m_maxZoomOut && newScale < m_maxZoomIn) m_scale = newScale; m_needsMatrixUpdate = true; }
		void ShiftPosition(glm::vec2 shiftQuantity) { m_pos.x += shiftQuantity.x; m_pos.y += shiftQuantity.y;  m_needsMatrixUpdate = true; }

		//Getters
		glm::vec2 GetPosition() { return m_pos; }
		float GetScale() { return m_scale; }
		glm::mat4 GetProjectionMatrix() { return m_projectionMatrix; }

	private:
		int m_screenWidth, m_screenHeight;
		float m_maxZoomIn, m_maxZoomOut;
		bool m_needsMatrixUpdate;
		float m_scale;
		glm::vec2 m_pos;   //two floats
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_orthoMatrix;
	};

	/// Position and scale change the projection matrix
/// At its core, all a camera object does is create a projection matrix.
/// A camera component should
/// Obtain projection matrix from camera component on gameobject
/// updating a camera component simply makes the component recalculate its projection matrix
/// if the camera hasn't moved or changed scale, its projection matrix remains the same

	//class Camera 
	//{
	//public:
	//	Camera(Transform2D* transf, glm::vec2 screenDimensions)
	//	{
	//		screenSize = screenDimensions;
	//		glm::ortho(0.0f, screenDimensions.x, 0.0f, screenDimensions.y);
	//		transform = transf;
	//	};

	//	Transform2D* transform;

	//	glm::mat4 projectionMatrix;
	//	glm::mat4 orthoMatrix;
	//	glm::vec2 screenSize;

	//	glm::vec2 prevPos{ 0, 0 }; /// previous position of camera
	//	float prevScale{ 0 }; /// previous scale of camera

	//	glm::mat4 GetProjectionMatrix()
	//	{
	//		return projectionMatrix;
	//	}

	//	void Update() /// modifies position and scale based on transform
	//	{
	//		if (transform != nullptr)
	//		{
	//			glm::vec2 pos = transform->Pos;
	//			float scale = transform->Scale;

	//			if (prevPos != pos || prevScale != scale)
	//			{
	//				glm::vec3 translationVec(-pos.x + screenSize.x / 2, -pos.y + screenSize.y / 2, 0.0f);
	//				projectionMatrix = glm::translate(orthoMatrix, translationVec);
	//				glm::vec3 scaleVec(scale, scale, 0.0f);
	//				projectionMatrix *= glm::scale(glm::mat4(1.0f), scaleVec);

	//				prevPos = pos;
	//				prevScale = scale;
	//			}
	//		}
	//	}
	//};

	//class TransformComponent
	//{
	//public:
	//	glm::vec2 Pos;
	//	float Scale;

	//	void Update() {};
	//};

	///// new GameObject obj
	///// obj.Components.push_back(new Transform2D);
	//
	//class GraphicsComponent
	//{
	//public:
	//	GraphicsComponent(Camera* cam)
	//	{
	//		RenderCamera = cam;
	//	}

	//	Camera* RenderCamera;

	//	void Draw()
	//	{
	//		if (!m_isVisible || m_textureID == -1) return;

	//		if (m_redraw)
	//		{
	//			const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	//			glm::vec4 destRect(m_pos.x, m_pos.y, m_width, m_height);

	//			p_SOL_S->Draw(destRect, uvRect, m_textureID, 0.0f, m_colour);
	//			p_SOL_S->End();
	//			p_SOL_S->Render();

	//			m_redraw = false;
	//		}
	//		else p_SOL_S->Render();
	//	}
	//};

	//class GameObject
	//{
	//public:
	//	GameObject(Camera* cam) 
	//	{
	//		if (cam != nullptr)
	//		{
	//			Graphics = new GraphicsComponent(cam);
	//		}
	//	}

	//	TransformComponent* Transform;
	//	GraphicsComponent* Graphics;
	//	ColliderComponent* Collider;

	//};

	//class ColliderComponent
	//{

	//};

	//class IGameWorld
	//{
	//public:
	//};

	//class MyGameWorld : IGameWorld
	//{
	//public:
	//	std::unordered_map<std::string, GameObject> GameObjectsMap;
	//};

	//void draw(IGameWorld* gw)
	//{
	//	//Set base depth
	//	glClearDepth(1.0);
	//	//Clear colour and depth buffer
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	//start the shader program
	//	m_SOL_shaderProgram.Use();
	//	//DrawCode, optional? Tells it to use texture unit 0
	//	glActiveTexture(GL_TEXTURE0);
	//	//Shader uses texture 0
	//	GLint textureUniform = m_SOL_shaderProgram.GetUniformLocation("mySampler");
	//	glUniform1i(textureUniform, 0);

	//	glm::mat4 projectionMatrix;
	//	GLint pUniform = m_SOL_shaderProgram.GetUniformLocation("P");

	//	for (size_t i = 0; i++; i < gw->GameObjects.size())
	//	{
	//		if (GameObjects.Graphics != nullptr)
	//		{
	//			glm::mat4 newMatrix = gw->GameObjects[i].Graphics->RenderCam.GetProjectionMatrix();
	//			if (newMatrix != projectionMatrix)
	//			{
	//				projectionMatrix = newMatrix;
	//				glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	//			}

	//			gw->GameObjects[i].Graphics.Draw();
	//		}
	//	}

	//	m_SOL_shaderProgram.Unuse();
	//	m_SOL_window.SwapBuffer();
	//}
}
