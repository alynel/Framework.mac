|***
 *	BST.inc
 *	Framework Beastlord Include
 *
 *	
 ***|
 
 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
 Sub _BST
	/echo in class sub
    /if (${Spawn[${MyTargetID}].PctHPs}<=${PetAssistAt} && ${PetOn} && ${PetCombatOn} && !${Me.Pet.Combat}) {
		/call CombatPet
	}
	/if ((${Spawn[${WorstHurt[both,1,200,TRUE]}].Type.NotEqual[Pet]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName.NotEqual[Corpse]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} <= ${Math.Calc[${${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName}Point}*.${tmpHealOverride}]}) || (${Spawn[${WorstHurt[both,1,200,TRUE]}].Type.Equal[Pet]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].Class.ShortName.NotEqual[Corpse]} && ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} <= ${Math.Calc[${PetPoint}*.${tmpHealOverride}]})) {
		|/call newSingleHeal "${Spawn[${WorstHurt[both,1,200,TRUE]}].CleanName}" "${Spawn[${WorstHurt[both,1,200,TRUE]}].Type}" ${Spawn[${WorstHurt[both,1,200,TRUE]}].PctHPs} 1 G
		/call NewCast ${Spawn[${WorstHurt[both,1,200,TRUE]}].ID} "Heals"
	} else /if (${DPSOn} && ${CombatStart} && ${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} && ${Spawn[${MyTargetID}].ID} && !${Me.Feigning}) {
		/echo in combat
		|/call CombatCast
		|/call newcombatcast
		/call NewCast ${MyTargetID} "DPS"
	}
/return

 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
 
sub script_bst
/echo in bst discs
	/if (${Me.AltAbilityReady[Bestial Alignment]}) {
		/alt act 245
		/alt act 127
		/alt act 241
		/alt act 1430
		/alt act 1240
	} else /if (${Me.CombatAbilityReady[${Spell[Ruaabri's Fury].RankName}]}) {
		/disc ${Spell[Ruaabri's Fury].RankName}
		/disc ${Spell[Savage Rancor].RankName}
	} else /if (${Me.AltAbilityReady[Ferociousness]}) {
		/alt act 966
	} else /if (${Me.AltAbilityReady[Companion's Fury]}) {
		/alt act 443
		/alt act 1431
		|add TDS BP
	} else /if (${Me.AltAbilityReady[Group Bestial Alignment]}) {
		/alt act 985
	} 
/return