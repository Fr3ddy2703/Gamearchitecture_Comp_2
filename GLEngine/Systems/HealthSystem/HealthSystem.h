#pragma once
#include "../Systems.h"

class HealthComponent;


class HealthSystem : Systems
{

public:
	ComponentManager<HealthComponent> HealthManager;
	HealthSystem() = default;

	void setHealth(int _entityID, int _health, int _maxhealth);
	void getHealth(int _entityID);

	void giveHealth(int _entityID, int _health);
	void takeDamage(int _damageTaker, int _damage);
};

