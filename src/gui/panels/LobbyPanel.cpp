#include "LobbyPanel.h"

#include "../uiElements/ImagePanel.h"
#include "../GameController.h"



LobbyPanel::LobbyPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) { }

void LobbyPanel::buildLobbyState(Game *game, Player *player) {

    wxColor white = wxColor(252, 210, 153);
    this->SetBackgroundColour(white);
    this->SetForegroundColour(*wxRED);

    // remove any existing UI
    this->DestroyChildren();

    wxBoxSizer *verticalLayout = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *horizontalLayout1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *horizontalLayout2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *verticalLayout2 = new wxBoxSizer(wxVERTICAL);

    ImagePanel *logo = new ImagePanel(
            this,
            "assets/zombiedice_logo_nobackground.png",
            wxBITMAP_TYPE_ANY,
            wxDefaultPosition,
            wxSize(800, 275)
    );
    verticalLayout->Add(logo, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);


    wxString txt1 = "You are:"; // Player Label
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

    wxString txt2 = player->get_player_name(); // Player Name
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

    // Check if game exists and is not nullptr
    if (game) {
        // Loop over all players and skip _me
        for (auto lobby_player : game->get_players()) {
            if (lobby_player->get_id() != player->get_id()) {
                // Display player name on list
                wxString player_txt = lobby_player->get_player_name();
                this->_displayOtherPlayersRHS = new wxStaticText(
                        this,
                        wxID_ANY,
                        player_txt,
                        wxDefaultPosition,
                        wxSize(200, 50),
                        wxALIGN_CENTER_HORIZONTAL,
                        player_txt
                );
                verticalLayout2->Add(this->_displayOtherPlayersRHS, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 0);
            }
        }
    }

    horizontalLayout2->Add(verticalLayout2, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    verticalLayout->Add(horizontalLayout2, 0, wxTOP | wxLEFT | wxRIGHT, 10);


    // button to start game - "link" missing
    wxButton *connectButton = new wxButton(this, wxID_ANY, "Start Game", wxDefaultPosition, wxSize(100, 40));
    connectButton->Bind(wxEVT_BUTTON, [](wxCommandEvent &event) {
        GameController::startGame();
    });
    verticalLayout->Add(connectButton, 0, wxALIGN_CENTER | wxALL, 10);

    this->SetSizerAndFit(verticalLayout);

    // Fix repaint issue
    this->GetParent()->SendSizeEvent();


}

