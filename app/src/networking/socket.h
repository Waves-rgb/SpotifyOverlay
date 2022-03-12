#pragma once

#include <winsock.h>
#include <string>

using namespace std;

struct recvData {
    char dataRaw[1024*16];
    string data;
    int size;
};

namespace networking {
    SOCKET getSocket();
    bool initialize();
    bool isConnected();
    bool connect(const char* ip, int port);
    bool disconnect();
    bool sendData(const char* data);
    recvData receive();
    long long getPing();
}