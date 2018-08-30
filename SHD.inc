|
|	SHD.inc
|	Framework Shadow Knight Include

Sub _shd
	/if (${Debug}) /echo _SK Enter Line#: ${Macro.CurLine}

	
	/if (${ReturnToCamp} && ${Math.Distance[${CampYLoc},${CampXLoc}]}>20) {
	    /varset ReturnToCamp 1
		/call DoWeMove 1 CheckForCombat
	    |/if (${Macro.IsTLO[Navigation]}) {
		|	/nav locxyz ${CampYLoc} ${CampXLoc} ${CampZLoc}
		|    /while (1) {
		|		/if (!${Navigation.Active}) /break
		|		/delay 1
		|    }
	    |} else {
		|    /varset ReturnToCamp 1
		|	/call DoWeMove 1 CheckForCombat
	    |}
	  
	}
	/if (${Me.CombatState.Equal[COMBAT]} && ${Select[${Me.Class.ShortName},WAR,PAL,SHD]} && ${CombatStart} && !${Me.ActiveDisc.ID} && (${Target.Named} || ${Me.XTarget}>1) && ${Target.Distance}<75) {
		/echo defensive
		/call SKDefense
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
/return 


 	|/if (${combat_function[]} && ${CombatStart}) {
	|		/echo combat_adj
	|		/call combat_adj
	|}
	
Sub SKDefense
	/echo in skdefense
	/if (!${Me.ActiveDisc.ID}) {
	
		/if (${Me.CombatAbilityReady[Deflection Discipline]} && (${Me.XTarget} > 3 || ${Target.Named}) && !${Me.CombatAbilityReady[${Spell[Unholy Guardian Discipline].RankName}]} && !${Me.CombatAbilityReady[${Spell[Doomscale Mantle].RankName}]} && !${Me.CombatAbilityReady[${Spell[Vizat's Carapace].RankName}]} && !${Me.CombatAbilityReady[${Spell[Unholy Aura Discipline].RankName}]}) {
			|/disc ${Spell[Deflection Discipline].RankName}
			/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Deflection Discipline].RankName}]}].ID}
		}
		
		/echo past deflect
		/if ((${Me.XTarget} > 3 || ${Target.Named} || ${Me.PctHPs} < 20) && !${Me.CombatAbilityReady[Deflection Discipline]} && !${Me.AltAbilityReady[Shield Flash]}) {
			/call CastWhat "Shield Flash"
		}
		/echo past shield flash
		/if (${Me.PctEndurance}>5) {
			/if (${Me.CombatAbilityReady[${Spell[Unholy Guardian Discipline].RankName}]}) {
				/if (${Me.CombatAbilityReady[${Spell[Cursed Guardian Discipline].RankName}]}) {
					|/disc ${Spell[${Spell[Cursed Guardian Discipline].RankName}].ID}
					/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Cursed Guardian Discipline].RankName}]}].ID}
				} else {
					|/disc ${Spell[${Spell[Unholy Guardian Discipline].RankName}].ID}
					/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Unholy Guardian Discipline].RankName}]}].ID}
				}
			
				/return				
			}
			
			/echo past gaurdian
			/if (${Me.CombatAbilityReady[${Spell[Unholy Aura Discipline].RankName}]}) {
					
				|/disc ${Spell[${Spell[Unholy Aura Discipline].RankName}].ID}
				/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Unholy Aura Discipline].RankName}]}].ID}
				
				/return				
			}
			
			/echo past Aura
			
			/if (!${Me.CombatAbilityReady[${Spell[Unholy Guardian Discipline].RankName}]} && ${Me.CombatAbilityReady[${Spell[Ichor Guard].RankName}]}) {
			
				/if (${Me.CombatAbilityReady[${Spell[Krellnakor Mantle].RankName}]}) {
					|/disc ${Spell[Krellnakor Mantle].RankName}
					/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Krellnakor Mantle].RankName}]}].ID}
					/goto :SKMantleEnd
				}
				
				/if (${Me.CombatAbilityReady[${Spell[Doomscale Mantle].RankName}]}) {
					|/disc ${Spell[Doomscale Mantle].RankName}
					/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Doomscale Mantle].RankName}]}].ID}
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
				
				/return
			}
			/echo past mantle
			
			/if (!${Me.CombatAbilityReady[${Spell[Unholy Guardian Discipline].RankName}]} && !${Me.CombatAbilityReady[${Spell[Ichor Guard].RankName}]} && ${Me.CombatAbilityReady[${Spell[Grelleth's Carapace].RankName}]}) {	
				/if (${Me.CombatAbilityReady[${Spell[Tylix's Carapace].RankName}]}) {
					|/disc ${Spell[Tylix's Carapace].RankName}
					/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Tylix's Carapace].RankName}]}].ID}
					/goto :SKArmorEnd
				}
				/if (${Me.CombatAbilityReady[${Spell[Vizat's Carapace].RankName}]}) {
					|/disc ${Spell[Vizat's Carapace].RankName}
					/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Vizat's Carapace].RankName}]}].ID}
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
				
				/return				
			}
		
			/echo past carapace
			
			
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

