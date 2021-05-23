#ifndef ZOMBIEDICE_LOBBYPANEL_H
#define ZOMBIEDICE_LOBBYPANEL_H

#include <wx/wx.h>
#include <wx/grid.h>
#include "../uiElements/InputField.h"


class LobbyPanel : public wxPanel {

public:
    LobbyPanel(wxWindow* parent);

private:
    wxGrid* _displayText;
    wxStaticText* _displayMeLHS;
    wxStaticText* _displayMeRHS;
    wxStaticText* _displayOtherPlayersRHS;
    wxStaticText* _displayOtherPlayersLHS;

};


#endif //ZOMBIEDICE_LOBBYPANEL_H