// Cpush+ version 0.10
// defines a class for particle tracks
// in a uniform magnetic field, with
// a simple leapfrog pushing method.

// compile me with boost-python!

#include <iostream>
#include <fstream>

#include <string>
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

typedef Vector3d eigvec;
typedef Matrix3d eigmat;

const double pi = 3.1415926;
const eigmat I  = eigmat::Identity();

// particle track class
class track{
public:
  // initialise track properties
  double mass, charge;

  // object constructor
  track(string);

  // field interpolation method
  eigmat interpolate(eigvec x, double step){
    // retrieve vector field
    eigvec B_ = eigvec(0,0,1);

    // compute magnetic rotation map
    eigmat hatmap;
    hatmap << +0,     -B_[2], +B_[1],
              +B_[2], +0,     -B_[0],
              -B_[1], +B_[0], +0;
    hatmap *= (charge * step) / (2 * mass);
    return hatmap;
  }

  // leapfrog pushing method
  int leapfrog(double step, int nsteps, string fname){
    // set transverse velocity
    double eV = 1E-03;
    double vx = sqrt((2 * eV * abs(charge))/mass);

    // initialise dynamic variables
    eigvec x_ = eigvec(0,  0, 0);
    eigvec v_ = eigvec(vx, 0, 0);

    // backwards half-step the velocity
    eigmat hatmap = -(1./2.) * interpolate(x_, step);
    v_  = (I + hatmap).inverse() * (I - hatmap) * v_;

    // open a stream to write to file
    fstream track_io (fname.c_str(), ios::out | ios::binary);
    if (track_io.is_open()){

      // particle pushing loop
      for (int n = 0; n <= nsteps; n++){

        // write the position & velocity to file
        track_io << n << ' ' << ' ' << x_[0] << ' ' << x_[1] << ' ' << x_[2];
        track_io      << ' ' << ' ' << v_[0] << ' ' << v_[1] << ' ' << v_[2] << endl;

        // update the velocity and position
        hatmap = interpolate(x_, step);
        v_  = (I + hatmap).inverse() * (I - hatmap) * v_;
        x_ += v_ * step;
      }
    }
    return 0;
  }
};

// track object constructor
track::track(string ptype){
  if ((ptype == "antiproton") || (ptype == "pbar")){
    mass   = +1.67E-27;
    charge = -1.60E-19;
  }

  if ((ptype == "positron") || (ptype == "e+")){
    mass   = +9.11E-31;
    charge = +1.60-19;
  }
}

// create a boost-python wrapper for the track class
#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(push)
{
    class_<track>("track", init<string>())
        .def("interpolate", &track::interpolate)
        .def("leapfrog", &track::leapfrog)
    ;
}
