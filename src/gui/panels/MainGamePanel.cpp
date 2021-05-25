#include "MainGamePanel.h"
#include "gui/uiElements/ImagePanel.h"
#include "gui/GameController.h"


MainGamePanel::MainGamePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(960, 680)) {
}


void MainGamePanel::buildGameState(std::vector<int>* scores, std::vector<std::string>* names){

    //set background color
    wxColor white = wxColor(252, 210, 153);
    this->SetBackgroundColour(white);

    // remove any existing UI
    this->DestroyChildren();

    //preparation for text generation
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

        this->buildStaticText(
                "score: " + std::to_string(scores->at(i)),
                handPosition + *(new wxPoint(0, 15)),
                wxSize(200, 18),
                textAlignment,
                false
        );
    }

    std::string diePNG = "assets/bomb_red.png";

    ImagePanel* testDie = new ImagePanel(this, diePNG, wxBITMAP_TYPE_ANY, MainGamePanel::tableCenter, MainGamePanel::dieSize);

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
