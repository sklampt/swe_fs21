#include "GameController.h"
#include "network/ClientNetworkManager.h"


// initialize static members
GameWindow* GameController::_gameWindow = nullptr;
ConnectionPanel* GameController::_connectionPanel = nullptr;
MainGamePanel* GameController::_mainGamePanel = nullptr;
StartPanel* GameController::_startPanel = nullptr;


//test vectors for MainGamePanel
std::vector<std::string> names{"kusi", "petra", "mike", "miguel"};
std::vector<int> scores{1,2,3,4};


void GameController::init(GameWindow* gameWindow) {

    GameController::_gameWindow = gameWindow;

    // Set up main panels
    GameController::_connectionPanel = new ConnectionPanel(gameWindow);
    GameController::_mainGamePanel = new MainGamePanel(gameWindow);
    GameController::_startPanel = new StartPanel(gameWindow);

    // Hide all panels
    GameController::_connectionPanel->Show(false);
    GameController::_mainGamePanel->Show(false);
    GameController::_startPanel->Show(false);

    GameController::_mainGamePanel->buildGameState(&scores, &names);

    // Only show connection panel at the start of the game
    GameController::_gameWindow->showPanel(GameController::_mainGamePanel);

    // Set status bar
    //GameController::showStatus("Not connected");     ->not yet available
}