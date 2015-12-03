/*******************************************************************************************************************************
	Nutzen/Aufgabe:
	Erstellung und Verwaltung eines regulaeren Buttons

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/

//
#pragma once
//

//_______________________________________________________________________________________________________________
// header
#include <SimpleTry.h>

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






// Klassendeklarationen und Definitionen
class CButton
{
	//===============================================================================================================
	private:
	
		//===========================================================================================================
		// Basisvariablen
		//

		static int										m_iCounter;											// globaler Zaehler der Buttonklasse

		stVector2Df										m_vecfPos;											// Position des Buttons
		stAniLabel										m_Label;											// Schriftzug
		stAniTex										m_Background;										// Hintergrund
		sf::IntRect										m_Hitbox;											// Hitbox
		
		//===========================================================================================================
		// Statusvariablen
		//
		bool											m_bEnabled;											// definiert ob dieser Button aktiv ist
		bool											m_bVisible;											// definiert ob dieser Button sichtbar ist
		bool											m_bSelected;										// definiert ob dieser Button selektiert wurde
		bool											m_bSelectable;										// definiert ob dieser Button selektiertbar ist

	//===============================================================================================================
	public:
		
		//===========================================================================================================
		// Initialmethoden - Konstruktor/Kopierkonstruktor/Destruktor - Initfunktion
		//
														CButton();
														~CButton();
		
		// Initialisierung des Buttons
		stState											Init(stVector2Df		vecPos,
															 std::string		sBgPath);

		//===========================================================================================================
		// Verwaltung
		//

		// Aktualisiert den Button
		stState											Update(float fTime);
		
		// Rendert den Button
		stState											Render(sf::RenderWindow& sfWindow);

		//===========================================================================================================
		// Manipulationsmethoden	
		
		//===========================================================================================================
		// set-Funktionen
		//
		void											setPos(stVector2Df vecPos);							// definiert die Position dieses Buttons
		void											setEnabled(bool bState);							// definiert ob dieser Button verwendet werden darf
		void											setVisibility(bool bState);							// definiert ob dieser Button sichtbar ist
		void											setSelected(bool bState);							// definiert ob dieser Button selektiert wurde
		void											setselectability(bool bState);						// definiert ob dieser Button selektierbar ist

		//===========================================================================================================
		// get-Funktionen
		//
		stVector2Df										getPos()				{ return m_vecfPos; }					// return Position des Buttons
		stAniLabel										getLabel()				{ return m_Label; }						// return Schriftzug
		stAniTex										getBackground()			{ return m_Background; }				// return Hintergrund
		sf::Sprite										getSprite()				{ return m_Background.getSprite(); }	// return Sprite

		bool											getEnabled()			{ return m_bEnabled; }					// return aktuelle Verwendbarkeit des Buttons
		bool											getVisibilty()			{ return m_bVisible; }					// return aktuelle Sichtbarkeit
		bool											getSelected()			{ return m_bSelected; }					// return den aktuellen Status der Selektierbarkeit




}; // CButton
//

