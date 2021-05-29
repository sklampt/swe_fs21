#include "Game.h"
#include "../exceptions/ZombieException.h"
#include "../serialization/vector_utils.h"


Game::Game() : unique_serializable() {
    this->_current_turn = new Turn();
    this->_players = std::vector<Player*>();
    this->_is_started = new serializable_value<bool>(false);
    this->_is_finished = new serializable_value<bool>(false);
    this->_current_player_idx = new serializable_value<int>(0);
    this->_play_direction = new serializable_value<int>(1);
    this->_round_number = new serializable_value<int>(0);
    this->_starting_player_idx = new serializable_value<int>(0);
}

Game::Game(std::string id, Turn *current_turn,
           std::vector<Player *> &players,
           serializable_value<bool> *is_started,
           serializable_value<bool> *is_finished,
           serializable_value<int> *current_player_idx,
           serializable_value<int> *play_direction,
           serializable_value<int> *round_number,
           serializable_value<int> *starting_player_idx
           ) : unique_serializable(id),
           _current_turn(current_turn),
           _players(players),
           _is_started(is_started),
           _is_finished(is_finished),
           _current_player_idx(current_player_idx),
           _play_direction(play_direction),
           _round_number(round_number),
           _starting_player_idx(starting_player_idx) { }


Game::Game(std::string id) : unique_serializable(id) {
    this->_current_turn = new Turn();
    this->_players = std::vector<Player*>();
    this->_is_started = new serializable_value<bool>(false);
    this->_is_finished = new serializable_value<bool>(false);
    this->_current_player_idx = new serializable_value<int>(0);
    this->_play_direction = new serializable_value<int>(1);
    this->_round_number = new serializable_value<int>(0);
    this->_starting_player_idx = new serializable_value<int>(0);

}

Game::~Game() {
    if(_is_started != nullptr) {
        delete _is_started;
        delete _is_finished;
        delete _current_turn;
        delete _current_player_idx;
        delete _starting_player_idx;
        delete _play_direction;
        delete _round_number;

        _is_started = nullptr;
        _is_finished = nullptr;
        _current_turn = nullptr;
        _current_player_idx = nullptr;
        _starting_player_idx = nullptr;
        _play_direction = nullptr;
        _round_number = nullptr;

    }
}
//accessors

Player* Game::get_current_player() const {
    if (_current_player_idx == nullptr || _players.size() == 0) {
        return nullptr;
    }
    return _players[_current_player_idx->get_value()];
}

bool Game::is_full() const {
    return _players.size() == _max_nof_players;
}

bool Game::is_started() const {
    return _is_started->get_value();
}

bool Game::is_finished() const {
    return _is_finished->get_value();
}

int Game::get_round_number() const {
    return _round_number->get_value();
}

int Game::get_player_index(Player *player) const {
    auto it = std::find(_players.begin(),_players.end(),player);
    if(it == _players.end()) {
        return -1;
    } else {
        return it - _players.begin();
    }
}

bool Game::is_player_in_game(Player *player) const {
    return std::find(_players.begin(),_players.end(),player) < _players.end();
}

bool Game::is_allowed_to_play_now(Player *player) const {
    return !player->has_folded() &&  player == get_current_player();
}

std::vector<Player*>& Game::get_players() {
    return _players;
}

void Game::setup_round(std::string &err) {
    _round_number->set_value(_round_number->get_value() + 1);
    for (int i = 0; i < _players.size(); i++) {
        _players[i]->setup_round(reinterpret_cast<std::string &>(i));
    }
}

void Game::wrap_up_round(std::string &err) {
    bool is_game_over = false;
    for (int i = 0; i < _players.size(); i++) {
        _players[i]->wrap_up_round(err);
        if(_players[i]->get_score() >= 13) {
            is_game_over = true;
        }
    }
}

void Game::update_current_player(std::string& err) {
    int nof_players = _players.size();
    int current_player_idx = _current_player_idx->get_value();
    ++current_player_idx %= nof_players;
    bool round_over = true;
    for (int i = 0; i < nof_players; i++) {
        if (_players[current_player_idx]->has_folded() == false) {
            _current_player_idx->set_value(current_player_idx);
            round_over = false;
            break;
        } else {
            ++current_player_idx %= nof_players;
        }
    }

    if (round_over) {
        // all players have folded and the round is over
        wrap_up_round(err);
    }
}

bool Game::start_game(std::string &err) {
    if (_players.size() < _min_nof_players) {
        err = "You need at least " + std::to_string(_min_nof_players) + " players to start the game.";
        return false;
    }

    if (!_is_started->get_value()) {
        this->setup_round(err);
        this->_is_started->set_value(true);
        return true;
    } else {
        err = "Could not start game, as the game was already started";
        return false;
    }
}

