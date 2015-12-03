/*******************************************************************************************************************************
	Nutzen/Aufgabe:
	Erstellung und Verwaltung eines regulaeren Buttons

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/

//
// header
#include "stButton.h"

//--------------------------------------------
// Definitionen
int CButton::m_iCounter = 0;

//--------------------------------------------
// Konsturktor
CButton::CButton()	:	m_vecfPos			(stVector2Df(0.0f)),
						m_Label				(stAniLabel()),
						m_Background		(stAniTex()),
						m_Hitbox			(sf::IntRect()),
						m_bEnabled			(false),
						m_bVisible			(false),
						m_bSelectable		(false)
{
	//


} // Konstruktor
//

//--------------------------------------------
// Desturktor
CButton::~CButton()
{
	/* ... */

} // Destruktor
//

//_______________________________________________________________________________________________________________
// Initialisierung
stState CButton::Init(stVector2Df vecPos, std::string sBgPath)
{
	//
	if (sBgPath.empty())
		return ST_NOT_FOUND;

	// Definitionen
	m_vecfPos	= vecPos;									 	// Position
	m_Hitbox	= sf::IntRect(0, 50, 50, 20);					// Hitbox

	// Hintergrund
	if (sBgPath.empty())
		return ST_NOT_FOUND;
	else
	{
	}

	//-----------
	return ST_OK;

} // Init
//

//_______________________________________________________________________________________________________________
// Aktualisiert den Button
stState CButton::Update(float fTime)
{
	// Wenn nicht aktiv dann gar nicht erst durchlaufen
	if (!m_bEnabled)
		return ST_OK;

	// Klassen aktualisieren
	m_Label.Update(fTime);




	//-----------
	return ST_OK;

} // Update
//

//_______________________________________________________________________________________________________________
// Rendering
stState CButton::Render(sf::RenderWindow& sfWindow)
{
	// Rendering
	// Nur rendern wenn er sichtbar Und aktiv ist

	if ( (m_bEnabled) && (m_bVisible) )
	{
		sfWindow.draw(m_Label);
	}

	//-----------
	return ST_OK;

} // Rendering
//

//_______________________________________________________________________________________________________________
// definiert die Position des Buttons
void CButton::setPos(stVector2Df vecPos)
{
	//
	m_vecfPos = vecPos;

} // setPos
//

//_______________________________________________________________________________________________________________
// definiert die Verwendbarkeit des Button
void CButton::setEnabled(bool bState)
{
	//
	m_bEnabled = bState;

} // setEnabled
//

//_______________________________________________________________________________________________________________
// definiert die Sichtbarkeit des Buttons
void CButton::setVisibility(bool bState)
{
	//
	m_bVisible = bState;

} // setVisibility
//

//_______________________________________________________________________________________________________________
// definiert den Status ob dieser Button selektiert wurde
void CButton::setSelected(bool bState)
{
	//
	m_bSelected = bState;

} // setSelected
//

//_______________________________________________________________________________________________________________
// definiert ob dieser Button Selektiert werden darf
void CButton::setselectability(bool bState)
{
	//
	m_bSelectable = bState;

} // setSelectability
//

//_______________________________________________________________________________________________________________