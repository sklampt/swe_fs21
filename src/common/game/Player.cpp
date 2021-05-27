//
// Created by marco on 02.05.21.
//

#include "Player.h"
#include "../exceptions/ZombieException.h"

Player::Player(std::string name) : unique_serializable() {
    this->_player_name = new serializable_value<std::string>(name);
    this->_has_folded = new serializable_value<bool>(false);
    this->_score = new serializable_value<int>(0);
}


Player::Player(std::string id, std::string name) : unique_serializable(id) {
    this->_player_name = new serializable_value<std::string>(name);
    this->_has_folded = new serializable_value<bool>(false);
    this->_score = new serializable_value<int>(0);
}

Player::Player(std::string id,
               serializable_value<std::string> *player_name,
               serializable_value<int> *score,
               serializable_value<bool> *has_folded
               ) :
               unique_serializable(id),
               _player_name(player_name),
               _score(score),
               _has_folded(has_folded) { }

Player::~Player() {
    if(_player_name != nullptr) {
        delete _player_name;
        delete _score;
        delete _has_folded;

        _player_name = nullptr;
        _score = nullptr;
        _has_folded = nullptr;
    }
}

std::string Player::get_game_id() {
    return _game_id;
}

void Player::set_game_id(std::string game_id) {
    _game_id = game_id;
}

int Player::get_score() const noexcept {
    return _score->get_value();
}

std::string Player::get_player_name() const noexcept {
    return this->_player_name->get_value();
}

bool Player::has_folded() const noexcept {
    return this->_has_folded->get_value();
}

void Player::setup_round(std::string &err) {
    _has_folded->set_value(false);
}

void Player::wrap_up_round(std::string &err) {
    //update scores
}

bool Player::fold(std::string &err) {
    if(has_folded()) {
        err = "This player has already folded.";
        return false;
    }
    _has_folded->set_value(true);
    return true;
}


void Player::write_into_json(rapidjson::Value &json, rapidjson::Document::AllocatorType &allocator) const {
    unique_serializable::write_into_json(json, allocator);

    // Double assign
    //    rapidjson::Value id_val(_id.c_str(), allocator);
    //    json.AddMember("id", id_val, allocator);

    rapidjson::Value name_val(rapidjson::kObjectType);
    _player_name->write_into_json(name_val, allocator);
    json.AddMember("player_name", name_val, allocator);

    rapidjson::Value has_folded_val(rapidjson::kObjectType);
    _has_folded->write_into_json(has_folded_val,allocator);
    json.AddMember("has_folded", has_folded_val, allocator);

    rapidjson::Value score_val(rapidjson::kObjectType);
    _score->write_into_json(score_val,allocator);
    json.AddMember("score", score_val, allocator);
}

Player *Player::from_json(const rapidjson::Value &json) {
    if (json.HasMember("id")
    && json.HasMember("player_name")
    && json.HasMember("has_folded")
    && json.HasMember("score")) {
        return new Player(
                json["id"].GetString(),
                serializable_value<std::string>::from_json(json["player_name"].GetObject()),
                serializable_value<int>::from_json(json["score"].GetObject()),
                serializable_value<bool>::from_json(json["has_folded"].GetObject()));
    } else {
        throw ZombieDiceException("Failed to deserialize Player class!");
    }
}

