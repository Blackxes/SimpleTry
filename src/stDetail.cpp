/*******************************************************************************************************************************
	Nutzen:
	Detailerzeugung fuer AnimateText

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/
//

// header
#include <SimpleTry.h>

//--------------------------------------------
// Statische Variablen definieren
int stDetail::iNumberOfDetails = 0;

//--------------------------------------------
// Konstruktor
stDetail::stDetail(int iID) :	m_bInitialized				(false),
								m_bAllwdToBeOvrwrttn		(true),
								m_iID						(iID),
								m_sLabel					("DETAIL"),

								m_bAnimate					(false),
								m_bAnimateMainRun			(false),
								m_bAnimateEndRunDone		(false),
								m_bAnimateEndRun			(false),
								m_bAnimateCalcEndRun		(false),

								m_eAniEndStyle				(AText_AniEndStyle::LABEL_AES_INSTANT),
								m_bInvertMinMax				(false),
								m_bFirstToMinVal			(true),

								m_eLastViewPoint			(AText_ViewPoint::VP_BASE),
								m_eNextViewPoint			(AText_ViewPoint::VP_BASE),
								m_eInitNextViewPoint		(AText_ViewPoint::VP_BASE),

								m_v2dfCurrVal				(stVector2Df(0.f)),
								m_v2dfCurrValOld			(stVector2Df(0.f)),
								m_v2dfBaseVal				(stVector2Df(0.f)),
								m_v2dfMinVal				(stVector2Df(0.f)),
								m_v2dfMaxVal				(stVector2Df(0.f)),
								m_v2dfAdjBaseToMin			(stVector2Df(0.f)),
								m_v2dfAdjBaseToMax			(stVector2Df(0.f)),	
								m_v2dfAdjMinToMax			(stVector2Df(0.f)),
								m_v2dfAdjMaxToMin			(stVector2Df(0.f)),
								m_v2dfAdjCurrToBase			(stVector2Df(0.f)),

								m_fFPS						(0.0f),
								m_fUpdate					(0.0f),
								m_fUpdateCounter			(0.0f),
								m_fAniSpeed					(0.0f),
								m_fRunTimes					(0.0f),
								m_iRunTimesCounter			(0),
								m_bEndAfterMaxRunTimes		(false),

								m_bIsAnimating				(false),
								m_bIsLastRun				(false),
								m_bIsAnimatingToBase		(false),
								m_bIsAnimatingToMin			(false),
								m_bIsAnimatingToMax			(false)
{
	// Struktur definieren
	m_strAniFrameTime.fAsFrames			= 0.0f;
	m_strAniFrameTime.fAsPercetage		= 0.0f;
	m_strAniFrameTime.fGlobalFrameTime	= 0.0f;

	// Detailzaehler hochzaehlen
	iNumberOfDetails++;

} // Konstruktor
//

//--------------------------------------------
// Destruktor
stDetail::~stDetail()
{	
	//
	iNumberOfDetails--;

	// ueberpruefen ob das Detail initialisiert war - Entsprechende Meldung schreiben
	if (!m_bInitialized)
		stLog->writeWarning("Nicht initialisiertes Detail wurde zerstoert - Nr. " + std::to_string(iNumberOfDetails));
	else
		stLog->writeInfo("Detail mit der ID " + std::to_string(m_iID) + " wurde zerstoert");

} // Destruktor

//--------------------------------------------
// Kopierkonstruktor
stDetail::stDetail(const stDetail &rhs)
												
{
	this->m_bInitialized			= rhs.m_bInitialized;
	this->m_bAllwdToBeOvrwrttn		= rhs.m_bAllwdToBeOvrwrttn;
	this->m_iID						= rhs.m_iID;
	this->m_sLabel					= rhs.m_sLabel;
	this->m_bAnimate				= rhs.m_bAnimate;
	this->m_bAnimateMainRun			= rhs.m_bAnimateMainRun;
	this->m_bAnimateEndRunDone		= rhs.m_bAnimateEndRunDone;
	this->m_eAniEndStyle			= rhs.m_eAniEndStyle;
	this->m_bInvertMinMax			= rhs.m_bInvertMinMax;
	this->m_bIsAnimating			= rhs.m_bIsAnimating;
	this->m_bFirstToMinVal			= rhs.m_bFirstToMinVal;
	this->m_eLastViewPoint			= rhs.m_eLastViewPoint;
	this->m_eNextViewPoint			= rhs.m_eNextViewPoint;
	this->m_v2dfCurrVal				= rhs.m_v2dfCurrVal;
	this->m_v2dfBaseVal				= rhs.m_v2dfBaseVal;
	this->m_v2dfMinVal				= rhs.m_v2dfMinVal;
	this->m_v2dfMaxVal				= rhs.m_v2dfMaxVal;
	this->m_v2dfAdjBaseToMin		= rhs.m_v2dfAdjBaseToMin;
	this->m_v2dfAdjBaseToMax		= rhs.m_v2dfAdjBaseToMax;
	this->m_v2dfAdjMinToMax			= rhs.m_v2dfAdjMinToMax;
	this->m_v2dfAdjCurrToBase		= rhs.m_v2dfAdjCurrToBase;
	this->m_fAniSpeed				= rhs.m_fAniSpeed;

	// Meldung das der Kopierkonstruktor aufgerufen wurde
	stLog->writeInfo("Kopierkonstruktor eines Details wurde aufgerufen - ID: " + std::to_string(m_iID));

} // Kopierkonstruktor
//

//
//

//
//

//_______________________________________________________________________________________________________________
// Initialisierung
stState stDetail::Init(	int					iID,
						bool				bAnimate,
						stVector2Df			v2dfBaseVal,
						stVector2Df			v2dfMinVal,
						stVector2Df			v2dfMaxVal,
						float				fFrameTime,
						float				fGlobalFrameTime,
						float				fFPS,
						float				fAniSpeed)
{

	// wenn ID 0 kann nicht initialisiert werden - es muss eine valide ID sein
	if (!iID)
		return ST_CANCEL;

	// Variablen Definieren
	m_bAnimate						= bAnimate;
	m_eAniEndStyle					= AText_AniEndStyle::LABEL_AES_INSTANT;
	m_bFirstToMinVal				= true;

	m_fAniSpeed							= fAniSpeed;
	m_fFPS								= fFPS;

	m_strAniFrameTime.fAsPercetage		= fFrameTime;
	m_strAniFrameTime.fGlobalFrameTime	= fGlobalFrameTime;
	m_strAniFrameTime.fAsFrames			= (fFrameTime / 100) * m_strAniFrameTime.fGlobalFrameTime;

	//
	m_bAllwdToBeOvrwrttn			= true;
	m_bAnimateCalcEndRun			= true;

	// Pro Frame 1 Update
	m_fUpdate				= 1 / m_strAniFrameTime.fAsFrames;
	m_fUpdateCounter		= 0.0f;

	// Naechsten Animationslauf definieren
	if (m_bFirstToMinVal)
		m_eNextViewPoint = AText_ViewPoint::VP_MIN;
	else
		m_eNextViewPoint = AText_ViewPoint::VP_MAX;

	// Initialisierten Wert einspeichern
	m_eInitNextViewPoint = m_eNextViewPoint;

	m_v2dfCurrVal			= v2dfBaseVal;
	m_v2dfBaseVal			= v2dfBaseVal;
	m_v2dfMinVal			= v2dfMinVal;
	m_v2dfMaxVal			= v2dfMaxVal;

	// Verrechnungswerte definieren/errechnen
	m_v2dfAdjBaseToMin	= calcAdjVal(v2dfBaseVal, v2dfMinVal, fGlobalFrameTime);
	m_v2dfAdjBaseToMax	= calcAdjVal(v2dfBaseVal, v2dfMaxVal, fGlobalFrameTime);
	m_v2dfAdjMinToMax	= calcAdjVal(v2dfMinVal, v2dfMaxVal, fGlobalFrameTime);
	m_v2dfAdjMaxToMin	= calcAdjVal(v2dfMaxVal, v2dfMinVal, fGlobalFrameTime);

	this->m_bInitialized = true;

	//-----------
	return ST_OK;

} // Initialisierungskonstruktor
//

//_______________________________________________________________________________________________________________
// Update-Funktion fuer (this) Detail
//
// Animationsfälle (Variablenstaten von m_bAnimateMain | m_bAnimateRun | m_bAnimateEndRunDone, m_bAnimateControlEndRun)
//
//		m_bAnimateMain = false
//			verlassen, alles gut
//		m_bAnimateMain = true
//			animation darf animieren
//
//		m_bAnimateRun = true
//			animation weiter laufen lassen
//
//		m_bAnimateRun = false | m_bAnimateEndRunDone = true
//			verlassen - Animation vollendet
//
//		m_bAnimateRun = false | m_bAnimateEndRunDone = false | m_bAnimateControlEndRun = false
//			animation nicht stoppen - Endanimation ermitteln
//				
//			INSTANT:	lauf verlassen und m_bAnimateEndRunDone true setzen
//			STD:		Abhaengig von dem letzten ViewPoint zum Max- oder Minwert "zuende"-animieren
//			TOBASE:		Zum Basiswert animieren lassen (Werte neu berechnen)
//
//		m_bAnimateRun = false | m_bAnimateEndRunDone = false | m_bAnimateControlEndRun = true
//			(betrifft nicht den Endanimationsstil "AES_INSTANT")
//			
//			Animation laufen lassen bis der Wechsel stattfinden soll
//			An dem Punkt animation stoppen
//
//
//
stState stDetail::Update(const float fTime)
{
	// Variablen
	/* ... */

	// Alten Wert einspeichern - muss vor dem ueberpruefen statt finden
	// weil sich der Wert anderweitig veraendert haben koennte
	m_v2dfCurrValOld = m_v2dfCurrVal;

	// Wenn nicht aninimiert werden soll, dann ST_OK zurueck
	// ODER
	// Wenn die Animation gestoppt werden soll und die Endanimation schon durchlaufen wurde
	if ( (!m_bAnimate) ||
		((!m_bAnimateMainRun) && (m_bAnimateEndRunDone)) )
	{
		m_bIsAnimating = false;
		return ST_OK;
	}


	// Timer hochzaehlen
	m_fUpdateCounter += fTime * m_fAniSpeed;

	// Ueberpruefen ob ein Update stattfinden darf
	if (m_fUpdateCounter < m_fUpdate)
		return ST_OK;
	else
		m_fUpdateCounter = 0.0f;

	// Detail animiert wenn es hier passiert
	m_bIsAnimating = true;

	// Werte reseten - sie werden innerhalb dieser Funkton neu definiert
	m_bIsAnimatingToBase	= false;
	m_bIsAnimatingToMin		= false;
	m_bIsAnimatingToMax		= false;

	// Wenn die Animationlaeufe durch sind
	// Maximalwert muss verdoppelt werden da 1 Durchlauf
	// einem halben im Rendering entspricht
	if ( (m_fRunTimes) && ( m_iRunTimesCounter > (m_fRunTimes * 2) ) && (m_bAnimateMainRun) )
	{
		// wenn beendet werden soll wenn das Maximum erreicht wurde
		if (m_bEndAfterMaxRunTimes)
			endAni();

		//
		return ST_OK;
	}

	// andernfalls wenn die Hauptanimation nicht mehr laufen soll ..
	// ueberpruefen ob die Endanimation bereits beendet wurde
	// und die Ueberpruefungen und Berechnungen fuer die Endanimation bereits
	// stattgefunden haben
	if ( (!m_bAnimateMainRun) && (!m_bAnimateEndRunDone) && (m_bAnimateCalcEndRun) )
	{
		// ueberpruefen ob es ein akutes Ende hat ..
		if (m_eAniEndStyle == AText_AniEndStyle::LABEL_AES_INSTANT)
		{
			m_bAnimateEndRunDone	= true;			// Endanimtion durchlaufen
			m_bAnimateEndRun		= false;		// Nicht mehr im Endrun weil Animation beendet wurde
			return ST_OK;
		}

		// andernfalls ..
		else
		{
			// unterscheiden welche Endstil gewaehlt wurde
			switch (m_eAniEndStyle)
			{
				case (AText_AniEndStyle::LABEL_AES_STD):
					//std::cout << "Bin drinne " << std::endl;
				break;

				case (AText_AniEndStyle::LABEL_AES_TOBASE):
					m_eLastViewPoint = AText_ViewPoint::VP_UNKNOWN;
					m_eNextViewPoint = AText_ViewPoint::VP_BASE;
					m_v2dfAdjCurrToBase = calcAdjVal(m_v2dfCurrVal, m_v2dfBaseVal);
				break;
			
			}
		}

		m_bAnimateCalcEndRun		= false;
		m_bAnimateEndRun			= true;		// Animation in die Endanimation versetzen

		return ST_OK;
	}

	//--------------------------------------------
	// Welcher Punkt ist das naechste Ziel
	switch(m_eNextViewPoint)
	{
		//--------------------------------------------
		// wenn das naechste Ziel der Basiswert ist
		case (AText_ViewPoint::VP_BASE):
		{
			// 
			m_bIsAnimatingToBase = true;

			// wenn der Standpunkt unbekannt ist
			if (m_eLastViewPoint == AText_ViewPoint::VP_UNKNOWN)
			{
				//
				updateMovement(m_v2dfCurrVal, m_v2dfCurrVal, m_v2dfBaseVal, m_v2dfAdjCurrToBase,
							   m_eInitNextViewPoint,
							   fTime);

				//std::cout << "N: BASE - L: UNKNOWN" << std::endl;
			}

			// wenn die Animation vom Minimalwert kommt
			else if (m_eLastViewPoint == AText_ViewPoint::VP_MIN)
			{
				//
				updateMovement(m_v2dfCurrVal, m_v2dfMinVal, m_v2dfBaseVal, m_v2dfAdjBaseToMin,
							   AText_ViewPoint::VP_MAX,
							   fTime);

				//std::cout << "N: BASE - L: MIN" << std::endl;
			}

			// wenn die Animation vom Maximalwert kommt
			else if (m_eLastViewPoint == AText_ViewPoint::VP_MAX)
			{
				//
				updateMovement(m_v2dfCurrVal, m_v2dfMaxVal, m_v2dfBaseVal, m_v2dfAdjBaseToMax,
							   AText_ViewPoint::VP_MIN,
							   fTime,
							   true);

				//std::cout << "N: BASE - L: MAX" << std::endl;
			}
		}
		break;

		//--------------------------------------------
		// wenn das naechste Ziel der MinVal ist
		case (AText_ViewPoint::VP_MIN):
		{
			// 
			m_bIsAnimatingToMin = true;

			//--------------------------------------------
			// wenn zuletzt beim BaseVal ...
			if (m_eLastViewPoint == AText_ViewPoint::VP_BASE)
			{
				//
				updateMovement(m_v2dfCurrVal, m_v2dfBaseVal, m_v2dfMinVal, m_v2dfAdjBaseToMin,
							   AText_ViewPoint::VP_MAX,
							   fTime);

				//std::cout << "N: MIN - L: BASE" << std::endl;

			} // case - wenn letztes Ziel BaseVal war
			
			//--------------------------------------------
			// Wenn zuletzt beim Maxval ..
			else if (m_eLastViewPoint == AText_ViewPoint::VP_MAX)
			{
				//
				updateMovement(m_v2dfCurrVal, m_v2dfMinVal, m_v2dfMaxVal, m_v2dfAdjMaxToMin,
							   AText_ViewPoint::VP_MAX,
							   fTime,
							   true);

				//	std::cout << "N: MIN - L: MAX" << std::endl;
			}

		} // switch (m_eNextViewPoint)
		break;
		
		//--------------------------------------------
		// wenn das naechste Ziel der Maximalwert ist
		case (AText_ViewPoint::VP_MAX):
		{
			//
			m_bIsAnimatingToMax = true;

			//--------------------------------------------
			if (m_eLastViewPoint == AText_ViewPoint::VP_MIN)
			{
				//
				updateMovement(m_v2dfCurrVal, m_v2dfMinVal, m_v2dfMaxVal, m_v2dfAdjMinToMax,
							   AText_ViewPoint::VP_MIN,
							   fTime);

				//std::cout << "N: MAX - L: MIN" << std::endl;
			}

			else if (m_eLastViewPoint == AText_ViewPoint::VP_BASE)
			{
				//
				updateMovement(m_v2dfCurrVal, m_v2dfBaseVal, m_v2dfMaxVal, m_v2dfAdjBaseToMax,
							   AText_ViewPoint::VP_MIN,
							   fTime);

				//std::cout << "N: MAX - L: BASE" << std::endl;
			}
		}
		break;
	}

	//-----------
	return ST_OK;

} // Update
//

