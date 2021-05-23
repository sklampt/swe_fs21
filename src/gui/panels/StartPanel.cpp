//
// Created by pete on 20.05.21.
//

#include "StartPanel.h"


#include "../uiElements/ImagePanel.h"
//#include "../../common/network/default.conf"     ->not yet available
#include "../GameController.h"

int default_port = 5050;

StartPanel::StartPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {

    wxColor white = wxColor(252, 210, 153);
    this->SetBackgroundColour(white);

    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);

    ImagePanel* logo = new ImagePanel(this, "assets/zombiedice_logo_nobackground.png", wxBITMAP_TYPE_ANY, wxDefaultPosition, wxSize(800, 275));
    verticalLayout->Add(logo, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);

    this->_portField = new InputField(
            this, // parent element
            "Server port:", // label
            100, // width of label
            wxString::Format("%i", default_port), // default value (variable from "default.conf")
            240 // width of field
    );
    verticalLayout->Add(this->_portField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

    this->_playerNameField = new InputField(
            this, // parent element
            "Player name:", // label
            100, // width of label
            "", // default value
            240 // width of field
    );
    verticalLayout->Add(this->_playerNameField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

    wxButton* connectButton = new wxButton(this, wxID_ANY, "Connect", wxDefaultPosition, wxSize(100, 40));
    connectButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        //GameController::connectToServer(); -> not yet implemented
    });
    wxButton* hostButton = new wxButton(this, wxID_ANY, "Host new lobby", wxDefaultPosition, wxSize(150, 40));
    connectButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        //GameController::connectToServer(); -> not yet implemented
    });
    verticalLayout->Add(connectButton, 0, wxALIGN_RIGHT | wxALL, 10);
    verticalLayout->Add(hostButton, 0, wxALIGN_RIGHT | wxALL, 10);

    this->SetSizerAndFit(verticalLayout);
}


wxString StartPanel::getPort() {
    return this->_portField->getValue();
}


wxString StartPanel::getPlayerName() {
    return this->_playerNameField->getValue();
}
