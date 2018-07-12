|***
 *	Quests.inc
 *	Framework Quest Subs Include
 *
 *	
 ***|
#event CustomExp "#*#You gain party experience#*#"

#Bind ShakeLoose   /shakeloose

Sub InitCustom
	/echo InitCustom called
	/if (${Group.Leader.ID}==${Me.ID}) {
		/grouproles set ${Me} 5
	}
	|/varset MeleeDistance 400
	/ini "Loot.ini" "B" "Burled Wood" "Keep"
	/ini "Loot.ini" "C" "Crystal Harvester Mold" "Keep"
	/ini "Loot.ini" "F" "Faceted Crystal" "Keep"
	/ini "Loot.ini" "S" "Shimmering Hay" "Keep"
	/ini "Loot.ini" "T" "Tin Ore" "Keep"
	/declare bCustomInitdone int outer 1
	/declare SpotName string outer
	/declare SpotTimer timer outer
	/declare CustomName string outer
	/declare CustomTimer timer outer
	/declare CampCTimer timer outer
	/declare custoncount int outer
	/declare firstkill string outer
	/declare myoldyloc int outer
	/declare myoldxloc int outer
	/declare bFirstBanditsDone int outer 0
	/declare bForgeOnce int outer 1
	/declare bBurledOnce int outer 0
	/declare customstucktimer timer outer 0
	/declare customlastdist[6] int outer 0
/return

Sub Event_CustomExp
	/if (${Defined[bCustomInitdone]}==FALSE) {
		/call InitCustom
	}
	    /if (${custoncount}==0) {
		/varset firstkill ${Time}
	    }
	    /varcalc custoncount (${custoncount}+1)
	    /echo ${Time} Killed ${custoncount} mobs so far since ${firstkill}
            /echo SLAIN >> ${MyTargetName} << EXP: ${If[${Me.PctExp}<${MyExp},${Math.Calc[100-${MyExp}+${Me.PctExp}]},${Math.Calc[${Me.PctExp}-${MyExp}]}]}% AAEXP: ${If[${Me.PctAAExp}<${MyAAExp},${Math.Calc[100-${MyAAExp}+${Me.PctAAExp}]},${Math.Calc[${Me.PctAAExp}-${MyAAExp}]}]}%
            /popup SLAIN >> ${MyTargetName} << EXP: ${If[${Me.PctExp}<${MyExp},${Math.Calc[100-${MyExp}+${Me.PctExp}]},${Math.Calc[${Me.PctExp}-${MyExp}]}]}% AAEXP: ${If[${Me.PctAAExp}<${MyAAExp},${Math.Calc[100-${MyAAExp}+${Me.PctAAExp}]},${Math.Calc[${Me.PctAAExp}-${MyAAExp}]}]}%
	/doevents flush CustomExp
/return
Sub IsAnyoneInGroupOutofRange(int bShake)
	/declare gn int local 0
	/declare currdist int local 0
	/declare calcdist int local 0
	/for gn 1 to 5
		/if (${Group.Member[${gn}].Type.Equal[PC]}==TRUE && ${Group.Member[${gn}].Distance3D} > 400) {
			/varset currdist ${Group.Member[${gn}].Distance3D}
			/echo ${Group.Member[${gn}].Name} is lagging behind at ${currdist}
			/squelch /bcaa //nav stop
			/if (${bShake}==0) {
				/bct ${Group.Member[${gn}].Name} //nav id ${Me.ID}
				/delay 2s
			} else {
				/varcalc calcdist ${customlastdist[${gn}]} + 20
				/if (${currdist} < ${calcdist}) {
					/beep
					/echo we are not getting anywhere time to shake loose...
					/bct ${Group.Member[${gn}].Name} //shakeloose
					/delay 6s
				}
			}
			/varset customlastdist[${gn}] ${Group.Member[${gn}].Distance3D}
			/return 1
		}
	/next gn
/return 0

