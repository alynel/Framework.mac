|***
 *	WAR.inc
 *	Framework Warrior Include
 *
 *	
 ***|
 
 |***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
Sub _war
	/if (${Debug}) /echo _war Enter Line#: ${Macro.CurLine}
	|/if (${combat_function[]}) {
	|	/echo combat_adj
	|	/call combat_adj
	|}
	
	/if (${ReturnToCamp} && ${Math.Distance[${CampYLoc},${CampXLoc}]}>10) {
	   /varset ReturnToCamp 1
	   /call DoWeMove 1 CheckForCombat
	}
	/if (${Me.CombatState.Equal[COMBAT]} && ${Select[${Me.Class.ShortName},WAR,PAL,SHD]} && ${CombatStart} && !${Me.ActiveDisc.ID} && (${Target.Named} || ${Me.XTarget}>3) && ${Target.Distance}<75) {
		/echo defensive
		/call WarDefense
	} else /if (${HealsOn} && ${Me.PctHPs} <= ${Math.Calc[${${Me.Class.ShortName}Point}*.${tmpHealOverride}]}) {
		/call newSingleHeal "${Me}" "PC" ${Me.PctHPs} 0 G
	} else /if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100 && ${CombatStart} && ${Select[${Role},pullertank,tank]}) {
		/echo aggro
		/call Mod_AggroCheck
	} else /if (${DPSOn} && ${CombatStart} && (${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} || ${Spawn[${MyTargetID}].ID} || !${Me.Feigning})) {
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
Sub WarDefense
	/if (!${Me.ActiveDisc.ID}) {
		/if (${Me.PctEndurance}>5) {
				/if (${Me.CombatAbilityReady[${Spell[Dichotomic Shield].RankName}]}) {
					/disc ${Spell[${Spell[Dichotomic Shield].RankName}].ID}
					/if (${ReportDefense}) /call AnnounceMessage 2 y "Dichotomic Shield" r "Active"
					/return		
				}
				/if (!${Me.CombatAbilityReady[${Spell[Dichotomic Shield].RankName}]}) {
						/if (${Me.CombatAbilityReady[${Spell[Defensive Discipline].RankName}]}) {
							/if (${Spell[${Spell[Culminating Stand Discipline].RankName}].ID}) {
								/disc ${Spell[Culminating Stand Discipline].RankName}
								/goto :WARStandEnd
								}
							/if (${Spell[${Spell[Last Stand Discipline].RankName}].ID}) {
								/disc ${Spell[Last Stand Discipline].RankName}
								/goto :WARStandEnd
								}
							/if (${Spell[${Spell[Final Stand Discipline].RankName}].ID}) {
								/disc ${Spell[Final Stand Discipline].RankName}
								/goto :WARStandEnd
								}
							/if (${Spell[${Spell[Defensive Discipline].RankName}].ID}) {
								/disc ${Spell[Defensive Discipline].RankName}
								/goto :WARStandEnd
								}						
							:WARStandEnd
							/if (${ReportDefense}) /call AnnounceMessage 2 y "Stand Discipline" r "Active"
							/return
						}
					}
		}
			/if (${Cast.Ready[${Me.Inventory[chest]}]}) {
				/call CastWhat "${Me.Inventory[chest]}" 
				/if (${Macro.Return.Equal[CAST_SUCCESS]} && ${ReportDefense}) /call AnnounceMessage 2 y "Clicking BP" r "Active"!
				/return
			}
			/if (${Me.CombatAbilityReady[${Spell[No Time To Bleed].RankName}]} && !${Me.CombatAbilityReady[${Spell[Defensive Discipline].RankName}]} && !${Me.CombatAbilityReady[${Spell[Dichotomic Shield].RankName}]}) {
					/if (${Me.CombatAbilityReady[${Spell[Pain Doesn't Hurt].RankName}]}) {
						/disc ${Spell[${Spell[Pain Doesn't Hurt].RankName}].ID}
						/if (${ReportDefense}) /call AnnounceMessage 2 y "Pain Doesn't Hurt" r "Active"
						/return
					}
					/if (${Me.CombatAbilityReady[${Spell[No Time To Bleed].RankName}]}) {
						/disc ${Spell[${Spell[No Time To Bleed].RankName}].ID}
						/if (${ReportDefense}) /call AnnounceMessage 2 y "No Time To Bleed" r "Active"
						/return
					}
					
			}
			/if (!${Me.CombatAbilityReady[${Spell[No Time To Bleed].RankName}]} && !${Me.CombatAbilityReady[${Spell[Defensive Discipline].RankName}]} && ${Me.CombatAbilityReady[${Spell[Armor of Draconic Runes].RankName}]} && ${Me.PctEndurance}>5) {
				/if (${Spell[${Spell[Armor of Tenacious Runes].RankName}].ID}) {
					/disc ${Spell[Armor of Tenacious Runes].RankName}
					/goto :WARRuneEnd
					}
				/if (${Spell[${Spell[Armor of Darkened Runes].RankName}].ID}) {
					/disc ${Spell[Armor of Darkened Runes].RankName}
					/goto :WARRuneEnd
					}
				/if (${Spell[${Spell[Armor of Stalwart Runes].RankName}].ID}) {
					/disc ${Spell[Armor of Stalwart Runes].RankName}
					/goto :WARRuneEnd
					}
				/if (${Spell[${Spell[Armor of Mystical Runes].RankName}].ID}) {
					/disc ${Spell[Armor of Mystical Runes].RankName}
					/goto :WARRuneEnd
					}
				/if (${Spell[${Spell[Armor of Phantasmic Runes].RankName}].ID}) {
					/disc ${Spell[Armor of Phantasmic Runes].RankName}
					/goto :WARRuneEnd
					}
				/if (${Spell[${Spell[Armor of Timeworn Runes].RankName}].ID}) {
					/disc ${Spell[Armor of Timeworn Runes].RankName}
					/goto :WARRuneEnd
					}
				/if (${Spell[${Spell[Armor of Draconic Runes].RankName}].ID}) {
					/disc ${Spell[Armor of Draconic Runes].RankName}
					/goto :WARRuneEnd
					}				
				:WARRuneEnd
				/if (${ReportDefense}) /call AnnounceMessage 2 y "Runes Discipline" r "Active"
				/return
			}			
			/if (!${Me.CombatAbilityReady[${Spell[No Time To Bleed].RankName}]} && !${Me.CombatAbilityReady[${Spell[Defensive Discipline].RankName}]} && ${Window[CombatAbilityWnd].Child[CAW_CombatEffectLabel].Text.Equal[No Effect]}) {
						/if (${Me.AltAbilityReady[Warlord's Bravery]}) {
							/call CastWhat "Warlord's Bravery"
							/if (${Macro.Return.Equal[CAST_SUCCESS]} && ${ReportDefense}) /call AnnounceMessage 2 y "Warlord's_Bravery" r "Active"
							/return	
						}
						/if (${Me.AltAbilityReady[Warlord's Tenacity]}) {
							/call CastWhat "Warlord's Tenacity" 
							/if (${Macro.Return.Equal[CAST_SUCCESS]} && ${ReportDefense}) /call AnnounceMessage 2 y "Warlords_Tenacity" r "Active"
							/return	
						}				
						/if (${Me.AltAbilityReady[Brace for Impact]}) {
							/call CastWhat "Brace for Impact" 
							/if (${Macro.Return.Equal[CAST_SUCCESS]} && ${ReportDefense}) /call AnnounceMessage 2 y "Brace_For_Impact" r "Active"		
							/return	
						}				
						/if (${Me.AltAbilityReady[Armor of Experience]}) {
							/call CastWhat "Armor of Experience"
							/if (${Macro.Return.Equal[CAST_SUCCESS]} && ${ReportDefense}) /call AnnounceMessage 2 y "Armor_of_Experience" r "Active"
							/return			
						}				
						/if (${Me.AltAbilityReady[Fundament: Third Spire of the Warlord]}) {
							/call CastWhat "Fundament: Third Spire of the Warlord" 
							/if (${Macro.Return.Equal[CAST_SUCCESS]} && ${ReportDefense}) /call AnnounceMessage 2 y "Third_Spire" r "Active"
							/return			
						}				
			}			
					/if (${Me.AltAbilityReady[Blade Guardian]}) {
						/call CastWhat "Blade Guardian"
						/if (${Macro.Return.Equal[CAST_SUCCESS]} && ${ReportDefense}) /call AnnounceMessage 2 y "Blade Guardian" r "Active"
						/return
					}	
					/if (${Me.AltAbilityReady[Hold the Line]}) {
							/call CastWhat "Hold the Line"
							/if (${Macro.Return.Equal[CAST_SUCCESS]} && ${ReportDefense}) /call AnnounceMessage 2 y "Hold_the_Line" r "Active"
							/return		
					} else {
							/if (${Me.AltAbilityReady[Resplendent Glory]}) {
								/call CastWhat "Resplendant Glory"
								/if (${Macro.Return.Equal[CAST_SUCCESS]} && ${ReportDefense}) /call AnnounceMessage 2 y "Respendant_Glory" r "Active"
								/return
							}
					}	
			/if (${Me.AltAbilityReady[Warlord's Resurgence]}) {
				/call CastWhat "Warlord's Resurgence"
				/if (${Macro.Return.Equal[CAST_SUCCESS]}) /if (${ReportDefense}) /call AnnounceMessage 2 y "Warlord's_Resurgence" r "Active"
				/return
			}
	}
/return	