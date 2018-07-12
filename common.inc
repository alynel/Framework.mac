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
		/if (${UseModHeal}==1 && ${HealsOn}==1 && (${Spawn[${WorstHurt[both,1,200,TRUE]}].Type.NotEqual[Pet]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName.NotEqual[Corpse]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} <= ${Math.Calc[${${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName}Point}*.${tmpHealOverride}]}) || (${Spawn[${WorstHurt[both,1,200,TRUE]}].Type.Equal[Pet]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName.NotEqual[Corpse]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} <= ${Math.Calc[${PetPoint}*.${tmpHealOverride}]})) {
			/echo DPS newSingleHeal "${Spawn[${WorstHurt[both,1,200,TRUE]}].CleanName}" "${Spawn[${WorstHurt[both,1,200,TRUE]}].Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} 0 G
			/call newSingleHeal "${Spawn[${WorstHurt[both,1,200,TRUE]}].CleanName}" "${Spawn[${WorstHurt[both,1,200,TRUE]}].Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} 1 G
			|(${Group.Member[${i}].Distance}<=200&& ${Group.Member[${i}].PctHPs}<100 && !${Group.Member[${i}].Hovering} && ${Group.Member[${i}].Type.NotEqual[Corpse]})
			/return
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
				/if (${DPSTimer${i}}) /echo ${DPSTimer${i}} ${i}
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
		/varset AggroSpell ${Aggro[${i}].Arg[1,|]}
            /varset AggroPCT ${Aggro[${i}].Arg[2,|]}
            /varset AggroGLT ${Aggro[${i}].Arg[3,|]}
            /varset AggroTarget ${Aggro[${i}].Arg[4,|]}
            /if (${DebugCombat}) /echo \atDEBUGCOMBAT AggroCheck ${Me.PctAggro} ${AggroGLT} ${AggroPCT} ${AggroSpell} \agLine#: ${Macro.CurLine}
            /if (${ConditionsOn} && ${DPSCOn} && ${If[${AggroCond[${i}]},0,1]}) /continue
            /if ((${AggroGLT.Equal[<]} && ${Me.PctAggro}<${AggroPCT}) || (${AggroGLT.Equal[>]} && ${Me.PctAggro}>${AggroPCT}) && (${Cast.Ready[${AggroSpell}]} || ${Me.AbilityReady[${AggroSpell}]} || (${Me.CombatAbilityReady[${AggroSpell}]} && !${Me.ActiveDisc.ID}))) {
                /echo Trying to control Aggro: ${Me.PctAggro} ${AggroGLT} ${AggroPCT} ${AggroSpell} 
                /if (${Select[${AggroTarget},null,Mob]} || ${AggroTarget.Equal[INC]} && ${Spawn[${MyTargetID}].Distance}>${MeleeDistance}) /varset AggroTID ${MyTargetID}
                /if (${AggroTarget.Equal[Me]}) /varset AggroTID ${Me.ID}
                /if (${AggroTarget.Equal[MA]}) /varset AggroTID ${Spawn[=${MainAssist}].ID}
                /if (${AggroTarget.Equal[Pet]}) /varset AggroTID ${Me.Pet.ID}
                /if (${AggroTarget.Equal[INC]} && ${Spawn[${MyTargetID}].Distance}<${MeleeDistance}) /continue
                /call CastWhat "${AggroSpell}" ${AggroTID} Aggro 0
				/call CastWhat "${AggroSpell}" ${AggroTID} Aggro
                /delay 10
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