bool Game::remove_player(Player *player_ptr, std::string &err) {
    int idx = get_player_index(player_ptr);
    if (idx != -1) {
        if (idx < _current_player_idx->get_value()) {
            // reduce current_player_idx if the player who left had a lower index
            _current_player_idx->set_value(_current_player_idx->get_value() - 1);
        }
        _players.erase(_players.begin() + idx);
        return true;
    } else {
        err = "Could not leave game, as the requested player was not found in that game.";
        return false;
    }
}

bool Game::add_player(Player* player_ptr, std::string& err) {
    if (_is_started->get_value()) {
        err = "Could not join game, because the requested game is already started.";
        return false;
    }
    if (_is_finished->get_value()) {
        err = "Could not join game, because the requested game is already finished.";
        return false;
    }
    if (_players.size() >= _max_nof_players) {
        err = "Could not join game, because the max number of players is already reached.";
        return false;
    }
    if (std::find(_players.begin(), _players.end(), player_ptr) != _players.end()) {
        err = "Could not join game, because this player is already subscribed to this game.";
        return false;
    }

    _players.push_back(player_ptr);
    return true;
}

bool Game::fold(Player *player, std::string &err) {
    if(!is_player_in_game(player)) {
        err = "Server refused to perform draw_card. Player is not part of the game.";
        return false;
    }
    if (!is_allowed_to_play_now(player)) {
        err = "It's not this players turn yet.";
        return false;
    }
    if (_is_finished->get_value()) {
        err = "Could not fold, because the requested game is already finished.";
        return false;
    }

    if (player->fold(err)) {
        // Allow next player to play
        update_current_player(err);
        return true;
    } else {
        return false;
    }
}

// Serializable interface
void Game::write_into_json(rapidjson::Value &json,
                                 rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    unique_serializable::write_into_json(json, allocator);

    rapidjson::Value is_finished_val(rapidjson::kObjectType);
    _is_finished->write_into_json(is_finished_val, allocator);
    json.AddMember("is_finished", is_finished_val, allocator);

    rapidjson::Value is_started_val(rapidjson::kObjectType);
    _is_started->write_into_json(is_started_val, allocator);
    json.AddMember("is_started", is_started_val, allocator);

    rapidjson::Value current_player_idx_val(rapidjson::kObjectType);
    _current_player_idx->write_into_json(current_player_idx_val, allocator);
    json.AddMember("current_player_idx", current_player_idx_val, allocator);

    rapidjson::Value play_direction_val(rapidjson::kObjectType);
    _play_direction->write_into_json(play_direction_val, allocator);
    json.AddMember("play_direction", play_direction_val, allocator);

    rapidjson::Value starting_player_idx_val(rapidjson::kObjectType);
    _starting_player_idx->write_into_json(starting_player_idx_val, allocator);
    json.AddMember("starting_player_idx", starting_player_idx_val, allocator);

    rapidjson::Value round_number_val(rapidjson::kObjectType);
    _round_number->write_into_json(round_number_val, allocator);
    json.AddMember("round_number", round_number_val, allocator);

    json.AddMember("players", vector_utils::serialize_vector(_players, allocator), allocator);
}


Game* Game::from_json(const rapidjson::Value &json) {
    if (json.HasMember("id")
        && json.HasMember("turn")
        && json.HasMember("is_finished")
        && json.HasMember("is_started")
        && json.HasMember("current_player_idx")
        && json.HasMember("play_direction")
        && json.HasMember("round_number")
        && json.HasMember("starting_player_idx")
        && json.HasMember("players"))
    {
        std::vector<Player*> deserialized_players;
        for (auto &serialized_player : json["players"].GetArray()) {
            deserialized_players.push_back(Player::from_json(serialized_player.GetObject()));
        }

        // TODO: create turn object
        Turn *current_turn;
        current_turn = new Turn();

        return new Game(
                json["id"].GetString(),
                current_turn,
                deserialized_players,
                serializable_value<bool>::from_json(json["is_started"].GetObject()),
                serializable_value<bool>::from_json(json["is_finished"].GetObject()),
                serializable_value<int>::from_json(json["current_player_idx"].GetObject()),
                serializable_value<int>::from_json(json["play_direction"].GetObject()),
                serializable_value<int>::from_json(json["round_number"].GetObject()),
                serializable_value<int>::from_json(json["starting_player_idx"].GetObject())
        );

    } else {
        throw ZombieDiceException("Failed to deserialize game_state. Required entries were missing.");
    }
}

