# mod-account-wide

### This is a module for [AzerothCore](http://www.azerothcore.org)

## What this mod does

1. This mod will attempt to copy known profession skill levels and recipes to each alt when you log in.
2. This assumes that your Azerothcore server can support all professions on one character.
   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;worldserver.conf: MaxPrimaryTradeSkill = 11

3. For loggin add these entries to the worldserver.conf

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Appender.accountwide=2,5,1,AccountWide.log,a<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Logger.accountwide=4,Console Server accountwide

4. This is a super early release and hasn't been tested a lot.

## Features to come

1.  Account wide Professions (already a mod out there, but maybe include it here)
2.  Account wide reputation
