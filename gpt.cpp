#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Entity {
public:
    float xPosition;
    float yPosition;
    float moveSpeed;

    Entity(float x = 0.0f, float y = 0.0f, float speed = 0.05f)
        : xPosition(x), yPosition(y), moveSpeed(speed) {}

    virtual void update() {} // Virtual function for updating
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

    void render() override {
        // Draw the yellow square at the player's position
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
        glBegin(GL_QUADS);
        glVertex2f(xPosition - 0.1f, yPosition - 0.1f);
        glVertex2f(xPosition + 0.1f, yPosition - 0.1f);
        glVertex2f(xPosition + 0.1f, yPosition + 0.1f);
        glVertex2f(xPosition - 0.1f, yPosition + 0.1f);
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

    void render() override {
        // Draw the red square at the enemy's position
        glColor3f(1.0f, 0.0f, 0.0f); // Red color
        glBegin(GL_QUADS);
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

    void update() {
        /*for (auto& entity : entities) {
            // Process input, update logic, etc.
	    entity->update();
        }*/
    }

    void render() {
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto entity : entities) {
		entity->render();
        }
    }
};

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "ECS Cube", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    ECS ecs;

    Player playerEntity(0.0f, 0.0f, 0.05f);
    ecs.entities.push_back(&playerEntity);

    // Create enemy entities
    Enemy enemy1Entity(-0.2f, 0.3f, 0.02f);
    Enemy enemy2Entity(0.4f, -0.1f, 0.03f);
    ecs.entities.push_back(&enemy1Entity);
    ecs.entities.push_back(&enemy2Entity);

    while (!glfwWindowShouldClose(window)) {
        ecs.update();
        ecs.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

