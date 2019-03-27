#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Solengine 
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);
		void update();

		glm::vec2 screenToWorld(glm::vec2 screenCoords);

		bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

		//Setters
		void setPosition(const glm::vec2& newPosition) { glm::vec2 adjust = { 20.0f, 20.0f }; m_position = newPosition + adjust; m_needsMatrixUpdate = true; }
		void setScale(float newScale) { if (newScale > m_maxZoomOut && newScale < m_maxZoomIn) m_scale = newScale; m_needsMatrixUpdate = true; }
		void shiftPosition(glm::vec2 shiftQuantity) { m_position.x += shiftQuantity.x; m_position.y += shiftQuantity.y;  m_needsMatrixUpdate = true; }

		//Getters
		glm::vec2 getPosition() { return m_position; }
		float getScale() { return m_scale; }
		glm::mat4 getCameraMatrix() { return m_cameraMatrix; }

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
