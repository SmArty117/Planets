#include "physics.h"

int NITER;

ofstream fout ("data/output.dat");

void createObjects() {
    // put a Sun in the middle:
    Vector sunPos({0, 0});
    Vector sunVel({0, 0});
    Object sun(sunPos, sunVel, 3e5);
    objects.push_back(sun);

    // make a planet as well:
    Vector pos1({0, 25});
    Vector vel1({3, 0});
    Object planet1(pos1, vel1, 1);
    objects.push_back(planet1);
}

void readFromFile() {
    ifstream fin ("data/planets.dat");
    double x, m;
    int np, nd;
    //read G and dt
    fin >> G >> dt >> NITER;
    // number of particles and dimensions
    fin >> np >> nd;

    // for each particle read the mass, nd position coordinates and nd velocity coordinates
    // create the object and push it to the vector
    for(int i = 0; i < np; i++) {
        fin >> m;
        // o.setCharge(q);
        Vector r;
        for(int j = 0; j < nd; j++) {
            fin >> x;
            r.setComp(j, x);
        }

        Vector v;
        for(int j = 0; j < nd; j++) {
            fin >> x;
            v.setComp(j, x);
        }

        Object o(r, v, m);
        objects.push_back(o);
    }
}

int main() {
    readFromFile();

    // just checking
    cout << gravForce(objects[1], objects[0]).getString() << endl;

    for(vector<Object>::iterator it = objects.begin(); it != objects.end(); it++)
        cout << totalForce(*it).getString() << endl;

    // run the sim NITER times
    for(int i = 0; i < NITER; i++) {
        leapfrogUpdate();
        for(vector<Object>::iterator it = objects.begin(); it != objects.end(); it++)
            fout << (*it).output();
        fout << "\n";
    }

    return 0;
}