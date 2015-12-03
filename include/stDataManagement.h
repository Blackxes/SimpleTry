/*******************************************************************************************************************************
	Nutzen/Aufgabe:
	Laden und Speichern von Werten in Dateien

	Die Datei "def.st" bitte nicht aendern oder deren Ort aendern ohne das SimpleTry sie finden kann

	DIESE KLASSE IST NICHT KOPIERBAR! - Kopierkonstruktor ist bewusst leer gelassen worden!

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
//

//--------------------------------------------
// Struktur einer Datei die geladen wurde
struct strFilecontent
{
	// Schluessel der Datei - aequivalent zu einer ID
	std::string					sFileKey;

	// Liste des Content der Datei
	std::list<std::string>		liContent;

}; // strFileContent
//

//--------------------------------------------
// streamstatums
enum eStreamState
{
	SSt_OPEN,			// wenn stream offen ist und Werte geladen oder eingespeichert werden koennen
	SSt_CLOSED,			// wenn der stream geschlossen ist
	SSt_ERROR,			// wenn die def.ts Datei nicht gefunden wurde
	SSt_COUNTER,		// Elementzaehler

}; // eFileState
//

//--------------------------------------------
// Errorstatus -	Falls es einen Fehler gibt
//					ist der so einfacher zu uebepruefen
enum eErrorState
{
	ESt_NONE,						// Kein Fehler
	ESt_STREAM_FAILED_OPENING,		// Fehler beim Oeffnen des Streams
	ESt_STREAM_FAILED_CLOSING,		// Fehler beim Schliessen des Streams
	ESt_FILE_EMPTY,					// Dateiname ist leer
	ESt_FILE_NO_DOT,				// Dateiname besitzt keinen Typtrenner
									// Eine Datei ohne . hat kein Datentyp
	ESt_KEY_EMPTY,					// Schluesselwort ist leer
									// Es kann nach keinem Wert gesucht werden
									// welcher keine Zugehoerigkeit hat
	ESt_SEARCH_NO_EQUAL,			// Kein gleichheitszeichen gefunden
									// "=" ist erforderlich um zu erkennen
									// wo sich der Wert befindet
	ESt_SEARCH_NO_STREAM,			// Es wurde kein Stream geoeffnet um 
									// in einer Datei etwas zu laden/sichern
	ESt_SEARCH_NOT_FOUND,			// Wenn die Suche durchgelaufen ist
									// Ohne das Schluesselwort gefunden zu haben
	ESt_COUNTER,					// Elementzaehler


}; // eErrorState
//





// Klassendeklarationen und Definitionen
class stDataManagement
{
	// Testklasse erlauben zu testen :D
	friend class testSimpleTry;
	
	//===============================================================================================================
	private:

		//===========================================================================================================
		// Basisvariablen	
		//
	
		// Hat die Contentliste Inhalt?
		bool													m_bIsListEmtpy;


		// Diese Liste representiert den Inhalt einer gestreamten Datei
		// ausgerufen hat.
		//std::list<strFilecontent>								m_liFilecontent;

		// Bestimmt wie viele Dateien maximal geladen werden duerfen
		// 0 = unendlich
		int														m_iMaxLoadedFiles;

		//===========================================================================================================
		// Formatierungsvariablen
		int														m_iCharackterPerLine;		// Wie viele Zeichen pro Zeile bis
																							// zum Gleichheitszeichen - Schluesselname eingeschlossen
		int														m_iSpaceAfterEqual;			// Leerzeichen zwischen dem Gleichheitszeichen und Wert

		//===========================================================================================================
		// Statusvariablen	
	
		eStreamState											m_StreamState;				// Aktueller Streamstatus
		eErrorState												m_LastErrorState;			// letzter Error Status

		//===========================================================================================================
		// Hilfsfunktionen
		//

		// validiert einen String auf leere
		// definiert den Error wenn der String leer ist
		// und fuellt auch den letzten Parameter mit dem Errorreport
		//
		// param1 - erwartet den zu ueberpruefenden String
		// param2 - erwartet den Fehlertyp wenn der String leer ist
		// param3 - erwartet den Container fuer den Errorreport (optional)
		// param4 - erwartet den String der in &ErrorContainer geschrieben wird wenn der String leer ist (optional)
		//
		// return true - wenn der String befuellt ist
		// return false - wenn der String leer ist
		//
		bool													isStringEmpty(std::string	sValue,
																			  eErrorState	ErrorIfFailed,
																			  std::string	&ErrorContainer = std::string(),
																			  std::string	ErrorContainerString = "");


	//===============================================================================================================
	public:

		//===========================================================================================================
		// Initialmethoden - Konstruktor/Kopierkonstruktor/Destruktor - Initfunktion
		//

																stDataManagement();										// Konstruktor
																stDataManagement(const stDataManagement &rhs) {}		// Kopierkonstruktor
																~stDataManagement();									// Destruktor

		// Initialisiert die Klasse mit Werten aus der def.st Datei - wenn sie Vorhanden ist
		stState													Init();

		//===========================================================================================================
		// Verwaltung
		//
		
		// filtert den absoluten Dateinamen auf einem string (Bsp. "cms/fileadmin/style.css" => "style")
		//
		// param1 - sString (std::string) erwartet einen String aus dem der absolute Dateiname gefiltert werden soll
		//
		//
		std::string												getAbsFilename(std::string sString);

		// sucht den vollstaendigen Dateinamen aus einem String
		//
		// param1 - sString (std::string) erwartet einen String aus dem der relative Dateiname gefiltert werden soll
		//
		std::string												getRelFilename(std::string sString);

		// sucht sich die Endung/Datentyp aus einem String (Moeglichst nur den vollstaengien Dateinamen) 
		// aus und gibt diese zurueck
		//
		// param1 - sString (std::string) erwartet einen String unabhaengig ob es ein Pfad oder Dateiname ist
		//
		// return ST_OK - wenn die Suche und das filtern erfolgreich waren
		// return ST_CANCEL - wenn das Filtern oder die Suche nicht erfolgreich war (Grund steht in sType)
		//
		std::string												getFiletype(std::string sString, bool addDot = true);

		// sucht den Dateipfad aus einem Pfad heraus
		//
		// param1 - sString (std::string) erwartet einen String unabhaengig ob es ein Pfad oder Dateiname ist
		//
		// return (givenString) - wenn der Pfad nicht erfolgreich gefunden wurde
		// return string - gefilerter Pfad
		//
		std::string												getFilepath(std::string sString);

		// Laedt den Inhalt einer Datei in die Klassenliste hinein
		//
		// param1 - erwartet die Datei die in die Liste geladen werden soll
		// param2 - erwartet den Oeffnungsmodus mit dem die Datei geoeffnet werden soll
		// param3 - erwartet den Dateischluessel (ID) unter dem die Datei in die Liste gespeichert werden soll
		//			- empfohlenswert ist es den Dateinamen zu verwenden um einfacher an den Inhalt zu kommen
		// 
		// return ST_OK - wenn das laden erfolgreich war
		// return ST_NOT_FOUND - wenn die Datei nicht gefunden wurde
		// return ST_CANCEL - wenn sFile oder sFileKey leer ist
		//
		//stState													loadFileInList(std::string				sFile,
		//																	   std::ios_base::openmode	openmode,
		//																	   std::string				sFileKey);

		// 

		// Speichert die Liste m_liDataLines in die (hoffentlich) gestreamte Datei m_sFile
		//
		// param1 - erwartet den Schluessel (ID) der Datei in der Liste die gespeichert werden soll
		// param2 - erwartet den Oeffnungsmodus in dem die Datei gesichert werden soll (Bsp. std::ios::out)
		//
		// return ST_OK - wenn das einspeichern erfolgreich war
		// return ST_NOT_FOUND - wenn der Dateischluessel nicht gefunden wurde
		//
		//stState													saveFileOutOfList(std::string				sFileKey);


		// speichert einen einzelnen Wert in eine Datei
		// Leerzeilen beim durchsuchen werden abgefangen!
		// Standard Oeffnungsmodus ist std::ios::in
		//
		// param1 - erwartet den Wert der gespeichert werden soll
		// param2 - erwartet das Schluesselwort zu welchem der Wert gehoert
		// param3 - erwartet den Dateinamen
		//			-	wenn keiner angegeben wurde, wird (wenn definiert) der Pfad und Name 
		//				der Datei aus der Klasse verwendet - Ist
		// 
		// return ST_OK - wenn das sichern erfolgreich war
		// return ST_NOT_FOUND - wenn die Datei nicht gefunden wurde
		// return ST_CANCEL -	wenn etwas beim einschreiben schief gelaufen ist oder sFile leer ist
		//						oder wenn value nicht in einen String gewandelt werden konnte
		//						
		//
		template<class T>
		stState													saveSingleData(T						&value,
																			   std::string				sKey,
																			   std::string				sFile);

		// Einspeichern von Daten als komplette Datei
		// Standard Oeffnungsmodus ist std::ios::out
		//
		// param1 - erwartet den value vom Typ T welcher in die Datei
		//			die unter sFile liegt gespeichert werden soll
		// param2 - erwartet den vollstaendigen Dateinamen
		// 
		// return ST_OK - wenn das speichern erfolgreich war
		// return ST_CANCEL - wenn sFile leer ist
		//
		template<class T>
		stState													saveCompleteData(T							&value,
																				 std::string				sFile);

		// Einen einzelnen Wert aus einer Datei auslesen
		// Leerzeilen beim durchsuchen werden abgefangen!
		//
		// param1 - erwartet die Variable in die der Wert gespeichert wird wenn die Suche erfolgreich war
		// param2 - erwartet das schluesselwort vom Wert welches ausgelesen werden soll
		// param3 - erwartet den Namen der Datei in der das Schluessewort und der zugehoerige Werte gefunden werden kann
		//			-	wenn dieser Parameter leer ist und der Stream geschlossen ist wirft die Funktion ST_CANCEL
		//
		// return ST_OK - wenn das auslesen und schreiben erfolgreich war
		// return ST_NOT_FOUND - wenn der gesuchte Key nicht gefunden wurde oder die Datei nicht gefunden wurde
		// return ST_CANCEL -	wenn kein Dateiname angegeben wurde und der Stream 
		//						vorher nicht erfolgreich geoeffnet wurde
		//
		stState													loadSingleData(std::string				&container,
																			   std::string				sKey,
																			   std::string				sFile);

		// Eine komplette Datei auslesen
		//
		// param1 - erwartet den container in den die Datei geschrieben wird
		// param2 - erwartet den vollstaendigen Dateinamen
		//
		// return ST_OK - wenn das auslesen und schreiben erfolgreich war
		// return ST_NOT_FOUND - wenn die Datei nicht gefunden wurde
		// return ST_CANCEL - wenn sFile leer ist
		// return ST_FAIL - wenn das auslesen nicht erfolgreich war
		//
		template<class T>
		stState													loadCompleteData(T						&container,
																				std::string				sFile);

		//===========================================================================================================
		// Manipulationsmethoden
		/* ... */
		
		//===========================================================================================================
		// add/sub/set/get-Funktionen
		//

		// get-Funktionen
		eErrorState												getLastErrorState() { return m_LastErrorState; }

		//===========================================================================================================
		// externe Hilfsfunktionen
		//

		// ueberpruefen ob bereits eine Logfile existiert
		//
		// param1 - erwartet den Dateinamen der ueberprueft werden soll
		//
		// return true - wenn die Datei existiert
		// return false - wenn die Datei nicht existiert
		bool												checkExistence(const std::string sFile);
		

}; // stDataManagement
//

