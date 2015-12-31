#ifndef UI_WIN_WINDOW_H_
#define UI_WIN_WINDOW_H_

#include <thread>
#include <Windows.h>

#include "base/macros.h"
#include "base/thread.h"

namespace ui {

class WinWindow
{
public:
	struct CreateParams
	{
		RECT bound;
	};

	WinWindow();
	virtual ~WinWindow();

	void Create(CreateParams* params);
	void Destroy();

private:
	void ThreadMain(void* arg);
	static LRESULT CALLBACK WndProc(HWND window,
									UINT message,
									WPARAM w_param,
									LPARAM l_param);

	HWND hwnd_;

	std::thread* msg_thread_;
};

} //namespace ui

#endif //UI_WIN_WINDOW_H_