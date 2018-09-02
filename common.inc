|***
 *	Common.inc
 *	Framework Common Subs Include
 *
 *	
 ***|
	 Sub Custom_declares
			/declare mctimerseconds int outer 0
			/declare mctimer timer outer 0
			/declare skincount int outer 0

			/echo in custom declares
			/declare cyclecount             int         outer       0
			/declare healcount             int         outer       0
			/declare SpawnSearchType	string outer npc
			/call LoadIni Mod_Heal selfheal									int	80	
			/call LoadIni Mod_Heal UseModHeal								int	 1
			/declare tmpHealOverride										float outer 99.99
			
			/declare badaggroid 											int outer 0
			/declare modSingleHeal[15]         string      outer
			/declare modSHCond[15]             string      outer       TRUE
	|		/if (${HealsOn}) {
	|        /call FindmodSingleHeals
	|		}

			/declare Mod_MostHurtName       string      outer		NULL
			/declare Mod_MostHurtType       string      outer		NULL
			/declare Mod_MostHurtID         int         outer       0
			/declare Mod_MostHurtHP         int         outer       100
			/declare Mod_MostHurtNo         int         outer       0
			/declare Mod_WorstClass         string      outer
			/declare Mod_GroupHealthAvg     int      	outer       0
			/declare Mod_HurtMember     	int 		outer 		0
			/declare NULLPoint     	int 		outer 		100
			
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
	   
		
			/call LoadIni Mod_Heal Xtarheal_ON								int	 0
			/call LoadIni Mod_Heal grpheal									int	 75
			/call LoadIni Mod_Heal PetPoint 								int  80	
			/call LoadIni Mod_Heal CLRPoint		 							int  80
			/call LoadIni Mod_Heal DRUPoint 								int  70
			/call LoadIni Mod_Heal SHMPoint 								int  60
			/call LoadIni Mod_Heal WIZPoint 								int  75
			/call LoadIni Mod_Heal MAGPoint 								int  75
			/call LoadIni Mod_Heal ENCPoint 								int  80
			/call LoadIni Mod_Heal NECPoint 								int  75
			/call LoadIni Mod_Heal WARPoint 								int  70
			/call LoadIni Mod_Heal MNKPoint 								int  60
			/call LoadIni Mod_Heal ROGPoint 								int  60
			/call LoadIni Mod_Heal RNGPoint 								int  90
			/call LoadIni Mod_Heal BSTPoint 								int  70
			/call LoadIni Mod_Heal SHDPoint 								int  90
			/call LoadIni Mod_Heal BRDPoint 								int  65
			/call LoadIni Mod_Heal BERPoint 								int  70
			/call LoadIni Mod_Heal PALPoint 								int  90
			/call LoadIni Mod_Heal GoMpoint 								int  80	
			
			/declare ReportDefense bool outer FALSE
			
			/plugin mq2worsthurt load
		

		
		/if (${Select[${Me.Class.ShortName},BER]}) {
			/declare epicaxe					string outer NULL
			/declare UseEpic					int outer 0
			/if (${FindItem[Raging Taelosian Alloy Axe].ID}) {
				/varset epicaxe		Raging Taelosian Alloy Axe
				/varset UseEpic 1
			} else /if (${FindItem[Vengeful Taelosian Blood Axe].ID}) {
				/varset epicaxe		Vengeful Taelosian Blood Axe
				/varset UseEpic 1
			}
		}
		
	/return

