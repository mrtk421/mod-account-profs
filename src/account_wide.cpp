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
/*-----------------------------------------------*/
/*    Get all the GUIDS (alts) on the account    */
/*-----------------------------------------------*/
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

        for (auto ctr: profIds)
        {
            std::vector<uint32> MaxSkills;
            uint32 max_skill_act = 0;
            for (auto& i : Guids)
            {
                LOG_INFO("accountwide", "MaxSkills_GUID: {}", i);
                QueryResult value_skill_results = CharacterDatabase.Query("SELECT `value` FROM `character_skills` WHERE `skill` = {} and `guid` = {};",ctr, i);
                    if (!value_skill_results)
                        continue;
                    do
		    {
                        Field* skill_fields = value_skill_results->Fetch();
                        MaxSkills.push_back(skill_fields[0].Get<uint32>());
                        if ( skill_fields[0].Get<uint32>() > max_skill_act )
                        {
                            max_skill_act = skill_fields[0].Get<uint32>();
                        }
                        LOG_INFO("accountwide", "First Aid Max: {}", value_skill_results->Fetch()[0].Get<uint32>());
                    } while (value_skill_results->NextRow());
            }
            LOG_INFO("accountwide", "Maximum Skill for {} on Account: {}", ctr, max_skill_act);
            theplayer->SetSkill(ctr, theplayer->GetSkillStep(ctr),max_skill_act , 450);
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
                if (spell_results->Fetch()[0].Get<uint32>() == 3909)
                {
                   //LOG_INFO("accountwide", "Player knows Spell: {}", spell_results->Fetch()[0].Get<uint32>());
                   //theplayer->learnSpell(  spell_results->Fetch()[0].Get<uint32>() );
                }


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
                            LOG_INFO("accountwide", "Learning {} : Spell:  {}", ctr, SkillInfo->Spell);
                            theplayer->learnSpell( SkillInfo->Spell );
                        }
                    }
                }
            }
        }
    }
};

void AddAccountWideScripts()
{
    new AccountWide();
}
