#include "GameController.h"
#include "network/ClientNetworkManager.h"
#include <common/network/requests/client_join_lobby_request.h>
#include <common/network/requests/client_update_game_request.h>
#include "common/game/Player.h"


// initialize static members
GameWindow* GameController::_gameWindow = nullptr;

Player* GameController::_me = nullptr;
Game* GameController::_currentGame = nullptr;

ConnectionPanel* GameController::_connectionPanel = nullptr;
MainGamePanel* GameController::_mainGamePanel = nullptr;
StartPanel* GameController::_startPanel = nullptr;
LobbyPanel* GameController::_lobbyPanel = nullptr;

//test vectors for MainGamePanel
std::vector<std::string> names{"kusi", "petra", "mike", "miguel"};
std::vector<int> scores{1,2,3,4};
std::vector<std::string> dieFaces{
    "bomb", "brain", "footsteps",
    "brain", "brain", "brain"
};
std::vector<std::string> dieColors{
        "red", "green", "yellow",
        "red", "red", "red"
};

void GameController::init(GameWindow* gameWindow) {

    GameController::_gameWindow = gameWindow;

    // Set up main panels
    GameController::_connectionPanel = new ConnectionPanel(gameWindow);
    GameController::_mainGamePanel = new MainGamePanel(gameWindow);
    GameController::_startPanel = new StartPanel(gameWindow);
    GameController::_lobbyPanel = new LobbyPanel(gameWindow);

    // Hide all panels
    GameController::_connectionPanel->Show(false);
    GameController::_mainGamePanel->Show(false);
    GameController::_startPanel->Show(false);
    GameController::_lobbyPanel->Show(false);

    // Only show connection panel at the start of the game
    GameController::_gameWindow->showPanel(GameController::_startPanel);
    // GameController::_mainGamePanel->buildGameState(&scores, &names, &dieFaces, &dieColors);
    // GameController::_gameWindow->showPanel(GameController::_mainGamePanel);
    // GameController::_gameWindow->showPanel(GameController::_lobbyPanel);

    // Set status bar
    GameController::showStatus("Not connected");
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
    GameController::_me = new Player(playerName);
    client_join_lobby_request request = client_join_lobby_request(GameController::_me->get_id(), GameController::_me->get_player_name());
    ClientNetworkManager::sendRequest(request);

}

void GameController::startGame() {
    client_update_game_request request = client_update_game_request(
            GameController::_currentGame->get_id(),
            GameController::_me->get_id()
            );
    ClientNetworkManager::sendRequest(request);
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

void GameController::showGameOverMessage() {
    std::string title = "Game Over!";
    std::string message = "Final score:\n";
    std::string buttonLabel = "Close Game";

    // sort players by score
    std::vector<Player*> players = GameController::_currentGame->get_players();
    std::sort(players.begin(), players.end(), [](const Player* a, const Player* b) -> bool {
        return a->get_score() < b->get_score();
    });

    // list all players
    for(int i = 0; i < players.size(); i++) {

        Player* playerState = players.at(i);
        std::string scoreText = std::to_string(playerState->get_score());

        // first entry is the winner
        std::string winnerText = "";
        if(i == 0) {
            winnerText = "     Winner!";
        }

        std::string playerName = playerState->get_player_name();
        if(playerState->get_id() == GameController::_me->get_id()) {
            playerName = "You";

            if(i == 0) {
                winnerText = "     You won!!!";
            }
        }
        message += "\n" + playerName + ":     " + scoreText + winnerText;
    }

    wxMessageDialog dialogBox = wxMessageDialog(nullptr, message, title, wxICON_NONE);
    dialogBox.SetOKLabel(wxMessageDialog::ButtonLabel(buttonLabel));
    int buttonClicked = dialogBox.ShowModal();
    if(buttonClicked == wxID_OK) {
        GameController::_gameWindow->Close();
    }
}
