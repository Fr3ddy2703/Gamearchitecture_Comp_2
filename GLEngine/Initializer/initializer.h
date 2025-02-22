#pragma once
#include "../Camera/camera.h"
#include "../Meshes/Sphere/Spheres.h"
#include "../Meshes/Cubes/Cubes.h"
#include "../Actor/Actor.h"
#include "../Components/HealthComponents/HealthComponent.h"
#include "../Components/ComponentManager.h"

class HealthSystem;
class HealthComponent;
class ElementBuffer;
class VertexBuffer;
struct GLFWwindow;

class initializer
{
public:

	/* Public variables*/
	GLFWwindow *window;
	static camera UseCamera;
	static float DeltaTime;
	Cube Floor;
	Cube Wall;
	Cube Wall2;
	Cube Wall3;
	Cube Wall4;

	
	/* Public Functions */
	initializer(){};

	virtual void Initialize();
	virtual void Create();
	virtual void Run();
	virtual void Update(float deltaTime);

	virtual  ~initializer();


private:
	/* private Shared Pointers */
	std::vector<Cube> Cubes; 
	std::vector<Spheres> Balls;
	std::shared_ptr<Player> player;
	std::shared_ptr<Enemy> enemy;
	std::shared_ptr<Item> item;

	/* private variables */
	bool irender = true;
	bool prender = true;
	bool erender = true;
};

