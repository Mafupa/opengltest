#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <string>
#include "Entity.h"

GLFWwindow* window; 

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	window = glfwCreateWindow(800, 800, "ECS Cube", nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		std::cerr << "Failed to create GLFW window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	ECS ecs;

	// Create player
	Player playerEntity(0.0f, 0.0f, 0.5f);
	ecs.entities.push_back(&playerEntity);

	// Create enemy entities
	Enemy enemy1Entity(-0.2f, 0.3f, 0.3f);
	Enemy enemy2Entity(0.4f, -0.1f, 0.3f);
	enemy2Entity.target = &playerEntity;
	enemy1Entity.target = &playerEntity;
	ecs.entities.push_back(&enemy1Entity);
	ecs.entities.push_back(&enemy2Entity);

	std::chrono::steady_clock::time_point frameStart, frameEnd;
	float deltaTime = 0.0f, elapsedTime = 0.0f, fps = 0.0f;
	int frameCount = 0;

	while (!glfwWindowShouldClose(window)) {
		frameStart = std::chrono::steady_clock::now();
		
		ecs.update(deltaTime);
		ecs.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
		frameEnd = std::chrono::steady_clock::now();
		std::chrono::duration<float> frameDuration =
			std::chrono::duration_cast<std::chrono::duration<float>>(frameEnd - frameStart);
		deltaTime = frameDuration.count();
		elapsedTime += deltaTime;
		frameCount++;
		if (elapsedTime >= 1.0f) {
			fps = static_cast<float>(frameCount) / elapsedTime;
			frameCount = 0;
			elapsedTime = 0.0f;
			if (0)
				std::cout << "FPS : " << fps << std::endl;
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
