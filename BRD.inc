|***
 *	BRD.inc
 *	Framework Bard Include
 *
 *	
 ***|
 
 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
 Sub _BRD
	/echo in class sub 
	/if (${Me.XTarget}>1 && ${SpawnCount[NPC radius 30]}>1 &&${Me.GemTimer[${MezAESpell}]}==0&&${Me.CurrentMana}>${Spell[${MezAESpell}].Mana}&&${Me.Gem[${MezAESpell}]}) {
		/squelch /twist once ${Me.Gem[${MezAESpell}]}
		/call BroadCast ${IRCOn} ${EQBCOn} g "MEZZING-> AE Mezzing Now - ${MezAESpell} "
	}	
    /if (${MezOn}) {
			/echo checking Mez
			/varset MezBroke 0
			/doevents MezBroke
			/if (!${MezBroke}) /call DoMezStuff
	}
	/if (${HealsOn} && ${Me.PctHPs} < ${SingleHealPoint}) {
		/call newSingleHeal "${Me}" "PC" ${Me.PctHPs} 0 G
	} else /if (${DPSOn} && ${CombatStart} && ${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} && ${Spawn[${MyTargetID}].ID} && !${Me.Feigning}) {
		/call CombatCast
	}
	/call DoDebuffStuff ${MyTargetID}

	
/return