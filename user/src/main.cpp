#include <mallow/config.hpp>
#include <mallow/mallow.hpp>

#include "ActorFactory/actorPatches.h"

#include "Scene/StageScene.h"

using mallow::log::logLine;

struct ScenePlayHook : public mallow::hook::Trampoline<ScenePlayHook>{
    static void Callback(StageScene* thisPtr){
        logLine("StageScene playing");
        Orig(thisPtr);
    }
};

extern "C" void userMain() {
    exl::hook::Initialize();
    mallow::init::installHooks();
    ca::actorPatches();

    ScenePlayHook::InstallAtSymbol("_ZN10StageScene7exePlayEv");
}
