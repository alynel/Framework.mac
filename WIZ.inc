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

	|/echo in class sub 
	|/if (${Spawn[${MyTargetID}].PctHPs}<=${PetAssistAt} && ${PetOn} && ${PetCombatOn}) {
	|	/echo in combatpet
	|	/call CombatPet
	|} else 
	/if (${HealsOn} && ${Me.PctHPs} <= ${Math.Calc[${${Me.Class.ShortName}Point}*.${tmpHealOverride}]}) {
		/echo in heal
		/call newSingleHeal "${Me}" "PC" ${Me.PctHPs} 0 G
	} else /if (${DPSOn} && ${CombatStart} && ${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} && ${Spawn[${MyTargetID}].ID} && !${Me.Feigning}) {
		|/call CombatCast
		|/call newcombatcast
		/echo combatcast
		/call NewCast ${MyTargetID} "DPS"
	}
	
/return 
