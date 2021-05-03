#include <gui/network/ClientNetworkManager.h>
#include <common/network/requests/client_join_lobby_request.h>
#include "GameController.h"


// initialize static members
GameWindow* GameController::_gameWindow = nullptr;
ConnectionPanel* GameController::_connectionPanel = nullptr;
MainGamePanel* GameController::_mainGamePanel = nullptr;



void GameController::init(GameWindow* gameWindow) {

    GameController::_gameWindow = gameWindow;

    // Set up main panels
    GameController::_connectionPanel = new ConnectionPanel(gameWindow);
    GameController::_mainGamePanel = new MainGamePanel(gameWindow);

    // Hide all panels
    GameController::_connectionPanel->Show(false);
    GameController::_mainGamePanel->Show(false);

    // Only show connection panel at the start of the game
    GameController::_gameWindow->showPanel(GameController::_connectionPanel);
}

void GameController::connectToServer() {

    // get values form UI input fields
    wxString inputServerAddress = GameController::_connectionPanel->getServerAddress().Trim();
    wxString inputServerPort = GameController::_connectionPanel->getServerPort().Trim();
    wxString inputPlayerName = GameController::_connectionPanel->getPlayerName().Trim();

    // check that all values were provided
    if(inputServerAddress.IsEmpty()) {
        GameController::showError("Input error", "Please provide the server's address");
        return;
    }
    if(inputServerPort.IsEmpty()) {
        GameController::showError("Input error", "Please provide the server's port number");
        return;
    }
    if(inputPlayerName.IsEmpty()) {
        GameController::showError("Input error", "Please enter your desired player name");
        return;
    }

    // convert host from wxString to std::string
    std::string host = inputServerAddress.ToStdString();

    // convert port from wxString to uint16_t
    unsigned long portAsLong;
    if(!inputServerPort.ToULong(&portAsLong) || portAsLong > 65535) {
        GameController::showError("Connection error", "Invalid port");
        return;
    }
    uint16_t port = (uint16_t) portAsLong;

    // convert player name from wxString to std::string
    std::string playerName = inputPlayerName.ToStdString();

    // connect to network
    ClientNetworkManager::init(host, port);

    // send request to join game
    //GameController::_me = new Player(playerName);
    //client_join_lobby_request request = client_join_lobby_request(GameController::_me->get_id(), GameController::_me->get_player_name());
    //ClientNetworkManager::sendRequest(request);

}

void GameController::updateGameState(Game* newGameState) {

    // the existing game state is now old
    // Game* oldGameState = GameController::_currentGameState;

    // save the new game state as our current game state
    //GameController::_currentGameState = newGameState;

    // if(oldGameState != nullptr) {

        // check if a new round started, and display message accordingly
        // if(oldGameState->get_round_number() > 0 && oldGameState->get_round_number() < newGameState->get_round_number()) {
        //     GameController::showNewRoundMessage(oldGameState, newGameState);
        // }

        // delete the old game state, we don't need it anymore
    //    delete oldGameState;
    // }

    // if(GameController::_currentGameState->is_finished()) {
    //     GameController::showGameOverMessage();
    // }

    // make sure we are showing the main game panel in the window (if we are already showing it, nothing will happen)
    GameController::_gameWindow->showPanel(GameController::_mainGamePanel);

    // command the main game panel to rebuild itself, based on the new game state
    // GameController::_mainGamePanel->buildGameState(GameController::_currentGameState, GameController::_me);
}

void GameController::startGame() {
    // client_update_game_request request = client_update_game_request(GameController::_currentGameState->get_id(), GameController::_me->get_id());
    // ClientNetworkManager::sendRequest(request);
}

wxEvtHandler* GameController::getMainThreadEventHandler() {
    return GameController::_gameWindow->GetEventHandler();
}


void GameController::showError(const std::string& title, const std::string& message) {
    wxMessageBox(message, title, wxICON_ERROR);
}


void GameController::showStatus(const std::string& message) {
    GameController::_gameWindow->setStatus(message);
}