| -------------------------------------------------------------------------------------
| SUB: VarStuff this will stop casting and do the most important stuff
| -------------------------------------------------------------------------------------    
	Sub VarStuff
		/if (${Me.Hovering}) /return
		/declare i int local

		/for i 1 to ${Var.Size}
			/if (${If[${VarCond[${i}]},1,0]} && V) {
				
				/call CastWhat "${Var[${i}].Arg[1,|]}" ${Var[${i}].Arg[2,|]} "Newsub" 1
				/break
			}
		/next i
	/return
  
  
| ----------------------------------------------------------------------------
| SUB: Load Ini
| ----------------------------------------------------------------------------
    Sub LoadIni(string sectionName, string varName, string varType, string varValue, string varArray, string varArray2, string FileName, string FileName2)
        /if (${Debug}) {
            /delay 2
            /echo \atDEBUG Sub Loadini S:${sectionName} V1:${varName} V2:${varType} V3:${varValue} V4:${varArray} V5:${varArray2} V6:${FileName} V7:${FileName2} \agLine#: ${Macro.CurLine}
        }
        /declare rkTemp                 string      local 
        /declare UtilInt                int         local        0 
        /declare FileName1              string      local        ${FileName}
        | Assign ini name to default ini if not defined
        /if (${FileName1.Length}==0  || ${FileName1.Equal[NULL]}) {
            /varset FileName1 ${IniFileName}
        }
        | Check if ini value is asking for an array ie buff1 to buff20
        
        /if (${Bool[${varArray}]}) {
            /if (${${varArray}.Size}>0) {
                /declare i int local
                /for i 1 to ${${varArray}.Size}
                    /if (!${Ini[${FileName1},${sectionName},${varArray}${i}].Length}) /ini "${FileName1}" "${sectionName}" "${varArray}${i}" "${varValue}"
                    /if (${Ini[${FileName1},${sectionName},${varArray}${i}].Length}) /varset ${varArray}[${i}] ${Ini[${FileName1},${sectionName},${varArray}${i}]}
                    /if (${Debug}) /echo \atDEBUG ${ConditionsOn} ${Int[${varArray2.Length}]} ${varArray2.Length} ${Bool[${varArray2.NotEqual[null]}]} ${varArray2}
                    /if (${Defined[ConditionsOn]}) {
                        /if (${ConditionsOn} && ${Int[${varArray2.Length}]}>0 && ${varArray2.NotEqual[null]}) {
                            | Check to see if the conditions file is a different file and update spell info.
                            /if (${FileName2.NotEqual[${FileName1}]}) /ini "${FileName2}" "${sectionName}" "${varName}${i}" "${${varArray}[${i}]}"
                            /if (!${Ini[${FileName2},${sectionName},${varArray2}${i}].Length}) {
                                /if (${${varArray}[${i}].NotEqual[null]}) {
                                    /ini "${FileName2}" "${sectionName}" "${varArray2}${i}" "TRUE"
                                } else {
                                    /ini "${FileName2}" "${sectionName}" "${varArray2}${i}" "FALSE"
                                }
                            }
                            /varset ${varArray2}[${i}]  ${Ini[${FileName2},${sectionName},${varArray2}${i},TRUE,noparse]}
                        } else /if (${Int[${varArray2.Length}]}>0 && ${varArray2.NotEqual[null]}) {
                            /varset ${varArray2}[${i}] TRUE
                        } 
                    } else {
                        /varset ${varArray2}[${i}] TRUE
                    }
                    /if (${${varArray}[${i}].NotEqual[null]}) {
                        | find out if there is a Rank and fix spell name.
                        /if (${varType.Equal[string]} && ${Int[${${varArray}[${i}].Left[1]}]}==0) {
                                /call SpellRankCheck "${${varArray}[${i}]}"
                            /varset ${varArray}[${i}] ${Macro.Return}
                        }
                        | code to fix the Heal PCT for those zones that knock your HPs down to 
                        /if (${sectionName.Equal[Heals]} && ${Select[${Zone.ID},795,796]}) {
                            /if (${Int[${${varArray}[${i}].Arg[2,|].Left[1]}]}>0) {
                                /varset UtilInt ${Int[${${varArray}[${i}].Arg[2,|]}]}
                                /varcalc UtilInt 70*(${UtilInt}/100)
                                /varset ${varArray}[${i}] ${${varArray}[${i}].Replace[|${${varArray}[${i}].Arg[2,|]},|${UtilInt}]}
                            }
                        } else /if (${sectionName.Equal[DPS]} && ${Int[${${varArray}[${i}].Arg[2,|].Left[1]}]}>0 && ${${varArray}[${i}].Arg[3,|].Equal[debuffall]}) {
                            /varcalc UtilInt ${Int[${${varArray}[${i}].Arg[2,|]}]}+100
                            /varset ${varArray}[${i}] ${${varArray}[${i}].Replace[|${${varArray}[${i}].Arg[2,|]},|${UtilInt}]}
                        }
                    }
                    /if (${Debug}) /echo  \atDEBUG Loadini ${i} - ${varArray}[${i}] - ${${varArray}[${i}]} - ${Macro.Return} - ${Me.AltAbility[${Macro.Return}]} \agLine#: ${Macro.CurLine}
                /next i
                /return
            }
        } else {
            /if (!${Defined[${varName}]} && ${Defined[varType]}) /declare ${varName} ${varType} outer 0
            |Using the varArray2 to tell if trying to find a conditional entry or not. False = conditional null = non-conditional
            /if (${varArray2.Length}==0 || ${varArray2.Equal[false]} || ${varArray2.Equal[NULL]}) {
                /if (!${Ini[${FileName1},${sectionName},${varName}].Length}) {
                    /if (${varValue.Length}) {
                        /ini "${FileName1}" "${sectionName}" "${varName}" "${varValue}"
                        /varset ${varName} ${varValue}
                        /if (${Debug}) /echo \atDEBUG Sub Loadini /varset ${varName} ${varValue} \agLine#: ${Macro.CurLine}
                    }
                } else {
                    /varset ${varName} ${Ini[${FileName1},${sectionName},${varName}]}
                }
                /if (${FileName1.Equal[${IniFileName}]}) {
                    /varset rkTemp ${${varName}}
                    | find out if there is a Rank and fix spell name.
                    /if (${varType.Equal[string]} && ${Int[${rkTemp.Left[1]}]}==0 && !${varName.Find[Help]}) {
                        /call SpellRankCheck "${${varName}}"
                        /if (${Macro.Return.NotEqual[null]}) /varset ${varName} ${Macro.Return}
                    }
                }
            } else /if (${Defined[ConditionsOn]}) {
                /if (${ConditionsOn}) {
                    /if (!${Ini[${FileName1},${sectionName},${varName}].Length}) {
                        /if (${varValue.Length}) {
                            /ini "${FileName1}" "${sectionName}" "${varName}" "${varValue}"
                            /varset ${varName} ${varValue}
                            /if (${Debug}) /echo \atDEBUG Sub Loadini /varset ${varName} ${varValue} \agLine#: ${Macro.CurLine}
                        }
                    } else {
                        /varset ${varName} ${Ini[${FileName1},${sectionName},${varName}]}
                    }
                } else {
                    /varset ${varName} ${varValue}
                }
            } else {
                /varset ${varName} ${varValue}
            }
            /if (${Debug}) /echo \atDEBUG Sub LoadIni: ${varName} - ${${varName}} \agLine#: ${Macro.CurLine}
            /varset rkTemp 
        }
        /if (${Debug}) /echo \atDEBUG Sub LoadIni: Leave \agLine#: ${Macro.CurLine}
    /return
   
   | -------------------------------------------------------------------------------------
