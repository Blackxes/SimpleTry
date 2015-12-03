/*******************************************************************************************************************************
	Nutzen:
	Initialisierung des Zeittimers.


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
// Klasse
class stTime
{
	//===============================================================================================================
	private:

		static int									m_iCounter;					// statischer Klassenzaehler

		float										m_fElapsedTime;				// vergangene Zeit
		sf::Clock									m_sfClock;					// Zeitklasse

		// globale Initialisation - um die getRandom Funktion funktional zu machen und dem srand() bug zu umgehen
		// srand() wird nur einmal initialisert wenn mind. eine Instanz dieser Klasse existiert
		static bool									m_bInitialized;

	//===============================================================================================================
	public:
			
		//===========================================================================================================
		// Initialmethoden - Konstruktor/Kopierkonstruktor/Destruktor - Initfunktion
		//

													stTime();
													~stTime();

		// Initialisierung
		stState										Init();

		// aktualiesiert die vergangene Zeit
		void										Update();
		

		//===========================================================================================================
		// add/sub/set/get-Funktionen

		float										getElapsed()		{ return m_fElapsedTime; }				// vergangene Zeit	

		// gibt eine zufaellig generierte Zahl zwischen iMin und iMax zurueck
		// iMin ist standardmaessig 0
		//
		// param1 - erwartet den Maximalwert den die Zahl haben darf
		// param2 - erwartet den Minimalwert
		// 
		// return - zuaellig generierte Zahl zwischen iMin und iMax
		float										getRandom(int iMax, int iMin = 0);

}; // stTime
//

//_______________________________________________________________________________________________________________
