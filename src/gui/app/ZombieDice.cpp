#include <wx/wx.h>
#include "ZombieDice.h"
#include "../windows/GameWindow.h"
#include "../GameController.h"

#include "../../server/start_server.h"
#include "common/serialization/token_generator.h"
#include "default.conf"


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

    // Test Server
    start_server("AD7CC04C-3B04-47A0-BDF9-C107F90530B5",
                 token_generator::generate(),
                 default_server_listen_port
                 );


    return true;
}