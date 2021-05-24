#include "GameController.h"
#include "network/ClientNetworkManager.h"


// initialize static members
GameWindow* GameController::_gameWindow = nullptr;
ConnectionPanel* GameController::_connectionPanel = nullptr;
MainGamePanel* GameController::_mainGamePanel = nullptr;
// StartPanel* GameController::_startPanel = nullptr;
LobbyPanel* GameController::_lobbyPanel = nullptr;



void GameController::init(GameWindow* gameWindow) {

    GameController::_gameWindow = gameWindow;

    // Set up main panels
    GameController::_connectionPanel = new ConnectionPanel(gameWindow);
    GameController::_mainGamePanel = new MainGamePanel(gameWindow);
    // GameController::_startPanel = new StartPanel(gameWindow);
    GameController::_lobbyPanel = new LobbyPanel(gameWindow);

    // Hide all panels
    GameController::_connectionPanel->Show(false);
    GameController::_mainGamePanel->Show(false);
    // GameController::_startPanel->Show(false);
    GameController::_lobbyPanel->Show(false);

    // Only show connection panel at the start of the game
    // GameController::_gameWindow->showPanel(GameController::_startPanel);
    GameController::_gameWindow->showPanel(GameController::_lobbyPanel);


    // Set status bar
    //GameController::showStatus("Not connected");     ->not yet available
}