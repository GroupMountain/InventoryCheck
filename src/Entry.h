#pragma once
#include <span>

#include "Config.h"
#include "Global.h"
#include "gmlib/gm/i18n/LangI18n.h"

#include <memory>

namespace InventoryCheck {

using namespace GMLIB::Files::I18n;

class Entry {

public:
    static std::unique_ptr<Entry>& getInstance();

    Entry(ll::mod::NativeMod& self) : mSelf(self) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    /// @return True if the mod is loaded successfully.
    bool load();

    /// @return True if the mod is enabled successfully.
    bool enable();

    /// @return True if the mod is disabled successfully.
    bool disable();

    /// @return True if the mod is unloaded successfully.
    bool unload();

    Config& getConfig();

    LangI18n& getI18n();

private:
    ll::mod::NativeMod& mSelf;
    std::optional<Config>     mConfig;
    std::optional<LangI18n>   mI18n;
};

} // namespace InventoryCheck
