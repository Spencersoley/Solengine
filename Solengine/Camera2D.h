#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ICamera.h"

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
		void SetPosition(const glm::vec2& newPosition) { glm::vec2 adjust = { 20.0f, 20.0f }; m_position = newPosition + adjust; m_needsMatrixUpdate = true; }
		void SetScale(float newScale) { if (newScale > m_maxZoomOut && newScale < m_maxZoomIn) m_scale = newScale; m_needsMatrixUpdate = true; }
		void ShiftPosition(glm::vec2 shiftQuantity) { m_position.x += shiftQuantity.x; m_position.y += shiftQuantity.y;  m_needsMatrixUpdate = true; }

		//Getters
		glm::vec2 GetPosition() { return m_position; }
		float GetScale() { return m_scale; }
		glm::mat4 GetCameraMatrix() { return m_cameraMatrix; }

	private:
		int m_screenWidth, m_screenHeight;
		float m_maxZoomIn, m_maxZoomOut;
		bool m_needsMatrixUpdate;
		float m_scale;
		glm::vec2 m_position;   //two floats
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;

	};
}
