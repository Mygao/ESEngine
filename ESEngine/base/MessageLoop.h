#ifndef BASE_MESSAGELOOP_H_
#define BASE_MESSAGELOOP_H_

namespace base {

class MessageLoop
{
public:
	MessageLoop();
	~MessageLoop();

	void Run();
	void Quit();

private:
	bool m_bQuit;

};

} //namespace base

#endif