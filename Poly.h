// ------------------------------------------------ file name -------------------------------------------------------- 
// Chantel Frizzell CSS343,section C 
// Jan 8. 2017 
// Jan 10, 2017 
// --------------------------------------------------------------------------------------------------------------------
// Create (and manipulate) polynomials from user input. 
// -------------------------------------------------------------------------------------------------------------------- 
// Notes on specifications, special algorithms, and assumptions. 
// -------------------------------------------------------------------------------------------------------------------- 

#include "stdafx.h"
#include <iostream>

using namespace std;

class Poly
{
	friend ostream& operator<<(ostream &outStream, const Poly &rat);
	friend istream& operator>>(istream &inStream, Poly &rat);

public:
	Poly();
	Poly(int coeff);
	Poly(int coeff, int pow);
	Poly(const Poly &polyToCopy);
	~Poly();

	int getCoeff(int index) const;
	int getSize() const;

	void setCoeff(int coeff, int pow);
	void setSize(int size);

	void Resize(); //maybe
	void ClearArray();

	Poly operator+(const Poly &rhs) const;
	Poly operator*(const Poly &rhs) const;
	Poly operator-(const Poly &rhs) const;
	
	Poly& operator=(const Poly &rhs);
	Poly& operator+=(const Poly &rhs);
	Poly& operator-=(const Poly &rhs);
	Poly& operator*=(const Poly &rhs);

	bool operator!=(const Poly &rhs) const;
	bool operator==(const Poly &rhs) const;

private: 
	int *coeffPtr;
	int size;

};


