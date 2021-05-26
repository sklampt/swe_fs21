//
// Created by pete on 20.05.21.
//

#include "StartPanel.h"
#include "../../server/start_server.h"
#include "../uiElements/ImagePanel.h"
#include "../GameController.h"

int default_port = 50500;

wxString StartPanel::getAddress() {
    return this->_portField->getValue();
}

wxString StartPanel::getPort() {
    return this->_portField->getValue();
}

wxString StartPanel::getPlayerName() {
    return this->_playerNameField->getValue();
}

unsigned long StartPanel::getPortAsLong() {
    // Convert port wxString to long
    unsigned long portAsLong;
    return this->_portField->getValue().ToULong(&portAsLong);
}

StartPanel::StartPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {

    wxColor white = wxColor(252, 210, 153);
    this->SetBackgroundColour(white);

    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);

    ImagePanel* logo = new ImagePanel(this, "assets/zombiedice_logo_nobackground.png", wxBITMAP_TYPE_ANY, wxDefaultPosition, wxSize(800, 275));
    verticalLayout->Add(logo, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);

    this->_serverAddressField = new InputField(
            this, // parent element
            "Server IP Address:", // label
            100, // width of label
            wxString::Format("%s", "127.0.0.1"), // default value (variable from "default.conf")
            240 // width of field
    );
    verticalLayout->Add(this->_serverAddressField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

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

    wxButton* connectButton = new wxButton(this, wxID_ANY, "CONNECT", wxDefaultPosition, wxSize(100, 50));
    connectButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        //GameController::connectToServer(); -> not yet implemented
    });

    wxButton* hostButton = new wxButton(this, wxID_ANY, "HOST YOUR SERVER", wxDefaultPosition, wxSize(150, 50));
    hostButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        // TODO: Create Host uuid resp. create player object
        // NTH: Make port dynamic maybe
        start_server("8E46D914-6230-4779-A12A-84AE4113E519", default_port);
        GameController::connectToServer();
    });
    verticalLayout->Add(connectButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    verticalLayout->Add(hostButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    this->SetSizerAndFit(verticalLayout);
}

