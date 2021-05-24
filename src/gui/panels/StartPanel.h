//
// Created by pete on 22.05.21.
//

#ifndef ZOMBIEDICE_STARTPANEL_H
#define ZOMBIEDICE_STARTPANEL_H


#include <wx/wx.h>
#include "../uiElements/InputField.h"


class StartPanel : public wxPanel {
public:
    StartPanel(wxWindow* parent);

    wxString getPort();
    wxString getPlayerName();

private:
    InputField* _portField;
    InputField* _playerNameField;

};

#endif //ZOMBIEDICE_STARTPANEL_H
