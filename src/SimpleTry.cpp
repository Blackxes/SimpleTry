/*******************************************************************************************************************************
	Nutzen:
	Deklaration aller Funktionen und Variablen
	Einbindung der header der Engine

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/
//

// header
#include <SimpleTry.h>

// Definitionen
/* ... */

//_______________________________________________________________________________________________________________
// Initialisierungsmethode der Engine
stState stInit()
{
	// Logfile initialisieren
	stLog->Init();
	stLog->writeInfo("Engine wurde gestartet");

	//
	stLog->writeDevider();

	// Dateimanagement initialisieren
	stLog->writeInfo("Initialisiere Dateimanagement ...");
	if (stData->Init() == ST_OK)
		stLog->writeInfo("Dateimanagement wurde initialisiert");
	else
		stLog->writeError("Dateimanagement konnte nicht initialisiert werden!");

	//
	stLog->writeDevider();

	// Zeit initialisieren
	stLog->writeInfo("Initialisiere Zeit ...");

	stTime* pTime = new stTime;
	if (pTime->Init() == ST_OK)
		stLog->writeInfo("Zeit wurde initialisiert");
	else
		stLog->writeError("Zeit konnte nicht initialisiert werden!");

	//
	SAFE_DELETE(pTime);

	//
	stLog->writeDevider();


	//-----------
	return ST_OK;

} // stInit

//_______________________________________________________________________________________________________________
// Engine beenden/herunterfahren
stState stExit()
{
	// Logfile schliessen und Inztanz loeschen
	stLog->writeInfo("Engine wurde geschlossen");
	if (stLog->Exit() == ST_NOT_FOUND)
	{
		std::cout << "Fehler beim schliessen der Logfile" << std::endl;
		return ST_FAIL;
	}

	//-----------
	return ST_OK;

} // stExit
//

//_______________________________________________________________________________________________________________
// main
int main()
{
	//
	return 0;
}
//