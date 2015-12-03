/*******************************************************************************************************************************
	Nutzen:
	Deklaration aller Funktionen und Variablen
	Einbindung der header der Engine

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/

//
#pragma once
//

// dll export/import definieren - Irrelevant in der Anwendung
/*
#ifndef SIMPLETRY_EXPORTS
	#define SIMEPLTRY_API __declspec(dllexport)
#else
	#define SIMEPLTRY_API __declspec(dllimport)
#endif
*/

// Meldungen ausblenden
/* ... */

//_______________________________________________________________________________________________________________
// sfml einbinden
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//_______________________________________________________________________________________________________________
// standard header einbinden
#include <stdarg.h>
#include <iostream>
#include <typeinfo>
#include <time.h>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <sys/stat.h>

//_______________________________________________________________________________________________________________
// Allgemeine Definitionen und Makros
#define SAFE_DELETE(x)		if ((x) != NULL) delete (x); (x) = NULL;

#define MAX(a,b)			if (a < b) ? b : a
#define MIN(a,b)			if (a < b) ? a : b
#define PI					3.1415926535897932384626433832795

// Logfileeinstellungen
#define ALL_REPORTING		true
#define ERROR_REPORTING		true
#define WARNING_REPORTING	true
#define INFO_REPORTING		true

// Vereinfachungen
#define and &&
#define or ||

// unsigned Datentypen
typedef bool			BOOL;
typedef unsigned int	UINT;
typedef unsigned short	USHORT;
typedef unsigned char	UCHAR;


//_______________________________________________________________________________________________________________
// Status
enum stState
{
	ST_NONE,			// Kein Status
	ST_OK,				// Alles Ok
	ST_FAIL,			// Fehler
	ST_NOT_FOUND,		// Nicht gefunden
	ST_INCORRECT,		// Ergebnis nicht vollstaendig oder fehlerhaft
	ST_CANCEL			// Abbgebrochen

}; // Status
//

//_______________________________________________________________________________________________________________
// Dateistatus
enum stDatastate
{
	DS_NONE,			// Kein Status
	DS_OK,				// Ok
	DS_DAMAGED,			// Beschaedigt
	DS_FAULTY,			// Datei entspricht nicht dem gewuenschten Stand/Status/Bezeichnung falsch sein/etc.
	DS_NOT_FOUND,		// Nicht gefunden
	DS_COUNTER,
};

//_______________________________________________________________________________________________________________
// Dateiinformationssammlung
struct stFileinfo
{
	std::string			sFilerel;		// Vollstaendiger Dateiname
	std::string			sFileabs;		// Eigentlicher Dateiname
	std::string			sDatatype;		// Datentyp
	std::string			sPath;			// Pfad
	stDatastate			sState;			// Status
};

//_______________________________________________________________________________________________________________
// Methoden
stState stInit();													// Engine initialisieren
stState stExit();													// Engine herunterfahren


//_______________________________________________________________________________________________________________
// Variablen/Inztanzen
/* ... */

//_______________________________________________________________________________________________________________
// vordefinierte Pfade und Dateinamen

// Pfad zu den ressourcen
const std::string			g_PathToRes					= "res/";
const std::string			g_PathToData				= g_PathToRes + "data/";

// logfiledateien
const std::string			g_PathToCSS					= g_PathToRes + "css/";
const std::string			g_PathToJS					= g_PathToRes + "js/";
const std::string			g_PathToFont				= g_PathToRes + "font/";
const std::string			g_PathToImg					= g_PathToRes + "img/";

// Dateien
const std::string			g_PathToDefault				= g_PathToData + "def.st";
const std::string			g_PathToBasicCSS			= g_PathToCSS + "basic.css";
const std::string			g_PathToBasicJS				= g_PathToJS + "basic.js";
const std::string			g_PathToBasicFont			= g_PathToFont + "BRLNSR.ttf";
const std::string			g_PathToJQuery				= g_PathToJS + "jquery.js";

//_______________________________________________________________________________________________________________
// ; einbinden
#include "stLog.h"
#include "stVector2Df.h"
#include "stVector2Db.h"
#include "stTime.h"
#include "stAniTex.h"
#include "stAniLabel.h"
#include "stDetail.h"
#include "stDataManagement.h"
#include "stButton.h"

#include "stHelpFunction.h"
//

//_______________________________________________________________________________________________________________
//