|***
 *	WIZ.inc
 *	Framework Wizard Include
 *
 *	
 ***|
 
 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
Sub _wiz
	/if (${Spawn[${MyTargetID}].PctHPs}<=${PetAssistAt} && ${PetOn} && ${PetCombatOn}) {
		/call CombatPet
	} else /if (${HealsOn} && ${Me.PctHPs} <= ${Math.Calc[${${Me.Class.ShortName}Point}*.${tmpHealOverride}]}) {
		/call newSingleHeal "${Me}" "PC" ${Me.PctHPs} 0 G
	} else /if (${DPSOn} && ${CombatStart} && ${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} && ${Spawn[${MyTargetID}].ID} && !${Me.Feigning}) {
		|/call CombatCast
		/call newcombatcast
	}

/return 
