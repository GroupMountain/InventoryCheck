#pragma once
#include <span>

#include "Config.h"
#include "Global.h"

namespace InventoryCheck {

using namespace GMLIB::Files::I18n;

class Entry {

public:
    static Entry& getInstance();

    Entry() : mSelf(*ll::mod::NativeMod::current()) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    /// @return True if the mod is loaded successfully.
    bool load();

    /// @return True if the mod is enabled successfully.
    bool enable();

    /// @return True if the mod is disabled successfully.
    bool disable();
/*
    /// @return True if the mod is unloaded successfully.
    bool unload();
*/
    Config& getConfig();

    LangI18n& getI18n();

private:
    ll::mod::NativeMod&     mSelf;
    std::optional<Config>   mConfig;
    std::optional<LangI18n> mI18n;
};

} // namespace InventoryCheck
