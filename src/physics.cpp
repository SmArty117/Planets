#include "physics.h"

vector<Object> objects;
vector<Vector> accelerations;

double G;
double dt;

// update routines:

void simpleUpdate() {
    vector<Object>::iterator i;

    // calculate accelerations
    for(i=objects.begin(); i!=objects.end(); i++)
        (*i).setAcceleration(totalForce(*i)*(1/(*i).m()));
    
    // do dr += v*dt + a*dt^2/2
    for(i=objects.begin(); i!=objects.end(); i++) {
        (*i).setPosition((*i).pos() + (*i).vel()*dt +
        (*i).acc()*(dt*dt/2));
        (*i).setVelocity((*i).vel() + (*i).acc()*dt);
    }
}

void leapfrogUpdate() {
    vector<Object>::iterator it;
    int i;

    // update positions
    for(it=objects.begin(); it!=objects.end(); it++)
        (*it).setPosition((*it).pos() + (*it).vel()*dt +
        (*it).acc()*(dt*dt/2));

    // save old accelerations and calculate new ones
    accelerations.clear();
    for(it=objects.begin(); it!=objects.end(); it++) {
        accelerations.push_back((*it).acc());
        (*it).setAcceleration(totalForce(*it)*(1/(*it).m()));
    }

    // update velocities with mean of old and new acc
    for(it=objects.begin(), i=0; it!=objects.end(); it++, i++)
        (*it).setVelocity((*it).vel() + ((*it).acc() + accelerations[i]) * (dt/2));
}


// force expressions: could include electrostatic, elastic, whatever.
Vector gravForce(Object o1, Object o2) {
    // gravitational force by o2 on o1
    // vector pointing from o1 to o2: pos(o2) - pos(o1);
    Vector dr = o2.pos() - o1.pos();

    // calculate the distance and cube it
    double dist = dr.mod();
    double distcube = dist*dist*dist;

    // return GMm / r^3 * r(vector)
    return G * o1.m() * o2.m() / (distcube) * dr;
}

// get the total force on an object. This function can be modified to include whatever forces we want.
Vector totalForce(Object o) {
    // total force from all the other objects on object o
    Vector force(NDIM);
    vector<Object>::iterator i;
    for(i = objects.begin(); i != objects.end(); i++)
        if(o != (*i))
            force += gravForce(o, *i);
    return force;
}
