|***
 *	ENC.inc
 *	Framework ENCHANTER Include
 *
 *	
 ***|
 
 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
Sub _enc
	
    /if (${MezOn}) {
		/echo checking Mez
		/varset MezBroke 0
		/doevents MezBroke
		/if (!${MezBroke}) /call DoMezStuff
	}
	
	/if (${Spawn[${MyTargetID}].PctHPs}<=${PetAssistAt} && ${PetOn} && ${PetCombatOn}) {
		/call CombatPet
	} 
	
	/if (${HealsOn} && ${Me.PctHPs} <= ${Math.Calc[${${Me.Class.ShortName}Point}*.${tmpHealOverride}]}) {
		/call newSingleHeal "${Me}" "PC" ${Me.PctHPs} 0 G
	} else /if (${DPSOn} && ${CombatStart} && ${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} && ${Spawn[${MyTargetID}].ID} && !${Me.Feigning}) {
		|/call CombatCast
		/echo combatcast
		|/call newcombatcast
		/call NewCast ${MyTargetID} "DPS"
	}

/return 

