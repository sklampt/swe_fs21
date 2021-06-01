#ifndef ZOMBIEDICE_STARTPANEL_H
#define ZOMBIEDICE_STARTPANEL_H


#include <wx/wx.h>
#include "../uiElements/InputField.h"


class StartPanel : public wxPanel {
public:
    StartPanel(wxWindow* parent);

    wxString getServerPort();
    wxString getPlayerName();
    wxString getServerAddress();
    void setServerAddress(std::string string);
    void setServerPort(std::string string);

private:
    wxWindow* _parent;

    InputField* _portField;
    InputField* _playerNameField;
    InputField* _serverAddressField;

    void setWindowTitle(std::string title);
};

#endif //ZOMBIEDICE_STARTPANEL_H