| -------------------------------------------------------------------------------------
| SUB: newcombatcast
| -------------------------------------------------------------------------------------    
	Sub newcombatcast
			/if (${DebugCombat}) /echo \atDEBUGCOMBAT CombatCast Enter \agLine#: ${Macro.CurLine}
			/declare i int local
			/declare DPSStart    int      local ${Math.Calc[${DebuffCount}+1]}
			/if (${DPSStart}>${DPS.Size}) /return
			/declare DPSAt       int      local ${AssistAt}
			/declare DPSTargetID int      local ${MyTargetID}
			/declare WeaveCheck  int      local 0
			/declare SkipFlag    int      local 0
			/for i ${DPSStart} to ${DPS.Size}
			/doevents

			/if (${Select[${Me.Class.ShortName},CLR,DRU,SHM,BST,PAL,RNG]} && ${UseModHeal}==1 && ${HealsOn}==1 && (${Spawn[${WorstHurt[both,1,200,TRUE]}].Type.NotEqual[Pet]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName.NotEqual[Corpse]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} <= ${Math.Calc[${${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName}Point}*.${tmpHealOverride}]}) || (${Spawn[${WorstHurt[both,1,200,TRUE]}].Type.Equal[Pet]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName.NotEqual[Corpse]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} <= ${Math.Calc[${PetPoint}*.${tmpHealOverride}]})) {
				/Echo Heal from Precombat While "${Spawn[${WorstHurt[both,1,200,TRUE]}].CleanName}" "${Spawn[${WorstHurt[both,1,200,TRUE]}].Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} 0 G
				|/echo ${Macro.CurLine}
				/call newSingleHeal "${Spawn[${WorstHurt[both,1,200,TRUE]}].CleanName}" "${Spawn[${WorstHurt[both,1,200,TRUE]}].Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} 1 G
				|/return
			}
			/if (${Spawn[${MyTargetID}].Type.Equal[Corpse]} || !${Spawn[${MyTargetID}].ID} || ${DPSPaused}) {
				/if (${DebugCombat}) /echo CombatCast: Return from CombatCast cause my target is a corpse or dead or DPSPaused ${DPSPaused}. \agLine#: ${Macro.CurLine}
				/return
			}
			
			/varset SkipFlag 0
			/while (${SkipFlag}==0) {
				/varset SkipFlag 1
				/if (!${Bool[${DPS[${i}].Arg[1,|]}]}) {
					/if (${DebugCombat}) CombatCast: /echo im skipping in CombatCast cause there is no spell: DPS${i}  \agLine#: ${Macro.CurLine}
					/break
				}
				/if (${DPS[${i}].Find[|weave]} || ${DPS[${i}].Find[|mash]} || ${DPS[${i}].Find[|ambush]}) /break
				/if (${DPS[${i}].Arg[1,|].NotEqual[script]} && ${DPS[${i}].Arg[1,|].NotEqual[command]} && !${Cast.Ready[${DPS[${i}].Arg[1,|]}]} && !${Me.SpellReady[${Spell[${DPS[${i}].Arg[1,|]}].RankName}]} && !${Me.AltAbilityReady[${DPS[${i}].Arg[1,|]}]} && !${Me.CombatAbilityReady[${Spell[${DPS[${i}].Arg[1,|]}].RankName}]} && !${Me.AbilityReady[${DPS[${i}].Arg[1,|]}]}) /break
				/if (${Cursor.ID}) /autoinventory
				/if (${ConditionsOn} && ${DPSCOn} && ${If[${DPSCond[${i}]},0,1]}) /break
				
				/if (${DPS[${i}].Arg[1,|].Equal[command]}) {
					/if (${Bool[${DPS[${i}].Arg[4,|]}]}) {
						/docommand /${DPS[${i}].Arg[3,|]} ${DPS[${i}].Arg[4,|]}
					} else {
						/docommand /${DPS[${i}].Arg[3,|]}
					}
					/break
				}
				/if (${DPS[${i}].Arg[1,|].Find[script]}) /call script_${Me.Class.ShortName}
				/if ((${Target.Mezzed.ID} && ${MainAssist.NotEqual[${Me}]} && ${Spell[${DPS[${i}].Arg[1,|]}].Category.NotEqual[Utility Detrimental]}) || (${Spell[${DPS[${i}].Arg[1,|]}].Subcategory.Equal[Mana Drain]} && ${MyTargetID} && !${Spawn[${MyTargetID}].Class.CanCast})) {
					/if (${DebugCombat}) /echo Skipping spell in CombatCast because target is mezzed and I'm not mainassist and it will wake up the mob. \agLine#: ${Macro.CurLine}
					/break
				}
				
				/if (${Select[${DPS[${i}].Arg[3,|]},Me,MA]}==0 && (${Me.CombatAbility[${DPS[${i}].Arg[1,|]}]} || ${Me.Ability[${DPS[${i}].Arg[1,|]}]})) {
					|/if (${DPSTimer${i}}) /echo ${DPSTimer${i}} ${i}
					/if (${DPSTimer${i}}) /break
				} else {
					/if ((${DPS[${i}].Arg[3,|].Equal[Me]} && (${Me.Buff[${DPS[${i}].Arg[1,|]}].ID} || ${Me.Song[${DPS[${i}].Arg[1,|]}].ID})) || (${Spawn[${MyTargetID}].PctHPs}<${DPSSkip} || ${Spawn[${MyTargetID}].PctHPs}>${DPSAt}) || (${ABTimer${i}} || ${DPSTimer${i}} || ${FDTimer${i}}) || (${Me.Class.Name.Equal[Cleric]} && ${DPS[${i}].Arg[1,|].Find[Hammer]} && ${Me.Pet.ID}) || (${Me.Class.Name.Equal[Wizard]} && ${Me.Pet.ID} && (${DPS[${i}].Arg[1,|].Find[sword]} || ${DPS[${i}].Arg[1,|].Find[blade]}))) /break
					/if (${DPS[${i}].Arg[3,|].Equal[MA]}) {
						/varset DPSTargetID ${Spawn[=${MainAssist}].ID}
					} else /if (${DPS[${i}].Arg[3,|].Equal[Me]} || ${DPS[${i}].Arg[3,|].Equal[Feign]}) {
						/varset DPSTargetID ${Me.ID}
					}
					/if (${Select[${DPS[${i}].Arg[3,|]},Me,MA]} && ${Me.Combat} && ${MainAssist.NotEqual[${Me}]}) {
						/attack off
						/delay 10 !${Me.Combat}
					}
					/if (${WeaveArray.Size}>0 && ${WeaveArray[1].NotEqual[null]} && ${Me.SpellInCooldown}) {
						/call WeaveStuff ${DPSTargetID}
						/varset WeaveCheck 1
					}
				}

				/call CastWhat "${DPS[${i}].Arg[1,|]}" ${DPSTargetID} DPS 0
				
				
				/varset MacroReturn ${Macro.Return}
				/if (${MacroReturn.Equal[CAST_SUCCESS]}) {
						/echo ** ${DPS[${i}].Arg[1,|]} on >> ${Spawn[${DPSTargetID}].CleanName} <<
					| Set timer for spells labeled once 5m
						/varset CastResult CAST_NO_RESULT
					/if (${DPS[${i}].Arg[3,|].Length} && ${DPS[${i}].Arg[3,|].Equal[once]}) {
						/varset DPSTimer${i} 5m
						
					| Timers for items    
					} else /if (${FindItemCount[=${DPS[${i}].Arg[1,|]}]}) {
						/varcalc DPSTimer${i} ${FindItem[=${DPS[${i}].Arg[3,|]}].Spell.Duration.TotalSeconds}*10
						
					| FD to lose aggro
					} else /if (${Select[${Me.Class.ShortName},BST,MNK,NEC,SHD]} && ${DPS[${i}].Arg[3,|].Equal[Feign]}) {
						/delay 30 ${Me.State.Equal[FEIGN]}
						/varset FDTimer${i} 60s
						/delay 10s ${Me.State.NotEqual[FEIGN]}
						/if (${Me.State.Equal[FEIGN]} && !${Me.Sitting}) /stand
					| Timers for spells
					} else /if (${Me.Book[${DPS[${i}].Arg[1,|]}]}) {
						| - Attack Buff Timers are seperate. DPS timers are cleared after every fight.
						/if (${Select[${DPSTargetID},${Me.ID},${Spawn[=${MainAssist}].ID}]}) {
							/varcalc ABTimer${i} (${Spell[${DPS[${i}].Arg[1,|]}].Duration.TotalSeconds}*${DurationMod})*10
							/if (${DebugCombat}) /echo DEBUGCOMBAT CombatCast Spell: ${DPS[${i}].Arg[1,|]} Timer: ABTimer${i} ${ABTimer${i}} Line#: ${Macro.CurLine}
						| - Custom timer for counterbias
						} else /if (${Me.Class.Name.Equal[Shaman]} && ${DPS[${i}].Arg[1,|].Find[counterbias]}) {
							/varset DPSTimer${i} 1.5m
						| Custom timer for Chanter suffocation
						} else /if (${Me.Class.Name.Equal[enchanter]} && ${DPS[${i}].Arg[1,|].Find[suffocation]}) {
							/varset DPSTimer${i} 1m
						| Custom timer for Beastlord Feralgia Timer
						} else /if (${Me.Class.Name.Equal[Beastlord]} && ${DPS[${i}].Arg[1,|].Find[feralgia]}) {
							/varset DPSTimer${i} 1.5m
						| Regular spells
						} else /if (${Spell[${DPS[${i}].Arg[1,|]}].Duration.TotalSeconds}>0) {
							/varcalc DPSTimer${i} ${Spell[${DPS[${i}].Arg[1,|]}].Duration.TotalSeconds}*10
						| Spells with no timers assign DPS interval
						} else {
							/varset DPSTimer${i} ${DPSInterval}s
						}
						
					| AA and disc timers
					} else /if (${Spell[${DPS[${i}].Arg[1,|]}].Duration}>0 && (${Me.AltAbility[${DPS[${i}].Arg[1,|]}]} || ${Me.CombatAbility[${DPS[${i}].Arg[1,|]}]})) {
						/varcalc DPSTimer${i} ${Spell[${DPS[${i}].Arg[1,|]}].Duration.TotalSeconds}*10
						
					| AA and disc with no timers assign DPS interval
					} else {
						/varset DPSTimer${i} ${DPSInterval}s
						
					}
					|/varset i 1
					/return
				} else /if (${MacroReturn.Equal[CAST_RESIST]}) {
					/echo ** ${DPS[${i}].Arg[1,|]} on >> ${Spawn[${DPSTargetID}].CleanName} << - RESISTED
					/if (${DPS[${i}].Arg[3,|].Length} && ${DPS[${i}].Arg[3,|].Equal[once]}) {
						/varset DPSTimer${i} 5m
					}
					
				} else /if (${MacroReturn.Equal[CAST_TAKEHOLD]}) {
					/echo ** ${DPS[${i}].Arg[1,|]} on >> ${Spawn[${DPSTargetID}].CleanName} << - DID NOT TAKE HOLD
					/varset DPSTimer${i} 5m
					
				}
			}

			
			/if (${Select[${DPS[${i}].Arg[3,|]},Me,MA]}) /call CombatTargetCheck
			/varset WeaveCheck 0
			/next i
			/if (${DebugCombat}) /echo \atDEBUGCOMBAT CombatCast: Leave \agLine#: ${Macro.CurLine}
	/return
