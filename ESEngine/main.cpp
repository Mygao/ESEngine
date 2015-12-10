#include <iostream>

#include "base/message_thread.h"
#include "btBulletDynamicsCommon.h"

int main(int argc, const char** argv)
{
	btDefaultCollisionConfiguration* collisionConf =
		new btDefaultCollisionConfiguration();

	delete collisionConf;

	return 0;
}