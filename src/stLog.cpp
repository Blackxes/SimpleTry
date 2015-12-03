/*******************************************************************************************************************************
	Nutzen: 
	schreibt in das Logfile

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/

// header
#include <SimpleTry.h>
//

//_______________________________________________________________________________________________________________
// Definitionen
int stLogfile::m_iLogID = 0;
stLogfile* stLog = new stLogfile;

//--------------------------------------------
// Konstruktor
stLogfile::stLogfile()
{
	m_sLogName						= "logfile.html";
	m_sLogfilePath					= "";
	
	m_iLogMaxLength					= -1;
	m_iMaxTitleLength				= 10;

	// Dateipfade
	m_mainHead						= "<head><body></head></body>";
	m_sPathCSS						= "";
	m_sPathCSS						= "";
	m_sPathjQuery					= "";

	// defaultwert
	m_sDefColor						= "#5C5C5C";
	m_iDefFontSize					= 16;
	m_sDefFontStyle					= "normal";
	m_sDefColor						= "#5C5C5C";
	m_sDefColorCodeTitle			= "#5C5C5C";
	m_sDefColorCodeText				= "#5C5C5C";
	m_sDefFontSizeTitle				= 16;
	m_sDefFontSizeText				= 16;
	m_sDefFontStyleTitle			= "normal";
	m_sDefFontStyleTitle			= "normal";

	m_bIsInitializied				= false;

} // Konstruktor
//

//--------------------------------------------
// Destruktor
stLogfile::~stLogfile()
{
	/* ... */

} // Destruktor
//

//_______________________________________________________________________________________________________________
// Initialiert die Logfile
stState stLogfile::Init()
{

	//--------------------------------------------
	// main-Definitionen - Pfade definiert in SimpleTry.h
	m_sPathCSS					= g_PathToBasicCSS;
	m_sPathJS					= g_PathToBasicJS;
	m_sPathjQuery				= g_PathToJQuery;

	//--------------------------------------------
	// css laden
	if (getDataContent(m_sPathCSS, m_mainCSS) == ST_NOT_FOUND)
	{
		std::cout << "CSS Datei nicht gefunden" << std::endl;
		std::cout << "Pfad: " << m_sPathCSS << std::endl;
		m_mainCSS = "";
	}

	//--------------------------------------------
	// javascript laden
	if (getDataContent(m_sPathJS, m_mainJS) == ST_NOT_FOUND)
	{
		std::cout << "JS Datei nicht gefunden" << std::endl;
		std::cout << "Pfad: " << m_sPathJS << std::endl;
		m_mainJS = "";
	}

	//--------------------------------------------
	// head
	m_mainHead		=	"	<head>\n"
						"	<title>" + m_sLogName + "</title>\n"
						"	<meta charset=\"utf-8\">\n"
						"	<script src=\"" + m_sPathjQuery + "\"></script>\n"						// jQuery einbinden		
						"	<style rel=\"stylesheet\">\n" + m_mainCSS + "</style>\n"				// css einbinden
						"	<script type=\"text/javascript\">\n" + m_mainJS + "</script>\n"			// js einbinden
						"	</head>\n";

	//--------------------------------------------
	// footer

	bool bLogExists = false;

	// Wenn ein bereits ein Log existiert
	if (stData->checkExistence("logfile.html"))
	{
		remove("logfile.html");
		bLogExists = true;
	}

	std::ofstream InitLog("logfile.html", std::ios::out);

	if (InitLog.is_open())
	{
		std::string init = "";

		// Logfile 'aufbauen'
		InitLog << "<html>";

		InitLog << m_mainHead << "\n";

		init +=	"<body>\n";
		init +=		"<!-- logfile -->\n";
		init +=		"<div id=\"container\">\n";
		init +=			"<h1>Logfile</h1>\n";
		init +=		"<div>\n";
		init +=		"<!-- Reihenfolge der listelemente - logtype/description/ -->\n";
		init +=		"<table id=\"log\">\n";

		InitLog << init;
		
		InitLog.close();
	}
	
	else
	{
		std::cout << "Logfile konnte nicht geoeffnet werden" << std::endl;

		//-------------
		return ST_FAIL;
	}

	// logfile schliessen
	InitLog.close();

	// wenn eine Logfile vorhanden war - Meldung einschreiben
	if (bLogExists)
	{
		writeInfo("Vorhande Logfile geloescht - Neue erstellt");
	}

	// information schreiben
	writeInfo("Logfile wurde erfolgreich initialisiert");

	// als initialisiert setzen
	m_bIsInitializied = true;

	//-----------
	return ST_OK;

} // Init
//

//_______________________________________________________________________________________________________________
// schliesst das Logfile
stState stLogfile::Exit()
{	
	writeInfo("Logfile wird geschlossen ...");
	
	std::ofstream EndLog("logfile.html", std::ios::out | std::ios::app);

	if (!EndLog.is_open())
	{
		std::cout << "Fehler beim vollstaendigen schliessen der Logfile" << std::endl;

		return ST_NOT_FOUND;
	}
	
	else
	{
		std::string report = "";

		report +=					"</table>\n";
		report +=				"</div>\n";
		report +=			"</div>\n";
		report +=		"</body>\n";
		report +=	"</html>\n";

		EndLog << report;
	}

	EndLog.close();

	

	//-----------
	return ST_OK;

} // Exit
//

