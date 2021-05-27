#include "LobbyPanel.h"

#include "../uiElements/ImagePanel.h"
#include "../GameController.h"



LobbyPanel::LobbyPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    
    wxColor white = wxColor(252, 210, 153);
    this->SetBackgroundColour(white);
    this->SetForegroundColour(*wxRED);

    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* horizontalLayout1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* horizontalLayout2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* verticalLayout2 = new wxBoxSizer(wxVERTICAL);
   
    ImagePanel* logo = new ImagePanel(
            this,
            "assets/zombiedice_logo_nobackground.png",
            wxBITMAP_TYPE_ANY,
            wxDefaultPosition,
            wxSize(800, 275)
            );
    verticalLayout->Add(logo, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);

    wxString txt1 = "You:";
    this->_displayMeLHS = new wxStaticText(
            this,
            wxID_ANY,
            txt1,
            wxDefaultPosition,
            wxSize(200, 100),
            wxALIGN_CENTER_HORIZONTAL,
            txt1
    );
    horizontalLayout1->Add(this->_displayMeLHS, 0, wxTOP | wxLEFT | wxRIGHT, 10);

    wxString txt2 = "Me";
    this->_displayMeRHS = new wxStaticText(
            //me->get_player_name(),
            this,
            wxID_ANY,
            txt2,
            wxDefaultPosition,
            wxSize(200, 100),
            wxALIGN_CENTER_HORIZONTAL,
            txt2
    );
    horizontalLayout1->Add(this->_displayMeRHS, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    verticalLayout->Add(horizontalLayout1, 0, wxTOP | wxLEFT | wxRIGHT, 10);


    // display other players
    wxString txt3 = "Other Players:";
    this->_displayOtherPlayersLHS = new wxStaticText(
            this,
            wxID_ANY,
            txt3,
            wxDefaultPosition,
            wxSize(200, 100),
            wxALIGN_CENTER_HORIZONTAL,
            txt3
    );
    horizontalLayout2->Add(this->_displayOtherPlayersLHS, 0, wxTOP | wxLEFT | wxRIGHT, 10);

    // fixed vector with players
    std::vector<std::string> players {
        "Booster",
        "Marco",
        "Robin",
        "Sina",
        "Tarzis"
    };
    std::size_t length = players.size();
    for(int i = 0; i < length; i++) {
        // player* playerState = players.at(i);
        // std::string playerName = playerState->get_player_name();
        // wxString txt4 = playerState->get_player_name();
        // wxString txt4 = players[i];
        // if(playerState->get_id() != GameController::_me->get_id()) {
            this->_displayOtherPlayersRHS = new wxStaticText(
                    this,
                    wxID_ANY,
                    players[i],
                    wxDefaultPosition,
                    wxSize(200, 50),
                    wxALIGN_CENTER_HORIZONTAL,
                    players[i]
            );
            verticalLayout2->Add(this->_displayOtherPlayersRHS, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 0);
        // }
    }
    horizontalLayout2->Add(verticalLayout2, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    verticalLayout->Add(horizontalLayout2, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    

    // button to start game - "link" missing
    wxButton* connectButton = new wxButton(this, wxID_ANY, "Start", wxDefaultPosition, wxSize(100, 40));
    connectButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        // GameController::connectToServer();
    });
    verticalLayout->Add(connectButton, 0, wxALIGN_RIGHT | wxALL, 10);

    this->SetSizerAndFit(verticalLayout);
}


// from Lama how to display players and winners    
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