Sub WaitForNavToFinish(int y,int x,int z)
	/declare bWait int local 0
	/varset customstucktimer 0
	/if (${SpawnCount[id ${Me.ID} loc ${x} ${y} radius 20]}==0) {
		/bcaa //chase on
		/bcaa //nav locyxz ${y} ${x} ${z}
		/delay 2s ${Navigation.Active}==TRUE
:navloop
		/call IsAnyoneInGroupOutofRange 0
		/if (${Macro.Return}==1) {
			/if (${bWait}==0) {
				/varset customstucktimer 10s
				/varset bWait 1
			}
			/if (${customstucktimer}==0) {
				/echo Custom Timer Triggered most likely due to a character getting stuck
				/beep
				/echo gonna try to unstick them
				/varset bWait 0
				/call IsAnyoneInGroupOutofRange 1
			}
			/delay 1s
			/goto :navloop
		}
		/if (${Me.XTarget} > 0 && ${Me.XTarget[1].ID}) {
			/varset MeleeDistance 400
			/echo we are under attack, lets stop and kill it.
			/bcaa //nav id ${Me.XTarget[1].ID}
			/delay 2s ${Navigation.Active}==TRUE
			/delay 10s ${Navigation.Active}==FALSE
			/return 0
		}
		/if (${Navigation.Active}==TRUE) {
			/delay 1s
			/goto :navloop
		}
	} else {
		/return 1
	}
/return 0

