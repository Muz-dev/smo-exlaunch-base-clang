#include <mallow/mallow.hpp>
#include "ModOptions.h"

namespace mallow::config {
    const char* path = "sd:/mallow.json";
    const char* defaultConfig = R"(
{
    "myModOption": true,
    "logger": {
        "enable": true,
        "reconnect": true,
        "ip": "192.168.1.110",
        "port": 3080
    }
}
    )";

    Allocator* getAllocator() {
        static DefaultAllocator allocator = {};
        return &allocator;
    }
    ConfigBase* getConfig() {
        static ModOptions modConfig = {};
        return &modConfig;
    }
    bool isEmu(){
        return false;
    }
}
