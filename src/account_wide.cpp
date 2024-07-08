/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"


class MyPlayer : public PlayerScript
{
public:
    MyPlayer() : PlayerScript("MyPlayer") { }

    void OnLogin(Player* theplayer) override
    {
	std::vector<uint32> Guids;
        uint32 playerAccountID = theplayer->GetSession()->GetAccountId();
        QueryResult guid_results = CharacterDatabase.Query("SELECT `guid` FROM `characters` WHERE `account`={};", playerAccountID);
	Field* fields = guid_results->Fetch();
	Guids.push_back(fields[0].Get<uint32>());

        std::vector<uint32> Spells;

        for (auto& i : Guids)
        {
	LOG_INFO("module", "INSIDE FOR");
            QueryResult spell_results = CharacterDatabase.Query("SELECT `spell` FROM `character_spell` WHERE `guid`={};", i);
            if (!spell_results)
                continue;
            do
            {
            	LOG_INFO("module", "GUIDS: Spell: {}", spell_results->Fetch()[0].Get<uint32>());
                Spells.push_back(spell_results->Fetch()[0].Get<uint32>());
            } while (spell_results->NextRow());
        }


    }
};

// Add all scripts in one
void AddMyPlayerScripts()
{
    new MyPlayer();
}