| -------------------------------------------------------------------------------------
| SUB: mod_AggroCheck
| -------------------------------------------------------------------------------------
	Sub mod_AggroCheck
		/echo agro test
		/if (!${Me.HaveExpansion[Rain of Fear]}) /return
		/if (${Target.Type.Equal[corpse]}) /return
		/if (${Defined[ParseDPS]}) /return
		/if (${DebugCombat}) /echo \atDEBUGCOMBAT AggroCheck Enter  \agLine#: ${Macro.CurLine}
		/declare i int local
		/declare j int local 0
		/declare AggroSpell string local
		/declare AggroGLT string local
		/declare AggroPCT int local    
		/declare AggroTarget string local
		/declare AggroTID int local
		
		:aggroagain
		/varset badaggroid 0
		


		/if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100) {
			/varset badaggroid ${SpawnSort[1,asc,PctAggro,xtarhater].ID}
		}
	
	:mobset
		/if (${Target.ID}!=${badaggroid} && ${Spawn[id ${badaggroid} npc radius 100].ID}) /target id ${badaggroid}
		/delay 5 ${Target.ID}==${badaggroid}
		
|		/if (${Me.PctAggro}==100) /return
		
		/for i 1 to ${Aggro.Size}
		
		/if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} == 100) {
			/return
		} else /if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100) {
			/varset badaggroid ${SpawnSort[1,asc,PctAggro,xtarhater].ID}
		}
		/varset AggroSpell ${Aggro[${i}].Arg[1,|]}
			/varset AggroPCT ${Aggro[${i}].Arg[2,|]}
			/varset AggroGLT ${Aggro[${i}].Arg[3,|]}
			/varset AggroTarget ${Aggro[${i}].Arg[4,|]}
			/if (${DebugCombat}) /echo \atDEBUGCOMBAT AggroCheck ${Me.PctAggro} ${AggroGLT} ${AggroPCT} ${AggroSpell} \agLine#: ${Macro.CurLine}
			/if (${ConditionsOn} && ${DPSCOn} && ${If[${AggroCond[${i}]},0,1]}) /continue
			/if ((${AggroGLT.Equal[<]} && ${Me.PctAggro}<${AggroPCT}) || (${AggroGLT.Equal[>]} && ${Me.PctAggro}>${AggroPCT}) && (${Me.SpellReady[${AggroSpell}]} || ${Me.AbilityReady[${AggroSpell}]} || ${Me.CombatAbilityReady[${AggroSpell}]})) {
				|/echo Trying to control Aggro: ${Me.PctAggro} ${AggroGLT} ${AggroPCT} ${AggroSpell} 
				/if (${Select[${AggroTarget},null,Mob]} || ${AggroTarget.Equal[INC]} && ${Spawn[${MyTargetID}].Distance}>${MeleeDistance}) /varset AggroTID ${badaggroid}
				/if (${AggroTarget.Equal[Me]}) /varset AggroTID ${Me.ID}
				/if (${AggroTarget.Equal[MA]}) /varset AggroTID ${Spawn[=${MainAssist}].ID}
				/if (${AggroTarget.Equal[Pet]}) /varset AggroTID ${Me.Pet.ID}
				/if (${AggroTarget.Equal[INC]} && ${Spawn[${MyTargetID}].Distance}<${MeleeDistance}) /continue
				
				/echo Trying to control Aggro: ${Me.PctAggro} ${AggroGLT} ${AggroPCT} ${AggroSpell} 
				
				/call NewCast ${badaggroid} "Aggro"
				|/call CastWhat "${AggroSpell}" ${AggroTID} Aggro 0
				|/call CastWhat "${AggroSpell}" ${AggroTID} Aggro
				
				/delay 1
				|/call DoCastingEvents
				/if (${Macro.Return.Equal[CAST_SUCCESS]}) {
					/echo Casting >> ${AggroSpell} << to control AGGRO on ${Spawn[${AggroTID}].CleanName}.
					/if (${AggroGLT.Equal[>]}) {
						/if (!${AggroOffTimer}) {
						   /if (${Me.Feigning} || ${Me.Invis}) /varset AggroOffTimer 20
						}
					}
					/return
				}   
			}
			
		/next i
		/target id ${MyTargetID}
		/if (${DebugCombat}) /echo \atDEBUGCOMBAT mod_AggroCheck Leave \agLine#: ${Macro.CurLine}
	/return												

