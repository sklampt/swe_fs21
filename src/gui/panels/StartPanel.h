#ifndef ZOMBIEDICE_STARTPANEL_H
#define ZOMBIEDICE_STARTPANEL_H


#include <wx/wx.h>
#include "../uiElements/InputField.h"


class StartPanel : public wxPanel {
public:
    StartPanel(wxWindow* parent);

    wxString getPort();
    wxString getPlayerName();
    wxString getAddress();

private:
    InputField* _portField;
    InputField* _playerNameField;
    InputField* _serverAddressField;

    unsigned long getPortAsLong();
};

#endif //ZOMBIEDICE_STARTPANEL_H
