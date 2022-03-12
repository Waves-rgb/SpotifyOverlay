#include "utils/common.h"
#include "networking/socket.h"

using namespace std;

int main() {
    if (!networking::initialize()) {
        fmt::print("Failed to initialize networking\n");
        return 1;
    }

    if (networking::connect(HOST, PORT)) fmt::print("Connected to {}:{}\n", HOST, PORT);
    else {
        fmt::print("Failed to connect to {}:{}\n", HOST, PORT);
        return 1;
    }
    for (;;) {
        fmt::print("Server ping: {}us.\n", networking::getPing());
    }
    return 0;
}
