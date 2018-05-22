
Sub Main
:MainLoop
/doevents
/goto :MainLoop
/return


Sub PortUs(Line)
/declare PortSpell string local
    /if (${Me.Class.ShortName.Equal[DRU]}) {
        /if (${Line.Equal[karana]} || ${Line.Equal[nkarana]}) /varset PortSpell Circle of Karana
        /if (${Line.Equal[lavastorm]}) /varset PortSpell Circle of Lavastorm
        /if (${Line.Equal[ro]} || ${Line.Equal[sro]}) /varset PortSpell Circle of Ro
        /if (${Line.Equal[misty]}) /varset PortSpell Circle of Misty
        /if (${Line.Equal[feerrott]}) /varset PortSpell Circle of Feerrott
        /if (${Line.Equal[commons]}) /varset PortSpell Circle of Commons
        /if (${Line.Equal[east]} || ${Line.Equal[ekarana]}) /varset PortSpell Succor: East
        /if (${Line.Equal[surefall]}) /varset PortSpell Circle of Surefall Glade
        /if (${Line.Equal[butcher]}) /varset PortSpell Circle of Butcher
        /if (${Line.Equal[steamfont]}) /varset PortSpell Circle of Steamfont
        /if (${Line.Equal[skyfire]}) /varset PortSpell Wind of the North
        /if (${Line.Equal[ej]} || ${Line.Equal[emerald]}) /varset PortSpell Wind of the South
        /if (${Line.Equal[dawnshroud]}) /varset PortSpell Circle of Dawnshroud
        /if (${Line.Equal[twilight]}) /varset PortSpell Circle of Twilight
        /if (${Line.Equal[grimling]}) /varset PortSpell Circle of Grimling
        /if (${Line.Equal[nexus]}) /varset PortSpell Circle of the Nexus
        /if (${Line.Equal[stonebrunt]}) /varset PortSpell Circle of Stonebrunt
        /if (${Line.Equal[tox]}) /varset PortSpell Circle of Toxxulia
        /if (${Line.Equal[barindu]}) /varset PortSpell Circle of Barindu
        /if (${Line.Equal[natimbi]}) /varset PortSpell Circle of Natimbi
        /if (${Line.Equal[pok]} || ${Line.Equal[knowledge]}) /varset PortSpell Circle of Knowledge
        /if (${Line.Equal[cobalt]}) /varset PortSpell Circle of Cobalt Scar
        /if (${Line.Equal[wakening]}) /varset PortSpell Circle of Wakening Lands
        /if (${Line.Equal[greatdivide]} || ${Line.Equal[gd]}) /varset PortSpell Circle of Great Divide
        /if (${Line.Equal[iceclad]}) /varset PortSpell Circle of Iceclad
        /if (${Line.Equal[combine]} || ${Line.Equal[dreadlands]}) /varset PortSpell Circle of the Combines
        /if (${Line.Equal[moors]}) /varset PortSpell Circle of Blightfire Moors
        /if (${Line.Equal[undershore]}) /varset PortSpell Circle of Undershore
        /if (${Line.Equal[arcstone]}) /varset PortSpell Circle of Arcstone
        /if (${Line.Equal[buriedsea]} || ${Line.Equal[buried]}) /varset PortSpell Circle of Buried Sea
        /if (${Line.Equal[steppes]}) /varset PortSpell Circle of The Steppes
        /if (${Line.Equal[direwind]}) /varset PortSpell Circle of Direwind
        /if (${Line.Equal[loping]}) /varset PortSpell Circle of Loping Plains
        /if (${Line.Equal[time]}) /varset PortSpell Circle of Plane of Time
        /if (${Line.Equal[brell]}) /varset PortSpell Circle of Brell's Rest
        /if (${Line.Equal[grounds]}) /varset PortSpell Circle of the Grounds
        /if (${Line.Equal[domain]}) /varset PortSpell Circle of the Domain
        /if (${Line.Equal[alra]}) /varset PortSpell Circle of Alra
        /if (${Line.Equal[shards]}) /varset PortSpell Circle of the Landing
    } else /if (${Me.Class.ShortName.Equal[WIZ]}) {
        /if (${Line.Equal[wkarana]}) /varset PortSpell West Portal
        /if (${Line.Equal[nro]}) /varset PortSpell Ro Portal
        /if (${Line.Equal[sro]} || ${Line.Equal[ro]}) /varset PortSpell Evacuate Ro
        /if (${Line.Equal[commons]}) /varset PortSpell Common Portal
        /if (${Line.Equal[nek]}) /varset PortSpell Nek Portal
        /if (${Line.Equal[karana]} || ${Line.Equal[nkarana]}) /varset PortSpell North Portal
        /if (${Line.Equal[gfay]}) /varset PortSpell Fay Portal
        /if (${Line.Equal[ej]} || ${Line.Equal[emerald]}) /varset PortSpell Markar's Relocation
        /if (${Line.Equal[skyfire]}) /varset PortSpell Tishan's Relocation
        /if (${Line.Equal[combine]} || ${Line.Equal[dreadlands]}) /varset PortSpell Combine Portal
        /if (${Line.Equal[dawnshroud]}) /varset PortSpell Dawnshroud Portal
        /if (${Line.Equal[twilight]}) /varset PortSpell Twilight Portal
        /if (${Line.Equal[grimling]}) /varset PortSpell Grimling Portal
        /if (${Line.Equal[nexus]}) /varset PortSpell Nexus Portal
        /if (${Line.Equal[tox]}) /varset PortSpell Tox Portal
        /if (${Line.Equal[barindu]}) /varset PortSpell Barindu Portal
        /if (${Line.Equal[natimbi]}) /varset PortSpell Natimbi Portal
        /if (${Line.Equal[pok]} || ${Line.Equal[knowledge]}) /varset PortSpell Knowledge Portal
        /if (${Line.Equal[cobalt]}) /varset PortSpell Cobalt Scar Portal
        /if (${Line.Equal[wakening]}) /varset PortSpell Wakening Lands Portal
        /if (${Line.Equal[greatdivide]} || ${Line.Equal[gd]}) /varset PortSpell Great Divide Portal
        /if (${Line.Equal[iceclad]}) /varset PortSpell Iceclad Portal
        /if (${Line.Equal[cazic]}) /varset PortSpell Cazic Portal
        /if (${Line.Equal[moors]}) /varset PortSpell Blightfire Moors Portal
        /if (${Line.Equal[undershore]}) /varset PortSpell Undershore Portal
        /if (${Line.Equal[arcstone]}) /varset PortSpell Arcstone Portal
        /if (${Line.Equal[bloodfields]}) /varset PortSpell Bloodfields Portal
        /if (${Line.Equal[sunderock]}) /varset PortSpell Sunderock Springs Portal
        /if (${Line.Equal[slaughter]}) /varset PortSpell Slaughter Portal
        /if (${Line.Equal[katta]}) /varset PortSpell Katta Castrum Portal
        /if (${Line.Equal[icefall]}) /varset PortSpell Icefall Glacier Portal
        /if (${Line.Equal[dragonscale]}) /varset PortSpell Dragonscale Hills Portal
        /if (${Line.Equal[time]}) /varset PortSpell Plane of Time Portal
        /if (${Line.Equal[brell]}) /varset PortSpell Brell's Rest Portal
        /if (${Line.Equal[grounds]}) /varset PortSpell Grounds Portal
        /if (${Line.Equal[sarith]}) /varset PortSpell Sarith Portal
        /if (${Line.Equal[alra]}) /varset PortSpell Alra Portal
        /if (${Line.Equal[shards]}) /varset PortSpell Shard's Landing Portal
    }


    /if (${Me.Book[${PortSpell}]}) {

        /target id ${Me.ID}

        /casting "${PortSpell}" gem1

    } else {

        /if (TRUE) /echo I do not have a port for ${Line}

    }

/return


Sub Event_Chat(ChatType,Sender,ChatText)

/if (${ChatText.Find[portto]} && ${Select[${Me.Class.ShortName},DRU,WIZ]}) /call PortUs ${ChatText.Arg[2]}
