/*******************************************************************************************************************************
	Nutzen:
	Detailerzeugung fuer AnimateText

	Autor:
	Alexander Bassov
*******************************************************************************************************************************/
//

// header
#include <SimpleTry.h>

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
// Teilt einen String in einzelne Listenteile auf
std::list<float> stExplodeList(std::string sString, char cSeperator)
{
	// Variablen
	std::list<float> list;					// Liste
	std::string sContainer;					// Zeichencontainer
	std::istringstream isStream(sString);	// 

	while(std::getline(isStream, sContainer, cSeperator))
	{
		// Konvertierung in ein float
		std::ostringstream Converted(sContainer);
		float iValue = (float) (atof(sContainer.c_str()));

		list.push_back(iValue);
	}

	//----------
	return list;

} // stExplodeList
//

//_______________________________________________________________________________________________________________
// Teilt einen String in einzelne Listenteile auf
std::list<std::string> stExplodeListString(std::string sString, char cSeperator)
{
	// Variablen
	std::list<std::string> list;			// Liste
	std::string sContainer;					// Zeichencontainer
	std::istringstream isStream(sString);	// 

	while(std::getline(isStream, sContainer, cSeperator))
		list.push_back(sContainer);

	//----------
	return list;

} // stExplodeList
//

//_______________________________________________________________________________________________________________
// Fuegt eine Liste zu einem String zusammen der durch cSeperator von den einzelnen Elementen getrennt wird
std::string stImplodeList(std::list<float> list, char cGlue, bool removeLast)
{
	// string
	std::string sString;
	for (std::list<float>::iterator it = list.begin(); it != list.end(); it++)
		sString += std::to_string(*it) + cGlue;

	// letztes "Klebestueck" entfernen
	if (removeLast)
		sString.pop_back();

	//-------------
	return sString;

} // stImplodeList
//

//_______________________________________________________________________________________________________________
// Fuegt eine Liste zu einem String zusammen der durch cSeperator von den einzelnen Elementen getrennt wird
std::string stImplodeListString(std::list<std::string> list, char cGlue, bool removeLast)
{
	// string
	std::string sString;
	for (std::list<std::string>::iterator it = list.begin(); it != list.end(); it++)
		sString += *it + cGlue;

	// letztes "Klebestueck" entfernen
	if (removeLast)
		sString.pop_back();

	//-------------
	return sString;

} // stImplodeList
//

//_______________________________________________________________________________________________________________