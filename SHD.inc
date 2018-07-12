|***
 *	SHD.inc
 *	Framework Shadow Knight Include
 *
 *	
 ***|
 
 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
Sub _shd
	/if (${Debug}) /echo _SK Enter Line#: ${Macro.CurLine}
	|/if (${combat_function[]} && ${CombatStart}) {
	|		/echo combat_adj
	|		/call combat_adj
	|}
	/if (${ReturnToCamp} && ${Math.Distance[${CampYLoc},${CampXLoc}]}>10) {
	   /varset ReturnToCamp 1
	   /call DoWeMove 1 CheckForCombat
	}
	/if (${Me.CombatState.Equal[COMBAT]} && ${Select[${Me.Class.ShortName},WAR,PAL,SHD]} && ${CombatStart} && !${Me.ActiveDisc.ID} && (${Target.Named} || ${Me.XTarget}>2) && ${Target.Distance}<75) {
		/echo defensive
		/call SKDefense
	} else /if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100 && ${CombatStart} && ${Select[${Role},pullertank,tank]}) {
		/echo aggro
		/call Mod_AggroCheck
	} else /if (${DPSOn} && ${CombatStart} && (${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} || ${Spawn[${MyTargetID}].ID} || !${Me.Feigning})) {
		/echo combat cast
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
 
Sub SKDefense
	/if (!${Me.ActiveDisc.ID}) {
		/if ((${Me.XTarget} > 3 || ${Target.Named}) && ${Me.CombatAbilityReady[Deflection Discipline]} && !${Me.CombatAbilityReady[${Spell[Cursed Guardian Discipline].RankName}]} && !${Me.CombatAbilityReady[${Spell[Krellnakor's Mantle].RankName}]} && !${Me.CombatAbilityReady[${Spell[Tylix's Carapace].RankName}]} && !${Me.CombatAbilityReady[${Spell[Unholy Aura Discipline].RankName}]}) {
			/disc ${Spell[Deflection Discipline].RankName}
		}
		
		/if ((${Me.XTarget} > 3 || ${Target.Named} || ${Me.PctHPs} < 20) && !${Me.CombatAbilityReady[Deflection Discipline]} && !${Me.AltAbilityReady[Shield Flash]}) {
			/call CastWhat "Shield Flash"
		}
		/if (${Me.PctEndurance}>5) {
			/if (${Me.CombatAbilityReady[${Spell[Unholy Guardian Discipline].RankName}]}) {
				/if (${Spell[${Spell[Cursed Guardian Discipline].RankName}].ID}) {
					/disc ${Spell[${Spell[Cursed Guardian Discipline].RankName}].ID}
					} Else {
					/disc ${Spell[${Spell[Unholy Guardian Discipline].RankName}].ID}
					}
				/if (${ReportDefense}) /call AnnounceMessage 2 y "Guardian Discipline, Defense line 1" r "Active"
				/return				
				}
			/if (!${Me.CombatAbilityReady[${Spell[Unholy Guardian Discipline].RankName}]} && ${Me.CombatAbilityReady[${Spell[Ichor Guard].RankName}]}) {
				/if (${Spell[${Spell[Krellnakor Mantle].RankName}].ID}) {
					/disc ${Spell[Krellnakor Mantle].RankName}
					/goto :SKMantleEnd
					}
				/if (${Spell[${Spell[Doomscale Mantle].RankName}].ID}) {
					/disc ${Spell[Doomscale Mantle].RankName}
					/goto :SKMantleEnd
					}
				/if (${Spell[${Spell[Bonebrood Mantle].RankName}].ID}) {
					/disc ${Spell[Bonebrood Mantle].RankName}
					/goto :SKMantleEnd
					}
				/if (${Spell[${Spell[Gorgon Mantle].RankName}].ID}) {
					/disc ${Spell[Gorgon Mantle].RankName}
					/goto :SKMantleEnd
					}
				/if (${Spell[${Spell[Malarian Mantle].RankName}].ID}) {
					/disc ${Spell[Malarian Mantle].RankName}
					/goto :SKMantleEnd
					}
				/if (${Spell[${Spell[Umbral Carapace].RankName}].ID}) {
					/disc ${Spell[Umbral Carapace].RankName}
					/goto :SKMantleEnd
					}
				/if (${Spell[${Spell[Soul Carapace].RankName}].ID}) {
					/disc ${Spell[Soul Carapace].RankName}
					/goto :SKMantleEnd
					}
				/if (${Spell[${Spell[Soul Shield].RankName}].ID}) {
					/disc ${Spell[Soul Shield].RankName}
					/goto :SKMantleEnd
					}
				/if (${Spell[${Spell[Soul Guard].RankName}].ID}) {
					/disc ${Spell[Soul Guard].RankName}
					/goto :SKMantleEnd
					}
				/if (${Spell[${Spell[Ichor Guard].RankName}].ID}) {
					/disc ${Spell[Ichor Guard].RankName}
					/goto :SKMantleEnd
					}					
				:SKMantleEnd
				/if (${ReportDefense}) /call AnnounceMessage 2 y "SK Mantle Defense, Defense line 2 r "Active""
				/return
				}
			/if (!${Me.CombatAbilityReady[${Spell[Ichor Guard].RankName}]} && ${Me.CombatAbilityReady[${Spell[Gorgon Carapace].RankName}]}) {	
				/if (${Spell[${Spell[Tylix's Carapace].RankName}].ID}) {
					/disc ${Spell[Tylix's Carapace].RankName}
					/goto :SKArmorEnd
					}
				/if (${Spell[${Spell[Vizat's Carapace].RankName}].ID}) {
					/disc ${Spell[Vizat's Carapace].RankName}
					/goto :SKArmorEnd
					}
				/if (${Spell[${Spell[Grelleth's Carapace].RankName}].ID}) {
					/disc ${Spell[Grelleth's Carapace].RankName}
					/goto :SKArmorEnd
					}
				/if (${Spell[${Spell[Sholothian Carapace].RankName}].ID}) {
					/disc ${Spell[Sholothian Carapace].RankName}
					/goto :SKArmorEnd
					}
				/if (${Spell[${Spell[Gorgon Carapace].RankName}].ID}) {
					/disc ${Spell[Gorgon Carapace].RankName}
					/goto :SKArmorEnd
					}					
				:SKArmorEnd
				/if (${ReportDefense}) /call AnnounceMessage 2 y "Carapace Discipline, Defense line 3" r "Active"
				/return				
				}
			}
		/if (!${Me.CombatAbilityReady[${Spell[Gorgon Mantle].RankName}]}) {
			/if (${Me.AltAbilityReady[Fundament: Third Spire of the Reaver]}) {
				/call CastWhat "Fundament: Third Spire of the Reaver"
				/if (${Macro.Return.Equal[CAST_SUCCESS]}) /if (${ReportDefense}) /call AnnounceMessage 2 y "Third Spire" r "Active"
				/return			
				}
			/if (!${Me.AltAbilityReady[Fundament: Third Spire of the Reaver]} && ${Me.AltAbilityReady[Armor of Experience]}) {
				/call CastWhat "Armor of Experience"
				/if (${Macro.Return.Equal[CAST_SUCCESS]}) /if (${ReportDefense}) /call AnnounceMessage 2 y "Armor of Experience"  r "Active"
				/return			
				}	
		}
	}
	
/return