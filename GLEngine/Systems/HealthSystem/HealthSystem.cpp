#include "pch.h"
#include "HealthSystem.h"
#include "../../Components/HealthComponents/HealthComponent.h"

void HealthSystem::setHealth(int _entityID, int _health, int _maxhealth)
{
	HealthManager.getComponent(_entityID).mCurrentHealth = _health;
	HealthManager.getComponent(_entityID).mMaxHealth = _maxhealth ;
}

void HealthSystem::getHealth(int _entityID)
{
	std::cout << "Current Health: " << HealthManager.getComponent(_entityID).mCurrentHealth << std::endl;
}

void HealthSystem::giveHealth(int _entityID, int _health)
{
	HealthManager.getComponent(_entityID).mCurrentHealth += _health;
}

void HealthSystem::takeDamage(int _damageTaker, int _damage)
{
	HealthManager.getComponent(_damageTaker).mCurrentHealth -= _damage;
}
