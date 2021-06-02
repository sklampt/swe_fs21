#include "ConnectionPanel.h"


#include "../uiElements/ImagePanel.h"
#include "../GameController.h"

ConnectionPanel::ConnectionPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {

    wxColor white = wxColor(255, 255, 255);
    this->SetBackgroundColour(white);

    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);
   
    ImagePanel* logo = new ImagePanel(
            this,
            "assets/zombiedice_logo_nobackground.png",
            wxBITMAP_TYPE_ANY, wxDefaultPosition,
            wxSize(200, 250)
            );
    verticalLayout->Add(logo, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);

    this->_serverAddressField = new InputField(
        this, // parent element
        "Server address:", // label
        100, // width of label
        "127.0.0.1", //default_server_host, // default value (variable from "default.conf")
        240 // width of field
    );
    verticalLayout->Add(this->_serverAddressField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

    this->_serverPortField = new InputField(
        this, // parent element
        "Server port:", // label
        100, // width of label
        wxString::Format("%i", "12345"), // default value (variable from "default.conf")
        240 // width of field
    );
    verticalLayout->Add(this->_serverPortField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

    this->_playerNameField = new InputField(
        this, // parent element
        "Player name:", // label
        100, // width of label
        "", // default value
        240 // width of field
    );
    verticalLayout->Add(this->_playerNameField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

    this->SetSizerAndFit(verticalLayout);
}


wxString ConnectionPanel::getServerAddress() {
    return this->_serverAddressField->getValue();
}


wxString ConnectionPanel::getServerPort() {
    return this->_serverPortField->getValue();
}


wxString ConnectionPanel::getPlayerName() {
    return this->_playerNameField->getValue();
}
