cmake_minimum_required(VERSION 3.13)
project(Zombiedice)

set(CMAKE_CXX_STANDARD 20)

include(cmake/GetGTest.cmake)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/sockpp/include
)

find_package(wxWidgets COMPONENTS core base net REQUIRED)
include(${wxWidgets_USE_FILE})

# Define all source files for Zombie Dice
set(SOURCE_FILES
        ### GUI
        src/gui/main.cpp
        src/gui/GameController.cpp
        src/gui/app/ZombieDice.cpp
        ## Windows
        src/gui/windows/GameWindow.cpp
        ## Panels
        src/gui/panels/MainGamePanel.cpp
        src/gui/panels/ConnectionPanel.cpp
        src/gui/panels/LobbyPanel.cpp
        src/gui/panels/StartPanel.cpp
        ## UIElements
        src/gui/uiElements/ImagePanel.cpp
        src/gui/uiElements/InputField.cpp
        ## Client Network
        src/gui/network/ClientNetworkManager.cpp
        src/gui/network/ResponseListenerThread.cpp

        ### COMMON
        ## Exceptions
        src/common/exceptions/ZombieException.h
        ## Game
        src/common/game/Game.cpp
        src/common/game/Turn.cpp
        src/common/game/Cup.cpp
        src/common/game/Die.cpp
        src/common/game/Player.cpp
        ## Network
        src/common/network/requests/client_request.cpp
        src/common/network/requests/client_join_lobby_request.cpp
        src/common/network/requests/client_update_game_request.cpp
        src/common/network/requests/client_exit_lobby_request.cpp

        src/common/network/responses/request_response_event.cpp
        src/common/network/responses/server_response.cpp
        src/common/network/responses/server_update_lobby_event.cpp
        src/common/network/responses/server_update_game_event.cpp

        ## Serialization
        src/common/serialization/json_utils.h
        src/common/serialization/serializable.h
        src/common/serialization/serializable_value.h
        src/common/serialization/unique_serializable.cpp
        src/common/serialization/uuid_generator.h
        src/common/serialization/value_type_helpers.h
        src/common/serialization/vector_utils.h
        src/common/serialization/token_generator.h

        ### Server
        src/server/game_instance.cpp
        src/server/game_instance_manager.cpp
        src/server/start_server.cpp
        src/server/player_manager.cpp
        src/server/server_network_manager.cpp
)

add_executable(
        ZombieDice
        ${SOURCE_FILES}
)

# set compile directives for client-executable
target_compile_definitions(ZombieDice PRIVATE RAPIDJSON_HAS_STDSTRING=1)
# Comment out if you don't want to print network-related messages into the console
target_compile_definitions(ZombieDice PRIVATE PRINT_NETWORK_MESSAGES=1)


add_library(
        zombie_lib
        ${SOURCE_FILES}
)

set_target_properties(
        zombie_lib
        PROPERTIES COMPILE_FLAGS "-O3 -std=c++2a -march=native"
)

# set compile directives for client-executable
target_compile_definitions(zombie_lib PRIVATE RAPIDJSON_HAS_STDSTRING=1)
# Comment out if you don't want to print network-related messages into the console
target_compile_definitions(zombie_lib PRIVATE PRINT_NETWORK_MESSAGES=1)


add_executable(
        unit_tests
        tests/main.cpp
        tests/common/exceptions.cpp
        tests/common/cup.cpp
        tests/common/die.cpp
        tests/common/player.cpp
        tests/common/game.cpp
        tests/common/turn.cpp
)

target_link_libraries(
        unit_tests
        zombie_lib
        gtest_main
        pthread
)

set_target_properties(
        unit_tests
        PROPERTIES COMPILE_FLAGS "-O3 -march=native"
)

# set compile directives for client-executable
target_compile_definitions(unit_tests PRIVATE RAPIDJSON_HAS_STDSTRING=1)
# Comment out if you don't want to print network-related messages into the console
target_compile_definitions(unit_tests PRIVATE PRINT_NETWORK_MESSAGES=1)

# link with wxWidgets
target_link_libraries(ZombieDice ${wxWidgets_LIBRARIES})

# linking to sockpp
if(WIN32)
        message("Detected Win32")
        target_link_libraries(zombie_dice ${CMAKE_SOURCE_DIR}/sockpp/cmake-build-debug/sockpp-static.lib)
        # Necessary to get sockets working under Windows (with MingW)
        target_link_libraries(Lama-client wsock32 ws2_32)
elseif(APPLE)
        # Do some mac stuff to fix out of sync warnings
        set(CMAKE_OSX_SYSROOT /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk)
        set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12")
        set(THREADS_PREFER_PTHREAD_FLAG ON)
        find_package(Threads REQUIRED)
        target_link_libraries(ZombieDice ${CMAKE_SOURCE_DIR}/sockpp/cmake-build-debug/libsockpp.dylib Threads::Threads)
else()
        message("Not Win32 or Apple, so probably a Linux") # We assume it's Linux in this case
        set(THREADS_PREFER_PTHREAD_FLAG ON)
        find_package(Threads REQUIRED)
        target_link_libraries(ZombieDice ${CMAKE_SOURCE_DIR}/sockpp/cmake-build-debug/libsockpp.so Threads::Threads)
endif()

# copy assets (images) to binary directory
file(INSTALL assets DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "--coverage")

# TODO: Decide if we want to use a Library to package functionality
# set source files for library
add_library(ZombieDice-lib ${SOURCE_FILES})
# set compile directives for server-library
target_compile_definitions(ZombieDice-lib PRIVATE RAPIDJSON_HAS_STDSTRING=1)

enable_testing()
