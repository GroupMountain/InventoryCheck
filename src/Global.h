#pragma once
#include <include_all.h>

#define PLUGIN_NAME "InventoryCheck"

extern ll::Logger logger;

extern std::string tr(std::string key, std::vector<std::string> data = {});

extern void initPlugin();
extern void RegisterCommand();

extern void mainForm(Player& pl);
extern void checkOnlineForm(Player& pl);
extern void checkAllForm(Player& pl);
extern void searchPlayerForm(Player& pl);
extern void searchResultForm(Player& pl, std::unordered_map<mce::UUID, std::string> resultList);
extern void searchNotFoundForm(Player& pl, std::string& name);
extern void checkPlayerForm(Player& pl, mce::UUID uuid);
extern void invalidInputForm(Player& pl);
extern void confirmWriteForm(Player& pl, mce::UUID uuid, std::string name);
extern void confirmDeleteForm(Player& pl, mce::UUID uuid, std::string name);
extern void deleteFailedForm(Player& pl, mce::UUID uuid, std::string name);

extern void listenEvent();
extern void initPlayerDataCache();

extern std::optional<std::string> getNameFromUuid(std::string uuid);