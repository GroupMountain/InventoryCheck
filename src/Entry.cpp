#include "Entry.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace InventoryCheck {

namespace {

std::unique_ptr<std::reference_wrapper<ll::plugin::NativePlugin>>
    selfPluginInstance; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

auto disable(ll::plugin::NativePlugin& /*self*/) -> bool { return true; }

auto enable(ll::plugin::NativePlugin& /*self*/) -> bool {
    RegisterCommand();
    listenEvent();
    logger.info("InventoryCheck Loaded!");
    logger.info("Author: GroupMountain");
    logger.info("Repository: https://github.com/GroupMountain/InventoryCheck");
    return true;
}

auto load(ll::plugin::NativePlugin& self) -> bool {
    selfPluginInstance = std::make_unique<std::reference_wrapper<ll::plugin::NativePlugin>>(self);
    initPlugin();
    initPlayerDataCache();
    return true;
}

auto unload(ll::plugin::NativePlugin& self) -> bool {
    selfPluginInstance.reset();
    return true;
}

} // namespace

auto getSelfPluginInstance() -> ll::plugin::NativePlugin& {
    if (!selfPluginInstance) {
        throw std::runtime_error("selfPluginInstance is null");
    }
    return *selfPluginInstance;
}

} // namespace InventoryCheck

extern "C" {
_declspec(dllexport) auto ll_plugin_disable(ll::plugin::NativePlugin& self) -> bool {
    return InventoryCheck::disable(self);
}
_declspec(dllexport) auto ll_plugin_enable(ll::plugin::NativePlugin& self) -> bool {
    return InventoryCheck::enable(self);
}
_declspec(dllexport) auto ll_plugin_load(ll::plugin::NativePlugin& self) -> bool { return InventoryCheck::load(self); }
_declspec(dllexport) auto ll_plugin_unload(ll::plugin::NativePlugin& self) -> bool {
    return InventoryCheck::unload(self);
}
}
