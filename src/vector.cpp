#include <iostream>
#include "vector.h"

using namespace std;


//Defualt constructor
Vector::Vector()
{
	m_x = m_y = 0;
}

//Constructor for setting values
Vector::Vector( double x, double y)
{
	m_x = x;
	m_y = y;
}

//Print out Vector values
void Vector::print()
{
	cout << "[" << m_x << "," << m_y << "]" << endl;
}

//Opereator for adding Vectors
Vector Vector::operator+(const Vector &rhs)
{
	Vector temp;

	temp.m_x = m_x + rhs.m_x;
	temp.m_y = m_y + rhs.m_y;

	return temp;
}
