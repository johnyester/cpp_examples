#include <iostream>
#include "boost/format.hpp"

#include "geo2ecef.h"

namespace jly_tutorials
{
	double Coord2::a = 6378137.0;              //WGS-84 semi-major axis
	double Coord2::e2 = 6.6943799901377997e-3;  //WGS-84 first eccentricity squared
	double Coord2::a1 = 4.2697672707157535e+4;  //a1 = a*e2
	double Coord2::a2 = 1.8230912546075455e+9;  //a2 = a1*a1
	double Coord2::a3 = 1.4291722289812413e+2;  //a3 = a1*e2/2
	double Coord2::a4 = 4.5577281365188637e+9;  //a4 = 2.5*a2
	double Coord2::a5 = 4.2840589930055659e+4;  //a5 = a1+a3
	double Coord2::a6 = 9.9330562000986220e-1;  //a6 = 1-e2
	double Coord2::deg2rad = 0.01745329252;
	double Coord2::rad2deg = 57.295779513;
	double Coord2::zp;
	double Coord2::w2;
	double Coord2::w;
	double Coord2::r2;
	double Coord2::r;
	double Coord2::s2;
	double Coord2::c2;
	double Coord2::s;
	double Coord2::c;
	double Coord2::ss;
	double Coord2::g;
	double Coord2::rg;
	double Coord2::rf;
	double Coord2::u;
	double Coord2::v;
	double Coord2::m;
	double Coord2::f;
	double Coord2::p;
	double Coord2::n;

	void show_xyz(xyz pos)
	{
		std::cout << boost::format("x, y, z = %1%, %2%, %3%\n") % pos.x % pos.y % pos.z;
	}

	void show_lla(lla loc)
	{
		std::cout << boost::format("lat, lon, alt = %1%, %2%, %3%\n") % loc.lat % loc.lon % loc.alt;
	}

}
