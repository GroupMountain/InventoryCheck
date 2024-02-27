#include "Global.h"

extern void mainForm(Player& pl) ;
extern void checkOnlineForm(Player& pl);
extern void checkAllForm(Player& pl) ;
extern void searchPlayerForm(Player& pl);
extern void searchResultForm(Player& pl, std::unordered_map<mce::UUID, std::string> resultList);
extern void searchNotFoundForm(Player& pl, std::string& name) ;
extern void checkPlayerForm(Player& pl, mce::UUID uuid);
extern void invalidInputForm(Player& pl);