Sub DoCleet
	/if (${Defined[bCustomInitdone]}==FALSE) {
		/call InitCustom
	}
	/if (${Group.MasterLooter.ID}!=${Me.ID}) {
		/echo I HAVE to be the masterlooter...
		/grouproles set ${Me} 5
		/beep
		/delay 1s
	}
	/if (${Window[TaskWnd].Open}==FALSE) {
		/beep
		/echo this macro requires that the TaskWnd is open but you CAN minimize t if you like
		/windowstate TaskWnd open
		/delay 2s ${Window[TaskWnd].Open}==TRUE
	}
	/if (${Window[TaskWnd].Child[TASK_TaskList].GetCurSel}!=1) {
		/invoke ${Window[TaskWnd].Child[TASK_TaskList].Select[Sprucing up Shakey]}
		/delay 5
	}
	/if (${Task.Title.NotEqual[Sprucing Up Shakey]}) {
		/echo this macro requires that the Task Sprucing Up Shakey is active
		/end
	}
	/if (${Task.Leader.NotEqual[${Me}]}) {
		/return
	}
	|need to clear this so we can loot it again at the end...
	/if (${Task[0].Step.Instruction.Equal[Speak with Cleet Miller at his Farm]}) {
		/if (${FindItemCount[Shimmering Hay]}) {
			/itemnotify "Shimmering Hay" leftmouseup
			/delay 1s ${Cursor.ID}
			/destroyitem
		}
	}
	/if (${Group.AnyoneMissing}==TRUE) {
		/echo groupmember gone awol need to wait for it
		/delay 1s
		/return
	}
	/if (${Task[0].Step.Instruction.Equal[Speak with Cleet Miller at his Farm]}) {
		/echo doing ${Task[0].Step.Instruction}
		/call WaitForNavToFinish -2200 -4140 0
		/if (${Macro.Return}==1) {
			/tar id ${Spawn[npc Cleet Miller].ID}
			/echo now hail cleet
			/keypress h
			/say till
		}
	} else /if (${Task[0].Step.Instruction.Equal[Loot Burled Wood]} && ${Me.XTarget}==0) {
		/if (${bBurledOnce}==0) {
			/varset bBurledOnce 1
			/call WaitForNavToFinish -2253 -4020 0
		}
		/echo doing ${Task[0].Step.Instruction}
		/bcaa //chase on
		/tar npc treant
		/delay 1s ${Target.ID}
		/echo treant aquired navigating to ${Target.Y} ${Target.X} ${Target.Z}
		/call WaitForNavToFinish ${Target.Y} ${Target.X} ${Target.Z}
		|/if (${Macro.Return}==1) {
			/bcaa //Stick 5
			/bcaa //attack on
		|}
	} else /if (${Task[0].Step.Instruction.Equal[Loot Tin Ore]} && ${Me.XTarget}==0) {
		/echo doing ${Task[0].Step.Instruction}
		/bcaa //chase on
		/tar npc goblin
		/call WaitForNavToFinish ${Target.Y} ${Target.X} ${Target.Z}
		|/if (${Macro.Return}==1) {
			/bcaa //Stick 5
			/bcaa //attack on
		|}
	} else /if (${Task[0].Step.Instruction.Equal[Loot Faceted Crystal]} && ${Me.XTarget}==0) {
		/echo doing ${Task[0].Step.Instruction}
		/if (${SpawnCount[npc bandit loc -7058 905 radius 100]}!=0) {
			/call WaitForNavToFinish 1089 -7220 36
			/if (${Macro.Return}==1) {
				/tar npc bandit
				/echo everyone is here we can attack
				/bcaa //Stick 5
				/bcaa //attack on
				/delay 10s ${Target.Distance3D} < 20 && ${Me.XTarget}
			}
		} else {
			/bcaa //chase on
			/tar npc bandit
			/call WaitForNavToFinish ${Target.Y} ${Target.X} ${Target.Z}
			|/if (${Macro.Return}==1) {
				/bcaa //Stick
				/bcaa //attack on
				/delay 10s ${Target.Distance3D} < 20 && ${Me.XTarget}
			|}
		}
	} else /if (${Task[0].Step.Instruction.Equal[Obtain a Crystal Harvester Mold from Spinner]} && ${Me.XTarget}==0) {
		/echo doing ${Task[0].Step.Instruction}
		/call WaitForNavToFinish -1450 -12775 4
		/if (${Macro.Return}==1) {
			/echo everyone is here we can attack spinner, unpause when he attacks
			/tar npc spinner
			/say enemy
		}
	} else /if (${Task[0].Step.Instruction.Find[Combine the Burled Wood]}==1 && ${Me.XTarget}==0) {
		/echo doing ${Task[0].Step.Instruction}
		/call WaitForNavToFinish -1436 -12885 6
		/if (${Macro.Return}==1) {
			/declare comb int local 1
			/if (!${Window[TradeskillWnd].Open}) {
				/itemtarget forge
				/click left item
			} else {
				/beep
				/beep
				/echo everyone is here we can combine the things
			:waitforharvester
				/if (${Window[TradeskillWnd].Open}) {
					/invoke ${Window[TradeSkillWnd].Child[COMBW_ExperimentButton].LeftMouseUp}
					/delay 2s ${Window[ContainerWindow]}==TRUE
				}
				/if (${Window[ContainerWindow]}) {
					/delay 2s
					/for comb 1 to 6
						/ctrl /itemnotify "Burled Wood" leftmouseup
						/delay 2s ${Cursor.ID}==85459
						/itemnotify enviro${comb} leftmouseup
						/delay 2s !${Cursor.ID}
						/delay 5
					/next comb
					/for comb 7 to 8
						/ctrl /itemnotify "Tin Ore" leftmouseup
						/delay 2s ${Cursor.ID}==85460
						/itemnotify enviro${comb} leftmouseup
						/delay 2s !${Cursor.ID}
						/delay 5
					/next comb
					/itemnotify "Faceted Crystal" leftmouseup
					/delay 2s ${Cursor.ID}==85461
					/itemnotify enviro9 leftmouseup
					/delay 2s !${Cursor.ID}
					/delay 5
					/itemnotify "Crystal Harvester Mold" leftmouseup
					/delay 2s ${Cursor.ID}==85462
					/itemnotify enviro10 leftmouseup
					/delay 2s !${Cursor.ID}
					/delay 5
					/combine ContainerWindow
					/delay 3s ${Cursor.ID}==85464
					/windowstate ContainerWindow close
				}
				/if (${FindItemCount[=Crystal Harvester]}==0) {
					/beep
					/delay 5s
					/echo [${Time}] waiting for you to create the Crystal Harvester
					/goto :waitforharvester
				}
				/echo we got it! time to move on.
				/autoinv
				/delay 1s
			}
		}
	} else /if (${Task[0].Step.Instruction.Find[Attempt to till the rocky soil]}==1 && ${Me.XTarget}==0) {
		/if (${bForgeOnce}==1) {
			/declare shortest int local 0
			/declare sn int local 0
			/declare distold int local 100000
			/declare tempsorter[5] int local
			/declare sorter[5] int local
			/varset sorter[1] ${Math.Distance[${Me.Y},${Me.X}:-1105,-12969]}
			/varset sorter[2] ${Math.Distance[${Me.Y},${Me.X}:-1704,-8707]}
			/varset sorter[3] ${Math.Distance[${Me.Y},${Me.X}:-2083,-5541]}
			/varset sorter[4] ${Math.Distance[${Me.Y},${Me.X}:-2340,-4250]}
			/for sn 1 to 4
				/if (${sorter[${sn}]} < ${distold}) {
					|/echo ${sorter[${sn}]} < ${distold}
					/varset distold ${sorter[${sn}]}
					/varset bForgeOnce ${sn}
				}
			/next sn
			/echo we need to go to waypoint ${bForgeOnce}
		}
		|/mqp on
		/if (${bForgeOnce}==1) {
			/echo need to get away from that stupid tarp we get stuck in
			/varset bForgeOnce 2
			/nav locyxz -1105 -12969 73
			/delay 2s ${Navigation.Active}==TRUE
			/delay 10s ${Navigation.Active}==FALSE
			/bcaa //chase on
			/bcaa //nav id ${Me.ID}
			/delay 2s
			/echo at waypoint 1
			/beep
			/return
		}
		/if (${bForgeOnce}==2) {
			/echo going to waypoint 2
			/call WaitForNavToFinish -1704 -8707 0
			/if (${Macro.Return}==1) {
				/echo at waypoint 2
				/beep
				/varset bForgeOnce 3
				/return
			}
			/return
		}
		/if (${bForgeOnce}==3) {
			/echo going to waypoint 3
			/call WaitForNavToFinish -2083 -5541 0
			/if (${Macro.Return}==1) {
				/echo at waypoint 3
				/beep
				/varset bForgeOnce 4
				/return
			}
			/return
		}
		/echo doing ${Task[0].Step.Instruction}
		/call WaitForNavToFinish -2340 -4250 0
		/if (${Macro.Return}==1) {
			/tar id ${Spawn[untilled].ID}
			/delay 1s
			/useitem "Crystal Harvester"
			/delay 5s
			/echo we have arrived at ${Target} get the shimmering hay from it.
		}
	} else /if (${Task[0].Step.Instruction.Find[Return to Cleet to discuss]}==1 && ${Me.XTarget}==0) {
		/echo doing ${Task[0].Step.Instruction}
		/call WaitForNavToFinish -2261 -4176 0
		/if (${Macro.Return}==1) {
			/tar npc cleet
			/keypress h
		}
	} else /if (${Task[0].Step.Instruction.Find[Question Chief Goonda]}==1 && ${Me.XTarget}==0) {
		/echo doing ${Task[0].Step.Instruction}
		/call WaitForNavToFinish -595 -9148 48
		/if (${Macro.Return}==1) {
			/tar npc goond
			/keypress h
			/echo we have arrived at ${Target} unpause when done
		}
	} else /if (${FindItemCount[85463]}==0 && ${Task[0].Step.Instruction.Find[Bring an immaculate]}==1 && ${Me.XTarget}==0) {
		/echo time to ${Task[0].Step.Instruction}
		/declare liondist int local 0
		/declare wolfdist int local 0
		/declare beardist int local 0
		/bcaa //chase on
		/varset liondist ${Spawn[npc lion].Distance3D}
		/varset wolfdist ${Spawn[npc wolf].Distance3D}
		/varset beardist ${Spawn[npc bear].Distance3D}
		/if (${liondist}!=0 && ${wolfdist}!=0 && ${beardist}!=0 && ${liondist} < ${wolfdist} && ${liondist} < ${beardist}) {
			/tar npc lion
		} else /if (${liondist}!=0 && ${wolfdist}!=0 && ${beardist}!=0 && ${wolfdist} < ${liondist} && ${wolfdist} < ${beardist}) {
			/tar npc wolf
		} else  /if (${liondist}!=0 && ${wolfdist}!=0 && ${beardist}!=0 && ${beardist} < ${liondist} && ${beardist} < ${wolfdist}) {
			/tar npc bear
		} else {
			|whatever, im not gonna spend time on checking every single scenario
			/tar npc lion
		}
		/delay 1s ${Target.ID}
		/echo ${Target} aquired navigating to ${Target.Y} ${Target.X} ${Target.Z}
		/call WaitForNavToFinish ${Target.Y} ${Target.X} ${Target.Z}
		/echo we arrived lets attack it
		/bcaa //Stick 5
		/bcaa //attack on
	} else /if (${FindItemCount[85463]}>=1 && ${Task[0].Step.Instruction.Find[Bring an immaculate]}==1 && ${Me.XTarget}==0) {
		/echo time to ${Task[0].Step.Instruction}
		/call WaitForNavToFinish -582 -8853 108
		/if (${Macro.Return}==1) {
			/bcg //camphere on
			:checkpet
			/if (${Pet.ID} && ${Pet.Stance.NotEqual[GUARD]}) {
				/echo its important that our pet stays put otherwise it will attack the spirit outside of camp and we dont want that.
				/pet guard
				/delay 3s ${Pet.Stance.Equal[GUARD]}
				/pet ghold on
				/delay 1s
				/beep
				/goto :checkpet
			}
			/halfmoon 10
			/tar npc goond
			/delay 1s
			/echo time to go down and give goonda the pelt then come back with the spirit so we can fight up here
			/nav id ${Target.ID}
			/delay 2s ${Navigation.Active}==TRUE
			/delay 20s ${Navigation.Active}==FALSE
			|/keypress h
			:waitforgivepelt
			/if (${Cursor.ID} && ${Cursor.ID}!=85463) {
				/autoinv
				/delay 1s ${Cursor.ID}==FALSE
			}
			/if (!${Cursor.ID} && ${Window[GiveWnd].Open}==FALSE) {
				/itemnotify #85463 leftmouseup
				/delay 2s ${Cursor.ID}
			}
			/if (${Window[GiveWnd].Open}==FALSE && ${Cursor.ID}==85463) {
				/click left target
				/delay 2s ${Window[GiveWnd].Open}==TRUE
				/beep
			}
			/if (${Window[GiveWnd].Open}) {
				/if (${Window[InventoryWindow].Open}) /windowstate InventoryWindow close
				/echo [${Time}] Give the pelt to Goonda
				/notify GiveWnd GVW_Give_Button leftmouseup
				/delay 3s
				/beep
				/goto :waitforgivepelt
			}
			/bcg //mqp on
			/echo we gave the pelt now lets pull the spirit up to the guys
			/delay 5s ${Task[0].Step.Instruction.Find[Prove your worth]}==1
			/delay 5s ${Me.XTarget} > 0
			/bcaa //nav locyxz -582 -8853 108
			/delay 2s ${Navigation.Active}==TRUE
			/delay 10s ${Navigation.Active}==FALSE
			/beep
			/echo what happens now?
			/echo we should be back at camp and spirit should be comming for us...
			:waitforspirit
			/if (${Spawn[npc ancient].Distance} > 50) {
				/delay 1s
				/echo still waiting for spirit to get here ${Spawn[npc ancient].Distance}
				/goto :waitforspirit
			}
			/if (${Pet.ID} && ${Pet.Stance.NotEqual[FOLLOW]}) {
				/pet follow
				/delay 3s ${Pet.Stance.Equal[FOLLOW]}
				/pet ghold off
				/delay 5
			}
			/bcaa //mqp off
			/tar npc ancient
			|/stick 5
			/attack on
		}
	} else /if (${Task[0].Step.Instruction.Find[Prove your worth]}==1 && ${Me.XTarget}==0) {
		/echo time to ${Task[0].Step.Instruction}
		/delay 1
	} else /if (${Task[0].Step.Instruction.Find[Give the Crystal Harvester]}==1 && ${Me.XTarget}==0) {
		/echo time to ${Task[0].Step.Instruction}
		/target clear
		/chase on
		/bcaa //switchnow
		/echo waiting for An Ancient Spirit to go back to his spot.
		/delay 3s
		/tar npc spirit
		/delay 1s ${Target.ID}
		/delay 60s ${Spawn[npc loc -9137 -689 55 radius 10].ID}==${Target.ID}
		/nav locyxz -595 -9148 48
		/delay 2s ${Navigation.Active}==TRUE
		/delay 20s ${Navigation.Active}==FALSE
		/nav id ${Spawn[npc ancient].ID}
		/delay 2s ${Navigation.Active}==TRUE
		/delay 10s ${Navigation.Active}==FALSE
		/echo now go down and give the spirit the harvester
		/itemnotify "Crystal Harvester" leftmouseup
		/if (!${Target.ID}) {
			/tar npc spirit
		}
		/delay 2s ${Cursor.ID}
		/stick 5
		/delay 5s ${Target.Distance} < 20
		/click left target
		/beep
		:waitforspirittogetharv
		/if (${Window[GiveWnd].Open} && ${Window[GiveWnd].Child[GVW_MyItemSlot0].Tooltip.Equal[Crystal Harvester]}) {
			/notify GiveWnd GVW_Give_Button leftmouseup
			/delay 1s
		}
		/beep
		/if (${Window[InventoryWindow].Open}) /windowstate InventoryWindow close
		/if (${FindItemCount[=Enchanted Crystal Harvester]}==0) {
			/if (${Target.CleanName.Find[an ancient spirit]}==1) {
				/if (${Target.Distance} > 20) {
					/nav id  ${Target.ID}
					/delay 2s ${Navigation.Active}==TRUE
					/delay 10s ${Navigation.Active}==FALSE
				}
				/if (${Target.Distance} < 20 && ${Cursor.ID}==85464) {
					/click left target
				}
				/echo [${Time}] give the Crystal Harvester to the ancient spirit
				/delay 3s
			} else {
				/tar npc ancient
				/delay 1s ${Target.ID}
			}			
			/goto :waitforspirittogetharv
		}
		/autoinv
		/delay 1s
		/nav locyxz -609 -9191 49
		/delay 2s ${Navigation.Active}==TRUE
		/delay 20s ${Navigation.Active}==FALSE
		/nav locyxz -582 -8853 108
		/delay 2s ${Navigation.Active}==TRUE
		/delay 20s ${Navigation.Active}==FALSE
		/echo ok we got it, time to move on
	} else /if (${Task[0].Step.Instruction.Find[Till the rocky soil]}==1 && ${Me.XTarget}==0) {
		/target clear
		/if (${Pet.ID} && ${Pet.Stance.NotEqual[FOLLOW]}) {
			/pet follow
			/delay 1s ${Pet.Stance.Equal[FOLLOW]}
		}
		/echo time to ${Task[0].Step.Instruction}
		/call WaitForNavToFinish -2340 -4250 0
		/if (${Macro.Return}==1) {
			/tar id ${Spawn[untilled].ID}
			/delay 1s ${Target.ID}
			/echo we have arrived at ${Target} now get the shimmering hay from it
			/useitem "Enchanted Crystal Harvester"
			/delay 2s
		}
		/if (${AdvLoot.SList[1].Name.Equal[Shimmering Hay]}) {
			/advloot shared "Shimmering Hay" ag
			/delay 1s
			/advloot shared "Shimmering Hay" giveto ${Me}
			/delay 1s
		}
	} else /if (${Task[0].Step.Instruction.Find[Tell Cleet Miller of your success]}==1 && ${Me.XTarget}==0) {
		/echo time to ${Task[0].Step.Instruction}
		/call WaitForNavToFinish -2261 -4176 0
		/if (${Macro.Return}==1) {
			/tar npc cleet
			/keypress h
			/echo we have arrived completed all steps now go out and look for the bigger belt and wee'er harvester
			/mqp on
		}
	}
