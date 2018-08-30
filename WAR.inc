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
	|/echo in war sub
	/if (${ReturnToCamp} && ${Math.Distance[${CampYLoc},${CampXLoc}]}>20) {
	   /varset ReturnToCamp 1
	   /call DoWeMove 1 CheckForCombat
	}
	/if (${Me.CombatState.Equal[COMBAT]} && ${Select[${Me.Class.ShortName},WAR,PAL,SHD]} && ${CombatStart} && !${Me.ActiveDisc.ID} && (${Target.Named} || ${Me.XTarget}>1) && ${Target.Distance}<75) {
		|/echo defensive
		/call WarDefense
	} else /if (${SpawnSort[1,asc,PctAggro,xtarhater].PctAggro} < 100 && ${CombatStart} && ${Select[${Role},pullertank,tank]}) {
		|/echo aggro
		|/call Mod_AggroCheck
		/call NewCast ${SpawnSort[1,asc,PctAggro,xtarhater].ID} "Aggro"
	} else /if (${DPSOn} && ${CombatStart} && (${Spawn[${MyTargetID}].Type.NotEqual[Corpse]} || ${Spawn[${MyTargetID}].ID} || !${Me.Feigning})) {
		|/echo combat cast
		|/call CombatCast
		|/call newcombatcast
		/call NewCast ${MyTargetID} "DPS"
	}
/return 

|/if (${combat_function[]}) {
	|	/echo combat_adj
	|	/call combat_adj
	|}
	
|***
 *	DES: 
 *	USE: 
 *	INI: 
 *  NOTE:
 ***|