|----------------------------------------------------------------------------
|- SUB: Death Sub
|----------------------------------------------------------------------------
	Sub DeathSub
		/echo You are sleeping with the fishes
		:DeathSubwait
		/if (${Window[RespawnWnd].Open} && ${ClickBacktoCamp}==1) {
			/nomodkey /notify RespawnWnd RW_OptionsList listselect 1 
			/delay 1s
			/nomodkey /notify RespawnWnd RW_SelectButton leftmouseup
			/delay 5s ${Me.Zoning}
		}
		/if (${Me.Hovering}) /goto :DeathSubwait
		/delay 1m !${Me.Zoning}
		/if (${ClickBacktoCamp}==1 && ${FindItem["Fellowship Registration Insignia"].Timer}==0) {
			/delay 30s ${Me.CombatState.Equal[ACTIVE]}
			/useitem "Fellowship Registration Insignia"
			/delay 2s ${FindItem["Fellowship Registration Insignia"].Timer}!=0
		} else /if (${ClickBacktoCamp}==1 && ${FindItem["Fellowship Registration Insignia"].Timer}!=0) {
			/echo \aw Bummer, Insignia on cooldown, you must really suck at this game...
		} else {
			/echo \aw Waiting on someone that knows how to heal to \ar rez me
		}
	/return

