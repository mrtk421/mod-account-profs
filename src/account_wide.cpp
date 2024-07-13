/* * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"


class AccountWide : public PlayerScript
{
public:
    AccountWide() : PlayerScript("AccountWide") { }

  void OnLogin(Player* theplayer) override
   {
    if (sConfigMgr->GetOption<bool>("Account.Wide.Enable", false) == true) {
/*-----------------------------------------------*/
/*    Get all the GUIDS (alts) on the account    */
/*-----------------------------------------------*/
        LOG_INFO("accountwide", "Account Wide Module Enabled");
        uint32 playerAccountID = theplayer->GetSession()->GetAccountId();
        std::vector<uint32> Guids;
        QueryResult guid_results = CharacterDatabase.Query("SELECT `guid` FROM `characters` WHERE `account`={};", playerAccountID);
        if (!guid_results)
            return;
        do
        {
            Field* act_fields = guid_results->Fetch();
            Guids.push_back(act_fields[0].Get<uint32>());
        } while (guid_results->NextRow());
/*-------------------------------------------------*/
/*    Set the Skill Level of all Profession IDs    */
/*-------------------------------------------------*/
        std::vector<uint32> profIds;
        profIds.push_back(129);        // First Aid
        profIds.push_back(164);        // Blacksmithing
        profIds.push_back(165);        // Leatherworking
        profIds.push_back(171);        // Alchemy
        profIds.push_back(182);        // Herbalism
        profIds.push_back(185);        // Cooking
        profIds.push_back(186);        // Mining
        profIds.push_back(197);        // Tailoring
        profIds.push_back(202);        // Engineering
        profIds.push_back(333);        // Enchanting
        profIds.push_back(393);        // Skinning
        profIds.push_back(755);        // Jewelcrafting
        profIds.push_back(773);        // Inscription
        profIds.push_back(356);        // Fishing

        for (auto ctr: profIds)
        {
            std::vector<uint32> ValueSkills;
            std::vector<uint32> MaxSkills;
            uint32 max_skill_act = 0;
            uint32 value_skill_act = 0;
            for (auto& i : Guids)
            {
                QueryResult value_skill_results = CharacterDatabase.Query("SELECT `value` FROM `character_skills` WHERE `skill` = {} and `guid` = {};",ctr, i);
                QueryResult max_skill_results = CharacterDatabase.Query("SELECT `max` FROM `character_skills` WHERE `skill` = {} and `guid` = {};",ctr, i);
                    if (!value_skill_results)
                        continue;
                    do
                    {
                        Field* max_skill_fields = max_skill_results->Fetch();
                        Field* value_skill_fields = value_skill_results->Fetch();
                        ValueSkills.push_back(value_skill_fields[0].Get<uint32>());
                        MaxSkills.push_back(max_skill_fields[0].Get<uint32>());
                        if ( max_skill_fields[0].Get<uint32>() > max_skill_act )
                        {
                            max_skill_act = max_skill_fields[0].Get<uint32>();
                        }
                        if ( value_skill_fields[0].Get<uint32>() > value_skill_act )
                        {
                            value_skill_act = value_skill_fields[0].Get<uint32>();
                        }
                    } while (value_skill_results->NextRow());
            }
            theplayer->SetSkill(ctr, theplayer->GetSkillStep(ctr),value_skill_act , max_skill_act);
        }
/*-----------------------------------------------------------------------------*/
/*    Build a list of all known spells for each GUID for the aaccount owner    */
/*-----------------------------------------------------------------------------*/
        std::vector<uint32> Spells;
        for (auto& i : Guids)
        {
            QueryResult spell_results = CharacterDatabase.Query("SELECT `spell` FROM `character_spell` WHERE `guid`={};", i);
            if (!spell_results)
                continue;
            do
            {
                Spells.push_back(spell_results->Fetch()[0].Get<uint32>());
            } while (spell_results->NextRow());
        }
/*----------------------------------------------------------------------*/
/*    Compare the spells to Profession spells and learn if not known    */
/*----------------------------------------------------------------------*/
        for (auto ctr: profIds)
        {
            for (uint32 i = 1; i < sSkillLineAbilityStore.GetNumRows(); ++i)
            {
                SkillLineAbilityEntry const* SkillInfo = sSkillLineAbilityStore.LookupEntry(i);
                if (SkillInfo)
                {
                    if ( std::find(Spells.begin(), Spells.end(), SkillInfo->Spell) != Spells.end() )
                    {
                        if ( SkillInfo->SkillLine == ctr && !theplayer->HasSpell(SkillInfo->Spell))
                        {
                            //LOG_INFO("accountwide", "Learning {} : Spell:  {}", ctr, SkillInfo->Spell);
                            theplayer->learnSpell( SkillInfo->Spell );
                        }
                    }
                }
            }
        }
    } else {
	LOG_INFO("accountwide", "Account Wide Module Disabled");
    }
  }

};

void AddAccountWideScripts()
{
    new AccountWide();
}
