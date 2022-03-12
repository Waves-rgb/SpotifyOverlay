#include "socket.h"
#include <winsock.h>
#include <chrono>
#include "../utils/common.h"

SOCKET sock;

SOCKET networking::getSocket() {
    return sock;
}

long long networking::getPing() {
    auto start = std::chrono::high_resolution_clock::now();

    if (!isConnected()) return -1;
    if (!sendData("ping")) return -1;

    const auto& rec = receive();
    if (rec.data != "pong") return -1;

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

bool networking::initialize() {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
}

bool networking::isConnected() {
    return sock != INVALID_SOCKET;
}

bool networking::connect(const char *ip, int port) {
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
        return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(sock);
        return false;
    }

    return true;
}

bool networking::disconnect() {
    return false;
}

bool networking::sendData(const char *data) {
    if (!isConnected()) {
        fmt::print("[{}@{}] Not connected\n", __FUNCTION__, __FILE__);
        if (!connect(HOST, PORT))
            return false;
    }

    return send(sock, data, (int)strlen(data), 0);
}

recvData networking::receive() {
    recvData data{};
    data.size = recv(sock, data.dataRaw, sizeof(data.dataRaw), 0);
    data.data = string(data.dataRaw, data.size);
    return data;
}
