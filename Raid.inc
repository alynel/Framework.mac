| Latest update DEC 2016
| RAID.inc
|HOLIES
|holyshit26=/if (${Raid.Members} && ${Me.CombatState.Equal[COMBAT]} && !${Bool[${Me.Buff[Divine Indemnification Rk. II].ID}]}) /bc I need DI
|holyshit26=/if (${Raid.Members} && ${Me.CombatState.Equal[COMBAT]} ${Target.PctHPs}<20) /bc I need a heal health <10

|CHANGES TO MAKE TO MACROS
|ADD _ #include Raid.inc to macro start
|ADD _ /call GeneralDeclares3 to submain
|If using kiss add #bind Switchnowraid      /switchnowraid
| ----------------------------------------------------------------------------
| SUB: Bind Switchnowraid
| ----------------------------------------------------------------------------
|   Sub Bind_Switchnowraid(raidtargetnow)
|       /echo New target called!
|       /call CombatReset
|        /varset MyTargetID ${raidtargetnow}
|		/target ${raidtargetnow}
|		/nav target
|        /call Combat
|    /return


|General
#event QM         		  "<#1#> Mana <10 percent QM please.#*#"
#event DI         		  "<#1#> I need DI#*#"
#event RC         		  "<#1#> I need RC#*#"
#event HealRequest        "<#1#> I need a heal"

#event Raidbuffup         "<#1#> RAIDBUFF#*#"
#event WARDCAST           "<#1#> Ward Faded#*#"
#event SPLASHNOW          "<#1#> SPLASH NOW#*#"

#event Relocate           "<#1#> Relocate#*#"
#event ChangeMA           "#1#tells the raid, I am the new Main Assist#*#"

#Event BerAlli         "#1#is targeted by a demolisher's alliance."
|Maestro
#event PalSplashHate      "#*#mana begins to seep away.#*#"
#event PalSplashHate      "#*#is drained.#*#"
#event PalSplashHate      "#*#Maestro of Rancor’s life is drained away.#*#"
#event PalSplashHate      "#*#life is drained away.#*#"
#event HealerCorruption   "#*#A dissonant chord rings in your ears#*#"
#event HealerCorruption   "#*#You are done in by bad things#*#"
|Inny
#event Innymove         "#1#tells the group, 'AURA#1#'#*#"
|Dracholiche
#event Relocate   "#*#The dragon beats its mighty wings and sends you flying.#*#"
#event Relocate   "#*#a dracholiche begins to cast a spell. <Dragon Fear>#*#"
#event Relocate   "#*#You feel a sense of doom upon you#*#"
|VimVigor
#event PalSplashHate   "#*#Curse you who would assault our faith!#*#"
#event PalSplashHate   "#*#Vim begins to cast a spell. <Barrier to Health>#*#"
#event PalSplashHate   "#*#Vim begins to cast a spell. <Increasing Decay>#*#"
#event PalSplashHate   "#*#Death pulses in your heart.#*#"
#event RitSpawn   "#*#The bond between Vim and Vigor has been weakened by your attacks. However, Bokon appear from nowhere and begin chanting, bolstering the magical power of Vim and Vigor, trying to keep their bond strong.#*#"
#event YellowAura   "#*#You are protected by the power of Anashti Sul#*#"
#event RadiantAnnounce   "#*#Death pulses in your heart.#*#"
#event RadiantAnnounce   "#*#Your ability to be healed is partially blocked.#*#"
#event RadiantAnnounce   "#*#You have become extremely vulnerable to disease.#*#"
#event Balance   "#*#Vim and Vigor have recovered their bond of health.#*#"
#event BurnVIM   "#*#With all the ritualists dead, it will take time for Vim and Vigor to regain their bond of health.#*#"
#event YellowAura2   "<#1#> I need a yellow Aura#*#"

