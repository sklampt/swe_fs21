#include "MainGamePanel.h"
#include "gui/uiElements/ImagePanel.h"
#include "gui/GameController.h"


MainGamePanel::MainGamePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(960, 680)) {
}


void MainGamePanel::buildGameState(Game* game, Player* me) {

    // Test vectors for MainGamePanel
    //    std::vector<std::string> names{"kusi", "petra", "mike", "miguel"};
    //    std::vector<int> scores{1,2,3,4};
    //    std::vector<std::string> dice{
    //            "bomb", "brain", "footsteps",
    //            "brain", "brain", "brain"
    //    };
    //    std::vector<std::string> colors{
    //            "red", "green", "yellow",
    //            "red", "red", "red"
    //    };

    // Unpack Player names and scores
    std::vector<int> scores;
    std::vector<std::string> names;
    for (auto player : game->get_players()) {
        scores.push_back(player->get_score());
        names.push_back(player->get_player_name());
    }

    // Unpack current turn information if current_turn exists else create empty vectors
    std::vector<Die *> current_hand;
    std::vector<Die *> brains;
    std::vector<Die *> footprints;
    std::vector<Die *> shotguns;
    if(game->_current_turn) {
        current_hand = game->get_current_turn()->getCurrentHand();
        brains = game->get_current_turn()->getBrains();
        footprints = game->get_current_turn()->getFootprints();
        shotguns = game->get_current_turn()->getShotguns();
    } else {
        // No current_turn is available create empty vectors
        current_hand = std::vector<Die *>();
        brains = std::vector<Die *>();
        footprints = std::vector<Die *>();
        shotguns = std::vector<Die *>();
    }


    //set background color
    wxColor white = wxColor(252, 210, 153);
    this->SetBackgroundColour(white);

    // remove any existing UI
    this->DestroyChildren();

    //preparation for text generation
    int numberOfPlayers = names.size();
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
                names.at(i),
                handPosition,
                wxSize(200, 18),
                textAlignment,
                true
        );

        this->buildStaticText(
                "score: " + std::to_string(scores.at(i)),
                handPosition + *(new wxPoint(0, 15)),
                wxSize(200, 18),
                textAlignment,
                false
        );
    }

    //Display "Current throw:"
    long textAlignment = wxALIGN_CENTER;
    this->buildStaticText(
            "Current throw:",
            MainGamePanel::thrownTextPos,
            wxSize(200, 18),
            textAlignment,
            true
    );

    //Display "Dice set aside"
    this->buildStaticText(
            "Dice set aside:",
            MainGamePanel::thrownTextPos + wxPoint(120, 0),
            wxSize(200, 18),
            textAlignment,
            true
    );


    // Display dice
    int n_dice = current_hand.size();

    for (int i = 0; i < n_dice; i++){
        std::string fileName = "assets/" + current_hand.at(i)->get_face_as_string() + "_" + current_hand.at(i)->get_color_as_string() + ".png";
        wxPoint offset = wxPoint((i / 3) * MainGamePanel::dieOffsetX, (i % 3) * MainGamePanel::dieOffsetY);
        ImagePanel* die = new ImagePanel(this, fileName, wxBITMAP_TYPE_ANY, MainGamePanel::uppermostDie + offset, MainGamePanel::dieSize);
    }

    //Display already thrown brains
    int n_brains = brains.size();
    for (int i = 0; i < n_brains; i++){
        std::string fileName = "assets/" + brains.at(i)->get_face_as_string() + "_" + brains.at(i)->get_color_as_string() + ".png";
        wxPoint offset = wxPoint(0, i * MainGamePanel::dieOffsetY);
        ImagePanel* die = new ImagePanel(this, fileName, wxBITMAP_TYPE_ANY, MainGamePanel::brainsPos + offset, MainGamePanel::dieSize);
    }

    //Display already thrown shotguns
    int n_shotguns = shotguns.size();
    for (int i = 0; i < n_shotguns; i++){
        std::string fileName = "assets/" + shotguns.at(i)->get_face_as_string() + "_" + shotguns.at(i)->get_color_as_string() + ".png";
        wxPoint offset = wxPoint(0, (i % 3) * MainGamePanel::dieOffsetY);
        ImagePanel* die = new ImagePanel(this, fileName, wxBITMAP_TYPE_ANY, MainGamePanel::shotgunsPos + offset, MainGamePanel::dieSize);
    }

    //Build Buttons
    wxButton* throwButton = new wxButton(this, wxID_ANY, "Throw Dice", MainGamePanel::throwAgainPos, MainGamePanel::buttonSize);
    throwButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        GameController::clientGameAction("throw");
    });

    wxButton* stopButton = new wxButton(this, wxID_ANY, "End Turn", MainGamePanel::stopTurnPos, MainGamePanel::buttonSize);
    stopButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        GameController::clientGameAction("endturn");
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