/return

Sub DoHorn
	/if (${Defined[bCustomInitdone]}==FALSE) {
		/call InitCustom
	}
	/if (${Window[TaskWnd].Open}==FALSE) {
		/beep
		/echo this macro requires that the TaskWnd is open but you CAN minimize t if you like
		/windowstate TaskWnd open
		/delay 2s ${Window[TaskWnd].Open}==TRUE
		/invoke ${Window[TaskWnd].Child[TASK_TaskList].Select[Defending Knowledge]}
		/delay 5
	}
	/if (${Task.Title.NotEqual[Defending Knowledge]}) {
		/echo this macro requires that the Task Defending Knowledge is active
		/end
	}
	/if (${Task.Leader.NotEqual[${Me}]}) {
		/return
	}
	/if (${Group.AnyoneMissing}==TRUE) {
		/echo groupmember gone awol need to wait for it
		/delay 1s
		/return
	}
	/if (${Task[0].Step.Instruction.Find[Speak with Bjerg Sen the Tranquil]}==1 && ${Me.XTarget}==0) {
		/bcga //chase on
		/echo doing ${Task[0].Step.Instruction}
		/call WaitForNavToFinish 712 -1138 -836
		/if (${Macro.Return}==1) {
			/tar id ${Spawn[npc Bjerg].ID}
			/echo now hail Bjerg
			/keypress h
			/say Plane of Knowledge
		}
	} else /if (${Task[0].Step.Instruction.Find[(Optional) Receive]}==1 && ${Me.XTarget}==0) {
		/echo doing ${Task[0].Step.Instruction}
		/call WaitForNavToFinish 808 -1121 -817
		/if (${Macro.Return}==1) {
			/tar id ${Spawn[npc Varlman].ID}
			/echo now hail Varlman
			/keypress h
			/say receive
		}
	} else /if (${Task[0].Step.Instruction.Find[(Optional) Prevent]}==1 && ${Me.XTarget}==0) {
		/if (${Task[0].Objective[5].Instruction.Find[? ? ?]}==1) {
			/echo doing ${Task[0].Objective[4].Instruction}
			/call WaitForNavToFinish 711 -1310 -876
			/if (${Macro.Return}==1) {
				/face heading 90
				/bcga //camphere on
				/delay 2s
				/halfmoon 10
				/delay 2s
				/call BlowHorn
			}
		} else /if (${Task[0].Objective[5].Status.Equal[Done]}) {
			/if (${Task[0].Objective[6].Status.NotEqual[Done]}) {
				/echo doing ${Task[0].Objective[6].Instruction}
				/call BlowHorn
			}
		}
		/if (${Task[0].Objective[7].Status.Equal[Done]}) {
			/if (${Task[0].Objective[8].Status.NotEqual[Done]}) {
				/echo doing ${Task[0].Objective[8].Instruction}
				/call BlowHorn
			}
		}
		/if (${Task[0].Objective[9].Status.Equal[Done]}) {
			/if (${Task[0].Objective[10].Status.NotEqual[Done]}) {
				/echo doing ${Task[0].Objective[10].Instruction}
				/call BlowHorn
			}
		}
		/if (${Task[0].Objective[11].Status.Equal[Done]}) {
			/if (${Task[0].Objective[12].Status.NotEqual[Done]}) {
				/echo doing ${Task[0].Objective[12].Instruction}
				/call BlowHorn
			}
		}
	} else /if (${Task[0].Step.Instruction.Find[(Optional) Speak]}==1 && ${Me.XTarget}==0) {
		/tar npc varlman
		/delay 1s
		/nav id ${Target.ID}
		/delay 2s ${Navigation.Active}==TRUE
		/delay 20s ${Navigation.Active}==FALSE
		/keypress h
		/delay 1s
	} else /if (${Task[0].Objective[15].Status.Equal[Done]}) {
		/if (${SpawnCount[a tranquil]}==1) {
			/bcg //mqp on
			/delay 2s
			/tar a tranquil
			/delay 1s
			/nav target
			/delay 2s ${Navigation.Active}==TRUE
			/delay 20s ${Navigation.Active}==FALSE
			/beep
			/echo u are in front of the chest now, type /open to open it and give the horn to whoever...
			/mqp on
		}
	}
	/if (${Me.XTarget} && !${Me.Combat}) {
		/echo not in combat need to be...
		/call GetClosestXTargetMob
		/if (${Macro.Return}!=0) {
			/tar id ${Macro.Return}
			/delay 1s ${Target.ID}==${Macro.Return}
			/nav target
			/delay 2s ${Navigation.Active}==TRUE
			/delay 20s ${Navigation.Active}==FALSE
			/attack on
		}
	}
