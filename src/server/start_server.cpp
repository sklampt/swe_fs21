// Entrypoint for hosting a server
//
#include <string>
#include "thread"
#include "server_network_manager.h"
#include "../default.conf"

void server_thread(const std::string host_uuid, const uint16_t server_port) {
    server_network_manager server(host_uuid, server_port);
}

const int start_server(const std::string& host_uuid, const uint16_t& server_port) {
    // create server_network_manager, which listens endlessly for new connections
    std::thread t = std::thread(server_thread, host_uuid, server_port);
    t.detach();
    return 0;
}