//
// Created by marco on 02.05.21.
//

#ifndef ZOMBIEDICE_PLAYER_H
#define ZOMBIEDICE_PLAYER_H

#include <string>
#include "Turn.h"
#include "../serialization/uuid_generator.h"
#include "../../../rapidjson/include/rapidjson/document.h"
#include "../serialization/unique_serializable.h"
#include "../serialization/serializable_value.h"


class Player : public unique_serializable {

private:
    serializable_value<std::string>* _player_name;
    serializable_value<bool>* _has_folded;
    serializable_value<int>* _score;

    std::string _game_id;

    /*
     * Deserialization constructor
     */
    Player(
            std::string id,
            serializable_value<std::string>* player_name,
            serializable_value<int>* score,
            serializable_value<bool>* has_folded
            );
public:
    explicit Player(std::string name);
    ~Player();

    Player(std::string id, std::string name);

    std::string get_game_id();
    void set_game_id(std::string game_id);

    int get_score() const noexcept;
    void update_score(int score);

    bool has_folded() const noexcept;
    std::string get_player_name() const noexcept;

    bool fold(std::string& err);
    void wrap_up_round(std::string& err);
    void setup_round(std::string& err);

    static Player* from_json(const rapidjson::Value& json);
    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const override;


};


#endif //ZOMBIEDICE_PLAYER_H
