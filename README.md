# Bot Locale Module

Этот модуль позволяет принудительно устанавливать локаль для сообщений ботов в чате.

## Возможности

- Принудительная установка локали для всех сообщений ботов (0-8)
- Независимость от локали игроков на сервере
- Простая настройка через конфигурационный файл

## Установка

1. Скопируйте папку `mod-bot-locale` в `modules/`
2. Пересоберите сервер
3. Скопируйте `conf/bot-locale.conf.dist` в `conf/bot-locale.conf`
4. Настройте параметры в конфигурационном файле

## Настройка

Откройте `bot-locale.conf` и установите:

```ini
# Включить модуль
BotLocale.Enable = 1

# Установить локаль (0-8)
BotLocale.DefaultLocale = 8
```

### Доступные локали:

- `0` = enUS (English - United States)
- `1` = koKR (Korean)
- `2` = frFR (French)
- `3` = deDE (German)
- `4` = zhCN (Chinese)
- `5` = zhTW (Taiwanese)
- `6` = esES (Spanish - Spain)
- `7` = esMX (Spanish - Mexico)
- `8` = ruRU (Russian)

## Требования

- AzerothCore с модулем mod-playerbots
- Заполненные тексты в таблице `ai_playerbot_text` (колонки `text_loc1` - `text_loc8`)

## Лицензия

Copyright (C) 2016+ AzerothCore <www.azerothcore.org>
