#include "stdafx.h"
#include "Poly.h"

//------------------------Poly------------------------------------
// Constructor with no parameters. Initialized with a single 
// value set to zero. 
//----------------------------------------------------------------
Poly::Poly()
{
	size = 1;
	coeffPtr = new int[size]; //need a delete
	coeffPtr[0] = 0;
}

//------------------------Poly------------------------------------
// Copy constructor for poly with only one term and no exponent.
//----------------------------------------------------------------
Poly::Poly(int coeff)
{
	size = 1;
	coeffPtr = new int[size]; //need a delete
	coeffPtr[0] = coeff;
}

//-------------------------Poly------------------------------------
// Copy constructor for a poly with a given coefficient and power.
// pow = the highest exponent currently expected.
//-----------------------------------------------------------------
Poly::Poly(int coeff, int pow)
{
	size = (pow + 1);
	coeffPtr = new int[size]; 
	for (int i = 0; i < size; i++)
	{
		coeffPtr[i] = 0;
	}
	coeffPtr[pow] = coeff;
}

//-------------------------Poly-------------------------------------
// Copy constructor to make a deep copy of the poly passed in by 
// parameter.
//-----------------------------------------------------------------
Poly::Poly(const Poly &polyToCopy)
{
	size = polyToCopy.size;
	coeffPtr = new int[size];
	for (int i = 0; i < size; i++)
	{
		coeffPtr[i] = polyToCopy.coeffPtr[i];
	}
}

//------------------------Poly----------------------------------------
// Deconstructor for a polynomial. 
// Deletes the pointer to free memory then 
// Sets the pointer to NULL
//--------------------------------------------------------------------
Poly::~Poly()
{
	delete[] coeffPtr;
	coeffPtr = nullptr;
}

//------------------------getCoeff------------------------------------
// Returns the requested coefficient if it is in range of the poly.
// Returns 0 if the index is out ouf range.
//--------------------------------------------------------------------
int Poly::getCoeff(int index) const
{
	if (index < 0)
	{
		return 0; // out of bounds
	}
	if (index > size)
	{
		return 0;
	}
	else 
	{
		return coeffPtr[index]; 
	}
}

//-------------------------getSize------------------------------------
// Returns the requested coefficient.
//--------------------------------------------------------------------
int Poly::getSize() const
{
	return size;
}

//-------------------------setSize------------------------------------
// Returns the requested coefficient.
//--------------------------------------------------------------------
void Poly::setSize(int size)
{
	this->size = size;
}

//------------------------setCoeff------------------------------------
// Sets the coefficient at the correct index
//--------------------------------------------------------------------
void Poly::setCoeff(int coeff, int pow)
{
	if ((pow >= 0) && (pow <= size))
	{
		coeffPtr[pow] = coeff;
	}
	else
	{
		while (pow > size)
		{
			this->Resize();
		}
		coeffPtr[pow] = coeff;
	}
}

//--------------------------Clear-------------------------------------
// Sets all values in array to zero
//--------------------------------------------------------------------
void Poly::ClearArray()
{
	for (int i = 0; i < size; i++)
	{
		coeffPtr[i] = 0;
	}
}

//------------------------------Resize----------------------------------
// Doubles the size of the array
//----------------------------------------------------------------------
void Poly::Resize()
{
	/*
	newSize += 1;
	int *tempPtr = new int[newSize];

	for (int i = 0; i < size; i++)
	{
		tempPtr[i] = coeffPtr[i];
	}

	for (int k = size; k < newSize; k++)
	{
		tempPtr[k] = 0;
	}

	tempPtr[newSize] = coeff;

	delete[] coeffPtr;
	coeffPtr = nullptr;
	coeffPtr = tempPtr;
	tempPtr = nullptr;
	*/
	
	int newSize = size * 2;
	int *temp = new int[size];
	for (int k = 0; k < size; k++)
	{
		temp[k] = coeffPtr[k];
	}
	delete[] coeffPtr;
	coeffPtr = new int[newSize];
	for (int i = 0; i < newSize; i++)
	{
		coeffPtr[i] = 0;
		if (i < size)
		{
			coeffPtr[i] = temp[i];
		}
	}
	delete[] temp;
	size = newSize;
	/*
	int newSize = (size * 2);
	int *resizedPtr = new int[newSize];
	int *temp = new int[size];
	
	for (int k = 0; k < newSize; k++)
	{
		resizedPtr[k] = 0; // initialize arrayPtr to zero coeffs
	}

	for (int i = 0; i < size; i++)
	{
		resizedPtr[i] = coeffPtr[i]; // update with corrected coeffs where necessary.
	}

	size = newSize;
	delete[] coeffPtr;
	coeffPtr = resizedPtr;
	*/
}


//-----------------------Overloaded Operator(+)------------------------
// Adds two polynomials together.
// Returns the result as a new polynomial
//---------------------------------------------------------------------
Poly Poly::operator+(const Poly & rhs) const
{   
	Poly returnPoly;
	returnPoly = *this;
	returnPoly += rhs;
	return returnPoly;
}

//-----------------------Overloaded Operator(-)------------------------
// Subtracts the second polynomial from the first.
//---------------------------------------------------------------------
Poly Poly::operator-(const Poly & rhs) const
{
	Poly returnPoly;
	returnPoly = *this;
	returnPoly -= rhs;
	return returnPoly;
}

//-------------------------Overloaded Operator(+=)------------------------
// Adds two polynomials together.
// Updates and returns the updated left-hand side polynomial. 
//-------------------------------------------------------------------------
Poly& Poly::operator+=(const Poly &rhs)
{
	while (size < rhs.size)
	{
		this->Resize();
	}
	
	for (int i = 0; i < size; i++)
	{
		int rhsCoeff = rhs.coeffPtr[i];
		if (i >= rhs.size)
		{
			rhsCoeff = 0;
		}
		coeffPtr[i] = (coeffPtr[i] + rhsCoeff);
	}
	return *this;
}

