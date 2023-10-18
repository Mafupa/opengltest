#include "Entity.h"

extern GLFWwindow* window; 


// Entity
Entity::Entity(float x, float y, float speed)
		: position(Vector2(x, y)), moveSpeed(speed) {}

void Entity::update(float deltaTime) {}
void Entity::render() {}


// Player
Player::Player(float x, float y, float speed) 
		: Entity(x, y, speed) {}

void Player::move(float dx, float dy) {
	position.x += dx * moveSpeed;
	position.y += dy * moveSpeed;
}

void Player::update(float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position.y += moveSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position.x -= moveSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position.y -= moveSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position.x += moveSpeed * deltaTime;
}
	
void Player::render(){
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
	glVertex2f(position.x - 0.05f, position.y - 0.05f);
	glVertex2f(position.x + 0.05f, position.y - 0.05f);
	glVertex2f(position.x + 0.05f, position.y + 0.05f);
	glVertex2f(position.x - 0.05f, position.y + 0.05f);
	glEnd();
}


// Enemy
Enemy::Enemy(float x, float y, float speed)
	: Entity(x, y, speed) {}

void Enemy::changeDirectionRandomly() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(0.0f, 2 * 3.14159f);
	float randomAngle = distribution(gen);
	direction.x += std::cos(randomAngle);
	direction.y += std::sin(randomAngle);
	behaviourCounter += rand() % 5;
}
void Enemy::update(float deltaTime){
	position.x += direction.x * moveSpeed * deltaTime;
	position.y += direction.y * moveSpeed * deltaTime;
	position.x = std::max(-1.0f, std::min(position.x, 1.0f));
	position.y = std::max(-1.0f, std::min(position.y, 1.0f));
	if (target != NULL) {
		float distance = std::sqrt((target->position.x - position.x)*(target->position.x - position.x) +
			(target->position.x - position.x)*(target->position.x - position.x));
		if (distance < 0.5f) {
			moveSpeed = 0.49f; 
			direction.x = target->position.x - position.x;
			direction.y = target->position.y - position.y;
			direction = direction.normalize();
		}
		else {
			moveSpeed = 0.2f; 
			behaviourCounter -= deltaTime;
			if (behaviourCounter <= 0.0f)
				changeDirectionRandomly();
		}
	}
}

void Enemy::render(){
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex2f(position.x - 0.05f, position.y - 0.05f);
	glVertex2f(position.x + 0.05f, position.y - 0.05f);
	glVertex2f(position.x + 0.05f, position.y + 0.05f);
	glVertex2f(position.x - 0.05f, position.y + 0.05f);
	glEnd();
}


// ECS
void ECS::update(float deltaTime) {
	for (auto& entity : entities) {
		entity->update(deltaTime);
	}
}

void ECS::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& entity : entities) {
		entity->render();
	}
}


