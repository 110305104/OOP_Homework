#include <math.h>
#include "Vector.h"

// Public //

// default constrcutor
Vector::Vector()
{
    allocSize=0;
    initialize(2);
    fDimension=2;
}

// construct a vector of the give dimension
Vector::Vector(int dimension)
{
    allocSize=0;
    initialize(dimension);
    fDimension=dimension;
}

// constructor for easier initialization
Vector::Vector(int size, const double elements[])
{
    initialize(size);
    fDimension = size;

    for(int i=0;i<size;i++)
    {
        fElements[i]=elements[i];
    }
    allocSize = size;
}

// copy constructor
Vector::Vector(const Vector &source)
{
    
    initialize(source.fDimension);
    fDimension = source.fDimension;
    allocSize = source.allocSize;

    for(int i=0;i<fDimension;i++)
    {
        this->fElements[i]=source.fElements[i];
    }

}

// destructor
Vector::~Vector()
{
   // delete[] fElements; //ASK delete[] fElements 跟 delete []fElements 的差異 -> free(): invalid next size (fast) Aborted (core dumped)
}

// get the dimension of the vector
int Vector::getDimension() const
{
    return fDimension;
}


/**
* set the dimension of the vector
* vector is trucated if the new dimension is shorter than the current one
* vector is copied over if the new dimension is longer
*/
void Vector::setDimension(int dimension)
{
    if(dimension>fDimension)
    {
        double *temp = new double[dimension];
        for(int i=0;i<fDimension;i++)
        {
            temp[i]=fElements[i];
        }

        for(int i=fDimension;i<dimension;i++)
        {
            temp[i]=0;
        }
        delete []fElements;
        fDimension=dimension;
        fElements=temp;
    }
    else
    {
        //直接重開重填
        Vector temp=*this;
        initialize(dimension);
        for(int i=0;i<temp.fDimension;i++)
        {
             fElements[i]=temp.fElements[i];
        }
        allocSize=fDimension=dimension;
        

        //這邊有問題 ASK Why
        /*
        for(int i=dimension;i<fDimension;i++)
        {
            delete &fElements[i];
        }

        fDimension=dimension;
        allocSize=dimension;
        //allocSize=fDimension=dimension;
        */
    }
}

/* operator overloading */
// assignment operator
Vector& Vector::operator=(const Vector &v2)
{
    for(int i=0;i<v2.fDimension;i++)
    {
        fElements[i]=v2.fElements[i];
    }
    allocSize=v2.allocSize;
    return *this;
}

// element access
// You need to have two versions: a constant one and non-constant one
double& Vector::operator[] (int index)
{
    return fElements[index];
}

double Vector::operator[] (int index) const
{
    return fElements[index];
}

// addition of two vectors
Vector Vector::operator+ (const Vector &v2) const
{
    if(fDimension!=v2.fDimension)
    {
        cout<<"error! The dimensions of the two vectors are not the same.\n";
        return *this;
    }
    else
    {
        Vector temp(fDimension);
        for(int i=0;i<fDimension;i++)
        {
            temp.fElements[i]=fElements[i]+v2.fElements[i];
        }
        return temp;
    }
}
// substraction of two vectors
Vector Vector::operator- (const Vector &v2) const
{
    if(fDimension!=v2.fDimension)
    {
        cout<<"error! The dimensions of the two vectors are not the same.\n";
        return *this;
    }
    else
    {
        Vector temp(fDimension);
        for(int i=0;i<fDimension;i++)
        {
            temp.fElements[i]=fElements[i]-v2.fElements[i];
        }
        return temp;
    }
}
// add the given vector to the current one
Vector& Vector::operator+= (const Vector &v2)
{
    if(fDimension!=v2.fDimension)
    {
        cout<<"error! The dimensions of the two vectors are not the same.\n";
        return *this;
    }
    else
    {
        for(int i=0;i<fDimension;i++)
        {
            fElements[i]+=v2.fElements[i];
        }
        return *this;
    }
}
// substract the given vector to the current one
Vector& Vector::operator-= (const Vector &v2)
{
    if(fDimension!=v2.fDimension)
    {
        cout<<"error! The dimensions of the two vectors are not the same.\n";
        return *this;
    }
    else
    {
        for(int i=0;i<fDimension;i++)
        {
            fElements[i]-=v2.fElements[i];
        }
        return *this;
    }
}
// unary negation operator
Vector Vector::operator- ()
{
    for(int i=0;i<fDimension;i++)
    {
        fElements[i]=-1*fElements[i];
    }
    return *this;
}
// scalar multiplication and assignment
Vector Vector::operator* (double scale)
{
    Vector temp(fDimension);
    for(int i=0;i<fDimension;i++)
    {
        temp.fElements[i]=fElements[i]*scale;
    }
    return temp;
}

Vector operator*(double scale, Vector v)//check .h
{
    Vector temp=v;
    for(int i=0;i<v.getDimension();i++)
    {
        temp[i]*=scale;
    }
    return temp;
}


// scalar multiplication and assignment
Vector& Vector::operator*= (double scale)
{
    for(int i=0;i<fDimension;i++)
    {
        fElements[i]*=scale;
    }
    return *this;
}

// equality
bool Vector::operator== (const Vector &v2) const
{
    if(fDimension==v2.fDimension)
    {
        for(int i=0;i<fDimension;i++)
        {
            if(fElements[i]!=v2.fElements[i])
                return false;
        }
        return true;
    }
    return false;
}
// inequality
bool Vector::operator!= (const Vector &v2) const
{
    //return(!operator== (const Vector &v2));   //ASK//
    //return(! (this== v2) );   //ASK//
    
    
    if(fDimension!=v2.fDimension)
        return true;
    else
    {
        for(int i=0;i<fDimension;i++)
        {
            if(fElements[i]!=v2.fElements[i])
                return true;
        }
    }
    return false;
    
}
// length of a vector
double Vector::length() const
{
    double len=0;
    for(int i=0;i<fDimension;i++)
    {
        len+=fElements[i]*fElements[i];
    }
    return sqrt(len);
}
// display the vector to the output stream
ostream & operator << (ostream &os, const Vector &v)
{
    os<<'(';
    for(int i=0;i<v.fDimension;i++)
    {
        os<<v.fElements[i];
        if(i!=v.fDimension-1)
            os<<','<<' ';
    }
    os<<')';
    return os;
}
//double operator*();

// Private //
// initialization routine for allocating appropriate memory
void Vector::initialize(int size)
{
    fElements=new double[size];
    for(int i=0;i<size;i++)
    {
        fElements[i]=0;
    }
}
