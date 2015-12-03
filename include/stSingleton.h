/*******************************************************************************************************************************
	Nutzen:
	Deklariert eine Klasse und sorgt dafuer das nur eine Instanz der Klasse vorhanden ist

	Autor:
	Heiko Kalista
*******************************************************************************************************************************/

//
#pragma once
//

//_______________________________________________________________________________________________________________
// header
/* ... */
//

//_______________________________________________________________________________________________________________
// Klasse
template <class T>
class TSingleton
{
	protected:

	// Membervariablen
	static T *m_pSingleton;   // Statisches Objekt

	public:

	// Memberfunktionen

	// Destruktor
	//
	virtual ~TSingleton ()
	{
	}

	// Get
	//
	// Aufgabe: Wenn nötig, statisches Objekt erzeugen und
	// Zeiger darauf zurückgeben
	//
	inline static T* Get ()
	{
	// Existiert schon eine Instanz?
	if (!m_pSingleton)
		m_pSingleton = new T;   // Nein, dann neue Instanz erzeugen

	// Zeiger auf die Instanz zurückgeben
	return (m_pSingleton);

	} // Get

	// Statisches Objekt freigeben
	//
	static void Del ()
	{
	// Gab es eine Instanz?
	if (m_pSingleton)
	{
		delete (m_pSingleton);  // Ja, dann freigeben
		m_pSingleton = NULL;    // und Zeiger auf NULL setzen
	}

	} // Del

}; // TSingleton
//

//_______________________________________________________________________________________________________________
// Die statische Variable erzeugen
//
template <class T>
T* TSingleton<T>::m_pSingleton = new T;
