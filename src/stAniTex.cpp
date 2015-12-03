/*******************************************************************************************************************************
Nutzen:
animiert frames

Autor:
Alexander Bassov
*******************************************************************************************************************************/


// header
#include <SimpleTry.h>

//--------------------------------------------
// Konstruktor
stAniTex::stAniTex() :	m_bAnimate					(false),
						m_bAnimateRun				(false),
						m_Fileinfo					(stFileinfo()),
						m_vecfPos					(stVector2Df(0.0f)),
						m_vecbLineSwitch			(stVector2Db(false)),
						m_vecbJumpToBegin			(stVector2Db(false)),
						m_vecbJumpToBeginFrame		(stVector2Db(false)),
						m_bSwapDirecWhenAxEnd		(false),
						m_eAniEndStyle				(ATexure_AniEndStyle::TEX_AES_NONE),
						m_eFramedirection			(ATexture_FrameRunDirection::FRD_NONE),
						m_fUpdateTimer				(0.0f),
						m_fUpdateTimerCap			(0.0f),
						m_iFPS						(0),
						m_fAniSpeed					(0.0f),
						m_vecfTexSize				(stVector2Df(0.0f)),
						m_vecfFrames				(stVector2Df(0.0f)),
						m_iFrameTop					(0),
						m_iFrameLeft				(0),
						m_iFrameWidth				(0),
						m_iFrameHeight				(0),
						m_vecfActiveFrame			(stVector2Df(0.0f)),
						m_Texture					(sf::Texture()),
						m_Sprite					(sf::Sprite()),
						m_BackupShape				(sf::RectangleShape()),
						m_liAnimations				(std::list<struct CallAnimation>()),
						m_itorAnimations			(std::list<struct CallAnimation>::iterator()),
						m_bBlockAniPermission		(true)
{
	/* ... */

} // Konstruktor
//

//_______________________________________________________________________________________________________________
// Destruktor
stAniTex::~stAniTex()
{
	/* ... */

} // Destruktor
//

//_______________________________________________________________________________________________________________
// Kopierkonstruktor
stAniTex::stAniTex(const stAniTex &rhs)
{
	//
	m_bAnimate					= rhs.m_bAnimate;

	m_Texture					= rhs.m_Texture;
	m_Sprite					= rhs.m_Sprite;

	m_liAnimations				= rhs.m_liAnimations;
	m_itorAnimations			= rhs.m_itorAnimations;

} // Kopierkonstruktor
//

//_______________________________________________________________________________________________________________
//

//

// Init - initialisiert die animation - wenn etwas fehlt oder falsch laeuft wird ein statisches Bild gewaehlt
stState stAniTex::Init(std::string	sFilename, 
					   bool			bAnimate)
{
	if ( (sFilename.empty()) || (!stData->checkExistence(sFilename)) )
		return ST_CANCEL;

	// Dateisammlung definieren
	m_Fileinfo.sFilerel		= stData->getRelFilename(sFilename);
	m_Fileinfo.sFileabs		= stData->getAbsFilename(sFilename);
	m_Fileinfo.sDatatype	= stData->getFiletype(sFilename);
	m_Fileinfo.sPath		= stData->getFilepath(sFilename);
	m_Fileinfo.sState		= stDatastate::DS_NONE;

	// Ueberpruefen ob es den Dateipfad gibt ...
	if (!m_Texture.loadFromFile(sFilename))
	{
		// Fehlerlog
		stLog->writeInfo("Folgende Texturdatei konnte nicht geladen werden: " + sFilename);

		//m_BackupShape.setSize(sf::Vector2f(32.0f, 32.0f));
		//m_BackupShape.setFillColor(sf::Color(255, 255, 255, 0));

		// Markieren um Fehler nachzuvollziehen
		m_Fileinfo.sState = stDatastate::DS_NOT_FOUND;

		//
		return ST_NOT_FOUND;
	}

	// Framedefinition errechnen
	// wenn die Rechnung fehlschlaegt bleiben die Wert leer
	// um fehlwerte zu verhindern
	bool bInvalid = false;
	std::list<std::string> liRelFilenameparts = stExplodeListString(m_Fileinfo.sFileabs, '.');

	if (liRelFilenameparts.empty())
		stLog->writeWarning("Invalid Animationfilename: " + m_Fileinfo.sFileabs);
	else
	{
		// letzter Eintrag ist normalerweise immer die Framedefinition
		std::string sFramedefition = *(--liRelFilenameparts.end());
		if (sFramedefition.empty())
			m_Fileinfo.sState = stDatastate::DS_FAULTY;

		// nur die Position von x finden und den Rest herausschneiden
		int iXPos = sFramedefition.find("x");
		if (iXPos != std::string::npos)
		{
			// Frames auf der X-Achse
			std::istringstream sXFrames(sFramedefition.substr(0, iXPos));
			sXFrames >> m_vecfFrames.x;

			// Frames aus der Y-Achse
			std::istringstream sYFrames(sFramedefition.substr(++iXPos, sFramedefition.size() - iXPos));
			sYFrames >> m_vecfFrames.y;

			// Animationsstart blockieren wenn eine Frameachse fehlt
			if ( (!m_vecfFrames.x) || (!m_vecfFrames.y) )
			{
				m_bBlockAniPermission = true;
				m_bAnimate = false;
				m_Fileinfo.sState = stDatastate::DS_FAULTY;
			}
		}
		else
			m_Fileinfo.sState = stDatastate::DS_FAULTY;
	}

	// wenn Datei noch undefiniert ist ist diese in Ordnung
	if (!m_Fileinfo.sState)
		m_Fileinfo.sState = stDatastate::DS_OK;

	// Spite zuweisen
	m_Sprite.setTexture(m_Texture);

	//-----------
	return ST_OK;

} // 
//

