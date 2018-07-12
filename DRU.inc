|***
 *	DRU.inc
 *	Framework DRUID Include
 *
 *	
 ***|
 
 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
 Sub _DRU
	|/echo in Dru sub

	/if (${Spawn[${MainAssist}].Type.NotEqual[Corpse]} && ${Spawn[${MainAssist}].PctHPs} <= ${Math.Calc[${${MainAssistClass}Point}*.${tmpHealOverride}]}) {
		|/echo in ma spot
		|/echo Going to heal MA "${MainAssist}" "${MainAssistType}" ${Spawn[${MainAssist} ${MainAssistType}].PctHPs} ${MostHurtNo}
		/echo ${Macro.CurLine}
		/call newSingleHeal "${MainAssist}" "${MainAssistType}" ${Spawn[${MainAssist} ${MainAssistType}].PctHPs} 6 G
		/if (${Macro.Return.Equal[CAST_SUCCESS]}) {
				/call BroadCast ${IRCOn} ${EQBCOn} o "${HealSpell} for >>${Spawn[${SHealName} ${SHealType}].CleanName} << cast on ${Spawn[${MyTargetID}].CleanName}"
			   
				/return
		}
	} else /if (${AutoRezOn} && !${Spawn[${MainAssist} ${MainAssistType}].ID} && ${Select[${MainAssistType},Mercenary,Pet]}==0) {
		/call CastWhat "Call of the Wild" ${Spawn[${MainAssist}'s corpse].ID}
	} else /if (${Select[${Me.Class.ShortName},BST,CLR,SHM,DRU,PAL]} && ${Group} && ${Group.Injured[95]} > 1) {
		|/echo in full group heal
		/call DoGroupHealStuff ${Group.AvgHPs}
	} else /if ((${Spawn[${WorstHurt[both,1,200,TRUE]}].Type.NotEqual[Pet]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName.NotEqual[Corpse]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} <= ${Math.Calc[${${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName}Point}*.${tmpHealOverride}]}) || (${Spawn[${WorstHurt[both,1,200,TRUE]}].Type.Equal[Pet]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName.NotEqual[Corpse]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} <= ${Math.Calc[${PetPoint}*.${tmpHealOverride}]})) {
		|/echo Going to heal "${Me}" "${Me.Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} ${MostHurtNo} 
		/Echo newSingleHeal "${Spawn[${WorstHurt[both,1,200,TRUE]}].CleanName}" "${Spawn[${WorstHurt[both,1,200,TRUE]}].Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} 0 G
		/echo ${Macro.CurLine}
		/call newSingleHeal "${Spawn[${WorstHurt[both,1,200,TRUE]}].CleanName}" "${Spawn[${WorstHurt[both,1,200,TRUE]}].Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} 1 G
		|(${Group.Member[${i}].Distance}<=200&& ${Group.Member[${i}].PctHPs}<100 && !${Group.Member[${i}].Hovering} && ${Group.Member[${i}].Type.NotEqual[Corpse]})
	} else {
		|/echo In Clr sub attacks
		/if (${CuresOn}) /call CheckCures   
		/if (${CombatStart} && (${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} || ${Spawn[${MyTargetID}].ID} || !${Me.Feigning})) {
			|/if (${MercOn} && !${MercAssisting} && ${MyTargetID} && ${Mercenary.State.Equal[Active]}) /call MercsDoWhat
			|/if (${DPSOn} && (!${Role.Equal[puller]} || !${ChainPull})) /call Mod_CombatCast
			|/if (${DPSOn} && (!${Role.Equal[puller]} || !${ChainPull})) /call CombatCast
			/if (${DPSOn} && (!${Role.Equal[puller]} || !${ChainPull})) /call newcombatcast
		}
	}
	
	|/varset tmpHealOverride 99.99
	/if (${DebugHeal}) /echo \amDEBUGHEALS Class Sub leave \agLine#: ${Macro.CurLine}
	/if (${AutoRezOn}) /call RezCheck
	/call WriteDebuffs
/return 