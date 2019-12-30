#include "Camera2D.h"

#include <iostream>

namespace Solengine
{
	Camera2D::Camera2D() :
		m_pos(0.0f, 0.0f),
		m_projectionMatrix(1.0f),
		m_orthoMatrix(1.0f),
		m_scale(1.0f),
		m_needsMatrixUpdate(1),
		m_screenWidth(500),
		m_screenHeight(500),
		m_maxZoomIn(5.0f),
		m_maxZoomOut(0.5f)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::Init(int screenWidth, int screenHeight)
	{
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
		Update();
	}

	void Camera2D::Update()
	{
		if (m_needsMatrixUpdate)
		{
			glm::vec3 translationVec(-m_pos.x + m_screenWidth / 2, -m_pos.y + m_screenHeight / 2, 0.0f);
			m_projectionMatrix = glm::translate(m_orthoMatrix, translationVec);
			glm::vec3 scaleVec(m_scale, m_scale, 0.0f);
			m_projectionMatrix *= glm::scale(glm::mat4(1.0f), scaleVec);

			m_needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::ScreenToWorld(glm::vec2 screenCoords)
	{
		//Invert Y direction
		screenCoords.y = m_screenHeight - screenCoords.y;
		//Converts 0 to centre
		screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		//Scale the coordinates
		screenCoords /= m_scale;
		//Translate with camera;
		screenCoords += m_pos;

		return screenCoords;
	}

	//AABB Camera culling
	bool Camera2D::IsBoxInView(const glm::vec2& position, const glm::vec2& dimensions)
	{
		glm::vec2 scaledScreenDimensions = glm::vec2(m_screenWidth, m_screenHeight) / m_scale;

		const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
		const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

		//Get a vector of the distance between the colliding tile and the agent
		glm::vec2 centrePos = position + dimensions;
		glm::vec2 distVec = centrePos - m_pos;

		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		// If the minimum collision distance is greater than the current distance, we have a collision
		if (xDepth > 0 && yDepth > 0)
		{
			return true;
		}

		return false;
	}
}