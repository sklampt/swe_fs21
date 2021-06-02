#ifndef ZOMBIEDICE_GUI_GAMEWINDOW_H
#define ZOMBIEDICE_GUI_GAMEWINDOW_H

#include "gui/panels/ConnectionPanel.h"


class GameWindow : public wxFrame
{
public:
    GameWindow(const wxString& title, const wxPoint& pos, const wxSize& size);

    void showPanel(wxPanel* panel);
    void setStatus(const std::string& message);

private:
    wxBoxSizer* _mainLayout;
    wxStatusBar* _statusBar;

    wxPanel* _currentPanel;

};


#endif //ZOMBIEDICE_GUI_GAMEWINDOW_H
