#include <wx/wx.h>
#include "ZombieDice.h"
#include "../windows/GameWindow.h"
#include "../GameController.h"

// Application entry point
bool ZombieDice::OnInit()
{
    // Allow loading of JPEG  and PNG image files
    wxImage::AddHandler(new wxJPEGHandler());
    wxImage::AddHandler(new wxPNGHandler());

    // Open main game window
    GameWindow* gameWindow = new GameWindow(
            "Zombie Dice - Braaainz!", // title of window,
            wxDefaultPosition, // position of the window
            wxDefaultSize // size of the window
    );
    gameWindow->Show(true);

    // Initialize game controller
    GameController::init(gameWindow);


    return true;
}