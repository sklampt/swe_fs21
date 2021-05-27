#include "MainGamePanel.h"
#include "gui/uiElements/ImagePanel.h"
#include "gui/GameController.h"


MainGamePanel::MainGamePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(960, 680)) {
}


void MainGamePanel::buildGameState(Game* game, Player* me) {

    // TODO: UNPACK GAME STATE INFO
    std::vector<int>* scores = nullptr;
    std::vector<std::string>* names = nullptr;
    std::vector<std::string>* dice = nullptr;
    std::vector<std::string>* colors = nullptr;

    //set background color
    wxColor white = wxColor(252, 210, 153);
    this->SetBackgroundColour(white);

    // remove any existing UI
    this->DestroyChildren();

    //preparation for text generation
    int numberOfPlayers = names->size();
    double anglePerPlayer = MainGamePanel::twoPi / (double) numberOfPlayers;


    //Display player names and scores
    for (int i = 0; i < numberOfPlayers; i++){
        double playerAngle = (double) i * anglePerPlayer;

        double horizontalRadius = MainGamePanel::otherPlayerHandDistanceFromCenter * 1.4; // 1.4 to horizontally elongate players' circle
        double verticalRadius = MainGamePanel::otherPlayerHandDistanceFromCenter;

        // get this player's position on that ellipse
        wxPoint handPosition = MainGamePanel::tableCenter;
        handPosition += this->getPointOnEllipse(horizontalRadius, verticalRadius, playerAngle);

        long textAlignment = wxALIGN_CENTER;

        this->buildStaticText(
                names->at(i),
                handPosition,
                wxSize(200, 18),
                textAlignment,
                true
        );

        this->buildStaticText(
                "score: " + std::to_string(scores->at(i)),
                handPosition + *(new wxPoint(0, 15)),
                wxSize(200, 18),
                textAlignment,
                false
        );
    }

    //Display "Dice thrown text"
    long textAlignment = wxALIGN_CENTER;
    this->buildStaticText(
            "Dice thrown:",
            MainGamePanel::thrownTextPos,
            wxSize(200, 18),
            textAlignment,
            true
    );


    // Display dice
    int n_dice = dice->size();

    for (int i = 0; i < n_dice; i++){
        std::string fileName = "assets/" + dice->at(i) + "_" + colors->at(i) + ".png";
        wxPoint offset = wxPoint((i / 3) * MainGamePanel::dieOffsetX, (i % 3) * MainGamePanel::dieOffsetY);
        ImagePanel* die = new ImagePanel(this, fileName, wxBITMAP_TYPE_ANY, MainGamePanel::uppermostDie + offset, MainGamePanel::dieSize);
    }


    //Build Buttons
    wxButton* throwButton = new wxButton(this, wxID_ANY, "Throw Again", MainGamePanel::throwAgainPos, MainGamePanel::buttonSize);
    throwButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        // GameController::connectToServer();
    });

    wxButton* stopButton = new wxButton(this, wxID_ANY, "End Turn", MainGamePanel::stopTurnPos, MainGamePanel::buttonSize);
    stopButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        // GameController::connectToServer();
    });

    //std::string linePNG = "assets/vertical_line.png";
    //ImagePanel* line = new ImagePanel(this, linePNG, wxBITMAP_TYPE_ANY, MainGamePanel::linePos, MainGamePanel::lineSize);



}



wxStaticText* MainGamePanel::buildStaticText(std::string content, wxPoint position, wxSize size, long textAlignment, bool bold) {
    wxStaticText* staticText = new wxStaticText(this, wxID_ANY, content, position, size, textAlignment);
    if(bold) {
        wxFont font = staticText->GetFont();
        font.SetWeight(wxFONTWEIGHT_BOLD);
        staticText->SetFont(font);
    }
    return staticText;
}

wxSize MainGamePanel::getBoundsOfRotatedSquare(double edgeLength, double rotationAngle) {
    double newEdgeLength = this->getEdgeLengthOfRotatedSquare(edgeLength, rotationAngle);
    return wxSize(newEdgeLength, newEdgeLength);
}


double MainGamePanel::getEdgeLengthOfRotatedSquare(double originalEdgeLength, double rotationAngle) {
    return originalEdgeLength * (abs(sin(rotationAngle)) + abs(cos(rotationAngle)));
}


wxPoint MainGamePanel::getPointOnEllipse(double horizontalRadius, double verticalRadius, double angle) {
    return wxPoint((int) (sin(angle) * horizontalRadius), (int) (cos(angle) * verticalRadius));
}