|----------------------------------------------------------------------------
|- SUB: FindTarget - melee attack portion removed. Melee attack moved into engage sub to reduce too far away and can not see messages
|---------------------------------------------------------------------------- 

	Sub FindTarget(int callfrom)
		/declare TempTargetID int local
		|/echo ${callfrom} Finding Something to kill!
		/varset MyTargetID 0
		/varset MyTargetName NULL
		/if (${Spawn[xtarhater named].ID}) {
			/varset TempTargetID ${Spawn[xtarhater named].ID}
			/call BroadCast ${IRCOn} ${EQBCOn} y "Grabbing Namer -> ${Spawn[${TempTargetID}].Name} <- ID:${Spawn[${TempTargetID}].ID} "
		} else /if (${Alert[4].Size} && ${Spawn[xtarhater alert 4].ID} && ${Spawn[xtarhater alert 4].Type.NotEqual[Corpse]}) {
			/varset TempTargetID ${NearestSpawn[1, xtarhater alert 4].ID}
			/call BroadCast ${IRCOn} ${EQBCOn} y "Grabbing MEZ Immune -> ${Spawn[${TempTargetID}].Name} <- ID:${Spawn[${TempTargetID}].ID} "
			
		} else {
			/varset TempTargetID ${SpawnSort[1,asc,PctHPs,xtarhater].ID}
			/call BroadCast ${IRCOn} ${EQBCOn} y "Grabbing Lowest HP Mob -> ${Spawn[${TempTargetID}].Name} <- ID:${Spawn[${TempTargetID}].ID} "
		}
			
		/call ValidateTarget ${TempTargetID}
			
		/if (${ValidTarget}==0) {
			/if (${Target.ID}) /squelch /alert add 2 id ${Target.ID}
			/varset MyTargetID 0
			/varset MyTargetName
			/echo invalid target
			/return
		} else {
			/if (${Target.ID}!=${TempTargetID}) {
			   /squelch /target clear
			   /delay 10 !${Target.ID}
			   /target id ${TempTargetID}
			   /delay 10 ${Target.ID}
			}
		   /varset MyTargetID ${Target.ID}
		   /varset MyTargetName ${Target.CleanName}
		   /echo valid target ${Target.CleanName} ${Target.ID}
		}
	|--Check target matches MA if not based off lowest hp in XTarget
		/if (${Target.ID}!=${Me.GroupAssistTarget.ID} && ${Group.MainAssist.ID}!=${Me.ID} && ${MyTargetID}!=${Me.GroupAssistTarget.ID} && ${Spawn[id ${Me.GroupAssistTarget.ID} ${SpawnSearchType}].ID}) {
			/varset MyTargetID ${Me.GroupAssistTarget.ID}
		} 
		|else /if ((!${Group.MainAssist.ID} || ${Group.MainAssist.ID}==${Me.ID}) && ${Spawn[${SpawnSearchType} id ${SpawnSort[1,desc,PctHPs,xtarhater].ID}].ID}) {
		|	/varset MyTargetID ${Spawn[${SpawnSearchType} id ${SpawnSort[1,desc,PctHPs,xtarhater].ID}].ID}
		|}
	|--Target the new target
		/if (${Target.ID}!=${MyTargetID} && ${Spawn[${SpawnSearchType} id ${MyTargetID}].ID} && ${DPSOn} && ${MeleeOn}) {
			/squelch /target id ${MyTargetID}
			/delay 10 ${Target.ID}==${MyTargetID}
		}
	/return 

