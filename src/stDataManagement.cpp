/*******************************************************************************************************************************
	Nutzen/Aufgabe:
	Funktion der Datei - Was macht sie

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/
//

// header
#include <SimpleTry.h>

stDataManagement* stData = new stDataManagement;

//--------------------------------------------
// Konstruktor
stDataManagement::stDataManagement()
{
	// Definitionen
	//m_liFilecontent				= std::list<strFilecontent>();
	m_iMaxLoadedFiles			= 0;

	m_iCharackterPerLine		= 40;
	m_iSpaceAfterEqual			= 2;

	// States
	m_LastErrorState			= eErrorState::ESt_NONE;
	m_StreamState				= eStreamState::SSt_CLOSED;
	m_bIsListEmtpy				= true;

} // Konstruktor
//

//--------------------------------------------
// Destruktor
stDataManagement::~stDataManagement()
{
	/* ... */

} // Destruktor
//

//_______________________________________________________________________________________________________________
// Initialisierung
stState stDataManagement::Init()
{
	// ueberpruefen ob die Datei gefunden werden kann
	if (!checkExistence(g_PathToDefault.c_str()))
		return ST_FAIL;
	else
	{
		// Werte laden
		//

		// 
		/*
			std::string tempContainer = "";

			if (loadSingleData(tempContainer, "MaxLoadedFiles", g_PathToDefault) == ST_OK)
			{
				std::stringstream MaxLoadedFiles;
				MaxLoadedFiles << tempContainer;
				MaxLoadedFiles >> m_iMaxLoadedFiles;
			}
		
			if (loadSingleData(tempContainer, "MaxLoadedFiles", g_PathToDefault) == ST_OK)
			{
				std::stringstream MaxLoadedFiles;
				MaxLoadedFiles << tempContainer;
				MaxLoadedFiles >> m_iMaxLoadedFiles;
			}
			m_iMaxLoadedFiles		= 
			m_iSpaceAfterEqual		= (loadSingleData(tempContainer, "MaxLoadedFiles", g_PathToDefault) == ST_OK) ? tempContainer : 0;
		*/
	}


	//-----------
	return ST_OK;

} // Init
//

//_______________________________________________________________________________________________________________
// ueberpreuft die Existenz einer moeglich bereits vorhandenen Logfile
bool stDataManagement::checkExistence(const std::string sFile)
{
	//
	const char* cFile = sFile.c_str();
	struct stat MyStat;

	// gibt false zurueck wenn die Datei nicht exitiert
	return ( stat(cFile, &MyStat) == 0 );

} // Exist
//

//_______________________________________________________________________________________________________________
// sucht den Dateinamen aus einem String
std::string stDataManagement::getRelFilename(std::string sString)
{
	//
	if (sString.empty())
		return "";

	// Pfad aufteilen - vorletzter Eintrag ist immer der vollstaendige Dateiname
	std::list<std::string> liStrparts = stExplodeListString(sString, '/');
	std::list<std::string>::iterator itorStrParts = --liStrparts.end();

	//
	if (itorStrParts->empty())
		return "";

	//---------
	return *itorStrParts;

}// getRelFilename
//

//_______________________________________________________________________________________________________________
// sucht den eigentlichen Dateinamen aus einem String
std::string	stDataManagement::getAbsFilename(std::string sString)
{
	//
	if (sString.empty())
		return "";

	// relativen Namen ziehen
	std::string sRelname = getRelFilename(sString);
	if (sRelname.empty())
		return "";

	// Endung entfernen
	std::list<std::string> liFilenameParts = stExplodeListString(sRelname, '.');
	liFilenameParts.pop_back();
	if (liFilenameParts.empty())
		return "";

	//-----------------------------------------------------
	return stImplodeListString(liFilenameParts, '.', true);

} // getAbsFilename
//

//_______________________________________________________________________________________________________________
// sucht sich die Endung/Datentyp aus einem Dateinamen aus und gibt diese zurueck
std::string stDataManagement::getFiletype(std::string sString, bool addDot)
{
	//
	if (sString.empty())
		return "";

	// aufteilen
	std::list<std::string> liStrparts = stExplodeListString(sString, '.');
	if (liStrparts.empty())
		return "";

	// vorletzter Eintrag ist immer die Endung
	std::list<std::string>::iterator itorStrparts = --(liStrparts.end());
	if (itorStrparts->empty())
		return "";

	// dot hinzufuegen
	if (addDot)
		itorStrparts->insert(0, ".");

	//-------------------
	return *itorStrparts;

} // getFiletype
//

//_______________________________________________________________________________________________________________
// filtert den Dateipfad aus einen Pfad
std::string stDataManagement::getFilepath(std::string sString)
{
	//
	if (sString.empty())
		return "";

	// aufteilen // letzten Eintrag entfernen (relativer Dateiname)
	std::list<std::string> liStrparts = stExplodeListString(sString, '/');
	liStrparts.pop_back();
	if (liStrparts.empty())
		return "";

	//------------------------------------------
	return stImplodeListString(liStrparts, '/');
	
} // getFilepath
//

