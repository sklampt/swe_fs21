#include "GameController.h"
#include "network/ClientNetworkManager.h"
#include <common/network/requests/client_join_lobby_request.h>
#include <common/network/requests/client_update_game_request.h>
#include "common/game/Player.h"
#include "server/start_server.h"


// default values
int default_port = 50500;

// initialize static members
GameWindow* GameController::_gameWindow = nullptr;

Player* GameController::_me = nullptr;
Game* GameController::_currentGame = nullptr;

//ConnectionPanel* GameController::_connectionPanel = nullptr;
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
    GameController::_mainGamePanel = new MainGamePanel(gameWindow);
    GameController::_startPanel = new StartPanel(gameWindow);
    GameController::_lobbyPanel = new LobbyPanel(gameWindow);

    // Hide all panels
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
    wxString inputServerAddress = GameController::_startPanel->getServerAddress().Trim();
    wxString inputServerPort = GameController::_startPanel->getServerPort().Trim();
    wxString inputPlayerName = GameController::_startPanel->getPlayerName().Trim();

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

    if (!GameController::_me) {
        // convert player name from wxString to std::string
        std::string playerName = inputPlayerName.ToStdString();

        GameController::_me = new Player(playerName);
    }

    // convert host from wxString to std::string
    std::string host = inputServerAddress.ToStdString();

    // convert port from wxString to uint16_t
    unsigned long portAsLong = 0;
    if(!inputServerPort.ToULong(&portAsLong) || portAsLong > 65535) {
        GameController::showError("Connection error", "Invalid port");
        std::cout << "Connection error: Invalid Port - " << std::to_string(portAsLong) << std::endl;
        return;
    }
    uint16_t port = (uint16_t) portAsLong;

    // connect to network
    ClientNetworkManager::init(host, port);

    // send request to join game
    if (ClientNetworkManager::isConnected()) {
    client_join_lobby_request request = client_join_lobby_request(
                                    GameController::_me->get_id(),
                                    GameController::_me->get_player_name()
                                );
    ClientNetworkManager::sendRequest(request);

    // Switch view to lobby panel
    GameController::_gameWindow->showPanel(GameController::_lobbyPanel);
    }
}

void GameController::createAndConnectToServer() {
    // We have to create the player object here to have its uuid ready for the server
    std::string playerName = GameController::_startPanel->getPlayerName().Trim().ToStdString();
    GameController::_me = new Player(playerName);

    start_server(GameController::_me->get_id(), default_port);
    GameController::_startPanel->setServerPort(std::to_string(default_port));
    GameController::_startPanel->setServerAddress("127.0.0.1");

    // Call client connect function
    GameController::connectToServer();
}

void GameController::startGame() {
    // TODO: Implement check that only host can start game
    std::string err = "";
    _currentGame->start_game(err);

    if (err == "") {
        client_update_game_request request = client_update_game_request(
                GameController::_currentGame,
                GameController::_me->get_id()
        );
        ClientNetworkManager::sendRequest(request);
    } else {
        GameController::showError("Lobby Error", "Could not start game: " + err);
    }
}

void GameController::updateGameState(Game *newGameState) {
    // the existing game state is now old
    Game* oldGameState = GameController::_currentGame;

    // save the new game state as our current game state
    GameController::_currentGame = newGameState;

    if(oldGameState != nullptr) {
        // check if a new round started, and display message accordingly
        if(oldGameState->get_round_number() > 0 && oldGameState->get_round_number() < newGameState->get_round_number()) {
            GameController::showNewTurnMessage(oldGameState, newGameState);
        }

        // delete the old game state, we don't need it anymore
        delete oldGameState;
    }

    if(GameController::_currentGame->is_finished()) {
        GameController::showGameOverMessage();
    }

    // Only switch to mainGamePanel if Game has started
    if(GameController::_currentGame->is_started()) {
        GameController::_gameWindow->showPanel(GameController::_mainGamePanel);
        // command the main game panel to rebuild itself, based on the new game state
        GameController::_mainGamePanel->buildGameState(GameController::_currentGame, GameController::_me);
    }
    else {
        // TODO: Implement this
        GameController::_lobbyPanel->buildLobby(GameController::_currentGame, GameController::_me);
    }
}

wxEvtHandler* GameController::getMainThreadEventHandler() {
    return GameController::_gameWindow->GetEventHandler();
}

void GameController::showError(const std::string& title, const std::string& message) {
    wxMessageBox(message, title, wxICON_INFORMATION);
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

void GameController::showNewTurnMessage(Game* oldGameState, Game* newGameState) {
    std::string title = "Turn Completed";
    std::string message = "The players gained the following minus points:\n";
    std::string buttonLabel = "Start next turn";

    // add the point differences of all players to the messages
    for(int i = 0; i < oldGameState->get_players().size(); i++) {

        Player* oldPlayerState = oldGameState->get_players().at(i);
        Player* newPlayerState = newGameState->get_players().at(i);

        int scoreDelta = newPlayerState->get_score() - oldPlayerState->get_score();
        std::string scoreText = std::to_string(scoreDelta);
        if(scoreDelta > 0) {
            scoreText = "+" + scoreText;
        }

        std::string playerName = newPlayerState->get_player_name();
        if(newPlayerState->get_id() == GameController::_me->get_id()) {
            playerName = "You";
        }
        message += "\n" + playerName + ":     " + scoreText;
    }

    wxMessageDialog dialogBox = wxMessageDialog(nullptr, message, title, wxICON_NONE);
    dialogBox.SetOKLabel(wxMessageDialog::ButtonLabel(buttonLabel));
    dialogBox.ShowModal();
}
