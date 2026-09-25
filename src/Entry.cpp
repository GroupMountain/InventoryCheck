#include "Entry.h"
#include "Global.h"
#include "Language.h"

#include "ll/api/Config.h"
#include "ll/api/Versions.h"
#include "ll/api/mod/RegisterHelper.h"

#include "gmlib/gm/i18n/LangI18n.h"
#include "gmlib/gm/i18n/JsonI18n.h"
#include "gmlib/mc/locale/I18nAPI.h"

#include "gmlib/gm/data/UserCache.h"
#include "ll/api/service/Bedrock.h"
#include "ll/api/service/PlayerInfo.h"

namespace InventoryCheck {

Entry& Entry::getInstance() {
    static Entry instance;
    return instance;
}

bool Entry::load() {
    mConfig.emplace();
    if (!ll::config::loadConfig(*mConfig, getSelf().getConfigDir() / u8"config.json")) {
        ll::config::saveConfig(*mConfig, getSelf().getConfigDir() / u8"config.json");
    }


    return true;
}
;

bool Entry::enable() {
    gmlib::I18nAPI::updateOrCreateLanguageFile(getSelf().getLangDir(), "en_US", en_US);
    gmlib::I18nAPI::updateOrCreateLanguageFile(getSelf().getLangDir(), "zh_CN", zh_CN);

    RegisterCommand();


    return true;
}

bool Entry::disable() {
    // Code for disabling the mod goes here.
    return true;
}



Config& Entry::getConfig() { return mConfig.value(); }


} // namespace InventoryCheck

LL_REGISTER_MOD(InventoryCheck::Entry, InventoryCheck::Entry::getInstance());

std::string tr(std::string const& key, std::vector<std::string> const& data) {
    return gmlib::I18nAPI::get(key, data);
}