//_______________________________________________________________________________________________________________
// validiert einen String auf leere
bool stDataManagement::isStringEmpty(std::string	sValue,
									 eErrorState	ErrorIfFailed,
									 std::string	&ErrorContainer,
									 std::string	ErrorContainerString)
{
	// Validieren starten
	if (sValue.empty())
	{
		// Dann Fehlermeldung schreiben
		m_LastErrorState = ErrorIfFailed;

		// Und Container fuellen
		ErrorContainer = ErrorContainerString;

		//-----------
		return true;
	}

	//----------
	return false;

} // isStringEmpty
//

//_______________________________________________________________________________________________________________
//

//
//

//
//

//
//

//
//

//_______________________________________________________________________________________________________________
// Laedt den Inhalt einer Datei in die Klassenliste hinein
/*stState stDataManagement::loadFileInList(std::string				sFile,
										 std::ios_base::openmode	openmode,
										 std::string				sFileKey)
{
	// wenn sFile leer ist kann nichts geladen werden
	//
	// wenn der Schluesse leer ist - machts kein Sinn 
	// den Inhalt einzuspeichern
	// da er nicht identifiziert werden kann
	if ( (sFile.empty()) || (sFileKey.empty()) )
	{
		return ST_CANCEL;
	}

	// ueberpruefen ob die Datei gefunden werden kann
	//

	std::ifstream loadFile (sFile, openmode);

	// wenn nicht dann Fehlermeldung
	if (!loadFile.is_open())
	{
		return ST_NOT_FOUND;
	}

	// andernfalls durchlaufen und einschreiben
	//

	std::string			sDataLine	= "";
	strFilecontent		Content;

	Content.sFileKey				= sFileKey;

	while (std::getline(loadFile, sDataLine))
	{
		// Leerzeilen abfangen
		if (sDataLine.empty())
			Content.liContent.push_back("\n");
		else
			Content.liContent.push_back(sDataLine);
	}


	//-----------
	return ST_OK;

}*/
// loadFileInList
//



//_______________________________________________________________________________________________________________
// Einen einzelnen Wert aus einer Datei auslesen
stState stDataManagement::loadSingleData(std::string				&container,
										 std::string				sKey,
										 std::string				sFile)
{
	// sKey validieren
	if (isStringEmpty(sKey, eErrorState::ESt_KEY_EMPTY))
	{
		// wenn leer dann Abbrechen
		return ST_CANCEL;
	}

	// sFile validieren
	if (isStringEmpty(sFile, eErrorState::ESt_FILE_EMPTY))
	{
		// wenn leer dann abbrechen
		return ST_CANCEL;
	}

	// Datei versuchen zu oeffnen
	//

	std::ifstream read(sFile, std::ios::in);

	// ueberpruefen obs passt
	if (!read.is_open())
	{
		m_LastErrorState = eErrorState::ESt_SEARCH_NO_STREAM;
		return ST_CANCEL;
	}

	// Wenn alles gut bisscher lief nach dem Schluesselwort suchen
	//

	// container fuer die aktuell gelesene Zeile
	std::string		sCurrLine		= "";

	// suche Starten ...
	while (getline(read, sCurrLine))
	{
		// Variablen
		//

		// Position des Schluesselwortes
		int iPosOfKey = sCurrLine.find(sKey);

		// wenn das Schluesselwort gefunden wurde
		if (iPosOfKey != std::string::npos)
		{
			// Nach "=" suchen
			int iPosOfEqual = sCurrLine.find("=");

			// wenn kein Gleichheitszeichen vorhanden ist - Fehlermeldung
			if (iPosOfEqual == std::string::npos)
			{
				m_LastErrorState = eErrorState::ESt_SEARCH_NO_EQUAL;
				return ST_CANCEL;
			}

			// Startposition des Wertes
			int iStartPosValue = iPosOfEqual + m_iSpaceAfterEqual;

			// Laenge des Wertes
			int iLengthOfValue = sCurrLine.length() - (iStartPosValue);

			// Wert ausschneiden
			std::string tempValue = sCurrLine.substr(iStartPosValue, iLengthOfValue);

			// ansonten als String zurueckgeben
			container = tempValue;

			//-----------
			return ST_OK;
		}
	}

	//------------------
	m_LastErrorState = eErrorState::ESt_SEARCH_NOT_FOUND;
	return ST_NOT_FOUND;

} // loadSingleData
//

//_______________________________________________________________________________________________________________





/*

stDataManagement data;

//
data.openStream("file", std::ios::out);
data.setCloseAfterUsePerm(false);

data.saveDataInList("false", "spieler_sichtbar");
data.saveDataInList("false", "spieler_sichtbar");
data.saveDataInList("false", "spieler_sichtbar");
data.saveDataInList("false", "spieler_sichtbar");
data.openStream("sdlf", std::ios::in);
data.saveDataInList("false", "spieler_sichtbar");
data.saveDataInList("false", "spieler_sichtbar");

data.setCloseAfterUsePerm(true);



//
data.setCloseAfterUsePerm(false);

data.saveSingleData("false", "spieler_sichtbar", "file", std::ios::in);
data.saveSingleData("false", "spieler_sichtbar");
data.saveSingleData("false", "spieler_sichtbar");
data.saveSingleData("false", "spieler_sichtbar");
data.saveSingleData("false", "spieler_sichtbar");
data.saveSingleData("false", "spieler_sichtbar");

data.setCloseAfterUsePerm(true);

*/