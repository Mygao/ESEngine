#include <iostream>

#include "base/message_thread.h"

int main(int argc, const char** argv)
{
	base::MessageThread oMessageThread("test");

	oMessageThread.Start();

	char a;
	std::cin >> a;

	oMessageThread.Stop();

	return 0;
}