//_______________________________________________________________________________________________________________
// Update - aktualiesiert den Framewechseltimer und seine Daten
stState stAniTex::Update(float fTime, stVector2Df vecPos, float fAngle)
{
	//
	m_fUpdateTimer += fTime;

	//
	if ( (!m_bAnimate) || (m_fUpdateTimer < m_fUpdateTimerCap ) )
		return ST_OK;
	else
		m_fUpdateTimer = 0.0f;

	//








	// Wenn sonst alles gut ist, animieren !!
	m_Sprite.setTextureRect(sf::IntRect(m_iFrameLeft, m_iFrameTop, m_iFrameWidth, m_iFrameHeight));
	m_Sprite.setOrigin(static_cast<float> (m_iFrameWidth / 2), static_cast<float> (m_iFrameHeight / 2));
	m_Sprite.setPosition(vecPos.x, vecPos.y);
	m_Sprite.setRotation(fAngle);

	//-----------
	return ST_OK;

} // Update
//

//_______________________________________________________________________________________________________________
// Aktualisiert den aktuellen Frame
bool stAniTex::updateFrame()
{
	/* ... */

	//----------
	return true;

} // updateFrame
//

//_______________________________________________________________________________________________________________
// Rendert die Textur
stState stAniTex::Render(sf::RenderWindow &window)
{
	window.draw(m_Sprite);

	//-----------
	return ST_OK;

} // Render
//

//_______________________________________________________________________________________________________________
// Erstellt einen Befehl in die m_liAnimation list
stState stAniTex::AddAnimationToList(std::string					sAniName,
									 int							iFrame,
									 ATexture_FrameRunDirection		m_RunDirection)
{
	// ueberpruefen ob 'AniName' ueberhaupt Inhalt hat
	if (sAniName.empty())
		return ST_FAIL;

	// ueberpruefen ob 'Frame' > (0)
	if (iFrame <= 0)
		return ST_FAIL;

	// Befehl deklarieren und definieren
	struct CallAnimation newCommand;

	newCommand.iAnimationName	= sAniName;
	newCommand.iFrame			= iFrame;

	m_liAnimations.push_back(newCommand);

	//-----------
	return ST_OK;

} //
//

//_______________________________________________________________________________________________________________
// Ruft die im Argument stehende Animatino auf
stState stAniTex::CallAnimation(std::string AniName)
{

	if (AniName.empty())
		return ST_FAIL;

	/*
	for (m_itAnimation = m_liAnimation.begin(); m_itAnimation != m_liAnimation.end(); m_itAnimation++)
	{
		if (m_itAnimation->iAnimationName.compare(AniName) == 0)
		{
			if (m_bXAxisFrameRun)
				m_iActiveFrameLineY = m_itAnimation->iFrame;
			else if (m_bYAxisFrameRun)
				m_iActiveFrameLineX = m_itAnimation->iFrame;

			return ST_OK;
		}
	}
	*/

	//-----------
	return ST_NOT_FOUND;

} // 
//

//_______________________________________________________________________________________________________________
// operator=
void stAniTex::operator=(const stAniTex &rhs)
{
	/*
	m_Vec2fPos					= rhs.m_Vec2fPos;
	m_fAngle					= rhs.m_fAngle;

	m_bAnimate					= rhs.m_bAnimate;
	m_bSwitchFrameLineAuto		= rhs.m_bSwitchFrameLineAuto;

	m_bCompleteAni				= rhs.m_bCompleteAni;
	m_bRunToBeginIfAniStopped	= rhs.m_bRunToBeginIfAniStopped;
	m_bRunToEndIfAniStopped		= rhs.m_bRunToEndIfAniStopped;

	m_bXAxisFrameRun			= rhs.m_bXAxisFrameRun;
	m_bYAxisFrameRun			= rhs.m_bYAxisFrameRun;

	m_fFrameDuration			= rhs.m_fFrameDuration;
	m_fFrameTimer				= rhs.m_fFrameTimer;

	m_iActiveFrameLineX			= rhs.m_iActiveFrameLineX;
	m_iActiveFrameLineY			= rhs.m_iActiveFrameLineY;
	m_iFrmsX					= rhs.m_iFrmsX;
	m_iFrmsY					= rhs.m_iFrmsY;
	m_iTop						= rhs.m_iTop;
	m_iLeft						= rhs.m_iLeft;
	m_iFrmWidth					= rhs.m_iFrmWidth;
	m_iFrmHeight				= rhs.m_iFrmHeight;

	m_iTexWidth					= rhs.m_iTexWidth;
	m_iTexHeight				= rhs.m_iTexHeight;

	m_Texture					= rhs.m_Texture;
	m_Sprite					= rhs.m_Sprite;

	m_skipShape					= rhs.m_skipShape;

	m_liAnimation				= rhs.m_liAnimation;
	m_itAnimation				= rhs.m_itAnimation;
	*/

} // operator =
//

//_______________________________________________________________________________________________________________
