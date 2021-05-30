#ifndef ZOMBIEDICE_LOBBYPANEL_H
#define ZOMBIEDICE_LOBBYPANEL_H

#include <wx/wx.h>
#include <wx/grid.h>
#include "../uiElements/InputField.h"
#include <vector>
#include <string>
#include <common/game/Game.h>


class LobbyPanel : public wxPanel {

public:
    LobbyPanel(wxWindow* parent);

    void buildLobby(Game *Game, Player *Player);

private:
    wxGrid* _displayText;
    wxStaticText* _displayMeLHS;
    wxStaticText* _displayMeRHS;
    wxStaticText* _displayOtherPlayersRHS;
    wxStaticText* _displayOtherPlayersLHS;

    // static const std::vector<std::string> players;
};


#endif //ZOMBIEDICE_LOBBYPANEL_H