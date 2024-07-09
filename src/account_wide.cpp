/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

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
/*------------------------------------------------------------------------------------------------------------------------------*/
/*	Get all the GUIDS (alts) on the account											*/
/*------------------------------------------------------------------------------------------------------------------------------*/
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
/*------------------------------------------------------------------------------------------------------------------------------*/
/*	Find out the Max Skill Level of each Profession										*/
/*------------------------------------------------------------------------------------------------------------------------------*/
	std::vector<uint32> MaxSkills;
	uint32 max_first_aid = 0;
        for (auto& i : Guids)
	{
	    LOG_INFO("accountwide", "MaxSkills_GUID: {}", i);
	    QueryResult value_skill_results = CharacterDatabase.Query("SELECT `value` FROM `character_skills` WHERE `skill` = 129 and `guid` = {};",i);
            if (!value_skill_results)
                continue;
            do
	    {
		Field* skill_fields = value_skill_results->Fetch();
		MaxSkills.push_back(skill_fields[0].Get<uint32>());
		if ( skill_fields[0].Get<uint32>() > max_first_aid )
		{
		    max_first_aid = skill_fields[0].Get<uint32>();
		}
//		uint32 sk_value = skill_fields[0].Get<uint32>();
		LOG_INFO("accountwide", "First Aid Max: {}", value_skill_results->Fetch()[0].Get<uint32>());
	    } while (value_skill_results->NextRow());
	}
	LOG_INFO("accountwide", "Maximum First Aid on Account: {}", max_first_aid);

/*------------------------------------------------------------------------------------------------------------------------------*/
/*	Build a list of all known spells for each GUID for the aaccount owner							*/
/*------------------------------------------------------------------------------------------------------------------------------*/
        std::vector<uint32> Spells;
        for (auto& i : Guids)
        {
	    LOG_INFO("accountwide", "Spells_GUID: {}", i);
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
/*-----------------------------------------------------------------------------------------------------------------------------*/
/*
        for (uint32 i = 1; i < sSkillLineAbilityStore.GetNumRows(); ++i)
        {
	    SkillLineAbilityEntry const* SkillInfo = sSkillLineAbilityStore.LookupEntry(i);
 	    if (SkillInfo)
		{
		if ( std::find(Spells.begin(), Spells.end(), SkillInfo->Spell) != Spells.end() )
		{
		    if ( SkillInfo->SkillLine == 197 && !theplayer->HasSpell(SkillInfo->Spell))
		    {
			//LOG_INFO("accountwide", "Learning Tailoring Spell:  {}", SkillInfo->Spell);
		        //theplayer->learnSpell( SkillInfo->Spell );
		    }
		}
	    }
	}
        for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
        {
            SkillLineEntry const* SkillInfo = sSkillLineStore.LookupEntry(i);

            if (!SkillInfo)
                continue;

            if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) && !SkillInfo->canLink)
                continue;

            uint32 SkillID = SkillInfo->id;
            //uint32 CategoryID = SkillInfo->categoryId;

            if (theplayer->HasSkill(SkillID))
            {
                switch (SkillID)
                {
                    case SKILL_ALCHEMY:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Alchemy Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_BLACKSMITHING:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Blacksmithing Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_ENCHANTING:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Enchanting Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_ENGINEERING:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Engineering Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_INSCRIPTION:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Inscription Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_JEWELCRAFTING:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Jewelcrafting Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_LEATHERWORKING:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Leatherworking Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_TAILORING:
                //player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), 450, 450);
                theplayer->SetSkill(SkillID, theplayer->GetSkillStep(SkillID),theplayer->GetSkillValue(SkillID) , 450);
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Tailoring Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_SKINNING:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Skinning Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_HERBALISM:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Herbalism Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_MINING:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Mining Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_COOKING:
			//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Cooking Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_FIRST_AID:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			//LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "First Aid Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    default:
                        break;
                }
	    }
	}
*/
    }
};

void AddAccountWideScripts()
{
    new AccountWide();
}
