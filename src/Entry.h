#pragma once
#include <span>

#include "Config.h"
#include "Global.h"
#include "gmlib/gm/i18n/LangI18n.h"

#include "gmlib/gm/data/UserCache.h"
#include <memory>

namespace InventoryCheck {

using namespace gmlib::i18n;

class Entry {

public:
    static Entry& getInstance();

    Entry() : mSelf((*ll::mod::NativeMod::current())) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    /// @return True if the mod is loaded successfully.
    bool load();

    /// @return True if the mod is enabled successfully.
    bool enable();

    /// @return True if the mod is disabled successfully.
    bool disable();

    /// @return True if the mod is unloaded successfully.

    Config& getConfig();

    LangI18n& getI18n();

    std::vector<gmlib::UserCache::UserCacheEntry> userCache;


private:
    ll::mod::NativeMod& mSelf;
    std::optional<Config>     mConfig;
    std::optional<LangI18n>   mI18n;
};

} // namespace InventoryCheck
