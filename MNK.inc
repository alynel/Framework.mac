|***
 *	MNK.inc
 *	Framework Monk Include
 *
 *	
 ***|
 
 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
Sub _MNK
	/if (${DebugFramework}) /echo in class sub
	/if (${HealsOn} && ${Me.PctHPs} <= ${Math.Calc[${${Me.Class.ShortName}Point}*.${tmpHealOverride}]}) {
		/call newSingleHeal "${Me}" "PC" ${Me.PctHPs} 0 G
	} else /if (${DPSOn} && ${CombatStart} && ${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} && ${Spawn[${MyTargetID}].ID} && !${Me.Feigning}) {
		|/call CombatCast
		/call newcombatcast
	}

/return

 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
 