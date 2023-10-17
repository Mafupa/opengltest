#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>

GLFWwindow* window; 

class Entity {
public:
	float xPosition;
	float yPosition;
	float moveSpeed;

	Entity(float x = 0.0f, float y = 0.0f, float speed = 0.05f)
		: xPosition(x), yPosition(y), moveSpeed(speed) {}

	virtual void update(float deltaTime) {} // Virtual function for updating
	virtual void render() {} // Virtual function for rendering
};



class Player : public Entity {
public:
	Player(float x = 0.0f, float y = 0.0f, float speed = 0.05f) 
		: Entity(x, y, speed) {}

	void move(float dx, float dy) {
		xPosition += dx * moveSpeed;
		yPosition += dy * moveSpeed;
	}

	void update(float deltaTime) override {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			yPosition += 0.5f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			xPosition -= 0.5f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			yPosition -= 0.5f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			xPosition += 0.5f * deltaTime;
		//printf("[%f, %f]\n", xPosition, yPosition);
	}

	void render() override {
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
		glVertex2f(xPosition - 0.05f, yPosition - 0.05f);
		glVertex2f(xPosition + 0.05f, yPosition - 0.05f);
		glVertex2f(xPosition + 0.05f, yPosition + 0.05f);
		glVertex2f(xPosition - 0.05f, yPosition + 0.05f);
		glEnd();
	}
};

class Enemy : public Entity {
public:

	Enemy(float x = 0.0f, float y = 0.0f, float speed = 0.03f)
		: Entity(x, y, speed) {}

	void moveRandomly() {
		// Generate random values for movement
		float dx = static_cast<float>(rand() % 3 - 1);  // Random value in range [-1, 1]
		float dy = static_cast<float>(rand() % 3 - 1);

		xPosition += dx * moveSpeed;
		yPosition += dy * moveSpeed;
	}
	void update(float deltaTime) override {}

	void render() override {
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f); // Red color
		glVertex2f(xPosition - 0.05f, yPosition - 0.05f);
		glVertex2f(xPosition + 0.05f, yPosition - 0.05f);
		glVertex2f(xPosition + 0.05f, yPosition + 0.05f);
		glVertex2f(xPosition - 0.05f, yPosition + 0.05f);
		glEnd();
	}
};


class ECS {
public:
	std::vector<Entity*> entities;

	void update(float deltaTime) {
		for (auto& entity : entities) {
		entity->update(deltaTime);
		}
	}

	void render() {
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto& entity : entities) {
		entity->render();
		}
	}
};

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	window = glfwCreateWindow(800, 600, "ECS Cube", nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		std::cerr << "Failed to create GLFW window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	ECS ecs;

	Player playerEntity(0.0f, 0.0f, 0.1f);
	ecs.entities.push_back(&playerEntity);

	// Create enemy entities
	Enemy enemy1Entity(-0.2f, 0.3f, 0.02f);
	Enemy enemy2Entity(0.4f, -0.1f, 0.03f);
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
		elapsedTime += frameDuration.count();
		frameCount++;
		if (elapsedTime >= 1.0f) {
			fps = static_cast<float>(frameCount) / elapsedTime;
			frameCount = 0;
			elapsedTime = 0.0f;
			system("clear");
			std::cout << "FPS : " << fps << std::endl;
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