//_______________________________________________________________________________________________________________
// ueberprueft ob noch ein animationsdurchlauf stattfinden kann
stState stDetail::updateMovement(stVector2Df		&vecCurrVal,
								 stVector2Df		&vecStartVal,
								 stVector2Df		&vecEndVal,
								 stVector2Df		&vecAdjVal,
								 AText_ViewPoint	eNextViewPoint,
								 const float		&fTime,
								 bool				bInvertControl)
{
	// Variablen
	//
	bool tempbReachEnd = false;		// haben wir das Ende eines Laufs erreicht?

	
	// wenn normal kontrolliert werden soll
	if (!bInvertControl)
	{
		if ((vecStartVal.x > vecEndVal.x) &&									
			((vecCurrVal.x + vecAdjVal.x) > vecEndVal.x) ||

			(vecStartVal.x < vecEndVal.x) &&
			((vecCurrVal.x + vecAdjVal.x)  < vecEndVal.x) )
		{
			// dann wert bewegen
			vecCurrVal += vecAdjVal;
		}

		else
		{
			tempbReachEnd = true;
		}
	}


	// wenn verkehrt herum kontrolliert werden soll
	else
	{
		// wenn StartVal groesser als EndVal ist
		if ((vecStartVal.x > vecEndVal.x) &&
		   ((vecCurrVal.x + vecAdjVal.x) < vecStartVal.x) ||

			// StartVal kleiner als EndVal ist
			(vecStartVal.x < vecEndVal.x) &&
			( (vecCurrVal.x + vecAdjVal.x) > vecStartVal.x) )
		{
			// dann wert bewegen
			vecCurrVal += vecAdjVal;
		}

		else
		{
			tempbReachEnd = true;
		}
	}

	if (tempbReachEnd)
	{
		// Der letzte ist immer das "alte" naechste Ziel
		m_eLastViewPoint = m_eNextViewPoint;	// Letzten Standpunkt angeben
		m_eNextViewPoint = eNextViewPoint;		// Naechsten Punkt angeben

		if (m_bAnimateEndRun)
		{
			m_bAnimateEndRunDone	= true;
			m_bAnimateEndRun		= false;
			m_bAnimateCalcEndRun	= true;

			//std::cout << "CURR X: " << m_v2dfCurrVal.x << std::endl;
			//std::cout << "BASE X: " << m_v2dfBaseVal.x << std::endl;
			//std::cout << "MIN: "  << m_v2dfMinVal.x << std::endl;
			//std::cout << "MAX: "  << m_v2dfMaxVal.x << std::endl;
		}

		// Animationslauf hochzaehlen
		m_iRunTimesCounter++;
	}

	//-----------
	return ST_OK;

} // updateMovement
//

