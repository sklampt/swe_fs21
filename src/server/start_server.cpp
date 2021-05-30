// Entrypoint for hosting a server
//
#include <string>
#include <unistd.h>
#include "thread"
#include "server_network_manager.h"
#include "game_instance_manager.h"
#include "../default.conf"

void server_thread(const std::string host_uuid, const uint16_t server_port) {
    // Initialize game_instance_manager state
    game_instance_manager::create_new_game_instance();
    server_network_manager server(host_uuid, server_port);
}

const int start_server(const std::string& host_uuid, const uint16_t& server_port) {
    // create server_network_manager, which listens endlessly for new connections
    std::thread t = std::thread(server_thread, host_uuid, server_port);
    t.detach();
    //TODO: Wait until server is started instead of fixed time
    sleep(2);
    return 0;
}