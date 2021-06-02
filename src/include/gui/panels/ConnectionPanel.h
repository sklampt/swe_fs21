#ifndef ZOMBIEDICE_CONNECTIONPANEL_H
#define ZOMBIEDICE_CONNECTIONPANEL_H

#include <wx/wx.h>
#include "../uiElements/InputField.h"


class ConnectionPanel : public wxPanel {

public:
    ConnectionPanel(wxWindow* parent);

    wxString getServerAddress();
    wxString getServerPort();
    wxString getPlayerName();

private:
    InputField* _serverAddressField;
    InputField* _serverPortField;
    InputField* _playerNameField;

};


#endif //ZOMBIEDICE_CONNECTIONPANEL_H
