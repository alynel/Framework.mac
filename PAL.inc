|***
 *	PAL.inc
 *	Framework Paladin Include
 *
 *	
 ***|
 
 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
Sub _pal
	/if (${Debug}) /echo _PAL Enter Line#: ${Macro.CurLine}
	/if (${Select[${Zone.ID},795,796]}!=0) {
		/varset tmpHealOverride 85.00
	}

	/if (${Me.CombatState.Equal[COMBAT]} && ${Select[${Me.Class.ShortName},WAR,PAL,SHD]} && ${CombatStart} && !${Me.ActiveDisc.ID} && (${Target.Named} || ${Me.XTarget}>3) && ${Target.Distance}<75) {
		/if (${DebugFramework}) /echo defensive
		/call PalDefense
	} else /if (${Spawn[${MainAssist}].Type.NotEqual[Corpse]} && ${Spawn[${MainAssist}].PctHPs} <= ${Math.Calc[${${MainAssistClass}Point}*.${tmpHealOverride}]}) {
		|/echo in ma spot
		|/echo Going to heal MA "${MainAssist}" "${MainAssistType}" ${Spawn[${MainAssist} ${MainAssistType}].PctHPs} ${MostHurtNo}
		/if (${DebugFramework}) /echo ${Macro.CurLine}
		/call NewCast ${Spawn[=${MainAssist}].ID} "Heals"
		
		|/call newSingleHeal "${MainAssist}" "${MainAssistType}" ${Spawn[${MainAssist} ${MainAssistType}].PctHPs} 6 G
		|/if (${Macro.Return.Equal[CAST_SUCCESS]}) {
		|		/call BroadCast ${IRCOn} ${EQBCOn} o "${HealSpell} for >>${MainAssist} << cast on ${Spawn[${MyTargetID}].CleanName}"
		|	   
		|		/return
		|}
	} else /if (${AutoRezOn} && !${Spawn[${MainAssist} ${MainAssistType}].ID} && ${Select[${MainAssistType},Mercenary,Pet]}==0) {
		/call CastWhat "${AutoRezWith}" ${Spawn[${MainAssist}'s corpse].ID}
	} else /if (${Select[${Me.Class.ShortName},BST,CLR,SHM,DRU,PAL]} && ${Group} && ${Group.Injured[${Math.Calc[95*.${tmpHealOverride}]}]} > 1) {
		|/echo in full group heal
		/call NewCast ${MyTargetID} "GHeals"
		|/call DoGroupHealStuff ${Group.AvgHPs}
	} else /if ((${Spawn[${WorstHurt[both,1,200,TRUE]}].Type.NotEqual[Pet]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName.NotEqual[Corpse]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} <= ${Math.Calc[${${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName}Point}*.${tmpHealOverride}]}) || (${Spawn[${WorstHurt[both,1,200,TRUE]}].Type.Equal[Pet]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName.NotEqual[Corpse]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} <= ${Math.Calc[${PetPoint}*.${tmpHealOverride}]})) {
		|/echo Going to heal "${Me}" "${Me.Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} ${MostHurtNo} 
		/if (${DebugFramework}) /echo newSingleHeal "${Spawn[${WorstHurt[both,1,200,TRUE]}].CleanName}" "${Spawn[${WorstHurt[both,1,200,TRUE]}].Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} 0 G
		|/echo ${Macro.CurLine}
		/call NewCast ${Spawn[${WorstHurt[both,1,200,TRUE]}].ID} "Heals"
		|/call newSingleHeal "${Spawn[${WorstHurt[both,1,200,TRUE]}].CleanName}" "${Spawn[${WorstHurt[both,1,200,TRUE]}].Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} 1 G
		|(${Group.Member[${i}].Distance}<=200&& ${Group.Member[${i}].PctHPs}<100 && !${Group.Member[${i}].Hovering} && ${Group.Member[${i}].Type.NotEqual[Corpse]})
	}  else /if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100 && ${CombatStart} && ${Select[${Role},pullertank,tank]}) {
		/if (${DebugFramework}) /echo aggro
		/call Mod_AggroCheck
	} else {
		|/echo In Clr sub attacks
		|/if (${CuresOn}) /call CheckCures   
		/if (${CombatStart} && (${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} || ${Spawn[${MyTargetID}].ID} || !${Me.Feigning})) {
			|/if (${MercOn} && !${MercAssisting} && ${MyTargetID} && ${Mercenary.State.Equal[Active]}) /call MercsDoWhat
			|/if (${DPSOn} && (!${Role.Equal[puller]} || !${ChainPull})) /call Mod_CombatCast
			|/if (${DPSOn} && (!${Role.Equal[puller]} || !${ChainPull})) /call CombatCast
			|/if (${DPSOn} && (!${Role.Equal[puller]} || !${ChainPull})) /call newcombatcast
			/call NewCast ${MyTargetID} "DPS"
		}
	} else /if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100 && ${CombatStart} && ${Select[${Role},pullertank,tank]}) {
		/echo aggro
		|/call Mod_AggroCheck
		/call NewCast ${SpawnSort[1,asc,PctAggro,xtarhater].ID} "Aggro"
	} else /if (${DPSOn} && ${CombatStart} && (${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} || ${Spawn[${MyTargetID}].ID} || !${Me.Feigning})) {
		/echo combat cast
		/call NewCast ${MyTargetID} "DPS"
		|/call CombatCast
		|/call newcombatcast
	}
	/if (${AutoRezOn}) /call RezCheck
