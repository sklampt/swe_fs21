// Entrypoint for hosting a server
//

#include "string"
#include "server_network_manager.h"
#include "../default.conf"

const int start_server(const std::string& host_uuid, const std::string& shared_token, const uint16_t& server_port) {
    // create server_network_manager, which listens endlessly for new connections
    server_network_manager server(host_uuid, shared_token, server_port);

    return 0;
}