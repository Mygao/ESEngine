#include "win_window.h"

namespace ui {

WinWindow::WinWindow()
	: hwnd_(NULL), msg_thread_(0)
{

}

WinWindow::~WinWindow()
{

}

void WinWindow::Create(CreateParams* params)
{
	msg_thread_ = new std::thread(&WinWindow::ThreadMain, this, params);
}

void WinWindow::Destroy()
{
	msg_thread_->join();
	DestroyWindow(hwnd_);
}

void WinWindow::ThreadMain(void* arg)
{
	CreateParams* params = static_cast<CreateParams*>(arg);
	const char* class_name = "DeviceWin32";

	HINSTANCE h_instance = GetModuleHandle(0);

	//Register Class
	WNDCLASSEX wnd_class;
	wnd_class.cbSize = sizeof(wnd_class);
	wnd_class.style = CS_HREDRAW | CS_VREDRAW;
	wnd_class.lpfnWndProc = WndProc;
	wnd_class.cbClsExtra = 0;
	wnd_class.cbWndExtra = 0;
	wnd_class.hInstance = h_instance;
	wnd_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wnd_class.lpszMenuName = "MainMenu";
	wnd_class.lpszClassName = class_name;
	wnd_class.hIconSm = 0;

	BOOL register_result = RegisterClassEx(&wnd_class);

	DWORD style = WS_OVERLAPPEDWINDOW;

	int x, y, width, height;

	x = params->bound.left;
	y = params->bound.top;
	width = params->bound.right - x;
	height = params->bound.bottom - y;


	hwnd_ = ::CreateWindow(class_name, "", style, x, y, width, height,
		NULL, NULL, h_instance, NULL);

	if (!hwnd_)
	{
		return;
	}

	ShowWindow(hwnd_, SW_SHOW);
	UpdateWindow(hwnd_);
	MSG msg;
	BOOL outer_loop = TRUE;

	while (outer_loop)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				outer_loop = FALSE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
}

//static
LRESULT CALLBACK WinWindow::WndProc(HWND window,
									UINT message,
									WPARAM w_param,
									LPARAM l_param)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(window, &ps);
			EndPaint(window, &ps);
		}
		return 1;

	case WM_ERASEBKGND:
		return 1;

	default:
		break;
	}

	return DefWindowProc(window, message, w_param, l_param);
}


}