//_______________________________________________________________________________________________________________
// globales Log
extern stDataManagement* stData;

//_______________________________________________________________________________________________________________
//

//
//

//	Template-Definitionen
//

//
//

//_______________________________________________________________________________________________________________
// Einspeichern von Daten als komplette Datei
template<class T>
stState stDataManagement::saveCompleteData(T						&value,
										   std::string				sFile)
{

	// Auf leere ueberpruefen
	if (isStringEmpty(sFile, eErrorState::ESt_FILE_EMPTY))
	{
		// wenn leer dann Abbrechen
		return ST_CANCEL;
	}

	// stream oeffnen
	std::ofstream save(sFile, std::ios::binary);

	// Daten speichern
	save.write( (char*) &value, sizeof (value));

	// schliessen
	save.close();

	//-----------
	return ST_OK;

} // saveCompleteData
//


//_______________________________________________________________________________________________________________
// Eine komplette Datei auslesen
template<class T>
stState stDataManagement::loadCompleteData(T						&container,
										   std::string				sFile)
{
	// Auf leere ueberpruefen
	if (isStringEmpty(sFile, eErrorState::ESt_FILE_EMPTY))
	{
		// wenn leer dann Abbrechen
		return ST_CANCEL;
	}

	// Stream oeffnen ..
	std::ifstream loadData(sFile, std::ios::binary);

	// wenn nicht offen ..
	if (!loadData.is_open())
	{
		// Und Meldung zurueck
		return ST_NOT_FOUND;
	}

	// auslesen
	loadData.read( (char*) &container, sizeof(container));

	// Datei schliessen
	loadData.close();

	//-----------
	return ST_OK;

} // loadSingleData
//

