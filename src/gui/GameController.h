#ifndef ZOMBIEDICE_GUI_GAMECONTROLLER_H
#define ZOMBIEDICE_GUI_GAMECONTROLLER_H

#include "windows/GameWindow.h"
#include "panels/ConnectionPanel.h"
#include "panels/MainGamePanel.h"
#include "network/ResponseListenerThread.h"
#include "../common/game/Game.h"


class GameController {

public:
    static void init(GameWindow* gameWindow);

    static void connectToServer();
    static void updateGameState(Game* newGameState);
    static void startGame();
    static void drawDice();
    static void keepGoing();
    static void score();

    static wxEvtHandler* getMainThreadEventHandler();
    static void showError(const std::string& title, const std::string& message);
    static void showStatus(const std::string& message);
    static void showNewTurnMessage(Game* oldGameState, Game* newGameState);
    static void showGameOverMessage();

private:
    static GameWindow* _gameWindow;
    static ConnectionPanel* _connectionPanel;
    static MainGamePanel* _mainGamePanel;

    static Player* _me;
    static Game* _currentGameState;

};


#endif //ZOMBIEDICE_GUI_GAMECONTROLLER_H