/return

Sub GetClosestXTargetMob
	/declare olddist int local 100000
	/declare lastid int local 0
	/declare i int local
	/for i 1 to 13
            /if (${Me.XTarget[${i}].ID} && ${Me.XTarget[${i}].TargetType.Equal[Auto Hater]} && ${Me.XTarget[${i}].Type.Equal[NPC]} && ${Me.XTarget[${i}].Distance3D} < ${olddist}) {
                /varset olddist ${Me.XTarget[${i}].Distance3D}
		/varset lastid ${Me.XTarget[${i}].ID}
            }
       /next i
/return ${lastid}

Sub BlowHorn
	/nav locyxz 683 -1182 -850
	/delay 2s ${Navigation.Active}==TRUE
	/delay 20s ${Navigation.Active}==FALSE
	/doortarget
	/delay 1s
	/click left door
	/delay 1s
/return
Sub Custom
	/if (${Zone.ShortName.Equal[qey2hh1_mission]}) {
		/call DoCleet
	} else /if (${Zone.ShortName.Equal[potranquility_errand]}) {
		/call DoHorn
	}
/return

Sub DoTheTrade
	/if (${Window[TradeWnd].Open} && !${Window[TradeWnd].MyTradeReady}) {
		/notify TradeWnd TRDW_Trade_Button leftmouseup
		/delay 2s ${Window[TradeWnd].MyTradeReady}==TRUE
		/echo waiting for ${Target} to click trade
		/delay 120s ${Window[TradeWnd].Open}==FALSE
		/if (!${Window[TradeWnd].Open}) {
			/echo he clicked trade...
		} else {
			/echo crap he is not clicking trade
			/end
		}
	}