| SUB: SpellRankCheck
| ------------------------------------ -------------------------------------------------           
    Sub SpellRankCheck(Rk_Check_What)
        /declare DebugRk                int         local 0
        /declare rkCheck                string      local null
        /declare rkCheck1               string      local 
        /declare rkdCheck               string      local
        /declare rkTemp                 string      ${Rk_Check_What.Arg[1,|]}
        /declare rkdTemp                string      ${Rk_Check_What.Arg[3,|]}
        |/varset DebugRk 1
        /if (${DebugRk}) /echo \atDEBUG SpellRankChecks: Enter \agLine#: ${Macro.CurLine}
        /if (${Rk_Check_What.Left[1].Equal[0]} || ${Int[${Rk_Check_What.Left[1]}]}>0) /return ${Rk_Check_What}
        | Check for Rk. in spell name and Remove it.   
        /if (${rkTemp.Find[ Rk.]}) {
            /varset rkTemp ${rkTemp.Left[${Math.Calc[${rkTemp.Find[ Rk.]}-1]}]} 
        }
        /if (${Int[${Me.Book[${rkTemp}]}]}==0 && ${Int[${Me.Book[${Spell[${rkTemp}].RankName}]}]}==0 && ${Int[${Me.AltAbility[${rkTemp}]}]}==0 && ${Int[${Me.AltAbility[${rkTemp}].Spell.ID}]}==0 && ${Int[${Me.CombatAbility[${Spell[${rkTemp}].RankName}]}]}==0) /return ${Rk_Check_What}
        /if (${DebugRk}) /echo \atDEBUG SpellRankChecks: 1 rkCheck: "${rkCheck}" rkTemp: "${rkTemp}" rkdCheck: "${rkdCheck}" rkdTemp: "${rkdTemp}"  \agLine#: ${Macro.CurLine}
        | If this is NOT an Alt Ability then it must be a spell.
        /if (${Int[${Me.AltAbility[${rkTemp}].ID}]}!=0 || ${Int[${Me.AltAbility[${rkTemp}].Spell.ID}]}!=0) {
           /if (${DebugRk}) /echo 1a. well we think ${rkTemp} is an AA
           /varset rkCheck ${rkTemp}
        } else {
           /if (${DebugRk}) /echo 1c. well ${rkTemp} is not an AA or CombatAbility
           /varset rkCheck ${Spell[${rkTemp}].RankName}
        }
        | check for null
        /if (${DebugRk}) /echo \atDEBUG SpellRankChecks: 2 rkCheck: ${rkCheck} rkTemp: ${rkTemp} Rk_Check_What: ${Rk_Check_What} \agLine#: ${Macro.CurLine}
        | must NOT be null so lets fix Rk_Check_What.
        /if (${rkCheck.NotEqual[${rkTemp}]}) {
            /if (${Rk_Check_What.Find[|]}>0) {
                /varset rkCheck1 ${rkCheck}${Rk_Check_What.Right[-${Math.Calc[${Rk_Check_What.Find[|]}-1]}]} 
                /varset rkCheck ${rkCheck1}
            }
        } else {
            /varset rkCheck ${Rk_Check_What}
        }
        /if (${Rk_Check_What.Arg[2,|].Equal[dual]}) {
           /if (${rkdTemp.Find[ Rk.]}) {
               /varset rkdTemp ${rkdTemp.Left[${Math.Calc[${rkdTemp.Find[ Rk.]}-1]}]} 
           }
           /if (${Int[${Me.AltAbility[${rkdTemp}].ID}]}!=0 || ${Int[${Me.AltAbility[${rkTemp}].Spell.ID}]}!=0) {
               /varset rkdCheck ${Spell[${rkdTemp}].RankName}
           } else {
               /if (${Me.Subscription.NotEqual[gold]}) {
                   /varset rkdCheck ${rkdTemp}
               } else {
                   /varset rkdCheck ${Spell[${rkdTemp}].RankName}
               }
           }
           /if (${DebugRk}) /echo \atDEBUG SpellRankChecks: 3 rkdCheck: ${rkdCheck} rkdTemp: ${rkdTemp} Rk_Check_What: ${Rk_Check_What} \agLine#: ${Macro.CurLine}
           /varset rkCheck ${rkCheck.Arg[1,|]}|dual|${rkdCheck}
        }
        /if (${DebugRk}) /echo \atDEBUG SpellRankChecks: 4 Rk_Check_What: ${Rk_Check_What} rkCheck: ${rkCheck} rkTemp: ${rkTemp}  \agLine#: ${Macro.CurLine}
        /if (${DebugRk}) /echo \atDEBUG SpellRankChecks: leave \agLine#: ${Macro.CurLine}
        |/varset DebugRk 0
    /return ${rkCheck}