//_______________________________________________________________________________________________________________
// startet die Animation
stState stDetail::startAni()
{
	//
	m_bAnimateEndRunDone	= false;
	m_bAnimateMainRun		= true;
	m_iRunTimesCounter		= 0;

	//-----------
	return ST_OK;

} // startAni
//

//_______________________________________________________________________________________________________________
// beendet die Animation
stState stDetail::endAni()
{
	//
	m_bAnimateMainRun = false;

	//-----------
	return ST_OK;

} // endAni

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
// Kopiert detail's Werte in this
void stDetail::copyFrom(stDetail detail)
{
	this->m_bInitialized				= detail.m_bInitialized;
	this->m_bAllwdToBeOvrwrttn			= detail.m_bAllwdToBeOvrwrttn;
	this->m_iID							= detail.m_iID;
	this->m_sLabel						= detail.m_sLabel;

	this->m_bAnimate					= detail.m_bAnimate;
	this->m_bAnimateMainRun				= detail.m_bAnimateMainRun;
	this->m_bAnimateEndRun				= detail.m_bAnimateEndRun;
	this->m_bAnimateEndRunDone			= detail.m_bAnimateEndRunDone;
	this->m_bAnimateCalcEndRun			= detail.m_bAnimateCalcEndRun;

	this->m_eAniEndStyle				= detail.m_eAniEndStyle;
	this->m_bInvertMinMax				= detail.m_bInvertMinMax;
	this->m_bFirstToMinVal				= detail.m_bFirstToMinVal;

	this->m_eLastViewPoint				= detail.m_eLastViewPoint;
	this->m_eNextViewPoint				= detail.m_eNextViewPoint;
	this->m_eInitNextViewPoint			= detail.m_eInitNextViewPoint;

	this->m_v2dfCurrVal					= detail.m_v2dfCurrVal;
	this->m_v2dfBaseVal					= detail.m_v2dfBaseVal;
	this->m_v2dfMinVal					= detail.m_v2dfMinVal;
	this->m_v2dfMaxVal					= detail.m_v2dfMaxVal;
	this->m_v2dfAdjBaseToMin			= detail.m_v2dfAdjBaseToMin;
	this->m_v2dfAdjBaseToMax			= detail.m_v2dfAdjBaseToMax;
	this->m_v2dfAdjMinToMax				= detail.m_v2dfAdjMinToMax;
	this->m_v2dfAdjMaxToMin				= detail.m_v2dfAdjMaxToMin;
	this->m_v2dfAdjCurrToBase			= detail.m_v2dfAdjCurrToBase;

	this->m_fFPS						= detail.m_fFPS;
	this->m_fUpdate						= detail.m_fUpdate;
	this->m_fUpdateCounter				= detail.m_fUpdateCounter;
	this->m_strAniFrameTime				= detail.m_strAniFrameTime;
	this->m_fAniSpeed					= detail.m_fAniSpeed;

	this->m_fRunTimes					= detail.m_fRunTimes;
	this->m_iRunTimesCounter			= detail.m_iRunTimesCounter;
	this->m_bEndAfterMaxRunTimes		= detail.m_bEndAfterMaxRunTimes;

	this->m_bIsAnimating				= detail.m_bIsAnimating;
	this->m_bIsLastRun					= detail.m_bIsLastRun;

	 this->m_bIsAnimatingToBase			= detail.m_bIsAnimatingToBase;
	 this->m_bIsAnimatingToMin			= detail.m_bIsAnimatingToMax;
	 this->m_bIsAnimatingToMax			= detail.m_bIsAnimatingToMax;

} // CopyFrom

//_______________________________________________________________________________________________________________
// Berechnet die Verrechnungswerte
stVector2Df stDetail::calcAdjVal(const stVector2Df &preVal, 
								 const stVector2Df &secVal, 
								 float				fFrameTime)
{
	// wenn (!fFrameTime) dann nehmen wir den Klassenstandard
	if (fFrameTime == 0.0f)
		fFrameTime = this->m_strAniFrameTime.fAsFrames;

	//--------------------------------------------------
	return ( (secVal - preVal) / (fFrameTime / 2) );

} // CalcAdjVals
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
// Setzt den Momentanen Wert auf den Basiswert
void stDetail::resetCurr()
{
	//
	m_v2dfCurrVal = m_v2dfBaseVal;

} // resetCurrSoft
//

//_______________________________________________________________________________________________________________
// definiert ob das Detail initialisiert wurde
// wird beim initialisieren auch automatisch definiert
void stDetail::setInitializationState(bool bState)
{
	//
	m_bInitialized = bState;

} // setInitialisationState

//_______________________________________________________________________________________________________________
// definiert die allgemeine Animationserlaubnis
void stDetail::setAniPermission(bool bPermission)
{
	//
	m_bAnimate = bPermission;

} // setAniPermission
//

//_______________________________________________________________________________________________________________
// definiert die Animationsdauer
void stDetail::setAniFrameTime(float fFrameTime)
{
	// Wert darf nicht unter Null sein
	m_strAniFrameTime.fAsFrames = (fFrameTime < 0) ? 0.0f : fFrameTime;

} // setFrameTime
//

//_______________________________________________________________________________________________________________
void stDetail::setGlobalAniFrameTime(float fFrameTime)
{
	// wenn Wert unter Null - dann gleich 0 setzen
	m_strAniFrameTime.fGlobalFrameTime = (fFrameTime < 0.0f) ? 0.0f: fFrameTime;

	// Werte neu berechnen
	m_strAniFrameTime.fAsFrames = (m_strAniFrameTime.fAsPercetage / 100) * m_strAniFrameTime.fGlobalFrameTime;

	m_fUpdate = 1 / m_strAniFrameTime.fAsFrames;

} // 
//

//_______________________________________________________________________________________________________________
// definiert die Animationsgeschwindigkeit
void stDetail::setAniSpeed(float fAniSpeed)
{
	// Wert darf nicht unter Null sein
	m_fAniSpeed = (fAniSpeed < 0.0f) ? 0.0f : fAniSpeed;

} // setAniSpeed
//

//_______________________________________________________________________________________________________________
// setzt den momentanen Wert
void stDetail::setCurrVal(stVector2Df CurrVal)
{ 
	//
	m_v2dfCurrVal = CurrVal;

} // setBaseVal 
//

//_______________________________________________________________________________________________________________
// definiert den Basiswert
void stDetail::setBaseVal(stVector2Df BaseVal)
{ 
	//
	m_v2dfBaseVal		= BaseVal;
	m_v2dfAdjBaseToMin	= calcAdjVal(m_v2dfBaseVal, m_v2dfMinVal);
	m_v2dfAdjBaseToMax	= calcAdjVal(m_v2dfBaseVal, m_v2dfMaxVal);

} // setBaseVal 
//