//_______________________________________________________________________________________________________________
// Log in die Liste schreiben
stState stLogfile::write(std::string title,
						 std::string text,
						 logtype eLogtype)
{

	// versuchen das Log zu oeffnen
	std::ofstream Log("logfile.html", std::ios::out | std::ios::app);
	
	if (Log.is_open())
	{
		// Variablen
		std::string sLogtype = "";


		switch(eLogtype)
		{
			case (logtype::LT_ERROR):
				sLogtype = " class=\"error\"";
				break;

			case (logtype::LT_INFO):
				sLogtype = " class=\"info\"";
				break;

			case (logtype::LT_WARNING):
				sLogtype = " class=\"warning\"";
				break;
		}

		// Log zusammenbauen
		std::string report = "";

		report += "<tr id=\"" + std::to_string(m_iLogID) + "\"" + sLogtype + ">\n";

		// eigentlicher Bericht
		report += "<th><h4>" + title + "</h4></th>\n";
		report += "<th><p>" + text + "</p></th>";

		report += "</tr>\n";

		// endgueltig ins Logfile schreiben
		Log << report;

		Log.close();

	}

	else
	{
		std::cout << "Fehler beim oeffnen der Logfile" << std::endl;
		Log.close();

		return ST_NOT_FOUND;
	}
	
	// logcounter und ID hochzaehlen
	//m_LogsCounter++;
	m_iLogID++;

	//-----------
	return ST_OK;

} // write
//

//_______________________________________________________________________________________________________________
// Schreibt einen Text in das Logfile
stState stLogfile::writeVector(stVector2Df vec, 
							   std::string title,
							   std::string varName,
							   bool toggleOut)
{
	std::ofstream Log("logfile.html", std::ios::out | std::ios::app);
	
	if (Log.is_open())
	{

		// Bericht
		std::string report = "";

		std::string open = (toggleOut) ? " open" : "";
		

		report +=	"<tr id=" + std::to_string(m_iLogID) + " class=\"list" + open + "\">\n";
		
		report +=		"<th> <h4>" + title + "</h4> </th>\n";
		report +=		"<th> <p>" + varName + "</p> </th>\n";
			
		report +=		"<th>";
		report +=			"<div class=\"" + open + "\"></div>";
		report +=		"</th>";
		report +=		"<th class=\"varList" + open + "\"> <ul>\n";

		report +=			"<li> <h5>X</h5> <p>" + std::to_string(vec.x) + "</p> </li>\n";
		report +=			"<li> <h5>Y</h5> <p>" + std::to_string(vec.y) + "</p> </li>\n";

		report +=			"</ul>";
		report +=		"</th>";
		report +=	"</tr>\n";

		Log << report;
	
		// Logfile schliessen
		Log.close();

		m_iLogID++;
	}

	else
	{
		return ST_NOT_FOUND;
	}

	//-----------
	return ST_OK;

} // write
//

//_______________________________________________________________________________________________________________
// schreibt ein Error in das Logfile
stState stLogfile::writeError(std::string sText)
{
	if ( (!ALL_REPORTING) || (!ERROR_REPORTING) )
		return ST_CANCEL;

	if (write("ERROR", sText, logtype::LT_ERROR) == stState::ST_NOT_FOUND)
	{
		return ST_NOT_FOUND;
	}

	//-----------
	return ST_OK;

} // writeError
//

//_______________________________________________________________________________________________________________
// schreibt ein Error in das Logfile
stState stLogfile::writeWarning(std::string sText)
{
	if ( (!ALL_REPORTING) || (!WARNING_REPORTING) )
		return ST_CANCEL;

	if (write("WARNUNG", sText, logtype::LT_WARNING) == stState::ST_NOT_FOUND)
	{
		return ST_NOT_FOUND;
	}

	//-----------
	return ST_OK;

} // writeError
//

//_______________________________________________________________________________________________________________
// schreibt ein Error in das Logfile
stState stLogfile::writeInfo(std::string sText)
{
	if ( (!ALL_REPORTING) || (!INFO_REPORTING) )
		return ST_CANCEL;

	if (write("INFO", sText, logtype::LT_INFO) == stState::ST_NOT_FOUND)
	{
		return ST_NOT_FOUND;
	}

	//-----------
	return ST_OK;

} // writeInfo
//

//_______________________________________________________________________________________________________________
// schreibt eine Trennlinie in das Logfile
stState stLogfile::writeDevider(std::string color)
{
	std::ofstream Log("logfile.html", std::ios::out | std::ios::app);
	
	if (Log.is_open())
	{
		// Berichtsvariable
		std::string report; 

		report += "<tr id=" + std::to_string(m_iLogID) + " class=\"dev\"";

		// wenn eine Farbe gewaehlt wurde
		if (!color.empty())
		{
			report += " style=\"color: " + color + "\"";
		}

		report += ">\n";

		report += "</tr>\n";

		Log << report;

		Log.close();

		m_iLogID++;
	}

	else
	{
		std::cout << "Log has not been found" << std::endl;
		return ST_NOT_FOUND;
	}
	
	//-----------
	return ST_OK;
	
} // writeDevider
//

//_______________________________________________________________________________________________________________
// liest Content einer Datei in die die Variable 'container'
stState stLogfile::getDataContent(std::string sFile, std::string &sContainer)
{
	std::ifstream GetData(sFile, std::ios::in);

	if (GetData.is_open())
	{
		std::string tempContainer = "";

		while (std::getline(GetData, tempContainer))
		{
			if (!tempContainer.empty())
				sContainer += tempContainer + "\n";
			else
				sContainer += "\n";
		}
	}

	else
	{
		GetData.close();
		return ST_NOT_FOUND;
	}

	GetData.close();

	//-----------
	return ST_OK;

} // getDataContent
//

//_______________________________________________________________________________________________________________
