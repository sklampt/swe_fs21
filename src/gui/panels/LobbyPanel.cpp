#include "LobbyPanel.h"

#include "../uiElements/ImagePanel.h"
#include "../GameController.h"
// ../../common/network/default.conf missing -> ok?


LobbyPanel::LobbyPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    
    wxColor white = wxColor(252, 210, 153);
    this->SetBackgroundColour(white);

    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);
   
    ImagePanel* logo = new ImagePanel(this, "assets/zombiedice_logo_nobackground.png", wxBITMAP_TYPE_ANY, wxDefaultPosition, wxSize(200, 250));
    verticalLayout->Add(logo, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);


    this->_displayMeLHS = new wxStaticText(
            "You:",
            wxDefaultPosition,
            wxSize(200, 18),
            textAlignment,
            true
    );
    verticalLayout->Add(this->_displayMeLHS, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);

    this->_displayMeRHS = new wxStaticText(
            me->get_player_name(),
            wxDefaultPosition,
            wxSize(200, 18),
            textAlignment,
            true
    );
    verticalLayout->Add(this->_displayMeLHS, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);

    this->_displayOtherPlayersLHS = new wxStaticText(
            "Other players:",
            wxDefaultPosition,
            wxSize(200, 18),
            textAlignment,
            true
    );
    verticalLayout->Add(this->_displayMeLHS, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);

    /*
    for(int i = 0; i < players.size(); i++) {
        player* playerState = players.at(i);
        std::string playerName = playerState->get_player_name();

        if(playerState->get_id() != GameController::_me->get_id()) {
            this->_displayOtherPlayersRHS = new wxStaticText(
                    otherPlayer->get_player_name(),
                    wxDefaultPosition,
                    wxSize(200, 18),
                    textAlignment,
                    true
            );
            verticalLayout->Add(this->_displayMeLHS, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);
        }
    }
    */

    wxButton* connectButton = new wxButton(this, wxID_ANY, "Start", wxDefaultPosition, wxSize(100, 40));
    connectButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        GameController::connectToServer();
    });
    verticalLayout->Add(connectButton, 0, wxALIGN_RIGHT | wxALL, 10);
}


    
/*
for(int i = 0; i < players.size(); i++) {

        player* playerState = players.at(i);
        std::string scoreText = std::to_string(playerState->get_score());

        // first entry is the winner
        std::string winnerText = "";
        if(i == 0) {
            winnerText = "     Winner!";
        }

        std::string playerName = playerState->get_player_name();
        if(playerState->get_id() == GameController::_me->get_id()) {
            playerName = "You";

            if(i == 0) {
                winnerText = "     You won!!!";
            }
        }
        message += "\n" + playerName + ":     " + scoreText + winnerText;
    }
*/