/return 


 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|

Sub PalDefense
	/if (!${Me.ActiveDisc.ID}) {
		/if (${Me.AltAbilityReady[Group Armor of the Inquisitor]}) {
			/call CastWhat "Group Armor of the Inquisitor"
			/if (${Macro.Return.Equal[CAST_SUCCESS]}) /if (${ReportDefense}) /call AnnounceMessage 2 y "Group Armor of the Inquisiton" r "Active"
			/return				
			}
		/if (${Me.PctEndurance}>5) {
			/if (${Me.CombatAbilityReady[${Spell[Holy Guardian Discipline].RankName}]}) {
				/if (${Spell[${Spell[Blessed Guardian Discipline].RankName}].ID}) {
					/disc ${Spell[${Spell[Blessed Guardian Discipline].RankName}].ID}
					} Else {
					/disc ${Spell[${Spell[Holy Guardian Discipline].RankName}].ID}
					}
				/if (${ReportDefense}) /call AnnounceMessage 2 y "Guardian Discipline, Defense line 1" r "Active"
				/return				
				}
			/if (!${Me.CombatAbilityReady[${Spell[Holy Guardian Discipline].RankName}]} && ${Me.CombatAbilityReady[${Spell[Honorific Mantle].RankName}]}) {
				/if (${Spell[${Spell[Kar'Zok Mantle].RankName}].ID}) {
					/disc ${Spell[Kar'Zok Mantle].RankName}
					/goto :PALMantleEnd
					}
				/if (${Spell[${Spell[Skalber Mantle].RankName}].ID}) {
					/disc ${Spell[Skalber Mantle].RankName}
					/goto :PALMantleEnd
					}
				/if (${Spell[${Spell[Brightwing Mantle].RankName}].ID}) {
					/disc ${Spell[Brightwing Mantle].RankName}
					/goto :PALMantleEnd
					}
				/if (${Spell[${Spell[Prominent Mantle].RankName}].ID}) {
					/disc ${Spell[Prominent Mantle].RankName}
					/goto :PALMantleEnd
					}
				/if (${Spell[${Spell[Honorific Mantle].RankName}].ID}) {
					/disc ${Spell[Honorific Mantle].RankName}
					/goto :PALMantleEnd
					}
				/if (${Spell[${Spell[Armor of Endless Honor].RankName}].ID}) {
					/disc ${Spell[Armor of Endless Honor].RankName}
					/goto :PALMantleEnd
					}					
				:PALMantleEnd
				/if (${ReportDefense}) /call AnnounceMessage 2 y "Mantle Discipline, Defense line 2" r "Active"	
				/return
				}
			/if (!${Me.CombatAbilityReady[${Spell[Honorific Mantle].RankName}]} && ${Me.CombatAbilityReady[${Spell[Armor of Courage].RankName}]}) {	
				/if (${Spell[${Spell[Armor of Mercy].RankName}].ID}) {
					/disc ${Spell[Armor of Mercy].RankName}
					/goto :PALArmorEnd
					}		
				/if (${Spell[${Spell[Devout Penitence].RankName}].ID}) {
					/disc ${Spell[Devout Penitence].RankName}
					/goto :PALArmorEnd
					}
				/if (${Spell[${Spell[Reverent Penitence].RankName}].ID}) {
					/disc ${Spell[Reverent Penitence].RankName}
					/goto :PALArmorEnd
					}
				/if (${Spell[${Spell[Armor of Zeal].RankName}].ID}) {
					/disc ${Spell[Armor of Zeal].RankName}
					/goto :PALArmorEnd
					}
				/if (${Spell[${Spell[Armor of Courage].RankName}].ID}) {
					/disc ${Spell[Armor of Courage].RankName}
					/goto :PALArmorEnd
					}		
				:PALArmorEnd
				/if (${ReportDefense}) /call AnnounceMessage 2 y "Penitence Discipline, Defense line 3" r "Active"
				/return 		
				}
			}
		/if (!${Me.CombatAbilityReady[${Spell[Armor of Courage].RankName}]}) {
			/if (${Me.AltAbilityReady[Armor of Experience]}) {
				/call CastWhat "Armor of Experience"
				/if (${ReportDefense}) /call AnnounceMessage 2 y "Armor of Experience" r "Active"
				/return				
				}
			/if (${Me.AltAbilityReady[Fundament: Third Spire of Holiness]}) {
				/call CastWhat "Fundament: Third Spire of Holiness"
				/if (${Macro.Return.Equal[CAST_SUCCESS]} && ${ReportDefense}) /call AnnounceMessage 2 y "First Spire" r "Active"
				/return			
				}
			}
	}
/return