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
	std::vector<uint32> Guids;
        uint32 playerAccountID = theplayer->GetSession()->GetAccountId();
        QueryResult guid_results = CharacterDatabase.Query("SELECT `guid` FROM `characters` WHERE `account`={};", playerAccountID);
	Field* fields = guid_results->Fetch();
	Guids.push_back(fields[0].Get<uint32>());

        std::vector<uint32> Spells;
	//LOG_INFO("accountwide", "Leatherworking Skill:  {}", theplayer->GetBaseSkillValue(SKILL_LEATHERWORKING)  );
	//LOG_INFO("accountwide", "Alchemy Skill:  {}", theplayer->GetBaseSkillValue(SKILL_ALCHEMY)  );

        for (auto& i : Guids)
        {
            QueryResult spell_results = CharacterDatabase.Query("SELECT `spell` FROM `character_spell` WHERE `guid`={};", i);
            if (!spell_results)
                continue;
            do
            {
                Spells.push_back(spell_results->Fetch()[0].Get<uint32>());
		if (spell_results->Fetch()[0].Get<uint32>() == 3908)
		{
		    //theplayer->learnSpell(  spell_results->Fetch()[0].Get<uint32>() );
		}

            } while (spell_results->NextRow());
        }

        for (uint32 i = 1; i < sSkillLineAbilityStore.GetNumRows(); ++i)
        {
	//LOG_INFO("accountwide", "Before sSkillLineAbilityStore declare");
	    SkillLineAbilityEntry const* SkillInfo = sSkillLineAbilityStore.LookupEntry(i);
	
	    //LOG_INFO("accountwide", "Before SkillID declare");
 if (SkillInfo && SkillInfo->Spell == 3908) {
	    LOG_INFO("accountwide", "SkillID {}", SkillInfo->ID);
}


/*
	LOG_INFO("accountwide", "Before SkillLine declare");
            uint32 SkillLineID = SkillInfo->SkillLine;
	LOG_INFO("accountwide", "Before Spell declare");
            uint32 SpellID = SkillInfo->Spell;
	    if (SpellID == 3908)
	    {
	LOG_INFO("accountwide", "Inside IF");
		//LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
		//LOG_INFO("accountwide", "SkillLine ID:  {}", SkillLineID );
		//LOG_INFO("accountwide", "Spell ID:  {}", SpellID);
		//LOG_INFO("accountwide", "-----------------------------");
	    }
*/


	}
/*
        for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
        {
            SkillLineEntry const* SkillInfo = sSkillLineStore.LookupEntry(i);

            if (!SkillInfo)
                continue;

            if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) && !SkillInfo->canLink)
                continue;

            uint32 SkillID = SkillInfo->id;
            uint32 CategoryID = SkillInfo->categoryId;

            if (theplayer->HasSkill(SkillID))
            {
                switch (SkillID)
                {
                    case SKILL_ALCHEMY:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Alchemy Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_BLACKSMITHING:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Blacksmithing Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_ENCHANTING:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Enchanting Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_ENGINEERING:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Engineering Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_INSCRIPTION:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Inscription Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_JEWELCRAFTING:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Jewelcrafting Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_LEATHERWORKING:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Leatherworking Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_TAILORING:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Tailoring Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_SKINNING:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Skinning Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_HERBALISM:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Herbalism Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_MINING:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Mining Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_COOKING:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
			LOG_INFO("accountwide", "Cooking Skill:  {}", theplayer->GetSkillValue(SkillID) );
			LOG_INFO("accountwide", "-----------------------------");
                        break;
                    case SKILL_FIRST_AID:
			LOG_INFO("accountwide", "Skill ID:  {}", SkillID );
			LOG_INFO("accountwide", "Category ID:  {}", CategoryID );
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
