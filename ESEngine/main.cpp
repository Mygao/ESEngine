#include <iostream>

#include "physics_engine.h"

int main(int argc, const char** argv)
{
	PhysicsEngine* physics_engine = new PhysicsEngine();

	physics_engine->CreateWorld();
	physics_engine->DestroyWorld();

	delete physics_engine;

	return 0;
}