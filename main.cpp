#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem> // for std::filesystem

namespace fs = std::filesystem;

const std::string DEFAULT_REMOTE = "username@host:/path";
const std::string DEFAULT_LOCAL = fs::current_path().string();

void print_usage() {
    std::cout << "Usage: ddb <push|pull> [source] [destination]\n";
    std::cout << "If [source] or [destination] is omitted, defaults will be used.\n";
    std::cout << "Example: ddb push\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string command = argv[1];
    std::string source, destination;

    if (command == "push") {
        source = (argc >= 3) ? argv[2] : DEFAULT_LOCAL;
        destination = (argc >= 4) ? argv[3] : DEFAULT_REMOTE;
    } else if (command == "pull") {
        source = (argc >= 3) ? argv[2] : DEFAULT_REMOTE;
        destination = (argc >= 4) ? argv[3] : DEFAULT_LOCAL;
    } else {
        print_usage();
        return 1;
    }

    std::string scp_cmd = "scp -r \"" + source + "\" \"" + destination + "\"";
    std::cout << "Executing: " << scp_cmd << std::endl;
    int result = system(scp_cmd.c_str());
    return result;
}