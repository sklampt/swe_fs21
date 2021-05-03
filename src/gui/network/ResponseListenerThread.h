//
// Created by marco on 02.05.21.
//

#ifndef ZOMBIEDICE_RESPONSELISTENERTHREAD_H
#define ZOMBIEDICE_RESPONSELISTENERTHREAD_H


#include <functional>
#include <wx/wx.h>
#include "sockpp/tcp_socket.h"
#include "sockpp/tcp_connector.h"


class ResponseListenerThread : public wxThread {

public:
    ResponseListenerThread(sockpp::tcp_connector* connection);
    ~ResponseListenerThread();

protected:
    virtual ExitCode Entry();

private:
    void outputError(std::string title, std::string message);


    sockpp::tcp_connector* _connection;

};

#endif //ZOMBIEDICE_RESPONSELISTENERTHREAD_H