//_______________________________________________________________________________________________________________
// speichert einen einzelnen Wert in eine Datei
template <class T>
stState stDataManagement::saveSingleData(T							&value,
										 std::string				sKey,
										 std::string				sFile)
{
	// Schluesselwort ueberpruefen
	if (isStringEmpty(sKey, eErrorState::ESt_KEY_EMPTY))
	{
		// wenn leer dann abbrechen
		return ST_CANCEL;
	}

	// Dateinamen auf leere pruefen
	if (isStringEmpty(sFile, eErrorState::ESt_FILE_EMPTY))
	{
		// wenn leer dann abbrechen
		return ST_CANCEL;
	}

	// Datei oeffnen
	std::ifstream read(sFile, std::ios::in);

	// üeberpruefen ob die Datei existiert
	if (!read.is_open())
	{
		// wenn Fehler dann Fehlermeldung
		m_LastErrorState = eErrorState::ESt_SEARCH_NO_STREAM;
		return ST_FAIL;
	}


	// wenn alles gut bisscher lief
	//

	// Variablen setzen
	std::string							sSingleLine = "";
	std::list<std::string>				liData;
	std::list<std::string>::iterator	itorData;


	// Datei kopieren
	while (std::getline(read, sSingleLine))
	{
		// Zeile in die Liste packen
		liData.push_back(sSingleLine);
		std::cout << sSingleLine << std::endl;
	}

	// schliessen
	read.close();

	// wenn schluesselwort eixistiert
	// Iterator auf die Zeile richten
	int		iPos		= 0;
	bool	bKeyFound	= false;
	
	//
	for (itorData = liData.begin(); itorData != liData.end(); itorData++)
	{
		// Nach schluesselwort suchen
		iPos = itorData->find(sKey);

		// wenn gefunden dann raus
		if (iPos != std::string::npos)
		{
			// andernfalls weiter
			bKeyFound = true;
			break;
		}
	}

	// wenn das Schluesselwort nicht gefunden wurde
	// Neue "Zeile" in der Liste hinzufuegen
	// Um ein Zeigen vom Iterator auf eine nicht vorhandene Zeile
	// zu verhindern
	if (!bKeyFound)
	{
		liData.push_back("");
		itorData--;
	}

	// Linecontainer erstellen
	std::string Line = sKey;

	// Leerzeichen fuellen wenn noetig

	// wenn das Schluesselwort kuerzer ist
	// Leerzeichen fuellen

	if (m_iCharackterPerLine > (int) sKey.length())
	{
		for (int i = 0; i < m_iCharackterPerLine - (int) sKey.length(); i++)
		{
			Line += " ";
		}
	}

	// wenn sKey groesser als m_iCharackterPerLine
	// wird der Wert ohne leer zwischenzeichen
	// eingespeichert
	//
	// Wert einspeichern
	Line += " = " + std::to_string(value);

	// in die Liste uebertragen
	*itorData = Line;


	// Liste speichern
	//

	// stream dafuer oeffnen
	std::ofstream write(sFile, std::ios::out);

	// wenn beim oeffnen ein Fehler entstand
	if (!write.is_open())
	{
		// Fehlermeldung
		m_LastErrorState = eErrorState::ESt_SEARCH_NO_STREAM;
		return ST_FAIL;
	}

	// einschreiben
	for (itorData = liData.begin(); itorData != liData.end(); itorData++)
	{
		write << (*itorData += "\n");
	}

	write.close();
			
	//-----------
	return ST_OK;

} // saveSingleData
//