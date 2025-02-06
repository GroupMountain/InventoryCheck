#include "Entry.h"
#include "Global.h"
#include "Language.h"

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
    mI18n.emplace(getSelf().getLangDir(), mConfig->language);
    mI18n->updateOrCreateLanguage("en_US", en_US);
    mI18n->updateOrCreateLanguage("zh_CN", zh_CN);
    mI18n->loadAllLanguages();
    if (GMLIB::Version::getProtocolVersion() != TARGET_PROTOCOL) {
        getSelf().getLogger().error(tr("error.protocolMismatch.info"));
        getSelf().getLogger().error(
            tr("error.protocolMismatch.version",
               {std::to_string(TARGET_PROTOCOL), std::to_string(GMLIB::Version::getProtocolVersion())})
        );
    }
    return true;
}

bool Entry::enable() {
    RegisterCommand();
    getSelf().getLogger().info("InventoryCheck Loaded!");
    getSelf().getLogger().info("Author: GroupMountain");
    getSelf().getLogger().info("Repository: https://github.com/GroupMountain/InventoryCheck");
    return true;
}

bool Entry::disable() {
    // Code for disabling the mod goes here.
    return true;
}
/*
bool Entry::unload() {
    getInstance().reset();
    return true;
}
*/
Config& Entry::getConfig() { return mConfig.value(); }

LangI18n& Entry::getI18n() { return mI18n.value(); }

} // namespace InventoryCheck

LL_REGISTER_MOD(InventoryCheck::Entry, InventoryCheck::Entry::getInstance());

std::string tr(std::string const& key, std::vector<std::string> const& data) {
    return InventoryCheck::Entry::getInstance().getI18n().get(key, data);
}