/*******************************************************************************************************************************
	Nutzen:
	animiert eine sf::Text Klasse

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/
//

// header
#include <SimpleTry.h>

//--------------------------------------------
// Definitionen
int stAniLabel::iCounter = 0;

//--------------------------------------------
// Konstruktor
stAniLabel::stAniLabel() :	m_bAnimate				(false),
							m_fFPS					(0.0f),
							m_fFrameTime			(0.0f),
							m_fAniSpeed				(0.0f),
							m_fUpdate				(0.0f),
							m_fUpdateTimer			(0.0f),
							m_fRenderUpdate			(0.0f),
							m_fRenderTimer			(0.0f),
							m_Pos					(new stDetail(10)),
							m_Origin				(new stDetail(20)),
							m_Scale					(new stDetail(30)),
							m_Angle					(new stDetail(40)),
							m_FontSize				(new stDetail(50)),
							m_Red					(new stDetail(60)),
							m_Green					(new stDetail(70)),
							m_Blue					(new stDetail(80)),
							m_Alpha					(new stDetail(90)),
							m_liDetails				(std::list<stDetail*>())
{
	//--------------------------------------------
	// Namensangabe - Wichtig nur fuer die Funktion 'ShowData(...)'
	// Zum ausgeben der Animationsdetails - fuer Testzwecke
	m_Pos->m_sLabel					= "position";
	m_Origin->m_sLabel				= "origin";
	m_Scale->m_sLabel				= "scale";
	m_Angle->m_sLabel				= "rotation";
	m_FontSize->m_sLabel			= "font-size";
	m_Red->m_sLabel					= "red component";
	m_Green->m_sLabel				= "green component";
	m_Blue->m_sLabel				= "blue component";
	m_Alpha->m_sLabel				= "opacity";

	//--------------------------------------------
	// Details in eine Liste fuegen - dadurch ist das definieren und verarbeiten einfacher
	this->m_liDetails.push_back(m_Pos);
	this->m_liDetails.push_back(m_Origin);
	this->m_liDetails.push_back(m_Scale);
	this->m_liDetails.push_back(m_Angle);
	this->m_liDetails.push_back(m_FontSize);
	this->m_liDetails.push_back(m_Red);
	this->m_liDetails.push_back(m_Green);
	this->m_liDetails.push_back(m_Blue);
	this->m_liDetails.push_back(m_Alpha);

	//--------------------------------------------
	// Endgueltige Definition
    setPosition(sf::Vector2f(0.f, 0.f));
    setScale(sf::Vector2f(1.f, 1.f));
    setRotation(0);
	setCharacterSize(0);
    setColor(sf::Color(0, 0, 0, 255));

	// Und eine neue Animationsklasse wurde erschaffen :D
	iCounter++;

} // Konstruktor
//

//--------------------------------------------
// Destruktor
stAniLabel::~stAniLabel()
{
	// Liste leeren
	m_liDetails.clear();

	// Details loeschen
	SAFE_DELETE(m_Pos);
	SAFE_DELETE(m_Scale);
	SAFE_DELETE(m_Scale);
	SAFE_DELETE(m_Angle);
	SAFE_DELETE(m_FontSize);
	SAFE_DELETE(m_Red);
	SAFE_DELETE(m_Green);
	SAFE_DELETE(m_Blue);
	SAFE_DELETE(m_Alpha);

	// Animationszaehler um einen verringern
	iCounter--;

} // Destruktor
//

//--------------------------------------------
// Kopierkonstruktor
stAniLabel::stAniLabel(const stAniLabel& rhs)
{
	//
	this->m_Font				= rhs.m_Font;
	this->setFont(this->m_Font);

	this->m_bAnimate			= rhs.m_bAnimate;
	this->m_fFPS				= rhs.m_fFPS;
	this->m_fFrameTime			= rhs.m_fFrameTime;
	this->m_fAniSpeed			= rhs.m_fAniSpeed;

	this->m_fUpdate				= rhs.m_fUpdate;
	this->m_fUpdateTimer		= rhs.m_fUpdateTimer;
	this->m_fRenderUpdate		= rhs.m_fRenderUpdate;
	this->m_fRenderTimer		= rhs.m_fRenderTimer;

	// Details neu defieren wenn noch nicht geschehen
	m_Pos		= new stDetail(10);
	m_Origin	= new stDetail(20);
	m_Scale		= new stDetail(30);
	m_Angle		= new stDetail(40);
	m_FontSize	= new stDetail(50);
	m_Red		= new stDetail(60);
	m_Green		= new stDetail(70);
	m_Blue		= new stDetail(80);
	m_Alpha		= new stDetail(90);

	this->m_Pos->copyFrom(*rhs.m_Pos);
	this->m_Scale->copyFrom(*rhs.m_Scale);
	this->m_Angle->copyFrom(*rhs.m_Angle);
	this->m_FontSize->copyFrom(*rhs.m_FontSize);
	this->m_Red->copyFrom(*rhs.m_Red);
	this->m_Green->copyFrom(*rhs.m_Green);
	this->m_Blue->copyFrom(*rhs.m_Blue);
	this->m_Alpha->copyFrom(*rhs.m_Alpha);

	this->m_liDetails			= rhs.m_liDetails;
	this->m_itDet				= m_liDetails.begin();

} // Kopierkonstruktor
//

//_______________________________________________________________________________________________________________
// deklariert die Details neu mit (new stDetail)
stState stAniLabel::resetDetList()
{

	//
	return ST_OK;

} // resetDetList
//

//_______________________________________________________________________________________________________________
// Basis Initialisierung
stState stAniLabel::Init(std::string			sText,
							std::string			sFontDataPath,
							bool				bAnimate,
							float				fFPS,
							stVector2Df			vecPosition)
{
	//
	if (!m_Font.loadFromFile(sFontDataPath))
	{
		stLog->writeError("Font konnte nicht geladen werden: Pfad falsch angegeben\?: " + sFontDataPath);
		std::cout << "Schriftart konnte nicht geladen werden!: " << sText << std::endl;

		return ST_FAIL;
	}

	// Definitionen
	this->setFont(m_Font);
	this->setStyle(sf::Text::Regular);
	this->setString(sText);
	this->setPosition(vecPosition.x, vecPosition.y);
	this->setOrigin(this->getPosition().x / 2, this->getPosition().y / 2);
	this->setScale(1.0f, 1.0f);
	this->setRotation(0);
	this->setCharacterSize(16);
	this->setColor(sf::Color(0, 0, 0, 255));

	//
	m_fAniSpeed			= 1.f;
	m_fFrameTime		= 60.f;
	m_fFPS				= fFPS;
	m_fUpdate			= 0.0f;
	m_fRenderUpdate		= 1 / m_fFPS;

	// Details
	//

	// Basiswerte definieren
	m_Pos->m_v2dfBaseVal					= vecPosition;
	m_Origin->m_v2dfBaseVal					= stVector2Df( this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
	m_Scale->m_v2dfBaseVal					= stVector2Df( this->getScale().x, this->getScale().y);
	m_Angle->m_v2dfBaseVal					= stVector2Df( (float) this->getRotation());
	m_FontSize->m_v2dfBaseVal				= stVector2Df( (float) this->getCharacterSize());
	m_Red->m_v2dfBaseVal					= stVector2Df( (float) this->getColor().r );
	m_Green->m_v2dfBaseVal					= stVector2Df( (float) this->getColor().g );
	m_Blue->m_v2dfBaseVal					= stVector2Df( (float) this->getColor().b );
	m_Alpha->m_v2dfBaseVal					= stVector2Df( (float) this->getColor().a );

	// ID-String aufbauen
	std::string sDetailsIds = "";

	sDetailsIds += std::to_string(m_Pos->getID()) + ",";
	sDetailsIds += std::to_string(m_Origin->getID()) + ",";
	sDetailsIds += std::to_string(m_Scale->getID()) + ",";
	sDetailsIds += std::to_string(m_Angle->getID()) + ",";
	sDetailsIds += std::to_string(m_FontSize->getID()) + ",";
	sDetailsIds += std::to_string(m_Red->getID()) + ",";
	sDetailsIds += std::to_string(m_Green->getID()) + ",";
	sDetailsIds += std::to_string(m_Blue->getID()) + ",";
	sDetailsIds += std::to_string(m_Alpha->getID());

	// Animationserlaubnis definieren
	m_bAnimate = bAnimate;

	//-----------
	return ST_OK;

} // Init
//

//_______________________________________________________________________________________________________________
// Funktion zum erstellen eines Details
stState stAniLabel::InitDetail(int				iID,
							   bool				bAnimate,
							   stVector2Df		vecBaseVal,
							   stVector2Df		vecMinVal,
							   stVector2Df		vecMaxVal,
							   float			fAniSpeed,
							   float			fFrameTime)
{

	// Variablen
	std::string sDetailName = "";

	// Iterator der Detailliste setzen
	if (setDetailItor(iID) == ST_NOT_FOUND)		
		return ST_NOT_FOUND;

	// ueberpruefen ob ein detail mit der (ID) bereits manuell initialisiert wurde
	if ( (*m_itDet)->m_bInitialized )
	{
		// Falls ja, soll ueberschrieben werden? (ST_CANCEL) wenn nicht
		if ( !(*m_itDet)->m_bAllwdToBeOvrwrttn)
		{
			stLog->writeWarning("\"Detail (" + std::to_string(iID) + ") konnte nicht ueberschrieben werden:\" Die Rechte zum ueberschreiben fehlen");
			return ST_CANCEL;
		}
	}

	// Detailiterator definieren um die Bezeichnung anzugeben
	if (setDetailItor(iID) == ST_NOT_FOUND)
		return ST_NOT_FOUND;

	// Detail initialisieren
	if ((*m_itDet)->Init(iID,
						 bAnimate,
						 vecBaseVal,
						 vecMinVal,
						 vecMaxVal,
						 fFrameTime,
						 m_fFrameTime,
						 m_fFPS,
						 fAniSpeed) == ST_CANCEL)
	{
		return ST_FAIL;
	}

	//-----------
	return ST_OK;

} // CreateDetail
//

//_______________________________________________________________________________________________________________
// Aktualisierung
stState stAniLabel::Update(float fTime)
{
	// Daten auf evtl. veraenderungen abseits der stDetail Klassen aktualisieren
	this->m_Pos->setCurrVal(stVector2Df(this->getPosition().x, this->getPosition().y));
	this->m_Origin->setCurrVal(stVector2Df(this->getOrigin().x, this->getOrigin().y));
	this->m_Scale->setCurrVal(stVector2Df(this->getScale().x, this->getScale().y));
	this->m_Angle->setCurrVal(stVector2Df(this->getRotation()));
	this->m_FontSize->setCurrVal(stVector2Df( (float) this->getCharacterSize()));
	this->m_Red->setCurrVal(stVector2Df(this->getColor().r));
	this->m_Green->setCurrVal(stVector2Df(this->getColor().g));
	this->m_Blue->setCurrVal(stVector2Df(this->getColor().b));
	this->m_Alpha->setCurrVal(stVector2Df(this->getColor().a));
	
	// Timer hochzaehlen
	m_fUpdateTimer += fTime;

	// solange nicht weiter bis geupdated werden darf
	if ( (!m_bAnimate) || (m_fUpdateTimer < m_fUpdate) )
		return ST_OK;
	else
		m_fUpdateTimer = 0.0f;

	// Details aktualisieren
	for (m_itDet = m_liDetails.begin(); m_itDet != m_liDetails.end(); m_itDet++)
		(*m_itDet)->Update(fTime);
	
	// Definieren
	this->setPosition(m_Pos->getCurrVal().x, m_Pos->getCurrVal().y);
	this->setOrigin(m_Origin->getCurrVal().x, m_Origin->getCurrVal().y);
	this->setScale(m_Scale->getCurrVal().x, m_Scale->getCurrVal().y);
	this->setRotation(m_Angle->getCurrVal().x);
	this->setCharacterSize((UINT) m_FontSize->getCurrVal().x);
	this->setColor(sf::Color((UINT) m_Red->getCurrVal().x,
							 (UINT) m_Green->getCurrVal().x,
							 (UINT) m_Blue->getCurrVal().x,
							 (UINT) m_Alpha->getCurrVal().x));

	//-----------
	return ST_OK;

} // Update
//

//_______________________________________________________________________________________________________________
// Zeichnet den Text auf den Bildschirm
stState stAniLabel::Render(sf::RenderWindow &window, float fTime)
{
	// sich selbst rendern
	window.draw(*this);

	//-----------
	return ST_OK;

} // Render
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
// startet die Animation
stState stAniLabel::startAnimation(std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::startAni, sIdList) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // startAnimation
//

//_______________________________________________________________________________________________________________
// endet die Animation
stState stAniLabel::endAnimation(std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::endAni, sIdList) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // endAnimation
//

//_______________________________________________________________________________________________________________
// Setzt den Status des gesuchten Details auf nicht vorhanden.
// die Funktion entfernt das Detail nicht in dem Sinne das sie es loescht sondern einfach nur
// nicht existent macht und somit unbrauchbar bis man es neu initialisiert
stState stAniLabel::resetDetail(std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::setInitializationState, sIdList, false) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // Remove
//

//_______________________________________________________________________________________________________________
// Setzt die BaseVals der gesuchten Details auf die Momentanen Werte von (*this)
stState stAniLabel::resetCurrVal(std::string sIdList)
{			
	//
	if (callDetFunc(&stDetail::resetCurr, sIdList) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;
	
} // ResetBaseVals
//

//_______________________________________________________________________________________________________________
// kopiert das Detail mit der id (iID) und uberschreibt (wenn erlaubt) die Details
// die in sIdList als String, kommaseperiert aufgefuehrt sind
stState stAniLabel::copyDet(int iID, std::string sIdList)
{
	// Detail suchen
	if (setDetailItor(iID) == ST_NOT_FOUND)
		return ST_NOT_FOUND;

	// wenn Detail gesetzt wurde
	if (callDetFunc(&stDetail::copyFrom, sIdList, *(*m_itDet)) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // copyDet
//

//_______________________________________________________________________________________________________________
// kopiert rhs in (this) Klasse
stState stAniLabel::copyFrom(stAniLabel rhs)
{
	//
	this->m_Font				= rhs.m_Font;
	this->setFont(this->m_Font);

	this->m_bAnimate			= rhs.m_bAnimate;
	this->m_fFPS				= rhs.m_fFPS;
	this->m_fFrameTime			= rhs.m_fFrameTime;
	this->m_fAniSpeed			= rhs.m_fAniSpeed;

	this->m_fUpdate				= rhs.m_fUpdate;
	this->m_fUpdateTimer		= rhs.m_fUpdateTimer;
	this->m_fRenderUpdate		= rhs.m_fRenderUpdate;
	this->m_fRenderTimer		= rhs.m_fRenderTimer;

	// Details neu defieren wenn noch nicht geschehen
	m_Pos		= new stDetail(10);
	m_Origin	= new stDetail(20);
	m_Scale		= new stDetail(30);
	m_Angle		= new stDetail(40);
	m_FontSize	= new stDetail(50);
	m_Red		= new stDetail(60);
	m_Green		= new stDetail(70);
	m_Blue		= new stDetail(80);
	m_Alpha		= new stDetail(90);

	this->m_Pos->copyFrom(*rhs.m_Pos);
	this->m_Scale->copyFrom(*rhs.m_Scale);
	this->m_Angle->copyFrom(*rhs.m_Angle);
	this->m_FontSize->copyFrom(*rhs.m_FontSize);
	this->m_Red->copyFrom(*rhs.m_Red);
	this->m_Green->copyFrom(*rhs.m_Green);
	this->m_Blue->copyFrom(*rhs.m_Blue);
	this->m_Alpha->copyFrom(*rhs.m_Alpha);

	this->m_liDetails			= rhs.m_liDetails;
	this->m_itDet				= m_liDetails.begin();

	//-----------
	return ST_OK;

} // copyFrom
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
// definiert die globale Aminationserlaubnis
void stAniLabel::setGlobalAniPerm(const bool bPermission)
{
	// 
	m_bAnimate = bPermission;

} // setGlobalAniPerm
//

//_______________________________________________________________________________________________________________
// definiert die globale Animationsdauer
bool stAniLabel::setGlobalFrameTime(const float fFrameTime)
{
	// die Zeit sollte nicht unter null sein
	if (fFrameTime < 0)
	{
		// Falls doch - korrigieren
		m_fFrameTime = 0.f;
		return true;
	}

	m_fFrameTime = fFrameTime;

	//----------
	return true;

} // setGlobalFrameTime
//

//_______________________________________________________________________________________________________________
// definiert die globale Animationsgeschwindigkeit
bool stAniLabel::setGlobalAniSpeed(float fAniSpeed)
{
	// Geschwindigkeit sollte nicht unter 0 sein
	if (fAniSpeed < 0)
	{
		// andernfalls korrigieren
		m_fAniSpeed = 0.f;
		return true;
	}

	m_fAniSpeed = fAniSpeed;

	//----------
	return true;

} // setGlobalAniSpeed
//

//_______________________________________________________________________________________________________________
// Erlauben oder verbieten zu animieren
stState stAniLabel::setAniPermission(bool bPermission, std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::setAniPermission, sIdList, bPermission) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // setAniPermission
//

//_______________________________________________________________________________________________________________
// Animationsende (neu)definieren
stState stAniLabel::setAniEndStyle(AText_AniEndStyle eStyle, std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::setAniEndStyle, sIdList, eStyle) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // setAniEndStyle
//

//_______________________________________________________________________________________________________________
// Definiert die Animationsdauer neu
stState stAniLabel::setFrameTime(float fFrameTime, std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::setAniFrameTime, sIdList, fFrameTime) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // setFrameDuration
//
//_______________________________________________________________________________________________________________

// definiert die Anzahl an Durchlauefen die die Animations machen soll (0|<0 = unendlig
stState stAniLabel::setAniRunTimes(float fRunTimes, std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::setAniRunTimes, sIdList, fRunTimes) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} //
//

//_______________________________________________________________________________________________________________
// Definiert den Basiswert neu
stState stAniLabel::setCurrVal(stVector2Df &vecCurrVal, std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::setCurrVal, sIdList, vecCurrVal) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // setBaseVal
//

//_______________________________________________________________________________________________________________
// Definiert den Basiswert neu
stState stAniLabel::setBaseVal(stVector2Df &vecBaseVal, std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::setBaseVal, sIdList, vecBaseVal) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // setBaseVal
//

//_______________________________________________________________________________________________________________
// Definiert den Minimalwert neu
stState stAniLabel::setMinVal(stVector2Df &vecMinVal, std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::setMinVal, sIdList, vecMinVal) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // setMinVal
//

//_______________________________________________________________________________________________________________
// Definiert den Maximalwert neu
stState stAniLabel::setMaxVal(stVector2Df &vecMaxVal, std::string sIdList)
{
	//
	if (callDetFunc(&stDetail::setMaxVal, sIdList, vecMaxVal) == ST_INCORRECT)
		return ST_INCORRECT;

	//-----------
	return ST_OK;

} // setMaxVal
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

//_______________________________________________________________________________________________________________
// setzt den Iterator der ID - wenn eine Ubereinstimmung gefunden wurde
stState stAniLabel::setDetailItor(unsigned short ID)
{
	// Nach der ID suchen - wenn die Schleife durchlaeuft wurde nichts gefunden
	for (m_itDet = m_liDetails.begin(); m_itDet != m_liDetails.end(); m_itDet++)
	{
		if ( (*m_itDet)->getID() == ID)
			return ST_OK;
	}

	//------------------
	return ST_NOT_FOUND;

} // SetList
//

