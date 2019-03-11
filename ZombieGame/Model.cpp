#include "Model.h"

#include <Solengine/ErrorHandler.h>

const float ZOMBIE_SPEED = 1.2f;

Model::Model() : m_globalFrameCount(0)
{
}

Model::~Model()
{
}

void Model::init(Player* player, int currentLevel, float gameSpeed)
{
	p_player = player;
	m_currentLevel = currentLevel;
	m_gameSpeed = gameSpeed;
}

void Model::updateModel(int pauseDuration, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets)
{
	m_globalFrameCount++;
	float adjustedDeltaTicks = (getDeltaTicks() - pauseDuration) * m_gameSpeed;
	updateAgents(adjustedDeltaTicks, humans, zombies, levels, bullets);
	updateBullets(adjustedDeltaTicks, humans, zombies, levels, bullets);
}

Uint32 Model::getDeltaTicks()
{
	static Uint32 prevTicks = SDL_GetTicks();
	Uint32 deltaTicks = SDL_GetTicks() - prevTicks;
	prevTicks = SDL_GetTicks();
	return deltaTicks;
}

void Model::updateAgents(float adjustedDeltaTicks, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets)
{
	for (size_t i = 0; i < zombies.size(); i++)
	{
		zombies[i]->move(adjustedDeltaTicks, m_globalFrameCount, humans, zombies);
	}

	p_player->move(adjustedDeltaTicks, humans, zombies, bullets);

	for (size_t i = 1; i < humans.size(); i++)
	{
		//Remember, the player is a human[0]. Player redefines move slightly!
		humans[i]->move(adjustedDeltaTicks, m_globalFrameCount, humans, zombies);
		if (m_globalFrameCount > 359)  m_globalFrameCount = 0;
	}

	//zombie collision
	for (size_t i = 0; i < zombies.size(); i++)
	{
		//zombie level
		zombies[i]->collisionWithLevel(levels[m_currentLevel]->getLevelData());
		//zombie zombie
		for (size_t j = i + 1; j < zombies.size(); j++)
		{
			zombies[i]->collisionWithAgent(zombies[j]);
		}
		//zombie human
		for (size_t j = 1; j < humans.size(); j++)
		{
			if (zombies[i]->collisionWithAgent(humans[j]))
			{
				zombies.push_back(new Zombie);
				zombies.back()->init(ZOMBIE_SPEED, humans[j]->getPosition());
				delete humans[j];
				humans[j] = humans.back();
				humans.pop_back();
			}
		}

		//zombie player (loss condition)
		if (zombies[i]->collisionWithAgent(p_player))
		{
			std::printf("***DEFEAT!***");
			Solengine::fatalError("");
		}
	}

	//human collision
	for (size_t i = 0; i < humans.size(); i++)
	{
		//human level
		humans[i]->collisionWithLevel(levels[m_currentLevel]->getLevelData());
		//human human
		for (size_t j = i + 1; j < humans.size(); j++)
		{
			humans[i]->collisionWithAgent(humans[j]);
		}
	}
}

void Model::updateBullets(float adjustedDeltaTicks, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bool bulletRemoved = false;
		bullets[i].move(adjustedDeltaTicks);

		if (bullets[i].collisionWithWorld(levels[m_currentLevel]->getLevelData()))
		{
			bullets[i] = bullets.back();
			bullets.pop_back();
			i--;
			bulletRemoved = true;
		}

		if (!bulletRemoved)
		{
			for (size_t j = 0; j < zombies.size(); j++)
			{
				if (bullets[i].collisionWithAgent(zombies[j]))
				{
					if (zombies[j]->applyDamage(bullets[i].getDamage()))
					{
						//True on zombie death
						delete zombies[j];
						zombies[j] = zombies.back();
						zombies.pop_back();
						j--;
						//m_numZombiesKilled++;
					}

					//Removes the bullet
					bullets[i] = bullets.back();
					bullets.pop_back();
					i--;
					bulletRemoved = true;

					//Bullet died, no need for more zombie loops
					break;
				}
			}
		}

		if (!bulletRemoved)
		{
			for (size_t j = 1; j < humans.size(); j++)
			{
				if (bullets[i].collisionWithAgent(humans[j]))
				{
					if (humans[j]->applyDamage(bullets[i].getDamage()))
					{
						//Zombie death when this returns true
						delete humans[j];
						humans[j] = humans.back();
						humans.pop_back();
						j--;
						//m_numHumansKilled++;
					}

					//Removes the bullet
					bullets[i] = bullets.back();
					bullets.pop_back();
					i--;
					//Bullet died, no need for more zombie loops
					break;
				}
			}
		}
	}
}