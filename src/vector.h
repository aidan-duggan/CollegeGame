#ifndef CLASS_VECTOR
#define CLASS_VECTOR

class Vector
{
public:
	//X and Y variables
	double m_x;
	double m_y;
	//Constructors, defualt and non-defualt to set x and y values
	Vector();
	Vector( double x, double y);
	//Method to print x and y values
	void print();
	//Overloaded + to add vector classes
	Vector operator+(const Vector &rhs);

};


#endif
