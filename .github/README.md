# mod-account-wide

### This is a module for [AzerothCore](http://www.azerothcore.org)

## What this mod does

1. This mod will attempt to copy known profession skill levels and recipes to each alt when you log in.
2. The included mod-account-wide.conf.dist configuration file overrides the MaxPrimaryTradeSkill to allow all professions.
   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;MaxPrimaryTradeSkill = 11

3. The mod can be enabled or disabled with the following entry in the configuration file (1 = enabled / 0 = disabled).

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Account.Profs.Enable = 1

4. For logging these entries are in the configuration file

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Appender.accountwide=2,5,1,AccountProfs.log,w<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Logger.accountprofs=4,Console Server accountprofs

4. This is a super early release and hasn't been tested a lot.

## Links

Github Repository:	https://github.com/mrtk421/mod-account-profs
Github Download:	https://github.com/mrtk421/mod-account-profs.git


## Features to come?

1.  Account wide mounts  (already a mod out there, but maybe include it here)
2.  Account wide reputation (questions on how to implement - thinking that once a rep hits exalted, it then gets to be acocunt wide). Lots of issues with At War factions and competing factions like Aldor/Scryer.
