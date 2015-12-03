/*******************************************************************************************************************************

		Nutzen:
		Animiert ein sf::Text

	//--------------------------------------------------------------------------------------------------------------------------
		Alle Kommentare dieser Klasse sind so ausgedrueck worden, so dass der Sinn ruebergebracht werden soll, nicht in logischer Weise

	//--------------------------------------------------------------------------------------------------------------------------
		Reihenfolge um eine Animations erfolgreich zu erreichen

		1. CAnimateText Instanz erzeugen und initialisieren (Init Funktion ist gegeben) z.B. "CAT"
		2. CreateDetail Funktion verwenden um ein Detail zu initialisieren
			- Funktion erfolgt erst wenn die "CAT" initialisiert wurde
			- Eine liste aller ID's ist weiter unten zu finden

		Die Details sind in ID eingeteilt die unten aufgelistet werden.

	//--------------------------------------------------------------------------------------------------------------------------
		ID's
				(x)		= Alle			
				(x) 	= Position						// vektor Detail
				(x) 	= Skalierung					// vektor Detail
				(x) 	= Rotation						// vektor Detail (range 0-360)
				(x) 	= Schriftgroesse				// vektor Detail
				(x) 	= Roter Farbanteil				// vektor Detail (range 0-255)
				(x) 	= Gruener Farbanteil			// vektor Detail (range 0-255)
				(x) 	= Blauer Farbanteil				// vektor Detail (range 0-255)
				(x) 	= Transparenz					// vektor Detail (range 0-255)

	//--------------------------------------------------------------------------------------------------------------------------
		Beschreibung der wichtigsten Variablen: (präfixe werden aufgelassen!)

		Animate						- Wird (dieses Detail) animiert?
		BaseVal						- Der Basiswert. An dem 'Punkt' startet die Animation mit ihren
		MinVal						- Minimaler Wert
		MaxVal						- Maximaler Wert
		FrameDuration				- Zeit die das Detail benötigt um eine halbe Animation durchzuführen
		
	//--------------------------------------------------------------------------------------------------------------------------
		Autor:
		Alexander Bassov

*******************************************************************************************************************************/

//
#pragma once
//

//_______________________________________________________________________________________________________________
// header
#include "stDetail.h"

//_______________________________________________________________________________________________________________
// Makros/Defines
/* ... */

//_______________________________________________________________________________________________________________
// globale Variablen/Externe Deklarationen
/* ... */

//_______________________________________________________________________________________________________________
// Vorwaertsdeklarationen
class stDetail;
enum AL_AniEndStyle;

//_______________________________________________________________________________________________________________
// Strukturen/enums/etc.
/* ... */





//_______________________________________________________________________________________________________________
// Klasse
class stAniLabel : public sf::Text
{
	//===============================================================================================================
	public:

		sf::Font								m_Font;								// Schriftart

	//===============================================================================================================
	private:
				
		//===============================================================================================================
		// Allgemeine Variablen
		static int								iCounter;							// zaehlt wie viele Inztanzen existieren

		bool									m_bAnimate;							// globale Animationserlaubnis
																					// Ist diese Wert false - macht es kein Unterschied mehr ob ein Detail sein m_bAnimate
																					// auf true hat - Es wird nichts animiert
		float									m_fFPS;								// Frames per Second - Selbsterklärend
		float									m_fFrameTime;						// globale Framezeit in der Einheit Frames !!
																					// Anders als bei Details - Dort ist die Einheit %
																					// Heißt bei einer globalen Framezeit von 60 Frames.
																					// Hat das Detail mit 50.00% eine Framezeit von 30 Frames. Also halb so schnell
																					// Ebenso funktioniert das mit 200.00% Dann ist das Detail mit diesem Wert doppelt so schnell

		float									m_fAniSpeed;						// Hauptwert für die Animationsgeschwindigkeit

		float									m_fUpdate;							// Wann ein Update stattfindet
		float									m_fUpdateTimer;						// Updatetimer
		float									m_fRenderUpdate;					// Wann ein Rendervorgang stattfindet
		float									m_fRenderTimer;						// Rendertimer

