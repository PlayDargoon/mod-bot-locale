/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Log.h"
#include "Common.h"

// Forward declaration of PlayerbotTextMgr interface
class PlayerbotTextMgr
{
public:
    static PlayerbotTextMgr* instance();
    void AddLocalePriority(uint32 locale);
    void ResetLocalePriority();
    uint32 GetLocalePriority();
};

#define sPlayerbotTextMgr PlayerbotTextMgr::instance()

// Force locale for playerbots
class ForceLocalePlayer : public PlayerScript
{
public:
    ForceLocalePlayer() : PlayerScript("ForceLocalePlayer") { }

    void OnPlayerLogin(Player* player) override
    {
        // Check if module is enabled
        if (!sConfigMgr->GetOption<bool>("ForceLocale.Enable", false))
            return;

        if (!player)
            return;

        // Get configured locale (default 7 = esMX, used for Russian in 8-locale setup)
        uint32 forcedLocale = sConfigMgr->GetOption<uint32>("ForceLocale.Locale", 7);

        // Validate locale
        if (forcedLocale >= MAX_LOCALES)
        {
            LOG_ERROR("module", "ForceLocale: Invalid locale {} configured (MAX_LOCALES={}). Using locale 7", 
                     forcedLocale, MAX_LOCALES);
            forcedLocale = 7;
        }

        // Reset all locale priorities and set only the forced one
        sPlayerbotTextMgr->ResetLocalePriority();
        
        // Add forced locale with high priority (simulate 100 players)
        for (uint8 i = 0; i < 100; ++i)
        {
            sPlayerbotTextMgr->AddLocalePriority(forcedLocale);
        }

        // Get locale name for logging
        const char* localeName = GetLocaleName(forcedLocale);
        
        LOG_INFO("module", "ForceLocale: Set playerbots locale to {} ({}) for player {}", 
                 localeName, forcedLocale, player->GetName());
    }

private:
    const char* GetLocaleName(uint32 locale)
    {
        switch (locale)
        {
            case LOCALE_enUS: return "enUS";
            case LOCALE_koKR: return "koKR";
            case LOCALE_frFR: return "frFR";
            case LOCALE_deDE: return "deDE";
            case LOCALE_zhCN: return "zhCN";
            case LOCALE_zhTW: return "zhTW";
            case LOCALE_esES: return "esES";
            case LOCALE_esMX: return "esMX";
            case LOCALE_ruRU: return "ruRU";
            default: return "Unknown";
        }
    }
};

// Add all scripts
void AddForceLocalePlayerScripts()
{
    new ForceLocalePlayer();
}
