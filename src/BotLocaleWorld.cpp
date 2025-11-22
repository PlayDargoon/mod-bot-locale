/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>
 */

#include "ScriptMgr.h"
#include "Config.h"
#include "PlayerbotTextMgr.h"

class BotLocaleWorld : public WorldScript
{
public:
    BotLocaleWorld() : WorldScript("BotLocaleWorld") { }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        // Check if module is enabled
        if (!sConfigMgr->GetOption<bool>("BotLocale.Enable", false))
        {
            LOG_INFO("module", ">> Bot Locale Module is disabled in configuration");
            return;
        }

        // Get configured locale
        int32 configuredLocale = sConfigMgr->GetOption<int32>("BotLocale.DefaultLocale", 8);

        // Validate locale range (0-8 for WotLK)
        if (configuredLocale < 0 || configuredLocale >= MAX_LOCALES)
        {
            LOG_ERROR("module", ">> Bot Locale Module: Invalid locale {} configured! Must be 0-8. Defaulting to 0 (English)", configuredLocale);
            configuredLocale = 0;
        }

        // Set the locale priority for bots
        sPlayerbotTextMgr->ResetLocalePriority();
        sPlayerbotTextMgr->AddLocalePriority(configuredLocale);
        
        // Add a high priority count to ensure this locale is always selected
        for (int i = 0; i < 100; ++i)
        {
            sPlayerbotTextMgr->AddLocalePriority(configuredLocale);
        }

        const char* localeNames[] = {"enUS", "koKR", "frFR", "deDE", "zhCN", "zhTW", "esES", "esMX", "ruRU"};
        LOG_INFO("module", ">> Bot Locale Module: Bots will use locale {} ({})", configuredLocale, localeNames[configuredLocale]);
    }
};

// Add all scripts in one
void AddBotLocaleScripts()
{
    new BotLocaleWorld();
}
