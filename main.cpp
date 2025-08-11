#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem> // for std::filesystem

namespace fs = std::filesystem;

const std::string REMOTE_PREFIX = "dingkaixing@10.xx.11.xx:";
const std::string DEFAULT_REMOTE_PATH = "/mnt/work/transport_transfer/tmp";
const std::string DEFAULT_LOCAL_PATH = fs::current_path().string();

void print_usage() {
    std::cout << "Usage:\n";
    std::cout << "  ddb push <local_path> [remote_path]\n";
    std::cout << "  ddb pull <remote_path> [local_path]\n";
    std::cout << "Examples:\n";
    std::cout << "  ddb push ./data_dir\n";
    std::cout << "  ddb push ./data_dir /mnt/nfs/working/user/custom_dir\n";
    std::cout << "  ddb pull /mnt/nfs/working/user/custom_dir\n";
    std::cout << "  ddb pull /mnt/nfs/working/user/custom_dir ./local_dir\n";
}

bool is_remote_path(const std::string& path) {
    // 简单判断路径是否为远端绝对路径
    return path.rfind("/", 0) == 0;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        print_usage();
        return 1;
    }

    std::string command = argv[1];
    std::string source, destination;
    std::string rsync_cmd;

    if (command == "push") {
        source = argv[2];
        if (argc >= 4) {
            // 用户自定义远端路径
            std::string remote_path = argv[3];
            if (!is_remote_path(remote_path)) {
                std::cerr << "Remote path must start with '/'.\n";
                return 1;
            }
            destination = REMOTE_PREFIX + remote_path;
        } else {
            // 默认远端路径
            destination = REMOTE_PREFIX + DEFAULT_REMOTE_PATH;
        }
        rsync_cmd = "rsync -avzP --exclude='.DS_Store' --exclude='*.tmp' \"" + source + "\" \"" + destination + "\"";
    } else if (command == "pull") {
        source = argv[2];
        if (!is_remote_path(source)) {
            std::cerr << "Remote path must start with '/'.\n";
            return 1;
        }
        source = REMOTE_PREFIX + source;
        destination = (argc >= 4) ? argv[3] : DEFAULT_LOCAL_PATH;
        rsync_cmd = "rsync -avzP --exclude='.DS_Store' --exclude='*.tmp' \"" + source + "\" \"" + destination + "\"";
    } else {
        print_usage();
        return 1;
    }

    std::cout << "Executing: " << rsync_cmd << std::endl;
    int result = system(rsync_cmd.c_str());
    return result;
}
