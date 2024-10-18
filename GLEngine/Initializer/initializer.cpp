#include "pch.h"
#include "initializer.h"

#include "../Input/input.h"
#include "../Shaders/shader.h"
#include "../Systems/HealthSystem/HealthSystem.h"

float initializer::DeltaTime = 0.f;
camera initializer::UseCamera = camera();

/* Systems */
HealthSystem hs;

void initializer::Initialize()
{
	window = window::initWindow();
	UseCamera.initCamera();

	/* Component manager */
	hs.HealthManager.addComponent(0); /* player */
	hs.HealthManager.addComponent(1); /* enemy */

	hs.setHealth(0, 100, 100); /* Player health */
	hs.setHealth(1, 50, 100); /* Enemy health */

	hs.getHealth(0);
	hs.getHealth(1);

	Run();
}

void initializer::Create()
{
	/* Scene */
	Floor.CreateCube(glm::vec3(18.f, 0.5f, 9.f), glm::vec3(1.f, 0.f, 9.f),Color::Green);

	/* Left wall */
	Wall.CreateCube(glm::vec3(20.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f),Color::Brown);
	Wall.AddCollider(Wall.GetScale(), ECollisionType::Boxes);

	/* Right wall */
	Wall2.CreateCube(glm::vec3(20.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 10.f),Color::Brown);
	Wall2.AddCollider(Wall2.GetScale(), ECollisionType::Boxes);

	/* Front wall */
	Wall3.CreateCube(glm::vec3(-1.f, 1.f, -9.f), glm::vec3(1.f, 0.f, 0.f),Color::Brown);
	Wall3.AddCollider(Wall3.GetScale(), ECollisionType::Boxes);

	/* Back wall */
	Wall4.CreateCube(glm::vec3(1.f, 1.f, -9.f), glm::vec3(19.f, 0.f, 0.f),Color::Brown);
	Wall4.AddCollider(Wall4.GetScale(), ECollisionType::Boxes);

	/* Player */
	player = std::make_shared<Player>();
	player->createPlayer(glm::vec3(0.5f), glm::vec3(10.f, 0.75f, 5.f), Color::Blue);

	/* Enemy */
	enemy = std::make_shared<Enemy>();
	enemy->createEnemy(glm::vec3(0.5f), glm::vec3(10.f, 0.75f, 10.f), Color::Red);

	/* Item */
	item = std::make_shared<Item>();
	item->createItem(glm::vec3(0.25f), 4.f, glm::vec3(15.f, 0.75f, 5.f), 1.f, glm::vec3(0.f, 0.f, 0.f), Color::Gold);

	//Spheres Sphere;
	//Sphere.CreateSphere(glm::vec3(0.25f),4.f, glm::vec3(15.25f, 0.75f, 2.5f), 1.f,glm::vec3(0.f, 0.f, 0.f),Color::Gold);
	//Sphere.AddCollider(Sphere.GetScale(), ECollisionType::ball);

	///* Creating the balls */
	//Spheres kule;
	//kule.CreateSphere(glm::vec3(0.25f),4.f, glm::vec3(15.f, 0.75f, 7.5f), 1.f,glm::vec3(0.f, 0.f, 0.f),Color::Gold);
	//kule.AddCollider(kule.GetScale(), ECollisionType::ball);

	
	Cubes.emplace_back(Floor);
	Cubes.emplace_back(Wall);
	Cubes.emplace_back(Wall2);
	Cubes.emplace_back(Wall3);
	Cubes.emplace_back(Wall4);
	/*Balls.push_back(kule);*/
	//Balls.push_back(Sphere);

}

void initializer::Run()
{
	Create();
	float FirstFrame = 0.0f;
	glm::vec3 color(Color::Grey);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		const auto CurrentFrame = static_cast<float>(glfwGetTime());
		DeltaTime = CurrentFrame - FirstFrame;
		FirstFrame = CurrentFrame;

		glClearColor(color.x, color.y, color.z, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(Shader::ShaderProgram);

		KeyBoardInput::processInput(window, player);
		Update(DeltaTime);


		glUniformMatrix4fv(UseCamera.projectionLoc, 1, GL_FALSE, glm::value_ptr(UseCamera.getProjection(window::width, window::height)));
		glUniformMatrix4fv(UseCamera.viewLoc, 1, GL_FALSE, glm::value_ptr(UseCamera.getView()));
		glUniform3fv(glGetUniformLocation(Shader::ShaderProgram, "viewPos"), 1, glm::value_ptr(UseCamera.cameraPos));
		for (auto& cube : Cubes)
		{
			cube.Draw();
		}
		//for (auto& sphere : Balls)
		//{
		//	sphere.DrawSphere();
		//}
		if (prender)
		{
			player->drawPlayer();
		}

		if (erender)
		{
			enemy->drawEnemy();
		}
		
	if (irender)
	{
		item->drawItem();
	}
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

void initializer::Update(float deltaTime)
{
	Collision collision;
	/* Enemy and player interaction */
	if(collision.checkBoxBoxCollision(player, enemy))
	{
		hs.takeDamage(0, 10);
		hs.takeDamage(1, 30);
		if (hs.HealthManager.getComponent(0).mCurrentHealth <= 0 )
		{
			prender = false;
			std::cout << "Player is dead" << "\n";
		}
		if (hs.HealthManager.getComponent(1).mCurrentHealth <= 0 )
		{
			erender = false;
			std::cout << "Enemy is dead" << std::endl;
		}
		hs.getHealth(0);
		hs.getHealth(1);
		collision.bounceBack(enemy, player, 1.f);
	}

	/* Interaction with the item */
	if (collision.checkPlayerItemCollision(player, item))
	{
		if (glfwGetKey(window, GLFW_KEY_E ))
		{
			irender = false;
			std::cout << "Item Collected" << "\n";
		}
	}
	collision.enemyAI(enemy, player, 1, deltaTime);

}

initializer::~initializer()
{
}
