# mod-account-wide

### This is a module for [AzerothCore](http://www.azerothcore.org)

## What this mod does

1. This mod will attempt to copy known profession skill levels and recipes to each alt when you log in.
2. This assumes that your Azerothcore server can support all professions on one character.
   
    worldserver.conf: MaxPrimaryTradeSkill = 11

3. For loggin add these entries to the worldserver.conf

    Appender.accountwide=2,5,1,AccountWide.log,a
    Logger.accountwide=4,Console Server accountwide

4. This is a super early release and hasn't been tested a lot.

