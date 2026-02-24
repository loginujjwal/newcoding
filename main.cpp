#include <wx/wx.h>
#include "AppFrame.hpp"

class LostAndFoundApp : public wxApp {
public:
    virtual bool OnInit() {
        AppFrame *frame = new AppFrame("Lost and Found Tracker");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(LostAndFoundApp);
