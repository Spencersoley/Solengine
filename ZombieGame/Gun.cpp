#include "Gun.h"

#include <random>
#include <ctime>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>


Gun::Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletDamage, float bulletSpeed) :
	m_name(name),
	m_fireRate(fireRate),
	m_bulletsPerShot(bulletsPerShot),
	m_spread(spread),
	m_bulletDamage(bulletDamage),
	m_bulletSpeed(bulletSpeed),
	m_frameCounter(0)
{

}

Gun::~Gun()
{
}

void Gun::update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime)
{
	m_frameCounter += deltaTime;
	if (m_frameCounter >= m_fireRate && isMouseDown)
	{
		fire(position, direction, bullets);
		m_frameCounter = 0;
	}
}

void Gun::reload()
{
	if (m_frameCounter < m_fireRate) m_frameCounter++;
}


void Gun::fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets)
{
	static std::mt19937 randomEngine((unsigned int)time(nullptr));
	std::uniform_real_distribution<float> randRotate(-m_spread, m_spread);

	for (int i = 0; i < m_bulletsPerShot; i++)
	{
		bullets.emplace_back(position, glm::rotate(direction, glm::radians(randRotate(randomEngine))), m_bulletDamage, m_bulletSpeed);
	}
}
