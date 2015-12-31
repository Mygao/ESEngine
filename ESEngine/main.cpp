#include <iostream>

#include "physics_engine.h"
#include "ui/win_window.h"

int main(int argc, const char** argv)
{
	PhysicsEngine* physics_engine = new PhysicsEngine();

	physics_engine->CreateWorld();
	physics_engine->DestroyWorld();

	delete physics_engine;

	ui::WinWindow oWnd;
	ui::WinWindow::CreateParams params;
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = 640;
	rect.bottom = 480;
	params.bound = rect;

	oWnd.Create(&params);

	std::cout << "Wait For Input." << std::endl;
	char a;
	std::cin >> a;

	oWnd.Destroy();
	std::cout << "Window Destroyed." << std::endl;

	return 0;
}