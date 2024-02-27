#include "Config.h"
#include "Global.h"
#include "Language.h"

GMLIB::Files::JsonConfig*     Config   = nullptr;
GMLIB::Files::I18n::LangI18n* Language = nullptr;
nlohmann::json                mPlayerDataCache;

std::optional<nlohmann::json> readFile(std::string path) {
    if (std::filesystem::exists(path)) {
        return GMLIB::Files::JsonFile::readFromFile(path);
    }
    return {};
}

void initPlayerDataCache() {
    mPlayerDataCache = nlohmann::json::object();
    auto data        = readFile("./plugins/InventoryCheck/data/PlayerDataCache.json");
    if (data.has_value()) {
        try {
            mPlayerDataCache = data.value();
        } catch (...) {}
    }
}

void saveCacheData() {
    std::string path = "./plugins/InventoryCheck/data/PlayerDataCache.json";
    GMLIB::Files::JsonFile::writeFile(path, mPlayerDataCache);
}

void initPlugin() {
    Config = new GMLIB::Files::JsonConfig("./plugins/InventoryCheck/config/config.json", defaultConfig);
    Config->init();
    std::string langPath     = "./plugins/InventoryCheck/language/";
    std::string languageCode = Config->getValue<std::string>({"language"}, "en_US");
    Language                 = new GMLIB::Files::I18n::LangI18n(langPath, languageCode);
    Language->updateOrCreateLanguage("en_US", defaultLanguage_en_US);
    Language->updateOrCreateLanguage("zh_CN", defaultLanguage_zh_CN);
    Language->loadAllLanguages();
    Language->chooseLanguage(languageCode);
    if (!std::filesystem::exists("./plugins/InventoryCheck/data/")) {
        std::filesystem::create_directories("./plugins/InventoryCheck/data/");
    }
    if (!std::filesystem::exists("./plugins/InventoryCheck/save/")) {
        std::filesystem::create_directories("./plugins/InventoryCheck/save/");
    }
}

std::string tr(std::string key, std::vector<std::string> data) { return Language->translate(key, data); }

void listenEvent() {
    auto& eventBus = ll::event::EventBus::getInstance();
    eventBus.emplaceListener<ll::event::player::PlayerConnectEvent>([](ll::event::player::PlayerConnectEvent& ev) {
        auto& pl                                  = ev.self();
        mPlayerDataCache[pl.getUuid().asString()] = pl.getRealName();
        saveCacheData();
    });
}

std::optional<std::string> getNameFromUuid(std::string uuid) {
    if (mPlayerDataCache.contains(uuid)) {
        return mPlayerDataCache[uuid].get<std::string>();
    }
    return {};
}