#include <iostream>

#include "base/MessageThread.h"

int main(int argc, const char** argv)
{
	base::MessageThread oMessageThread("test");

	oMessageThread.Start();

	char a;
	std::cin >> a;

	oMessageThread.Stop();

	return 0;
}