		// Details oeffentlich gestellt damit man die Funktionen der einzelnen Details nutzen kann
		// und somit unnoetigen Code umgeht
		stDetail*								m_Pos;								// Positionsinfo
		stDetail*								m_Origin;							// Zentralpunktinfo
		stDetail*								m_Scale;							// Skalierungsinfo
		stDetail*								m_Angle;							// Rotationsinfo
		stDetail*								m_FontSize;							// Schriftgroesse
		stDetail*								m_Red;								// Rotanteilinfo
		stDetail*								m_Green;							// Gruenanteilinfo
		stDetail*								m_Blue;								// Blauanteilinfo
		stDetail*								m_Alpha;							// Durchsichtigkeitsinfo
		
		//===============================================================================================================
		// Liste der Animationsdetails
		std::list<stDetail*>					m_liDetails;						// Liste aller Details
		std::list<stDetail*>::iterator		    m_itDet;							// Iterator

		//===============================================================================================================
		// interne Funktionen
		//

		// Leert die aktuelle Liste der Details und fuegt die aktuellen Details neu ein
		stState									resetDetList();

		// durchlaeuft die Details und ruft die uebergebene Funktion samt des Parameters auf welcher uebergeben wurde
		// Templatefunktion um die Durchlaeufe der Details auf die Funktionen die angefragt worden sind zu vereinfachen
		//
		// 2 Ueberladene Funktionen. Eine ohne Parameterliste - die andere mit
		template<class T>
		stState									callDetFunc(T				(stDetail::*pFunc)(),
															std::string		sIdList);

		template<class T, class U>
		stState									callDetFunc(T				(stDetail::*pFunc)(U),
															std::string		sIdList,
															U				tValue);

	//===============================================================================================================
	public:

		
		

		
		//===========================================================================================================
															stAniLabel();
															~stAniLabel();
															stAniLabel (const stAniLabel& rhs);
        
        //===========================================================================================================
        // Initialisierung
        //

		// Basisinformationen initialisieren
		//
		// param1 - erwartet einen String der als Text dargestellt wird
		// param2 - erwartet den Pfad zur Schriftart
		stState												Init		(std::string			sText,								// String
																		 std::string 			sFontDataPath,						// Schriftart (Pfad)
																		 bool					bAnimate	= false,				// Soll der Text animiert werden?
																		 float					fFPS		= 60,					// Frames per Second
																		 stVector2Df			vecPosition = stVector2Df(0.0f));	// Position

		//===========================================================================================================
		// Ein Detail erstellen und einspeichern - Gibt (ST_CANCEL) zurueck wenn die ID bereits vorhanden ist
		// Und das Detail nicht ueberschrieben werden darf
		//
		// Wenn ein Wert == 0 oder (empty()) dann werden die initialisierten Werte verwendet
		// Ausnahmen sind folgende: ID
		stState												InitDetail(int					ID,													// ID des details | IDs in der Datei definiert
																	   bool					bAnimate			= true,							// Soll das detail animiert werden?
																	   stVector2Df			vecBaseVal			= stVector2Df(1.f),				// Basiswert
																	   stVector2Df			vecMinVal			= stVector2Df(1.f),				// Minimalwert
																	   stVector2Df			vecMaxVal			= stVector2Df(1.f),				// Maximalwert
																	   float				fAniSpeed			= 1.f,							// Animationsgeschwindigkeit
																	   float				fFrameTime			= 100.f);						// Animationsdauer (in Prozent)

		//===========================================================================================================
		// Aktualisieren
		stState												Update(float fTime);

		// Rendern
		stState												Render(sf::RenderWindow &window, float fTime);
		
		//===========================================================================================================
		// Verwaltungsfunktionen
		stState												startAnimation(std::string sIdList);						// startet die Animation 
		stState												endAnimation(std::string sIdList);							// beendet die Animation
		stState												resetDetail(std::string sIdList);
		stState												resetCurrVal(std::string sIdList);							// Setzt die CurrWerte des Details auf das gezeigt wird auf BaseVals Wert

		// kopiert das Detail mit der id (iID) und uberschreibt (wenn erlaubt) die Details
		// die in sIdList als String, kommaseperiert aufgefuehrt sind
		stState												copyDet(int iID, std::string sIdList);


		// kopiert rhs in (this) Klasse
		stState												copyFrom(stAniLabel rhs);

		//===========================================================================================================
		// set-Funktionen

		void												setGlobalAniPerm(bool bPermission);							// Globale Animationserlaubnis
		bool												setGlobalFrameTime(float fFrameTime);						// Globale Animationsdauer
		bool												setGlobalFPS(float fFPS);									// Globale Anzahl an Frames dieser Klasse
		bool												setGlobalAniSpeed(float fAniSpeed);							// Globale Animationsgeschwindigkeit

