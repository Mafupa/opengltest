#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include "GLFW/glfw3.h"
#include "Vector2.h"

class Entity {
public:
	Vector2 position;
	float moveSpeed;

	Entity(float x = 0.0f, float y = 0.0f, float speed = 0.05f);
	virtual void update(float deltaTime);
	virtual void render();
};



class Player : public Entity {
public:
	Player(float x = 0.0f, float y = 0.0f, float speed = 0.05f);

	void move(float dx, float dy);

	void update(float deltaTime) override;

	void render() override;
};

class Enemy : public Entity {
public:
	Vector2 direction;
	Entity *target = NULL;
	bool hunting = false;
	float behaviourCounter = 0.0f;

	Enemy(float x = 0.0f, float y = 0.0f, float speed = 0.03f);
	
	void changeDirectionRandomly();

	void update(float deltaTime) override;

	void render() override;
};


class ECS {
public:
	std::vector<Entity*> entities;

	void update(float deltaTime);

	void render();
};

#endif
