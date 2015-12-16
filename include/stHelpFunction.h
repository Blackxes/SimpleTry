/*******************************************************************************************************************************
	Nutzen/Aufgabe:
	Funktion der Datei - Was macht sie

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/

//
#pragma once
//

//_______________________________________________________________________________________________________________
// header
/* ... */

//_______________________________________________________________________________________________________________
// Makros/Defines
/* ... */

//_______________________________________________________________________________________________________________
// globale Variablen/Externe Deklarationen
/* ... */

//_______________________________________________________________________________________________________________
// Vorwaertsdeklarationen
/* ... */

//_______________________________________________________________________________________________________________
// Strukturen/enums/etc.
/* ... */

//_______________________________________________________________________________________________________________
// Funktionen
//

//--------------------------------------------
// Teilt den String in einzelstrings auf die durch cSeperator getrennt werden
// und speichert sie in eine Liste
template <class T>
std::list<T>		stExplodeList(std::string sString, char cSeperator = ',');
std::list<float>		stExplodeList(std::string sString, char cSeperator = ',');
std::list<std::string>	stExplodeListString(std::string sString, char cSeperator = ',');

//--------------------------------------------
// Feugt die Listenelemente aneinander und erzeugt einen string
// der durch den Parameter cSeperator von den einzenen Elementen getrennt wird
std::string			stImplodeList(std::list<float> liList, char cGlue = ',', bool removeLast = false);
std::string			stImplodeListString(std::list<std::string> liList, char cGlue = ',', bool removeLast = false);

//--------------------------------------------
//
/* ... */

//_______________________________________________________________________________________________________________
//