Sub WarDefense
	|/echo in War defensive
	/if (!${Me.ActiveDisc.ID}) {
	
		/if (${Me.PctEndurance}>5) {
			/if (${Me.CombatAbilityReady[${Spell[Dichotomic Shield].RankName}]}) {
				|/disc ${Spell[${Spell[Dichotomic Shield].RankName}].ID}
				/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Dichotomic Shield].RankName}]}].ID}
				
				/return		
			}
			
			/echo past dico
			
			/if (!${Me.CombatAbilityReady[${Spell[Dichotomic Shield].RankName}]} && ${Me.CombatAbilityReady[${Spell[Defensive Discipline].RankName}]}) {
				/if (${Me.CombatAbilityReady[${Spell[Defensive Discipline].RankName}]}) {
				
					/if (${Me.CombatAbilityReady[${Spell[Culminating Stand Discipline].RankName}]}) {
						|/disc ${Spell[Culminating Stand Discipline].RankName}
						/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Culminating Stand Discipline].RankName}]}].ID}
						/goto :WARStandEnd
					}
					
					/if (${Me.CombatAbilityReady[${Spell[Last Stand Discipline].RankName}]}) {
						|/disc ${Spell[Last Stand Discipline].RankName}
						/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Last Stand Discipline].RankName}]}].ID}
						/goto :WARStandEnd
					}
					
					/if (${Me.CombatAbilityReady[${Spell[Final Stand Discipline].RankName}]}) {
						|/disc ${Spell[Final Stand Discipline].RankName}
						/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Final Stand Discipline].RankName}]}].ID}
						/goto :WARStandEnd
					}
					
					/if (${Me.CombatAbilityReady[${Spell[Defensive Discipline].RankName}]}) {
						|/disc ${Spell[Defensive Discipline].RankName}
						/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Defensive Discipline].RankName}]}].ID}
						/goto :WARStandEnd
					}		
					
					:WARStandEnd
					/return
				}
			}
			
			/echo past defensive disc
		}
		
		/if (${Me.ItemReady[chest]}) {
			/useitem "${Me.Inventory[chest]}"
			/return
		}
		
		/echo past chest
		
		/if (${Me.CombatAbilityReady[${Spell[No Time To Bleed].RankName}]} && !${Me.CombatAbilityReady[${Spell[Defensive Discipline].RankName}]} && !${Me.CombatAbilityReady[${Spell[Dichotomic Shield].RankName}]}) {
				/if (${Me.CombatAbilityReady[${Spell[Pain Doesn't Hurt].RankName}]}) {
					|/disc ${Spell[${Spell[Pain Doesn't Hurt].RankName}].ID}
					/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Pain Doesn't Hurt].RankName}]}].ID}
					/return
				}
				/if (${Me.CombatAbilityReady[${Spell[No Time To Bleed].RankName}]}) {
					|/disc ${Spell[${Spell[No Time To Bleed].RankName}].ID}
					/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[No Time To Bleed].RankName}]}].ID}
					/return
				}
				
		}
		
		/echo past no time to bleed
		
		/if (!${Me.CombatAbilityReady[${Spell[No Time To Bleed].RankName}]} && !${Me.CombatAbilityReady[${Spell[Defensive Discipline].RankName}]} && ${Me.CombatAbilityReady[${Spell[Armor of Draconic Runes].RankName}]} && ${Me.PctEndurance}>5) {
			/if (${Me.CombatAbilityReady[${Spell[Armor of Tenacious Runes].RankName}]}) {
				|/disc ${Spell[Armor of Tenacious Runes].RankName}
				/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Armor of Tenacious Runes].RankName}]}].ID}
				/goto :WARRuneEnd
				}
			/if (${Me.CombatAbilityReady[${Spell[Armor of Darkened Runes].RankName}]}) {
				|/disc ${Spell[Armor of Darkened Runes].RankName}
				/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Armor of Darkened Runes].RankName}]}].ID}
				/goto :WARRuneEnd
				}
			/if (${Me.CombatAbilityReady[${Spell[Armor of Stalwart Runes].RankName}]}) {
				|/disc ${Spell[Armor of Stalwart Runes].RankName}
				/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Armor of Stalwart Runes].RankName}]}].ID}
				/goto :WARRuneEnd
				}
			/if (${Me.CombatAbilityReady[${Spell[Armor of Mystical Runes].RankName}]}) {
				|/disc ${Spell[Armor of Mystical Runes].RankName}
				/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Armor of Mystical Runes].RankName}]}].ID}
				/goto :WARRuneEnd
				}
			/if (${Me.CombatAbilityReady[${Spell[Armor of Phantasmic Runes].RankName}]}) {
				|/disc ${Spell[Armor of Phantasmic Runes].RankName}
				/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Armor of Phantasmic Runes].RankName}]}].ID}
				/goto :WARRuneEnd
				}
			/if (${Me.CombatAbilityReady[${Spell[Armor of Timeworn Runes].RankName}]}) {
				|/disc ${Spell[Armor of Timeworn Runes].RankName}
				/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Armor of Timeworn Runes].RankName}]}].ID}
				/goto :WARRuneEnd
				}
			/if (${Me.CombatAbilityReady[${Spell[Armor of Draconic Runes].RankName}]}) {
				|/disc ${Spell[Armor of Draconic Runes].RankName}
				/disc ${Me.CombatAbility[${Me.CombatAbility[${Spell[Armor of Draconic Runes].RankName}]}].ID}
				/goto :WARRuneEnd
				}				
			:WARRuneEnd
			/return
		}			
		/echo past runes
		/if (!${Me.CombatAbilityReady[${Spell[No Time To Bleed].RankName}]} && !${Me.CombatAbilityReady[${Spell[Defensive Discipline].RankName}]} && ${Window[CombatAbilityWnd].Child[CAW_CombatEffectLabel].Text.Equal[No Effect]}) {
					/if (${Me.AltAbilityReady[Warlord's Bravery]}) {
						|/call CastWhat "Warlord's Bravery"
						/alt act ${Me.AltAbility[Warlord's Bravery].ID}
						/return	
					}
					/if (${Me.AltAbilityReady[Warlord's Tenacity]}) {
						|/call CastWhat "Warlord's Tenacity" 
						/alt act ${Me.AltAbility[Warlord's Tenacity].ID}
						/return	
					}				
					/if (${Me.AltAbilityReady[Brace for Impact]}) {
						|/call CastWhat "Brace for Impact" 
						/alt act ${Me.AltAbility[Brace for Impact].ID}
						/return	
					}				
					/if (${Me.AltAbilityReady[Armor of Experience]}) {
						|/call CastWhat "Armor of Experience"
						/alt act ${Me.AltAbility[Armor of Experience].ID}
						/return			
					}				
					/if (${Me.AltAbilityReady[Fundament: Third Spire of the Warlord]}) {
						|/call CastWhat "Fundament: Third Spire of the Warlord" 
						/alt act ${Me.AltAbility[Fundament: Third Spire of the Warlord].ID}
						/return			
					}				
		}		
		/echo past bravery
				/if (${Me.AltAbilityReady[Blade Guardian]}) {
					|/call CastWhat "Blade Guardian"
					/alt act ${Me.AltAbility[Blade Guardian].ID}
					/return
				}	
				/if (${Me.AltAbilityReady[Hold the Line]}) {
						|/call CastWhat "Hold the Line"
						/alt act ${Me.AltAbility[Hold the Line].ID}
						/return		
				} else {
						/if (${Me.AltAbilityReady[Resplendent Glory]}) {
							|/call CastWhat "Resplendant Glory"
							/alt act ${Me.AltAbility[Resplendent Glory].ID}
							/return
						}
				}
		/echo past blade gaurdian
		/if (${Me.AltAbilityReady[Warlord's Resurgence]}) {
			|/call CastWhat "Warlord's Resurgence"
			/alt act ${Me.AltAbility[Warlord's Resurgence].ID}
			/return
		}
		/echo past resurgence
	}
/return	