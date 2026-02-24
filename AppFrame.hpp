#ifndef APPFRAME_HPP
#define APPFRAME_HPP

#include <wx/wx.h>
#include "HashTable.hpp"
#include <wx/grid.h>

class AppFrame : public wxFrame {
public:
    AppFrame(const wxString& title);

private:
    HashTable hashTable;
    

    // Input Fields
    wxTextCtrl *idCtrl, *nameCtrl, *categoryCtrl, *dateCtrl, *locationCtrl, *searchIdCtrl;
    wxGrid* grid;

    void OnAdd(wxCommandEvent& event);
    void OnSearch(wxCommandEvent& event);
    void OnShowAll(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif
