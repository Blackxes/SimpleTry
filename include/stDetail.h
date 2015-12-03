/*******************************************************************************************************************************
	Nutzen:
	Detailklasse fuer CAnimateText

	Beschreibung:

	Verwaltet die werte des Details und errechnet auch die noetigen Werte von sich aus.
	Beinhaltet eine eigene Update funktion die die meiste Arbeit abnimmt.

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
struct AniFrameTime
{
	float fAsFrames;			// Frameanzahl als Frames
	float fAsPercetage;		// Frameanzahl als Prozent
	float fGlobalFrameTime;	// Die globale Animationsdauer. Einheit ist Frames
							// Heißt das bei 60 Frames eine Animation 60 Frames benoetigt um einen Lauf zu machen

}; // AniFrameTime
//

//--------------------------------------------
// Animationsende - Wie soll die Animation gestoppt werden
enum AText_AniEndStyle
{
	LABEL_AES_INSTANT,			// Hoert sofort mit der Animation auf
	LABEL_AES_STD,				// Animiert (Abhaengig von welchen Wert die Animation 'kommt': Min oder Max) bis zum Min oder MaxVal zuende
	LABEL_AES_TOBASE			// Animiert vom momentanen Standpunkt bis zum Basiswert

}; // AniEndStyle
//

//--------------------------------------------
// Standpunkt der Animation
enum AText_ViewPoint
{
	VP_BASE,			// Basiswert
	VP_MIN,				// Minimalwert
	VP_MAX,				// Maximalwert
	VP_UNKNOWN			// Unbekannt - Zum Beispiel in mitten einer Animation

}; // ViewPoint
//





// Klassendeklarationen und Definitionen
class stDetail
{
	// stAnimateText erlauben direkte Abfragen zu erlauben
	friend class stAniLabel;
	
	//===============================================================================================================
	private:

		//===========================================================================================================
		// Basisvariablen	
		static int									iNumberOfDetails;			// Zaehlt wie viele Details INSGESAMT existieren

		bool										m_bInitialized;				// Gibt an, ob das Detail bereits initialisiert wurde und keine std werte mehr besitzt
		bool										m_bAllwdToBeOvrwrttn;		// Darf das detail ueberschrieben werden wenn es neu initialisiert wird

		int											m_iID;						// ID des Details
		std::string									m_sLabel;					// Bezeichnung des Details (Fuer Ausgaben und Debuging) gespeichert als string


		bool										m_bAnimate;					// Wird dieses Detail aninimiert?
																				// Das ist der Globale Wert der ueber allem steht. 
																				// Ist dieser false - wird nicht animiert - egal was ist

		bool										m_bAnimateMainRun;			// Ist dieser Wert false greifen anders als bei m_bAnimateMain
																				// die End-Animations-Einstellungen
																				// Also es wird nicht abgebrochen sondern vorher ueberprueft
																				// wie das Detail die Animation beenden soll.

		bool										m_bAnimateEndRunDone;		// Dieser Wert bestimmt ob die Endanimations durchlaufen wurde
																				// Wenn dieser Wert true erreicht ist nach einem Animationsstopp
																				// Die Endanimation durchlaufen worden und die Animation stoppt endgueltig

		bool										m_bAnimateEndRun;			// Bestimmt ob die Animation nach einem Wechsel des Viewpoints stoppen soll
																				// Also in die Endanimation gehen soll (wenn eine vorhanden ist)

		bool										m_bAnimateCalcEndRun;		// gibt an ob nach einem false setzen von m_bAnimateRun
																				// (das stoppen der Animation)
																				// die Endanimationsoptionen, Unterscheidungen, Berechnungen, etc.
																				// (z.B. ob es sich um den Endanimationsstil "AES_INSTANT" handelt)
																				// durchlaufen worden sind.
																				// Ist dieser Wert false und m_bAnimateRun ebenfalls
																				// werden m_eAniEndStyle analysiert und die jeweiligen Operationen durchgefuehrt

		AText_AniEndStyle							m_eAniEndStyle;				// Animationsendart - wie soll die Animation enden?

		bool										m_bInvertMinMax;			// Soll Der Wert Min und Max vertauscht werden

		bool										m_bFirstToMinVal;			// Soll die Animation zuerst zum MinVal animieren?

		AText_ViewPoint								m_eLastViewPoint;			// Letzter Positionsstandpunkt - wo war die Animation zuletzt
		AText_ViewPoint								m_eNextViewPoint;			// Naechster Positionsstandpunkt - wo will die Animation als naechstes hin
		AText_ViewPoint								m_eInitNextViewPoint;		// Initialisierter NaechsterPositionstandpunkt Wert

		stVector2Df 								m_v2dfCurrVal;				// Momentaner Wert
		stVector2Df 								m_v2dfCurrValOld;			// Momentaner Wert vom letzten Update
		stVector2Df									m_v2dfBaseVal;				// Basiswert
		stVector2Df									m_v2dfMinVal;				// Minimalwert
		stVector2Df									m_v2dfMaxVal;				// Maximalwert
		stVector2Df									m_v2dfAdjBaseToMin;			// Verrechnungswert vom Basis- zum Minimalwert
		stVector2Df									m_v2dfAdjBaseToMax;			// Verrechnungswert vom Basis- zum Maximalwert
		stVector2Df									m_v2dfAdjMinToMax;			// Verrechnungswert vom Minimal- zum Maximalwert
		stVector2Df									m_v2dfAdjMaxToMin;			// Verrechnungswert vom Maximal- zum Minimalwert
		stVector2Df									m_v2dfAdjCurrToBase;		// Verrechnungswert vom Momentanen zum Basiswert
																				// wird erst verwendet wenn Animation stoppt
																				// und (m_eAniEndStyle == AES_TOBASE) ist

		float										m_fFPS;						// Frames per Second
		float										m_fUpdate;					// Angabe wann ein Update stattfindet
		float										m_fUpdateCounter;			// Zaehler fuer das Updaten

		AniFrameTime								m_strAniFrameTime;			// Struktur der Frameinformationen

		float										m_fAniSpeed;				// Wie schnell soll die Animation laufen (def = 1.0f)
		float										m_fRunTimes;				// Wie viele Male soll animiert werden? (0 = unendlich)
		int											m_iRunTimesCounter;			// Laufzaehler
		bool										m_bEndAfterMaxRunTimes;		// Animation beenden wenn das Maximum 

		//===========================================================================================================
		// Statusvariablen
		//

		bool										m_bIsAnimating;				// Animiert das Detail grade?
		bool										m_bIsLastRun;				// Ist das der Letzte Lauf bevor die Animation stoppt?
		bool										m_bIsAnimatingToBase;		// Animiert grade zum Basiswert
		bool										m_bIsAnimatingToMin;		// Animiert grade zum Minimalwert
		bool										m_bIsAnimatingToMax;		// Animiert grade zum Maximalwert

		//===========================================================================================================
		// Interne Funktionen
		//

		// Funktionen die der Update-funktion assistieren
		//

		// Ueberprueft ob noch ein Animationsdurchlauf stattfinden kann
		// und fuehrt ihn gegebenenfalls aus
		//
		// param1 - erwartet den momentanen Wert
		// param2 - erwartet den Wert, der als "Anfang" dient
		// param3 - erwartet den Wert, der als "Ende" dient
		// param4 - erwartet die aktuelle Zeit
		// param5 - soll die Abfrage (10 > 20) gedreht werden in (10 < 20) ?
		//			Uebepreuft wird folgendes:
		//			Legende: (StartVal = ST | EndVal = EV | VW = Verrechnungswert | AG = Animationsgeschwindigkeit):
		//
		//			- wenn (ST < EV) und ( (ST + VW * fTime) * AG < EV)
		//			ODER
		//			- wenn (ST > EV) und ( (ST + VW * fTime) * AG > EV)
		//
		//			Bei bInvertControl = true wuerde es so aussehen
		//
		//			- wenn (ST > EV) und ( (ST + VW * fTime) * AG < EV)
		//			ODER
		//			- wenn (ST < EV) und ( (ST + VW * fTime) * AG > EV)
		//
		// param6 - erwartet die Animationsgeschwindigkeit (wenn 0 dann wird m_fAniSpeed verwendet)
		//
		// return ST_OK - wenn das Update erfolgreich war
		// return ST_CANCEL - wenn kein weiterer Lauf mehr durchgefuehrt werden kann
		//
		stState										updateMovement(stVector2Df		&vecCurrVal,
																   stVector2Df		&vecStartVal,
																   stVector2Df		&vecEndVal,
																   stVector2Df		&vecAdjVal,
																   AText_ViewPoint	eNextViewPoint,
																   const float		&fTime,
																   bool				bInvertControl = false);

		//--------------------------------------------

		// gibt den errechneten Verrechnungswert zurueck
		// Wenn fAniDuration 0 ist - wird der (this)-Wert genommen
		stVector2Df									calcAdjVal(const	stVector2Df		&preVal, 
															   const	stVector2Df		&secVal, 
																		float			fFrameTime = 0);
		//
		void										copyFrom(stDetail detail);

		//===========================================================================================================
		// Initialmethoden - Konstruktor/Kopierkonstruktor/Destruktor - Initfunktion

		// Nur die Klasse stAnimateText hat die moeglichkeit Details zu erstellen und zu zerstoeren
		// Deswegen werden Konstruktor/Kopierkonstruktor und Destruktor private gesetzt

													stDetail(int iID);
													stDetail(const stDetail& rhs);
													~stDetail();

	//===============================================================================================================
	public:

		// Initialisierung
		//
		// ACHTUNG: Wenn der CurrVal == 0 ist - uebernimmt er den Wert von BaseVal
		// Das dient dazu das Der Wert nicht leer bleibt und das Textobject gerendert werden kann
		stState										Init(int				iID,
														 bool				bAnimate,
														 stVector2Df		v2dfBaseVal,
														 stVector2Df		v2dfMinVal,
														 stVector2Df		v2dfMaxVal,
														 float				fFrameTime,
														 float				fGlobalFrameTime,
														 float				fFPS,
														 float				fAniSpeed);

		//===========================================================================================================
		// Verwaltung

		// Aktualisiert und berechnet die Werte neu
		stState										Update(float fTime);
		
		stState										startAni();			// Startet Animation
		stState										endAni();			// Beendet Animation

		//
		inline stDetail operator= (const stDetail& rhs) { std::cout << "Detail" << std::endl; return *this; }

		//===========================================================================================================
		// Manipulationsmethoden	
		
		//===========================================================================================================
		// add/sub/set/get-Funktionen
		//

		//--------------------------------------------
		// set-FUNKTIONEN
		void										resetCurr();									// Setzt den Momentanen Wert auf den Basiswert

		void										setInitializationState(bool bState);			// definiert ob das Detail initialisiert wurde

		void										setAniPermission(bool bPermission);				// definiert die allgemeine Animationserlaubnis
		void										setAniFrameTime(float fFrameTime);				// definiert die Animationsdauer
		void										setGlobalAniFrameTime(float fFrameTime);		// Hauptanimationsdauer in Frames
		void										setAniSpeed(float fSpeed);						// definiert die Animationsgeschwindigkeit

		void										setCurrVal(stVector2Df vecCurrVal);				// momentanen Wert definieren
		void										setBaseVal(stVector2Df vecBaseVal);				// Basiswert definieren
		void										setMinVal(stVector2Df vecMinVal);				// Minimalwert definieren
		void										setMaxVal(stVector2Df vecMaxVal);				// Maximalwert definieren

		void										setAniRun(bool bPermission);					// definiert die aktuelle Animationserlaubnis
		void										setAniEndStyle(AText_AniEndStyle EndStyle);		// definiert die Art wie das Detail endet wenn es angehalten wird
		void										setAniRunTimes(float fRunTimes);				// definiert wie viele Durchlaeufe die Animations maximal machen soll (0|<0 = unendlig)

		//--------------------------------------------
		// get-FUNKTIONEN
		bool										getGlobalAniPermision()	{	return m_bAnimate; }
		bool										getRunAniPermision()	{	return m_bAnimateMainRun; }
		int											getID()					{	return m_iID; }
		AText_ViewPoint								getLastViewPoint()		{	return m_eLastViewPoint; }
		AText_ViewPoint								getNextViewPoint()		{	return m_eNextViewPoint; }
		AText_AniEndStyle							getAniEndStyle()		{	return m_eAniEndStyle; }
		AniFrameTime								getFrameTime()			{	return m_strAniFrameTime; }
		float										getAniSpeed()			{	return m_fAniSpeed; }

		stVector2Df									getCurrVal()			{	return m_v2dfCurrVal; }
		stVector2Df									getBaseVal()			{	return m_v2dfBaseVal; }
		stVector2Df									getMinVal()				{	return m_v2dfMinVal; }
		stVector2Df									getMaxVal()				{	return m_v2dfMaxVal; }

		int											getNmbOfDetails()		{	return iNumberOfDetails; }

}; // CDetail
//

//_______________________________________________________________________________________________________________