// ------------------------Overloaded Operator(*=)--------------------------
//  Returns the product of two polynomials together by multiplying the 
//  current term of first polynomial with every term in the second 
//  polynomial. 
//  CURRENTLY HAS A BUG - NOT WORKING CORRECTLY
//-------------------------------------------------------------------------
Poly& Poly::operator*=(const Poly &rhs)
{
	*this = (*this) * rhs;
	return *this;
}

//-------------------------Overloaded Operator(-=)------------------------
// Subtracts the second polynomila from the first.
// Updates and returns the updated left-hand side polynomial. 
//-------------------------------------------------------------------------
Poly& Poly::operator-=(const Poly &rhs)
{
	while (size < rhs.size)
	{
		this->Resize();    // I know doubling can be inefficient, but did not have time to make it more efficient.
	}

	int rhsCoeff;
	for (int i = 0; i < size; i++)
	{
		if (i >= rhs.size)
		{
			rhsCoeff = 0;
		}
		else
		{
			rhsCoeff = rhs.coeffPtr[i];
		}
		coeffPtr[i] = (coeffPtr[i] - (rhsCoeff));
	}
	return *this;
}

//-------------------------Overloaded Operator(=)------------------------
// Makes a deep copy of the polynomial on the rhs and sets the lhs equal
// to it.
//-------------------------------------------------------------------------
Poly& Poly::operator=(const Poly &rhs)
{
	if (&rhs != this)
	{
		delete[] coeffPtr;
		coeffPtr = nullptr;
		size = rhs.size;
		coeffPtr = new int[size];
		
		for (int i = 0; i < size; i++)
		{
			coeffPtr[i] = rhs.coeffPtr[i];
		}
	}
	return *this;
}

// ------------------------Overloaded Operator(*)--------------------------
//  Returns the product of two polynomials together by multiplying the 
//  current term of first polynomial with every term in the second 
//  polynomial. 
//  CURRENTLY HAS A BUG - NOT WORKING CORRECTLY
//-------------------------------------------------------------------------
Poly Poly::operator*(const Poly & rhs) const
{	
	int tempSize = (size + rhs.size - 1);     //constructor will add 1, thus the -1
	int *product = new int[tempSize];

	for (int k = 0; k < tempSize; k++)
	{
		product[k] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < rhs.size; j++)
			{
				product[i + j] += (coeffPtr[i] * rhs.coeffPtr[j]);  // += because there may already be 
																   // a coefficient present. 
			}
	}
	return *product;
}

//-------------------------Overloaded Operator(==)------------------------
//Returns true is the polynomials are equal
//-------------------------------------------------------------------------
bool Poly::operator==(const Poly &rhs) const
{
	bool equal;
	for (int i = 0; i < size; i++)
	{
		if (coeffPtr[i] = rhs.coeffPtr[i])
		{
			equal = true;
		}
		else
		{
			equal = false;
		}
		if (equal = false)
		{
			return equal;
		}
	}
	return equal;
}

//-------------------------Overloaded Operator(!=)------------------------
//Returns true is the polynomials are equal
//-------------------------------------------------------------------------
bool Poly::operator!=(const Poly &rhs) const
{
	return !(*this == rhs);
}

// -----------------------Overloaded Operator(>>)-----------------------------
//  
//
//---------------------------------------------------------------------------
istream& operator>>(istream &inStream, Poly &poly)
{
	int coefficient, power;
	//poly.ClearArray();
	bool anotherTerm = true;

	while (anotherTerm && (inStream >> coefficient >> power))
	{
		if ((power == -1) && (coefficient == -1))
		{
			anotherTerm = false;
			break;
		}
		poly.setCoeff(coefficient, power);
	}
	return inStream;
}

// -----------------------Overloaded Operators(<<)----------------------------
// Displays the polynomial
// E.g. [2 5 -6 7 2 4 -1 -1] will be printed as 2x^5  -6x^7 +2x^4
// If coefficient and power are both zero, then 0 is printed. 
// If coefficient is non-zero, but power is zero, then no x gets printed. 
// ---------------------------------------------------------------------------
ostream& operator<<(ostream &outStream, const Poly &poly)
{
	int coefficient;
	int power;
	int countZeroCoeffs = 0;
	bool noTerms = true;

	for (int i = poly.size-1; i >= 0; i--)
	{
		coefficient = poly.getCoeff(i);
		power = i;

		if (coefficient == 0)
		{	
			// Checks for no terms
			countZeroCoeffs++;
		}
		else
		{
			if (power == 0)
			{
				if (coefficient >= 0)
				{
					outStream << " +" << coefficient << " ";
				}
				else
				{
					outStream << " " << coefficient << " ";
				}
			}
			else if (power == 1)
			{
				if (coefficient >= 0)
				{
					outStream << "+" << coefficient << "x";
				}
				else
				{
					outStream << coefficient << "x";
				}
			}
			else if (power < 0)
			{
			
				outStream << "Index Out Of Bounds";
			}
			else 
			{
				// Adds any existing terms to outStream. 
				if (coefficient >= 0)
				{
					outStream << "+" << coefficient << "x^" << power << " ";
				}
				else
				{
					outStream << coefficient << "x^" << power << " ";
				}
				
			}
		}
		if (countZeroCoeffs == poly.size)
		{
			// If the polynomial has no terms, display zero.
			outStream.clear();
			outStream << 0;
		}
	}
	return outStream;
}

