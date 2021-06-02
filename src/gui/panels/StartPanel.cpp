//
// Created by pete on 20.05.21.
//

#include "StartPanel.h"
#include "../uiElements/ImagePanel.h"
#include "../GameController.h"


StartPanel::StartPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {

    wxColor white = wxColor(252, 210, 153);
    this->SetBackgroundColour(white);

    // Store window pointer for later use
    this->_parent = parent;

    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);

    ImagePanel* logo = new ImagePanel(
            this,
            "assets/zombiedice_logo_nobackground.png",
            wxBITMAP_TYPE_ANY,
            wxDefaultPosition,
            wxSize(800, 275)
            );
    verticalLayout->Add(logo, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);

    this->_serverAddressField = new InputField(
            this, // parent element
            "Server IP Address:", // label
            100, // width of label
            wxString::Format("%s", "127.0.0.1"),
            240 // width of field
    );
    verticalLayout->Add(this->_serverAddressField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

    this->_portField = new InputField(
            this, // parent element
            "Server port:", // label
            100, // width of label
            "50500",
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
        GameController::connectToServer();
    });

    wxButton* hostButton = new wxButton(this, wxID_ANY, "HOST A SERVER", wxDefaultPosition, wxSize(150, 50));
    hostButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        GameController::createAndConnectToServer();
        StartPanel::setWindowTitle("Zombie Dice - Braaainz! - SERVER MODE");
    });
    verticalLayout->Add(connectButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    verticalLayout->Add(hostButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    this->SetSizerAndFit(verticalLayout);
}

wxString StartPanel::getServerAddress() {
    return this->_serverAddressField->getValue();
}

void StartPanel::setServerAddress(std::string string) {
    this->_serverAddressField->setValue(string);
}

wxString StartPanel::getServerPort() {
    return this->_portField->getValue();
}

void StartPanel::setServerPort(std::string string) {
    this->_portField->setValue(string);
}

wxString StartPanel::getPlayerName() {
    return this->_playerNameField->getValue();
}

void StartPanel::setWindowTitle(std::string title) {
    this->_parent->SetLabel(title);
}

