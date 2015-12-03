/*******************************************************************************************************************************
	Nutzen:
	das Handeln mit der Zeit

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/
//

// header
#include <SimpleTry.h>

//--------------------------------------------
// Definitionen
bool	stTime::m_bInitialized	= false;
int		stTime::m_iCounter		= 0;

//--------------------------------------------
// Konstruktor
stTime::stTime()
{

	// Defaultwerte definieren
	m_fElapsedTime = 0.0f;

	

	// Zaehler hochzaehlen
	m_iCounter++;

} // Kostruktor
//

//______________________________________________________________________________________________________________________________
// Destruktor
stTime::~stTime()
{
	// Zaehler anpassen
	m_iCounter--;

} // Destruktor
//

//______________________________________________________________________________________________________________________________
// Initialisiert die Zeitklasse
stState stTime::Init()
{
	// einmalige Initialisierung
	if (!m_bInitialized)
	{
		// wenn aus irgendeinem Grund bereits eine Instanz existiert
		// und die Initialisierung das 2x durchgefuehrt wird - Fehlermeldung
		if (m_iCounter > 1)
		{
			stLog->writeWarning("stTime Klasseninstanz wurde bereits initialisiert. Aktuelle Initialisierung wird uebersprungen!");
			return ST_FAIL;
		}
		else
		{
			// Als initialisiert definieren
			std::srand( (int) time(0));
			m_bInitialized = true;
		}
	}

	//-----------
	return ST_OK;

} // Init
//

//______________________________________________________________________________________________________________________________
// aktualisiert die Zeiten
void stTime::Update()
{
	//
	m_fElapsedTime = m_sfClock.restart().asSeconds();

} // Update
//

//______________________________________________________________________________________________________________________________
// erzeugt eine zufaellig generierte Zahl
float stTime::getRandom(int iMax, int iMin)
{
	if (iMin > iMax)
	{
		stLog->writeInfo("Zufallszahl nicht generierbar da Min groesser als Max ist");
		return 0;
	}

	//
	int rand_number = iMax - iMin;

	//---------------------------------------------------------
	return ( (float) (std::rand() % rand_number) + iMin);

}  // getRandom
//