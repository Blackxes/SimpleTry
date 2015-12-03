/*******************************************************************************************************************************
	Nutzen: 
	home datei. enthält alle nötogen header und namespaces

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/

//
#pragma once
//

//_______________________________________________________________________________________________________________
// header
/* ... */
//

//_______________________________________________________________________________________________________________
// Vorwaertsdeklarationen
class stVector2Df;

//_______________________________________________________________________________________________________________
// externe Definition - globale Nutzung moeglich
/* ... */

//_______________________________________________________________________________________________________________
// Strukturen - Enumeratoren - etc.


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
// Struktur fuer die Logtypen
enum logtype
{
	LT_INFO,
	LT_ERROR,
	LT_WARNING,
	LT_VECTOR,
	LT_OTHER,
};





// Klassendeklarationen und Definitionen
class stLogfile
{
	
	//===============================================================================================================
	private:

		//===========================================================================================================
		// Basisvariablen	

		//static int											m_LogsCounter;					// Wie viele Logs insgesamt geschrieben wurden

		std::string											m_sLogName;						// Dateiname der Logfile
		std::string											m_sLogfilePath;					// Pfad der Logfile
		static int											m_iLogID;						// ID des Logs

		int													m_iLogMaxLength;				// Maximallaenge des Logs (Wie viele Logs insgesamt) -1 = unendlich

		int													m_iMaxTitleLength;				// Maximallaenge des Titels

		std::string											m_mainHead;						// header der Logfile
		std::string											m_mainFooter;					// footer der Logfile
		std::string											m_mainJS;						// Javascript der Logfile - wenn jQuery nicht gefunden wurd
																							// werden die js-Funktionen eingestellt
		std::string											m_mainCSS;						// css-styles
		std::string											m_sPathCSS;						// css Dateipfad
		std::string											m_sPathJS;						// javascript Dateipfad
		std::string											m_sPathjQuery;					// jQuery Dateipfad

		std::string											m_sDefColor;					// main-Color der Texte (in hex)
		int													m_iDefFontSize;					// Standard schriftgroese der Texte (in px)
		std::string											m_sDefFontStyle;				// Standard schriftstyle der Texte (in px)

		std::string											m_sDefColorCodeTitle;			// Standard Farbcode des Titels
		std::string											m_sDefColorCodeText;			// Standard Farbcode des Textes
		int													m_sDefFontSizeTitle;			// Standard Schriftgroesse des Titels
		int													m_sDefFontSizeText;				// Standard Schriftgreosse des Textes
		std::string											m_sDefFontStyleTitle;			// Standard Schriftstil des Titels
		std::string											m_sDefFontStyleText;			// Standard Schriftstil des Textes


		//===========================================================================================================
		// Statusvariablen
		bool												m_bIsInitializied;				// Ist die Logfile bereits initialisiert worden?

		//===========================================================================================================
		// Interne Funktionen
		//

		// liest die Datei im angegeben Pfad aus und schreibt sie in die Variable 'container'
		//
		// param1 - erwartet den Dateinamen
		// param2 - erwartet eine Variable in die der Inhalt geschrieben wird
		//
		// return ST_OK - wenn das auslesen und einschreiben erfolgreich war
		// return ST_NOT_FOUND - wenn die Datei nicht gefunden wurde
		stState												getDataContent(std::string sFile,
																		   std::string &sContainer);

		// schreibt einfachen Text in das Logfile - Textfarbe (hex) / Schriftgroesse (px) / Schriftstyle variabel
		//
		// param1 - erwartet einen Titel
		// param2 - erwartet einen Text
		// param3 - erwartet den Logtypen (standardmaessig 
		inline stState										write(std::string title, 
																  std::string text,
																  logtype eLogtype = logtype::LT_OTHER);	



	//===============================================================================================================
	public:

		//===========================================================================================================
		// Initialmethoden - Konstruktor/Kopierkonstruktor/Destruktor - Initfunktion
															stLogfile();
															stLogfile(const stLogfile &rhs) {}
															~stLogfile();

		// interne Initialisierung und das Herunterfahren
		stState												Init();
		stState												Exit();
		
		// schreibt einen Vektor vom Typ 'stVector2Df' in das Logfile - toggleOUt definiert ob die erzeugte Liste
		// beim oeffnen der Logfile bereits am Anfang ausgeklappt werden soll. Standardmaeßig muss man die Liste selbst oeffnen
		//
		// param1 - erwartet einen Vektor vom Typ "stVector2Df"
		// param2 - erwartet den Vektornamen
		// param3 - erwartet einen Titel
		// param4 - erwartet einen bool (Soll die Werteliste des Vektors beim oeffnen der Logfile bereits ausgeklappt sein?)
		//
		// return ST_OK - wenn das einschreiben erfolgreich war
		// return ST_NOT_FOUND - wenn das Logfile nicht gefunden wurde
		stState												writeVector(stVector2Df vec,
																		std::string varName,
																		std::string title = "Vektor",
																		bool bToggleOut = false);
		
		// schreibt einen Error in das Logfile
		//
		// param1 - erwartet die Errormeldung als Text
		//
		// return ST_OK - wenn das einschreiben erfolgreich war
		// return ST_NOT_FOUND - wenn die Logfile nicht gefunden wurde
		stState												writeError(std::string sError);

		// schreibt eine Warnung in das Logfile
		//
		// param1 - erwartet die Warnung als Text
		//
		// return ST_OK - wenn das einschreiben erfolgreich war
		// return ST_NOT_FOUND - wenn die Logfile nicht gefunden wurde
		stState												writeWarning(std::string sWarning);

		// schreibt eine Information in das Logfile
		//
		// param1 - erwartet die Information als Text
		//
		// return ST_OK - wenn das einschreiben erfolgreich war
		// return ST_NOT_FOUND - wenn die Logfile nicht gefunden wurde
		stState												writeInfo(std::string sInformation);

		// fuegt eine Trennlinie in das Logfile ein
		//
		// param1 - erwartet die Farbe in der der Trenner eingetragen werden soll (standardmaessig in der basic.css angegeben)
		//
		// return ST_OK - wenn das einschreiben erfolgreich war
		// return ST_NOT_FOUND - wenn die Logfile nicht gefunden wurde
		stState												writeDevider(std::string color = "");
		
		
		//===========================================================================================================
		// Verwaltung
		/* ... */

}; // Logfile
//

//_______________________________________________________________________________________________________________
// globales Log
extern stLogfile* stLog;