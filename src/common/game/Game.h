#ifndef ZOMBIEDICE_GAME_H
#define ZOMBIEDICE_GAME_H


#include <string>
#include "Player.h"
#include "Turn.h"
#include "../serialization/serializable.h"
#include "../serialization/serializable_value.h"
#include "../serialization/unique_serializable.h"


#define LAMA_SERVER

class Game : public unique_serializable {

private:
    static const int _max_nof_players = 6;
    static const int _min_nof_players = 2;

    serializable_value<bool>* _is_started;
    serializable_value<bool>* _is_finished;
    serializable_value<int>* _round_number;
    serializable_value<int>* _current_player_idx;
    serializable_value<int>* _play_direction;
    serializable_value<int>* _starting_player_idx;

    std::vector<Player*> _players;

    Game(std::string id);

    // Serialization constructor
    Game(
            std::string id,
            Turn* current_turn,
            std::vector<Player*>& players,
            serializable_value<bool>* is_started,
            serializable_value<bool>* is_finished,
            serializable_value<int>* current_player_idx,
            serializable_value<int>* play_direction,
            serializable_value<int>* round_number,
            serializable_value<int>* starting_player_idx
            );
    int get_player_index(Player* player) const;
public:
    Game();
    ~Game();


    bool is_full() const;
    bool is_started() const;
    bool is_finished() const;
    bool is_player_in_game(Player* player) const;
    bool is_allowed_to_play_now(Player* player) const;
    std::vector<Player *> &get_players();
    int get_round_number() const;
    Turn* get_current_turn() const;
    Player* get_current_player() const;

    void setup_round(std::string& err);
    bool remove_player(Player* player, std::string& err);
    bool add_player(Player* player,std::string& err);
    bool start_game(std::string& err);
    bool roll(Player* player, std::string& err);
    bool fold(Player* player, std::string& err);

    void update_current_player(std::string& err);
    void wrap_up_round(std::string& err);

    //rapidjson::Value *to_json();

    static Game *from_json(const rapidjson::Value& json);
    virtual void write_into_json(rapidjson::Value& json,
                                 rapidjson::Document::AllocatorType& allocator
                                 ) const override;

    Turn* _current_turn;
};

#endif //ZOMBIEDICE_GAME_H