//_______________________________________________________________________________________________________________
// setzt den Minimalwert
void stDetail::setMinVal(stVector2Df MinVal)
{ 
	//
	m_v2dfMinVal		= MinVal;
	m_v2dfAdjBaseToMin	= calcAdjVal(m_v2dfBaseVal, m_v2dfMinVal);
	m_v2dfAdjMinToMax	= calcAdjVal(m_v2dfMinVal, m_v2dfMaxVal);
	m_v2dfAdjMaxToMin	= calcAdjVal(m_v2dfMaxVal, m_v2dfMinVal);

} // setBaseVal 
//

//_______________________________________________________________________________________________________________
// setzt den Maximalwert
void stDetail::setMaxVal(stVector2Df MaxVal)
{ 
	//
	m_v2dfMaxVal		= MaxVal;
	m_v2dfAdjBaseToMax	= calcAdjVal(m_v2dfMinVal, m_v2dfMaxVal);
	m_v2dfAdjMinToMax	= calcAdjVal(m_v2dfMinVal, m_v2dfMaxVal);
	m_v2dfAdjMaxToMin	= calcAdjVal(m_v2dfMaxVal, m_v2dfMinVal);

} // setBaseVal 
//

//_______________________________________________________________________________________________________________
// definiert ob die Animation weiterlaufen oder halten soll
void stDetail::setAniRun(bool bPermission)
{
	//
	m_bAnimateMainRun = bPermission;

} // setAniRun

//_______________________________________________________________________________________________________________
// definiert den Animationsendstyle
void stDetail::setAniEndStyle(AText_AniEndStyle EndStyle)
{
	//
	m_eAniEndStyle = EndStyle;

} // setAniEndStyle
//

//_______________________________________________________________________________________________________________
// definiert die Anzahl an durchlauefen
void stDetail::setAniRunTimes(float fRunTimes)
{
	//
	m_fRunTimes = fRunTimes;

} // setAniRunTimes
//

//_______________________________________________________________________________________________________________