/return
Sub CountTradeSlots
	/declare m int local
	/declare numslots int local 0
	/for m 0 to 7
		/if (${Window[TradeWnd].Child[TRDW_TradeSlot${m}].Tooltip.Length}) {
			/varcalc numslots ${numslots} + 1
		}
	/next m
/return ${numslots}

Sub TradeSafeTarget(int targid)
	/echo [TradeSafeTarget] im supposed to locate ${targid} now
	/declare thetargetid int local
	/varset thetargetid ${targid}
:saferetarget
	/if (${Target.ID} && ${Target.ID}==${thetargetid}) /return
	/if (${thetargetid}) {
		/if (${Spawn[${thetargetid}].Distance}<200) {
			/echo Targeting ${Spawn[${thetargetid}]}
			/target id ${thetargetid}
			/delay 1s ${Target.ID}==${thetargetid}
		}
	}
	/if (!${Target.ID}) {
		/echo [SafeTarget] couldnt find a target, retrying
		/delay 1s
		/goto :saferetarget
	}
/return

Sub ClericInGroup
	/declare gn int local 0
	/for gn 1 to 5
		/if (${Group.Member[${gn}].Class.Name.Equal[Cleric]}==TRUE) {
			/return ${gn}
		}
	/next gn
/return 0

| ----------------------------------------------------------------------------
| SUB: ShakeLoose Section - gets unstuck
| ----------------------------------------------------------------------------
Sub Bind_ShakeLoose
	/nav stop
	/varset ReturnToCamp 0
        /varset ChaseAssist 0
	/stick off
	/play stop
	/keypress back hold
	/delay 2s
	/keypress back up
	/tar id ${Group.Leader.ID}
	/face fast away
	/keypress forward hold
	/delay 2s
	/keypress forward up
/return
