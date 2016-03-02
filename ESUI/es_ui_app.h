#ifndef ES_UI_APP_H_
#define ES_UI_APP_H_

#include <wx/wx.h>

class ESUIApp : public wxApp
{
public:
	ESUIApp() : wxApp() {}
	virtual ~ESUIApp() {}

	virtual bool OnInit();
};

DECLARE_APP(ESUIApp)

#endif //ES_UI_APP_H_