#ifndef ZOMBIEDICE_CLIENT_MAINGAMEPANEL_H
#define ZOMBIEDICE_CLIENT_MAINGAMEPANEL_H

#include <wx/wx.h>
#include <vector>
#include <string>
#include "../../common/game/Die.h"
#include "../../common/game/Player.h"
#include "../../common/game/Game.h"

class MainGamePanel : public wxPanel {

public:
    MainGamePanel(wxWindow* parent);

    void buildGameState(Game* game, Player* me);

private:

    wxStaticText* buildStaticText(std::string content, wxPoint position, wxSize size, long textAlignment, bool bold = false);

    wxSize getBoundsOfRotatedSquare(double edgeLength, double rotationAngle);
    double getEdgeLengthOfRotatedSquare(double originalEdgeLength, double rotationAngle);

    wxPoint getPointOnEllipse(double horizontalRadius, double verticalRadius, double angle);

    // define key constant layout values
    wxSize const panelSize = wxSize(960, 680); // also set in the constructor implementation
    wxPoint const tableCenter = wxPoint(480, 300);
    wxSize const cardSize = wxSize(80, 124);

    double const otherPlayerHandSize = 160.0;
    double const otherPlayerHandDistanceFromCenter = 180.0;
    double const otherPlayerLabelDistanceFromCenter = 275.0;


    wxPoint const discardPileOffset = wxPoint(-84, -42);
    wxPoint const drawPileOffset = wxPoint(4, -42);
    wxPoint const turnIndicatorOffset = wxPoint(-100, 98);

    wxSize const dieSize = wxSize(44,66);
    wxPoint const uppermostDie = wxPoint(30, 50);
    wxPoint const linePos = wxPoint(240, 340);
    wxSize const lineSize = wxSize(547, 680);
    int dieOffsetX = 60;
    int dieOffsetY = 80;
    wxPoint const thrownTextPos = wxPoint(30, 20);
    wxPoint const throwAgainPos = wxPoint(30, 580);
    wxPoint const stopTurnPos = wxPoint(30, 630);
    wxSize const buttonSize = wxSize(100, 40);


    double const twoPi = 6.28318530718;


};


#endif //ZOMBIEDICE_CLIENT_MAINGAMEPANEL_H
