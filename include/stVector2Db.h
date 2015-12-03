/*******************************************************************************************************************************
	Nutzen/Aufgabe:
	Erzeugt ein 2 dimensionalen Vector vom Typ float

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
/* ... */





//_______________________________________________________________________________________________________________
// Klasse
class stVector2Db
{
		
	//===============================================================================================================
	public:
		
		//===========================================================================================================
		// Basisvariablen	
		union 
		{
			struct
			{
				bool	x;
				bool	y;
			};

			bool c[2];
		};
	

		//===========================================================================================================
		// Initialmethoden - Konstruktor/Kopierkonstruktor/Destruktor - Initfunktion
		//
		stVector2Db() :	x (0.f),			// Konstruktor
						y (0.f)		{}

		stVector2Db(bool xy) :	x (xy),				// Konstruktor
								y (xy)		{}

		stVector2Db(bool x, bool y) :	x(x),				// Konstruktor
										y(y)		{}

		stVector2Db(const stVector2Db &rhs) :	x(rhs.x),			// Kopierkonstruktor
												y(rhs.y)	{}

		// Destruktor
		~stVector2Db()	{};

		// Cast-Operatoren
		/* ... */


		//
		// Zuweisungsoperatoren
		inline stVector2Db operator =  (const stVector2Db& rhs)						{ return stVector2Db (this->x = rhs.x,	this->y = rhs.y);	}			// Zuweisung mit Vektor
		inline stVector2Db operator =  (const bool& v)								{ return stVector2Db (this->x = v,		this->y = v);		}			// Zuweisung mit float
		/*
		inline stVector2Df operator += (const stVector2Df& rhs)						{ return stVector2Df (this->x += rhs.x,	this->y += rhs.y);	}			// Zuweisungsaddition mit Vektor
		inline stVector2Df operator += (const float& v)								{ return stVector2Df (this->x += v,		this->y += v);		}			// Zuweisungsaddition mit float
		inline stVector2Df operator -= (const stVector2Df& rhs)						{ return stVector2Df (this->x -= rhs.x,	this->y -= rhs.y);	}			// Zuweisungssubtraktion mit Vektor
		inline stVector2Df operator -= (const float& v)								{ return stVector2Df (this->x -= v,		this->y -= v);		}			// Zuweisungssubtraktion mit float
		inline stVector2Df operator *= (const stVector2Df& rhs)						{ return stVector2Df (this->x *= rhs.x,	this->y *= rhs.y);	}			// Zuweisungsmultiplikation mit Vektor
		inline stVector2Df operator *= (const float& v)								{ return stVector2Df (this->x *= v,		this->y *= v);		}			// Zuweisungsmultiplikation mit float
		inline stVector2Df operator /= (const stVector2Df& rhs)						{ return stVector2Df (this->x /= rhs.x,	this->y /= rhs.y);	}			// Zuweisungsdivision mit Vektor
		inline stVector2Df operator /= (const float& v)								{ return stVector2Df (this->x /= v,		this->y /= v);		}			// Zuweisungsdivision mit Vektor
		*/

		//inline stVector2Df operator - (const stVector2Df& rhs)						{ std::cout << "Minus Operator" << std::endl; stVector2Df (this->x - rhs.x, this->y - rhs.y);	}	

		// Nicht anwenden wenn das wissen besteht das (x > rhs.x und y < rhs.y) - Es wird kein brauchbares Ergebnis geliefert
		//	inline bool operator <  (const stVector2Df& rhs)							{ if ( (this->x < rhs.x)	and (this->y < rhs.y) )		return true; else return false; };
		//	inline bool operator <  (const float& v)									{ if ( (this->x < v)		and (this->y < v) )			return true; else return false; };
		//	inline bool operator >  (const stVector2Df& rhs)							{ if ( (this->x > rhs.x)	and (this->y > rhs.y) )		return true; else return false; };
		//	inline bool operator >  (const float& v)									{ if ( (this->x > v)		and (this->y > v) )			return true; else return false; };


}; //
//

//_________________________________________________________________________________________________________________________________________________________________________________________________
		// Arithmetische Operatoren
		/*
		inline stVector2Df operator + (const stVector2Df& a, const stVector2Df& b)		{ return stVector2Df (a.x + b.x,		a.y + b.y);			}			// Addition mit Vektor
		inline stVector2Df operator + (const stVector2Df& a)							{ return stVector2Df (+a.x,				+a.y);				}			// Addition mit Vektor
		inline stVector2Df operator + (const stVector2Df& v, const float& f)			{ return stVector2Df (v.x + f,			v.y + f);			}			// Addition mit float
		inline stVector2Df operator - (const stVector2Df& a, const stVector2Df& b)		{ return stVector2Df (a.x - b.x,		a.y - b.y);			}			// Subtraktion mit Vektor
		inline stVector2Df operator - (const stVector2Df& a)							{ return stVector2Df (-a.x , -a.y);							}			// Subtraktion mit Vekto
		inline stVector2Df operator * (const stVector2Df& a, const stVector2Df& b)		{ return stVector2Df (a.x * b.x,		a.y * b.y);			}			// Multiplikation mit Vektor
		inline stVector2Df operator * (const stVector2Df& v, const float& f)			{ return stVector2Df (v.x * f,			v.y * f);			}			// Multiplikation mit float
		inline stVector2Df operator / (const stVector2Df& a, const stVector2Df& b)		{ return stVector2Df (a.x / b.x,		a.y / b.y);			}			// Division mit Vektor
		inline stVector2Df operator / (const stVector2Df& v, const float& f)			{ return stVector2Df (v.x / f,			v.y / f);			}			// Division mit float
		*/

//_________________________________________________________________________________________________________________________________________________________________________________________________
		// Logische Operatoren
		inline bool operator ==	(const stVector2Db& a, const stVector2Db b)			{ if ((a.x == b.x) and (a.y == b.y)) return true; else return false; }	// Gleichheitsprüfung
		inline bool	operator != (const stVector2Db& a, const stVector2Db b)			{ if ((a.x != b.x) and (a.y != b.y)) return true; else return false; }	// Ungleichheitspruüfung

//
//_________________________________________________________________________________________________________________________________________________________________________________________________