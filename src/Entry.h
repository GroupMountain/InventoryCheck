#pragma once

#include <ll/api/plugin/NativePlugin.h>

namespace InventoryCheck {

[[nodiscard]] auto getSelfPluginInstance() -> ll::plugin::NativePlugin&;

} // namespace InventoryCheck
