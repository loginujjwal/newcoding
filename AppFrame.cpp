#include "AppFrame.hpp"
#include <wx/statline.h>

enum {
    ID_ADD = 1,
    ID_SEARCH,
    ID_SHOW_ALL
};

wxBEGIN_EVENT_TABLE(AppFrame, wxFrame)
    EVT_BUTTON(ID_ADD, AppFrame::OnAdd)
    EVT_BUTTON(ID_SEARCH, AppFrame::OnSearch)
    EVT_BUTTON(ID_SHOW_ALL, AppFrame::OnShowAll)
wxEND_EVENT_TABLE()

AppFrame::AppFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(900, 600)) {

    SetMinSize(wxSize(900, 600));

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColour("#f5f5f5")); 

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticBoxSizer* formBox = new wxStaticBoxSizer(wxVERTICAL, panel, "Add Lost & Found Item");
    wxGridSizer* formGrid = new wxGridSizer(2, 5, 5);

    idCtrl = new wxTextCtrl(panel, wxID_ANY);
    nameCtrl = new wxTextCtrl(panel, wxID_ANY);
    categoryCtrl = new wxTextCtrl(panel, wxID_ANY);
    dateCtrl = new wxTextCtrl(panel, wxID_ANY);
    locationCtrl = new wxTextCtrl(panel, wxID_ANY);

    wxColour textBg = *wxWHITE;
    wxColour textFg = wxColour("#333333");

    idCtrl->SetBackgroundColour(textBg); idCtrl->SetForegroundColour(textFg);
    nameCtrl->SetBackgroundColour(textBg); nameCtrl->SetForegroundColour(textFg);
    categoryCtrl->SetBackgroundColour(textBg); categoryCtrl->SetForegroundColour(textFg);
    dateCtrl->SetBackgroundColour(textBg); dateCtrl->SetForegroundColour(textFg);
    locationCtrl->SetBackgroundColour(textBg); locationCtrl->SetForegroundColour(textFg);

    formGrid->Add(new wxStaticText(panel, wxID_ANY, "ID:"), 0, wxALIGN_CENTER_VERTICAL);
    formGrid->Add(idCtrl, 1, wxEXPAND);
    formGrid->Add(new wxStaticText(panel, wxID_ANY, "Name:"), 0, wxALIGN_CENTER_VERTICAL);
    formGrid->Add(nameCtrl, 1, wxEXPAND);
    formGrid->Add(new wxStaticText(panel, wxID_ANY, "Category:"), 0, wxALIGN_CENTER_VERTICAL);
    formGrid->Add(categoryCtrl, 1, wxEXPAND);
    formGrid->Add(new wxStaticText(panel, wxID_ANY, "Date (YYYY-MM-DD):"), 0, wxALIGN_CENTER_VERTICAL);
    formGrid->Add(dateCtrl, 1, wxEXPAND);
    formGrid->Add(new wxStaticText(panel, wxID_ANY, "Location:"), 0, wxALIGN_CENTER_VERTICAL);
    formGrid->Add(locationCtrl, 1, wxEXPAND);

    formBox->Add(formGrid, 0, wxEXPAND | wxALL, 5);

    wxButton* addBtn = new wxButton(panel, ID_ADD, "Add Item");
    addBtn->SetBackgroundColour(wxColour("#007acc")); 
    addBtn->SetForegroundColour(*wxWHITE);
    formBox->Add(addBtn, 0, wxALIGN_RIGHT | wxALL, 5);

    mainSizer->Add(formBox, 0, wxEXPAND | wxALL, 10);

    // Separator
    wxStaticLine* line1 = new wxStaticLine(panel, wxID_ANY);
    mainSizer->Add(line1, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

    // Search Section
    wxBoxSizer* searchSizer = new wxBoxSizer(wxHORIZONTAL);
    searchIdCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    searchIdCtrl->SetBackgroundColour(textBg);
    searchIdCtrl->SetForegroundColour(textFg);

    wxButton* searchBtn = new wxButton(panel, ID_SEARCH, "Search");
    wxButton* showAllBtn = new wxButton(panel, ID_SHOW_ALL, "Show All Items");

    searchBtn->SetBackgroundColour(wxColour("#007acc"));
    searchBtn->SetForegroundColour(*wxWHITE);
    showAllBtn->SetBackgroundColour(wxColour("#007acc"));
    showAllBtn->SetForegroundColour(*wxWHITE);

    searchSizer->Add(new wxStaticText(panel, wxID_ANY, "Search by ID:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    searchSizer->Add(searchIdCtrl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    searchSizer->Add(searchBtn, 0);
    searchSizer->AddStretchSpacer();
    searchSizer->Add(showAllBtn, 0);

    mainSizer->Add(searchSizer, 0, wxEXPAND | wxALL, 10);

    // Grid Table
    grid = new wxGrid(panel, wxID_ANY);
    grid->CreateGrid(0, 5);
    grid->SetColLabelValue(0, "ID");
    grid->SetColLabelValue(1, "Name");
    grid->SetColLabelValue(2, "Category");
    grid->SetColLabelValue(3, "Date");
    grid->SetColLabelValue(4, "Location");
    grid->EnableEditing(false);
    grid->SetLabelBackgroundColour(wxColour("#e6f0fa"));
    grid->SetLabelTextColour(*wxBLACK);
    grid->SetLabelFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    grid->AutoSizeColumns();

    mainSizer->Add(grid, 1, wxEXPAND | wxALL, 10);

    panel->SetSizer(mainSizer);
    Centre();
}

void AppFrame::OnAdd(wxCommandEvent&) {
    Item item;
    item.id = idCtrl->GetValue().ToStdString();
    item.name = nameCtrl->GetValue().ToStdString();
    item.category = categoryCtrl->GetValue().ToStdString();
    item.date = dateCtrl->GetValue().ToStdString();
    item.location = locationCtrl->GetValue().ToStdString();

    if (item.id.empty() || item.name.empty()) {
        wxMessageBox("ID and Name are required.", "Input Error", wxICON_ERROR);
        return;
    }

    hashTable.addItem(item);
    wxMessageBox("Item added successfully!", "Success", wxICON_INFORMATION);

    idCtrl->Clear();
    nameCtrl->Clear();
    categoryCtrl->Clear();
    dateCtrl->Clear();
    locationCtrl->Clear();
}

void AppFrame::OnSearch(wxCommandEvent&) {
    string id = searchIdCtrl->GetValue().ToStdString();
    if (id.empty()) {
        wxMessageBox("Please enter an ID to search.", "Input Required", wxICON_WARNING);
        return;
    }

    Item* item = hashTable.searchItem(id);
    if (item) {
        wxString result = "ID: " + item->id + "\nName: " + item->name +
                          "\nCategory: " + item->category + "\nDate: " + item->date +
                          "\nLocation: " + item->location;
        wxMessageBox(result, "Item Found", wxICON_INFORMATION);
    } else {
        wxMessageBox("Item not found.", "Result", wxICON_WARNING);
    }
}

void AppFrame::OnShowAll(wxCommandEvent&) {
    grid->ClearGrid();
    if (grid->GetNumberRows() > 0)
        grid->DeleteRows(0, grid->GetNumberRows());

    vector<Item> items = hashTable.getAllItems();
    if (!items.empty())
        grid->AppendRows(items.size());

    int row = 0;
    for (const auto& item : items) {
        grid->SetCellValue(row, 0, item.id);
        grid->SetCellValue(row, 1, item.name);
        grid->SetCellValue(row, 2, item.category);
        grid->SetCellValue(row, 3, item.date);
        grid->SetCellValue(row, 4, item.location);
        row++;
    }

    grid->AutoSizeColumns();
}