|Kill adds
|Lcea
#event GoreLeft      "#*#Gorenaire's left wing twitches#*#" -avoid right side
#event GoreRight      "#*#Gorenaire's right wing twitches#*#"-avoid left side
#event GoreBack      "#*#Gorenaire's tail twitches#*#"-avoid back side
#event GorePop1      "#*#Gorenaire's freezing breath coalesces into living things. Angry living things.#*#"-Blizzards and Squalls Spawn
#event GorePop2     "#*#Praetor Denik shouts, 'We need reinforcements at the #1# breach!#*#"-avoid back side
#event GorePop3      "#*#Gorenaire calls for aid, and you immediately hear the beating of wings.#*#"-Drake's Spawning
#event GorePop4      "#*#Denik shouts, 'Be ready, incoming enemy reinforcements! I don't like the look of those shields!#*#"-Flame Assulters Inc
#event GorePop5      "#*#Praetor Denik shouts, 'Heroes! We need you in the#*#"-Giants Inc
#event GorePop6      "#*#Tsaph Katta shouts, 'No! We cannot allow out praetor august magio to be killed! Only they can repair our barriers, and we need those barriers!#*#"-Barrier Adds In Trouble
|Sul Group Mission
#event Sul     			  "#*#has been targeted for poison blast!#*#"
#event Sul2				  "#*#Anashti Sul, Lady of Life begins to cast a spell. <Mark of Sul>#*#"
#event Sul3				  "<#1#> BACKOFF#*#"


#event FASTKILL       	  "<#1#> Kill them now#*#"



Sub GeneralDeclares3
   /echo Setting up all raid Variables.
   /declare Tank1	 string outer Gegolian
   /declare Tank2	 string outer Oamuk
   /declare Tank3	 string outer Oamuk
   /declare Tank4	 string outer Oamuk
   /declare Tank5	 string outer Oamuk

   /declare Innymovevariable	 string outer Empty
   /declare ClericSPLASHROTATION int outer 0
   /declare Cleric1 string outer Amriel
   /declare Cleric2 string outer Suede
   /declare Cleric3 string outer Dennwiny
   /declare raidbuffup string outer NULL
   /declare movetotarget int outer 0
   /declare movecall int outer 0
   /declare AEOK int outer 0
   /declare CampXLoc2               int         outer       ${Me.X}
   /declare CampYLoc2              int         outer       ${Me.Y}
   /declare InnyXLoc               int         outer       ${Me.X}
   /declare InnyYLoc               int         outer       ${Me.Y}

/return


|---------------------------------------------------------------------
|General
Sub Event_QM(Line,NeedQM)
    /if (${Me.Class.ShortName.Equal[CLR]}) {
		/tar ${NeedQM}
		/if (${Target.PctMana}<10) /alt act 135
		}
/return

Sub Event_SPLASHNOW
    /if (${Me.Class.ShortName.Equal[PAL]}) {
		/echo Pally Splash
		/call WaitCast
		/tar ${MainAssist}
		/casting "${Spell[Splash of Atonement].RankName}"
		/return
		}
	/if (${Me.Class.ShortName.Equal[CLR]} && ${Me.SpellReady[Convalescent Splash].RankName}) {
		/echo Cleric Splash
		/call WaitCast
		/tar ${MainAssist}
		/casting "${Spell[Convalescent Splash].RankName}"
		/return
		}
	    /if (${Me.Class.ShortName.Equal[SHM]} && ${Me.SpellReady[Spiritual Surge].RankName}) {
		/echo Shaman Splash
		/call WaitCast
		/tar ${MainAssist}
		/casting "${Spell[Spiritual Surge].RankName}"
		/return
		}
/return

Sub Event_WARDCAST(Line,NeedWARD)
    /if (${Me.Class.ShortName.Equal[CLR]}) {
		/target ${NeedWARD}
		/call WaitCast
		/if (!${Target.Buff[Ward of Surety].ID}) /casting "${Spell[Ward of Surety].RankName}"
		/bc Casting WARD
		}
/return

Sub Event_DI(Line,NeedDI)
    /if (${Me.Class.ShortName.Equal[CLR]}) {
		/call WaitCast
		/target ${NeedDI}
		/casting "${Spell[Divine Indemnification].RankName}"
		/bc Casting DI
		}
/return


Sub Event_RC(Line,NeedRC)
    /if (${Me.Class.ShortName.Equal[CLR]}) {
		/target ${NeedRC}
		/alt act 153
		/bc Casting RC on ${NeedDI}
		}
/return

Sub Event_HealRequest(Line,NeedHeal)
    /if (${Me.Class.ShortName.Equal[RNG]}) {
		/call WaitCast
	}
		/target ${NeedHeal}
		/bc Healing ${NeedHeal}
		/casting "${Spell[Cloudfont].RankName}"
		}
	/if (${Me.Class.ShortName.Equal[BST]}) {
		/call WaitCast
		/target ${NeedHeal}
		/bc Healing ${NeedHeal}
		/casting "${Spell[Sabhattin's Mending].RankName}"
		}
/return

