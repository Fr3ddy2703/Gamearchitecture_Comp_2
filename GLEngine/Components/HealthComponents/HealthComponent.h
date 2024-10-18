#pragma once
#include "../Components.h"

class HealthComponent : public Components
{
public:
	/* Public variables */
	int mCurrentHealth = 100;
	int mMaxHealth = 100;

	HealthComponent() = default;

};
