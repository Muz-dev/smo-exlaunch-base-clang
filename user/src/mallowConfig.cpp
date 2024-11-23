#include <mallow/mallow.hpp>

namespace mallow::config {
    const char* path = "sd:/mallow.json";
    const char* defaultConfig = "";
    Allocator* getAllocator() {
        static DefaultAllocator allocator = {};
        return &allocator;
    }
    ConfigBase* getConfig() {
        static ConfigBase modConfig = {};
        return &modConfig;
    }
    bool isEmu(){
        return false;
        //return !al::isExistFile("sd:/atmosphere/package3");
    }
}