|----------------------------------------------------------------------------
|- SUB: Melee Engage Target - Need a StickHow variable in the mac. Ini option for melee just a declared variable set to null for classes that wont enageg in melee
|- Basic use will check the that the target is in assist range, stick and when in melee range start attacking ( reduces too far away and can not see messages )
|- Advanced use ( smart assist ) will check that the target is range of the MA before engaging....keeps melee from charging out after a mob on incoming
|- For classes that have a before combat move, it is recommended  to copy/paste this sub into new macro and rename. Add opening move ( ber, rog ) to just before turning on attack 
|---------------------------------------------------------------------------- 
	Sub EngageTarget
	:Engage
		/echo Engaging >> ${MyTargetID}
		/doevents
		/if (${Me.State.Equal[FEIGN]}) /stand
		
		/if (${Stick.Status.Equal[ON]}) /stick off
		/if (${IAmDead} && ${CampZone}==${Zone.ID} && (${Me.Buff[Resurrection Sickness].ID} || ${SpawnCount[pccorpse ${Me}]}==0) ) /varset IAmDead 0
		/if (${DPSOn} && ${MeleeOn} && !${AutoFireOn}) {
			/if (${Target.ID}!=${MyTargetID} && ${Spawn[${SpawnSearchType} id ${MyTargetID}].ID} && ${DPSOn} && ${MeleeOn}) {
				/squelch /target id ${MyTargetID}
				/delay 10 ${Target.ID}==${MyTargetID}
			}
			/if (${DPSOn} && ${MeleeOn} && ${Spawn[${SpawnSearchType} id ${MyTargetID}].PctHPs}>0 && ${Target.ID}==${MyTargetID} && ${Stick.Status.Equal[OFF]}) {
				/if (${StickHow.NotEqual[NULL]}) {
					/stick ${StickHow}
				} else /if (${Math.Calc[${Target.MaxRangeTo}*0.8]} > 29) {
					/stick snaproll rear
				} else {
					/stick ${Math.Calc[${Target.MaxRangeTo}*0.8]} behind uw
				}
				/delay 10 ${Stick.Active}
			}
			/if (${Select[${Role},tank,pullertank,hunter]}) {
				/if (${Me.Ability[Taunt]} && ${Me.AbilityReady[Taunt]}) /doability Taunt
			}
			/if (!${Me.Combat} && ${BeforeArray[1].NotEqual[null]}) /call BeforeAttack ${MyTargetID}
			/if (!${Me.Combat} && ${DPSOn} && ${MeleeOn} && ${Target.PctHPs}<=${AssistAt} && ${Target.PctHPs}>0 && ${Target.ID}==${MyTargetID} && ${Spawn[id ${MyTargetID} ${SpawnSearchType} radius ${MeleeDistance}].ID}) {
					/if (!${Me.Combat} && ${BeforeArray[1].NotEqual[null]}) /call BeforeAttack ${MyTargetID}
				}
				/squelch /attack on
				/delay 10 ${Me.Combat}
				/if (${Cursor.ID}) /call CheckCursor Combat
				
		}
		/varset MercAssisting 0
		/varset CombatStart 1
		/echo  ATTACKING -> ${Spawn[${MyTargetID}].CleanName} <-
	
		
		/if (${Select[${Role},pettank,pullerpettank]} && !${Attacking}) { 
			/pet attack
			/pet swarm
			/varset Attacking 1
		}
		
		/varset  MyExp ${Me.PctExp}
		/varset  MyAAExp ${Me.PctAAExp}
		/if (${Select[${Zone.ID},795,796]}!=0) {
			/varset tmpHealOverride 85.00
		}
		
		|COMBAT LOOP
		
		/while (1) {
			/echo in combatwhile
			/varcalc cyclecount (${cyclecount})+1
			/doevents
			
			/if (${IAmDead}) {
				/varset MyTargetID 0
				/return
			}
			
			/if (${DPSOn} || ${MeleeOn} || ${PetOn}) /call CombatTargetCheck
			/if (${Role.Equal[offtank]} && !${Spawn[=${MainAssist}].ID}) /switchma ${Me} tank 0
			/if (${DebuffAllOn} && (${Role.NotEqual[puller]} || !${ChainPull})) {
			   /call DoDebuffStuff ${MyTargetID}
				/if (${Spawn[${MyTargetID}].Type.Equal[Corpse]} || !${Spawn[${MyTargetID}].ID} || ${DPSPaused}) {
				   /call CombatReset 0 combat
				   /break
				}
			} 
			
			/call _${Me.Class.ShortName}
			|/echo past class sub call
			/if (!${UseMQ2Melee} && ${Spawn[${MyTargetID}].Distance}>${Spawn[${MyTargetID}].MaxRangeTo} && ${MeleeOn} && !${Stick.Active}) /moveto id ${MyTargetID} mdist ${Spawn[${MyTargetID}].MaxRangeTo}
			|/if (${CombatStart} && ${AutoFireOn} && ${Target.ID}==${MyTargetID} && !${Bool[${Target.Mezzed.ID}]}) /range
			
			/if (!${NamedCheck} && (${BurnAllNamed} || ${GMailEvents.Find[named]})) /call NamedWatch 0
			/if (${checkmana} && ${Me.PctMana}<65) /call CastMana combat
			|/call WriteDebuffs
			
			/if (${Role.Equal[puller]} && ${ChainPull}) {
				/if (${Math.Distance[${CampYLoc},${CampXLoc}:${Spawn[=${MainAssist}].Y},${Spawn[=${MainAssist}].X}]}<=75) {
					/if (!${PullHold} && ${MobCount}<2 && !${Me.XTarget[${XTSlot2}].ID} && ${If[${Target.Named},0,1]}==1) {
						/if (${Target.ID} && ${Target.PctHPs} < ${ChainPullHP}) {
							/call FindMobToPull 0
							/if (${Macro.Return}>0 && (!${PullXPCheck} || (${Spawn[${ChainPullTemp}].Distance}<${Math.Calc[${PullRange}+400]} && ${PullXPCheck})) && ${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]} && ${Me.PctAggro}<50) {
								/varset PullMob ${Macro.Return}
								/if (${UseMQ2Melee}) /squelch /melee melee=0
								/if (${Stick.Active}) /squelch /stick off 
								/squelch /attack off
								/delay 10
								/if (${UseMQ2Melee}) /squelch /melee melee=1
								/varset ChainPull 2
								/varset MyTargetID 0
								/varset Attacking 0
								/return
							}
						}
					}
				} else /if (${SpamTankWait}) {
					/call BroadCast ${IRCOn} ${EQBCOn} r "Holding Pulls. Tank to far from camp."
					/varset SpamTankWait 0 
				}
				/if (${Role.Equal[puller]} && ${ChainPull} && ${DebuffAllOn}) /call DebuffCast ${MyTargetID} 1 
				/if (${Role.Equal[puller]} && ${ChainPull} && ${DPSOn}) /call newcombatcast
			}   
|  ||  (${Me.XTarget[1].ID} > 0 && ${Spawn[${SpawnSearchType} id ${MyTargetID}].Distance}>${MeleeDistance}
			/if ((${Spawn[corpse id ${MyTargetID}].ID}) || (!${Spawn[targetable id ${MyTargetID}].ID}) || ${Me.Feigning} ||  (${Me.XTarget[1].ID} > 0 && ${Spawn[${SpawnSearchType} id ${MyTargetID}].Distance}>${MeleeDistance}) ) {
				/call CombatReset 0 combat
				/varset MyTargetID 0
				/varset healcount 0
				/break					
			}

			
		}
		
		/if (${cyclecount}>0) {
				/if (${DebugFramework}) /echo CYCLES: ${cyclecount}
				/varset cyclecount 0
			}
		/varset tmpHealOverride 99.99
	/return