		stState												setAniPermission (bool bPermission, std::string sIdList);
		stState												setAniEndStyle (AText_AniEndStyle eStyle, std::string sIdList);
		stState												setFrameTime (float fFrameTime, std::string sIdList);
		stState												setAniRunTimes(float fRunTimes, std::string sIdList);
		stState												setCurrVal (stVector2Df& vecCurrVal, std::string sIdList);
		stState												setBaseVal (stVector2Df& vecBaseVal, std::string sIdList);
		stState												setMinVal (stVector2Df& vecMinVal, std::string sIdList);
		stState												setMaxVal (stVector2Df& vecMaxVal, std::string sIdList);

		//===============================================================================================================
		// get-Funktionen
		bool												getGlobalAniPermission()			{ return m_bAnimate; }
		float												getGlobalFrameTime()				{ return m_fFrameTime; }
		float												getGlobalAniSpeed()					{ return m_fAniSpeed; }

		bool												getDetAniPermission(int ID);
		stVector2Df											getAniEndStyle(int ID);
		stVector2Df											getFrameTime(int ID);
		stVector2Df											getBaseVal(int ID);
		stVector2Df											getMinVal(int ID);
		stVector2Df											getMaxVal(int ID);

		std::list<stDetail*>								getDetList()			{ return m_liDetails; }
		stDetail*											getDetPos()				{ return m_Pos; }
		stDetail*											getDetOrigin()			{ return m_Origin; }
		stDetail*											getDetScale()			{ return m_Scale; }
		stDetail*											getDetAngle()			{ return m_Angle; }
		stDetail*											getDetFontSize()		{ return m_FontSize; }
		stDetail*											getDetRed()				{ return m_Red; }
		stDetail*											getDetGreen()			{ return m_Green; }
		stDetail*											getDetBlue()			{ return m_Blue; }
		stDetail*											getDetAlpha()			{ return m_Alpha; }

	//***************************************************************************************************************
	// interne Funktinoen
	private: 
	
	
		//===========================================================================================================
		// setzt den Iterator der Detailsliste auf das detail mit der uebergebenen ID. ueberprueft 
		// ob die ID gueltig ist. Wenn nicht dann gibt die Funktion 
		//
		// param1	- erwartet die ID des Details welches in den Klasseniterator geladen werden soll
		//
		// return ST_OK			- wenn das Detail mit der passenden ID gefunden und der Iterator definiert wurde
		// return ST_NOT_FOUND	- wenn die ID keinem Detail zugewiesen werden konnte
		//
		stState												setDetailItor(unsigned short ID);

}; // AnimateText
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
//
template<class T, class U>
stState	stAniLabel::callDetFunc( T(stDetail::*pFunc)(U), std::string sIdList, U tValue)
{
	//
	std::list<float> liIDList = stExplodeList(sIdList, ',');

	//
	for(std::list<float>::iterator itorIdList = liIDList.begin(); itorIdList != liIDList.end(); itorIdList++)
	{
		if (setDetailItor( (USHORT) *itorIdList) == ST_NOT_FOUND)
		{
			stLog->writeWarning("Detail: " + std::to_string(*itorIdList) + " konnte nicht zugeordnet werden");
			return ST_INCORRECT;
		}
		else
			((*m_itDet)->*pFunc)(tValue);
	}

	//-----------
	return ST_OK;

} // callDetFunc
//


//_______________________________________________________________________________________________________________
// Diese Funktion dient als referenz zu der anderen um Code zu sparen da die beiden Funktionen
// derselben Logik folgen bis auf die Parameteruebergabe
template<class T>
stState stAniLabel::callDetFunc( T(stDetail::*pFunc)(), std::string sIdList)
{
	//
	std::list<float> liIDList = stExplodeList(sIdList, ',');

	//
	for(std::list<float>::iterator itorIdList = liIDList.begin(); itorIdList != liIDList.end(); itorIdList++)
	{
		if (setDetailItor( (USHORT) *itorIdList) == ST_NOT_FOUND)
		{
			stLog->writeWarning("Detail: " + std::to_string(*itorIdList) + " konnte nicht zugeordnet werden");
			return ST_INCORRECT;
		}
		else
			((*m_itDet)->*pFunc)();
	}

	//-----------
	return ST_OK;

} // setDetVal
//

//_______________________________________________________________________________________________________________