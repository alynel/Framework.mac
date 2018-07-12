|***
 *	BER.inc
 *	Framework BERZERKER Include
 *
 *	
 ***|
 
 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
 
 Sub _BER
	/echo in class sub
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
 sub script_ber
	/echo in ber discs
	/if (${Me.CombatAbilityReady[${Spell[Disconcerting Discipline].RankName}]}) {
		/echo 1
		/call CastWhat "${Spell[Disconcerting Discipline].RankName}" ${Spawn[${MyTargetID}].ID} DPS 0
	} else /if (${Me.ItemReady[${epicaxe}]}) {
		/echo 2
		/call CastWhat "${epicaxe}" ${Spawn[${MyTargetID}].ID} DPS 0
	} else /if (${Me.AltAbilityReady[Focused Furious Rampage]}) {
		/echo 3
		/call CastWhat "${Spell[Brutal Discipline].RankName}" ${Spawn[${MyTargetID}].ID} DPS 0
		/alt act 379
		/alt act 465 
		
		/alt act 3710 
		/alt act 961 
		/alt act 7019 
	} else /if (${Me.CombatAbilityReady[${Spell[Cleaving Acrimony Discipline].RankName}]}) {
		/echo 4
		/call CastWhat "${Spell[Cleaving Acrimony Discipline].RankName}" ${Spawn[${MyTargetID}].ID} DPS 0
		/alt act 1501
		/alt act 610
		/useitem "Cohort's Warmonger Coat"
	} else /if (${Me.CombatAbilityReady[${Spell[Frenzied Resolve Discipline].RankName}]}) {
		/echo 5
		/call CastWhat "${Spell[Frenzied Resolve Discipline].RankName}" ${Spawn[${MyTargetID}].ID} DPS 0
	} else /if (${Me.CombatAbilityReady[${Spell[Avenging Flurry Discipline].RankName}]}) {
		/echo 6
		/call CastWhat "${Spell[Avenging Flurry Discipline].RankName}" ${Spawn[${MyTargetID}].ID} DPS 0
	} 
/return