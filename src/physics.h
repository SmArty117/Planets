#include<cmath>
#include<iostream>
#include<fstream>
#include<cstdio>
#include<vector>
#include<string>

using namespace std;

#define NDIM 2
#define EPS  1.e-8

extern double G;
extern double dt;

// function for comparing floats and doubles. Very basic.
bool flequals(double a, double b);


// the Vector class, that supports all of this stuff. Much important
class Vector{
    private:
        double *v;
        int dim;
    public:
        // constructors
       /*  Vector(double a[], int dimensions = NDIM); */
        explicit Vector(int dimensions = NDIM);
        Vector(const Vector& vec);
        Vector(const vector<double>& vec);

        // a destructor because why not
        ~Vector();

        // some getters and checks and stuff
        int getDim() const;
        double mod() const;
        double ang() const;
        double comp(int i) const;
        void print() const;
        bool isZero() const;
        string getString() const;

        // only function that actually modifies components
        void setComp(int i, double value);

        // operators
        Vector & operator=(const Vector & b);
        Vector operator-() const;
        Vector & operator+=(const Vector & b);
        Vector & operator-=(const Vector & b);
        Vector operator+(const Vector & b) const;
        Vector operator-(const Vector & b) const;
        Vector operator*(double a) const;
        friend Vector operator*(double a, Vector vec);
        friend bool operator==(Vector lhs, Vector rhs);
        friend bool operator!=(Vector lhs, Vector rhs);
        
        // zero vector 
        static Vector zero(int dimensions = NDIM);
};

// The Object class. This represents anything: planets, stars, astronauts...
class Object{
    private:
        Vector position;
        Vector velocity;
        Vector acceleration;
        double mass;
        double charge;
    public:
        Object();

        Object(Vector initPosition = Vector::zero(NDIM),
         Vector initVelocity = Vector::zero(NDIM),
         double initMass = 0.0, 
         double initCharge = 0.0);

        /* Object(const vector<double> & initPosition,
         const vector<double> & initVelocity,
         double initMass = 0.0,
         double initCharge = 0.0); */

        // setters
        void setPosition(const Vector & newPos);
        void setVelocity(const Vector & newVel);
        void setAcceleration(const Vector & newAcc);
        void setMass(double m);
        void setCharge(double q);

        //getters
        double m() const;
        double q() const;
        Vector pos() const;
        Vector vel() const;
        Vector acc() const;
        string output() const;

        // I wanna know when i have the same object
        friend bool operator==(const Object & lhs, const Object & rhs);
        friend bool operator!=(const Object & lhs, const Object & rhs);
};

// list of all objects in a system:
extern vector<Object> objects;
extern vector<Vector> accelerations;

// forces:
Vector gravForce(Object o1, Object o2);
Vector totalForce(Object o);

// update routines:
void leapfrogUpdate();
void simpleUpdate();