Sub Event_Raidbuffup(Line,MainAssist)
  /if (${Select[${Me.Class.ShortName},WAR,WIZ,NEC,SHD,MAG,ROG,MNK,BRD,BER]}) /return 
  /if (${Select[${Me.Class.ShortName},ENC]}) {
	/varset raidbuffup ${Spell[Hastening of Prokev].RankName}
	/memorize "${raidbuffup}" gem ${MiscGem}
	/delay 15s
	/tgb on
	/tar ${MainAssist}
    /alt act 992
    /casting "${Spell[Hastening of Prokev].RankName}" -maxtries 3
    /delay 30s
    /return
  }
  /if (${Select[${Me.Class.ShortName},CLR]}) {
    /varset raidbuffup ${Spell[Unified Hand of Nonia].RankName}
	/memorize "${raidbuffup}" gem${MiscGem}
	/delay 15s
	/tgb on
	/tar ${MainAssist}
	/bc test
	/alt act 992
	/casting "${Spell[Unified Hand of Nonia].RankName}" gem8
	/delay 30s
    /return
  }
  /if (${Select[${Me.Class.ShortName},SHM]}) {
	/varset raidbuffup ${Spell[Talisman of the Doomscale].RankName}
	/memorize "${raidbuffup}" gem${MiscGem}
	/delay 15s
	/tgb on
    /tar ${MainAssist}
	/alt act 992
	/casting "${Spell[Talisman of the Doomscale].RankName}" -maxtries 3
    /return
  }
  /if (${Select[${Me.Class.ShortName},RNG]}) {
  	/varset raidbuffup ${Spell[Shout of the Copsestalker].RankName}
	/memorize "${raidbuffup}" gem${MiscGem}
	/delay 15s
	/tgb on
    /tar ${MainAssist}
    /alt act 992
	/casting "${Spell[Shout of the Copsestalker].RankName}" -maxtries 3
    /return
  }
  /if (${Select[${Me.Class.ShortName},PAL]}) {
	/varset raidbuffup ${Spell[Brell's Stalwart Bulwark].RankName}
	/memorize "${raidbuffup}" gem${MiscGem}
	/delay 15s
	/tgb on
    /tar ${MainAssist}
    /alt act 992
	/casting "${Spell[Brell's Stalwart Bulwark].RankName}" -maxtries 3
    /return
  }
  /if (${Select[${Me.Class.ShortName},BST]}) {
	/varset raidbuffup ${Spell[Stormblood's Unity].RankName}
	/memorize "${raidbuffup}" gem${MiscGem}
	/delay 15s
	/tgb on
    /tar ${MainAssist}
    /alt act 992
	/casting "${Spell[Stormblood's Unity].RankName}" -maxtries 3
	/return
  }
  /if (${Select[${Me.Class.ShortName},DRU]}) {
	/varset raidbuffup ${Spell[Shieldstone Blessing].RankName}
	/memorize "${raidbuffup}" gem${MiscGem}
	/delay 15s
	/tgb on
    /tar ${MainAssist}
    /alt act 992
	/casting "${Spell[Shieldstone Blessing].RankName}" -maxtries 3
    /return
  }
/return

Sub Event_SWITCH(Line,ASSIST)
    /if (${Macro.Name.Equal[kissassistraid.mac]}) /switch
	/if (${Macro.Name.Equal[eoknuke.mac]}) /keypress esc
/return

|Sub Event_Relocate(Line,ASSIST)
|/target ${MainAssist}
|/varset movetotarget ${Target.ID}
|/moveto id ${movetotarget} mdist 5
|/return
Sub Event_BerAlli
    /popup Ber Alliance fired
/return

|------------------------------------------------------------
|Maestro
Sub Event_PalSplashHate
    /if (${Me.Class.ShortName.Equal[PAL]}) {
		/call WaitCast
		/echo Pally Splash
		/if (${Me.Sitting}) /stand
		/tar ${Me}
		/call WaitCast
		/casting "${Spell[Splash of Atonement].RankName}"
		/delay 5s
		/if (!${Me.Sitting}) /sit
		}
/return


Sub Event_HealerCorruption
    /if (${Me.Class.ShortName.Equal[Clr]}) {
	/bc Curing Group
	/call WaitCast
	/casting "${Spell[Nullify Corruption].RankName}"
	} else /if (${Me.Class.ShortName.Equal[DRU]}) {
	/bc Curing Group
	/call WaitCast
	/casting "${Spell[Chant of the Kromtus].RankName}"
	} else /if (${Me.Class.ShortName.Equal[SHM]}) {
	/bc Curing Group
	/call WaitCast
	/casting "${Spell[Chant of the Kromtus].RankName}"
	}
/return


|---------------------------------------------------------------------
|Sul Group Mission


Sub Event_Sul(Line,MainAssist)
/target ${MainAssist}
/bc moving
/varset movetotarget ${Target.ID}
/moveto id ${movetotarget} mdist 5
/return

Sub Event_Sul2(Line,NeedDI)
 /if (${Me.Class.ShortName.Equal[WIZ]}) {
	/tar Anashti
	/alt act 547
	/bc Dispelling Aweful BUFF!
	}
/return

Sub Event_Sul3(Line,NeedDI)
/switch
/pet back off 
/target ${MainAssist}
/bc YEAH YEAH YEAH 
/varset movetotarget ${Target.ID}
/moveto id ${movetotarget} mdist 2
/return

Sub Event_ChangeMA(Line,NEWMAINTANK)
    /if (${MainAssist.Equal[${Tank1}]} && ${Macro.Name.Equal[kissassist.mac]}) {
		/varset MainAssist ${Tank2}
		/return
		}
	/if (${MainAssist.Equal[${Tank2}]} && ${Macro.Name.Equal[kissassist.mac]}) {
		/varset MainAssist ${Tank3}
		/return
		}
	/if (${MainAssist.Equal[${Tank3}]} && ${Macro.Name.Equal[kissassist.mac]}) {
		/varset MainAssist ${Tank4}
		/return
		}
	/if (${MainAssist.Equal[${Tank4}]} && ${Macro.Name.Equal[kissassist.mac]}) {
		/varset MainAssist ${Tank1}
		/return
		}
	/if (${Macro.Name.Equal[Eokk.mac]}) {
		/keypress esc
        /assist ${Tank2}
		/return
		}
	/if (${Macro.Name.Equal[Eokk.mac]}) {
		/keypress esc
        /assist ${Tank3}
		/return
		}
	/if (${Macro.Name.Equal[Eokk.mac]}) {
		/keypress esc
        /assist ${Tank4}
		/return
		}
	/if (${Macro.Name.Equal[Eokk.mac]}) {
		/keypress esc
        /assist ${Tank4}
		/return
		}
	/if (${Macro.Name.Equal[Autoclericraid.mac]}) {
		/varset tankname ${NEWMAINTANK}
		/echo Main Tank set to ${NEWMAINTANK}
		/return
		}
	/if (${Macro.Name.Equal[Autoshamraid.mac]}) {
		/varset tankname ${NEWMAINTANK}
		/echo Main Tank set to ${NEWMAINTANK}
		/return
		}
	/if (${Macro.Name.Equal[Autozerker.mac]}) {
		/varset tankname ${NEWMAINTANK}
		/echo Main Tank set to ${NEWMAINTANK}
		/return
		}
	}
/return

Sub Event_FASTKILL(Line,MainAssist)
  /if (${Select[${Me.Class.ShortName},PAL,DRU,WAR,WIZ,NEC,SHD,MAG,ROG,MNK]}) /return 
  /if (${Select[${Me.Class.ShortName},ENC]}) {
	/tar ${MainAssist}
	/delay 1s
    /return
  }
  /if (${Select[${Me.Class.ShortName},CLR]}) {
    /tar ${MainAssist}
	/delay 1s
    /return
  }
  /if (${Select[${Me.Class.ShortName},SHM]}) {
  /return
|Ancestral Aid - Increase Dex Cap 310
|Prophet's Gift of Ruchu - Increase Chance to Critical Hit by 65%, Increase Critical Hit Damage by 110%
|3rd Spire of the Ancestors - Increase Proc Rate by 25%, Increase Min Hit Dmg by 45%
|Roar of the Lion - Add proc Lion's Roar (13265-16929 dmg) with 400% rate mod
  }
  /if (${Select[${Me.Class.ShortName},RNG]}) {
  
  /return
|  Auspice of the Hunter - Increase Chance to Critical Hit by 225%, Increase Chance to Critical Nuke by 33%, Increase ATK by 380
|  Scarlet Cheetah Fang - Twincast the next 25 skill attacks
  
  }
  /if (${Select[${Me.Class.ShortName},BER]}) {
	/bc Burning
	/stopdisc
	/alt act 752
	/alt act 752
	/alt act 752
	/disc ${Spell[Frenzied Resolve].RankName}
	/delay 1s
	/disc ${Spell[Untamed Rage].RankName}
	/delay 1s
	/disc ${Spell[Cry Havoc].RankName}
	/delay 1s
	/disc ${Spell[Shared Cruelty].RankName}
	/delay 1s
	/disc ${Spell[Sapping Strikes].RankName}
	/delay 1s
	/disc ${Spell[Bubbling Rage].RankName}
	/delay 1s
	/alt act 752
	/delay 5s
	/disc ${Spell[Amplified Frenzy].RankName}
	/delay 1s
	/alt act 1501
	/alt act 610
	/useitem "Cohort's Warmonger Coat"
|	/useitem (epic)
	/alt act 1142
	/alt act 379
	/alt act 465
	/alt act 3710
	/alt act 961
	/alt act 7019
	/alt act 1142
	/return
	}
  /if (${Select[${Me.Class.ShortName},BST]}) {
	| 1 RF + BA + Frenzied Swipes + Beastial Bloodrage + Glyph
	| 2 Spirit Frenzy + Bloodlust + First Spire
	  
	| 3 Ferociousness

	  /return
  }
    /if (${Select[${Me.Class.ShortName},BRD]}) {
	|  Aria of Maetanrus - Increase HasteV3 by 25%, Increase Chance to Triple Attack by 40%, Increase Chance to Flurry by 21.6%*
	|Fierce Eye - Increase Critical Hit Damage by 12%, Increase Proc Rate by 300%
	|Quick Time - Decrease Weapon Delay by 14.5%, Increase Atk by 1080*, Increase Chance to Hit by 79.2%*
	|Funeral Dirge - Increase Hit Damage Taken by 22%
	/return
  }

/return



|-------------------------------------------------------
|Inny


Sub Event_Innymove(Line,ASSIST)
/moveto loc ${InnyYLoc} ${InnyXLoc} mdist 1
/delay 5s
/moveto loc ${CampYLoc2} ${CampXLoc2} mdist 1
/delay 5s
/return

Sub Event_Relocate(Line,Aura)
	/if (${Aura}== 1){
	/varset InnyYLoc
	/varset InnyXLoc
	/return
	}
	/if (${Aura}== 2){
	/varset InnyYLoc
	/varset InnyXLoc
	/return
	}
	/if (${Aura}== 3){
	/varset InnyYLoc
	/varset InnyXLoc
	/return
	}
/return


|---------------------------------------------------------
|Dracholiche





|--------------------------------------------------------------------------------
|Lcea

Sub Event_GoreLeft 
    /stick snaproll left
/return

Sub Event_GoreRight
    /stick snaproll right
/return

Sub Event_GoreBack
    /stick snaproll left
/return

Sub Event_GorePop1
    /popup Blizzards and Squalls Spawn
/return

Sub Event_GorePop2(Line,Breach)
    /popup Break through at ${Breach} gate
/return

Sub Event_GorePop3
    /popup Drake's Spawning
/return

Sub Event_GorePop4
    /popup Flame Assulters Inc
/return

Sub Event_GorePop5
    /popup Giants Inc
/return

Sub Event_GorePop6
    /popup Barrier Adds In Trouble
/return


|--------------------------------------------------------------------------------
| Vim and Vigor


Sub Event_RadiantAnnounce
    /bc I need RC
/return

Sub Event_YellowAura
    /bc I need a yellow Aura
/return

Sub Event_RitSpawn
    /popup Ritualists Spawned!
/return

Sub Event_YellowAura2(Line,NeedAura)
    /popup Break through at ${NeedAura} gate
/return

Sub Event_Balance
    /popup Balance Mobs
/return

Sub Event_BurnVIM
    /popup Burn Vim
/return


|--------------------------------------------------------------------------------
|Misc

Sub WaitCast(string sentFrom)
:rewaitcast
|	/if (${sentFrom.Equal[SingleHeal]} && ${CastingInterruptOn}) {
|		/call KACheckHP
|	} else /if (${Select[${sentFrom},dps,gom,burn]} > 0 && ${CastingInterruptOn}) {
|		/call KACheckDPS
|	} else /if (${Select[${sentFrom},buffs,buffs-nomem]} > 0 && ${CastingInterruptOn}) {
|		/call KACheckBUFFS
|	}
	/if (${Cast.Status.NotEqual[I]} || ${Me.Casting.ID}) {
		/delay 1
		/goto :rewaitcast
	}
	/echo ${Cast.Result}
/return