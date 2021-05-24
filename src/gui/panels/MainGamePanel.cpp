#include "MainGamePanel.h"
#include "gui/uiElements/ImagePanel.h"
#include "gui/GameController.h"


MainGamePanel::MainGamePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(960, 680)) {
}


void MainGamePanel::buildGameState(std::vector<int>* scores, std::vector<std::string>* names){

    // remove any existing UI
    //this->DestroyChildren();

    int numberOfPlayers = names->size();

    double anglePerPlayer = MainGamePanel::twoPi / (double) numberOfPlayers;

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
    }
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
