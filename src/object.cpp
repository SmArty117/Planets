#include "physics.cpp"

Object::Object() {
    this->position = Vector::zero();
    this->velocity = Vector::zero();
    this->acceleration = Vector::zero();
    this->mass = 0.0;
    this->charge = 0.0;
}

Object::Object(const Vector initPosition, const Vector initVelocity, double initMass, double initCharge) {
    if(initPosition.getDim() != initVelocity.getDim()) {
        cerr << "Different dimensions of vectors. Cannot initialize object.";
        return;
    }
    this->position = Vector(initPosition);
    this->velocity = Vector(initVelocity);
    this->mass = initMass;
    this->charge = initCharge;
    this->acceleration = Vector(initPosition.getDim());
}

/* Object::Object(const vector<double> & initPosition, const vector<double> & initVelocity, double initMass, double initCharge) {
    if(initPosition.size() != initVelocity.size()) {
        cerr << "Different dimensions of vectors. Cannot initialize object.";
        return;
    }
    this->position = Vector(initPosition);
    this->velocity = Vector(initVelocity);
    this->mass = initMass;
    this->charge = initCharge;
} */

// setters
void Object::setCharge(double q) {
    this->charge = q;
}

void Object::setMass(double m) {
    this->mass = m;
}

void Object::setPosition(const Vector & newPos) {
    this->position = newPos;
}

void Object::setVelocity(const Vector & newVel) {
    this->velocity = newVel;
}

void Object::setAcceleration(const Vector & newAcc) {
    this->acceleration = newAcc;
}

// getters
double Object::m() const {
    return mass;
}
double Object::q() const {
    return charge;
}
Vector Object::pos() const {
    return Vector(position);
}
Vector Object::vel() const {
    return Vector(velocity);
}
Vector Object::acc() const {
    return Vector(acceleration);
}

string Object::output() const {
    string str("");
    int dim = this->pos().getDim();
    // add the position
    for(int i = 0; i < dim; i++) {
        str += to_string(this->pos().comp(i)) + "\t";
    }

    // add the velocity
    for(int i = 0; i < dim; i++) {
        str += to_string(this->vel().comp(i)) + "\t";
    }

    // add the KE
    str += to_string(this->m()*this->vel().mod()*this->vel().mod()/2) + "\t";

    // add the ang mom
    str += to_string(this->m() * this->vel().mod() * this->pos().mod() * sin(this->vel().ang() - this->pos().ang())) + "\t";

    return str;
}

bool operator==(const Object & lhs, const Object & rhs) {
    if(lhs.position != rhs.position)
        return false;
    if(lhs.velocity != rhs.velocity)
        return false;
    if(lhs.acceleration != rhs.acceleration)
        return false;
    if(lhs.mass != rhs.mass)
        return false;
    if(lhs.charge != rhs.charge)
        return false;
    return true;
}

bool operator!=(const Object & lhs, const Object & rhs) {
    return !(lhs == rhs);
}