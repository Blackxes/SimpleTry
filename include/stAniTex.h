/*******************************************************************************************************************************
	Nutzen:
	animiert Bilder indem die Klasse Teilframes aus kompletten Bilder herausrendert.

	Es wird empfohlen horizontale Animationen zu weahlen. Diese Klasse ist darauf ausgelegt
	horizontale Animation als Standardwert zu verwenden.
	Dennoch sind vertikale ebenfalls verwendbar und funktionieren genauso gut wie die horizontalen Animationen.
	Ist ein wenig mehr parameter Zugabe noetig.

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

//--------------------------------------------
// Animationslaufrichtung
enum ATexture_FrameRunDirection
{
	//
	FRD_NONE,
	FRD_VERTICALLY,
	FRD_HORIZONTALLY,
	FRD_COUNTER,
};

//--------------------------------------------
// Akzeptierte Bildformate
enum ImgType
{
	//
	IT_NONE,
	IT_BMP,
	IT_PNG,
	IT_TGA,
	IT_JPG,
	IT_JPEG,
	IT_GIF,
	IT_PSD,
	IT_HDR,
	IT_PIC,
	IT_COUNTER,
};

//--------------------------------------------
// Endanimationsstil wenn die Animation gestoppt wird
enum ATexure_AniEndStyle
{
	//
	TEX_AES_NONE,			// Keine Endanimations
	TEX_AES_INSTANT,		// Bei dem aktuellen Frame "stehen bleiben"
	TEX_AES_TOEND,			// Zum letzten Frame der aktuellen Zeile/Spalte
	TEX_AES_TOBEGIN,		// Zurueck zum ersten Frame der aktuellen Zeile/Spalte 
							// oder, abhaengig von der Konfiguration, zum ersten Frame der ersten (Spalte/Zeile)
	TEX_AES_COUNTER,		// Zaehler
};


//--------------------------------------------
// Struktur des Animationsbefehls
struct CallAnimation
{
	//
	std::string		iAnimationName;			// Animationsname
	int				iFrame;					// Animationslinie
	bool			bXAxisFrameRun;			// horizontaler Lauf?
	bool			bYAxisFrameRun;			// vertikaler Lauf?

}; // CallAnimation
//





// Klassendeklarationen und Definitionen
class stAniTex : public sf::Sprite
{
	
	//===============================================================================================================
	private:
		
		//
		bool											m_bAnimate;						// allgemeine Animationserlaubnis
		bool											m_bAnimateRun;					// Aktuelle Animationserlaubnis
																						// Bei false springen die Endanimationen ein
		
		stFileinfo										m_Fileinfo;						// Dateiinformationssammlung

		stVector2Df										m_vecfPos;						// Position

		stVector2Db										m_vecbLineSwitch;				// definiert ob nach dem erreichen des letzten Frame der aktuellen
																						// Achse (X/Y) die zu der betroffenen Achse die querliegende aufzaehlt
																						// Beispiel: 
																						// XMax = 3
																						// X = 3
																						// Y = 1
																						//
																						// if (X >= Max)
																						//	Y++
																						// Y Wert betraegt 2

		stVector2Db										m_vecbJumpToBegin;				// definiert ob nach erreichen der letzten Achsen (X/Y)
																						// zurueck zu den jeweiligen Anfaengen gesprungen wird
																						// row3 -> row1 / column7 -> column1

		stVector2Db										m_vecbJumpToBeginFrame;			// definiert ob nach erreichen des Framezaehlerlimits
																						// der aktuellen Achse (X/Y) zurueck zum Zaehlerbegin
																						// gesprungen wird
																						// X4 -> X1 / Y5 -> Y1

		stVector2Db										m_bSwapDirecWhenAxEnd;			// Wenn die betroffene Achse true ist (X/Y)
																						// wechselt sie die Animationsrichtung (forward/backwards)

		ATexure_AniEndStyle								m_eAniEndStyle;					// Animationsendungsart
		ATexture_FrameRunDirection						m_eFramedirection;				// Laufrichtung der Animation
		
		float											m_fUpdateTimer;					// Timer fuer das Update
		float											m_fUpdateTimerCap;				// Zeitcap ab wann ein Update stattfindet
		int												m_iFPS;							// Frames per Second
		float											m_fAniSpeed;					// Animationsgeschwindigkeit

		stVector2Df										m_vecfTexSize;					// Texturebreite- und Hoehe
		stVector2Df										m_vecfFrames;					// Frames auf der X/Y Achse
		int												m_iFrameTop;					// Abstand oben
		int												m_iFrameLeft;					// Abstand links
		int												m_iFrameWidth;					// Framebreite
		int												m_iFrameHeight;					// Framehoehe

		stVector2Df										m_vecfActiveFrame;				// Aktiver Frame auf X/Y

		sf::Texture										m_Texture;						// Animationsbild
		sf::Sprite										m_Sprite;						// Sprite zur Textur

		sf::RectangleShape								m_BackupShape;					// Ersatzform fuer nicht erkannte Texturen


		// Liste fuer die Animationsnamen
		std::list<CallAnimation>						m_liAnimations;					// Animationsliste
		std::list<CallAnimation>::iterator				m_itorAnimations;				// Iterator


		//===========================================================================================================
		// Statusvariablen	
		//
		bool											m_bBlockAniPermission;			// blockiert das starten der Animation

		//===========================================================================================================
		// Interne Funktionen
		//

		// Aktualisiert den aktuellen Frame auf Basis der Parameter
		//
		// 
		bool											updateFrame();
	
	//===============================================================================================================
	public:

														// Konstruktor - Destruktor - Kopierkonstruktor
														stAniTex();
														~stAniTex();
														stAniTex(const stAniTex &rhs);

		//===========================================================================================================
		// Initialmethoden - Konstruktor/Kopierkonstruktor/Destruktor - Initfunktion
		//

		// Initialisierung
		//
		// param1	- sFileName - erwartet den Dateinamen der Texture
		// param2	- bAnimate - erwartet 
		//
		// return ST_OK - wenn die Initialisierung erfolgreich war
		// return ST_NOT_FOUND - wenn die Datei nicht gefunden wurde
		stState											Init(std::string	sFilename,
															 bool			bAnimate = false);

		// Aktualisiert die allgemeinen Daten der Animation
		//
		// param1	- fTime - erwartet die vergangene Zeit
		// param2	- fPosX - erwartet die X-Position der Texture
		// param3	- fPoxY - erwartet die Y-Position der Texture
		// param4	- fAngle - erwartet den Winkel der Texture
		stState											Update(float		fTime, 
															   stVector2Df	vecPos = stVector2Df(0.0f),
															   float		fAngle = 0.0f);

		// rendert die Texture
		//
		// param1 - erwartet das Renderfenster vom sfml
		stState											Render(sf::RenderWindow &window);

		//===========================================================================================================
		// Verwaltung
		// 

		// Diese Funktion erstellt ein Animationslauf der in m_liAnimation gespeichert wird. 
		// Dieser Animationslauf kann mit "CallAnimation" und dem entsprechenden Namen "gerufen" werden
		//
		// param1 - erwartet den Namen des Befehls
		// param2 - erwartet 
		//
		// return ST_OK - wenn das hinzufuegen erfolgreich war
		// return ST_FAIL - wenn Animationsname leer oder iFrame <= 0
		stState											AddAnimationToList(std::string					sAniName,
																		   int							iFrame,
																		   ATexture_FrameRunDirection	m_RunDirection = ATexture_FrameRunDirection::FRD_HORIZONTALLY);

		// "ruft" einen Animationslauf aus der Liste auf
		//
		// param1 - Name des Animationslaufs
		//
		// return ST_OK - wenn Animation gefunden und ausgefuehrt wurde. 
		// return ST_NOT_FOUND - wenn Animation nicht gefunden wurde
		// Die Animationsrichtung wird aus der Klasse uebernommen
		stState											CallAnimation(std::string AniName);

		//===========================================================================================================
		// add/sub/set/get-Funktionen
		//

		// Sprite der Animation
		sf::Sprite										getSprite()					{ return m_Sprite; };

		//===========================================================================================================
		// Operatoren
		void											stAniTex::operator= (const stAniTex &rhs);		// operator =
		
	
	
	//===============================================================================================================
	// FUNKTIONEN
		
		
		
		
		
		//===========================================================================================================
		// Manipulationsmethoden	
		
		

	//

}; // stAnimateTexture
//

//_______________________________________________________________________________________________________________