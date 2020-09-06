#include <iostream>
#include <utility>

#include "geo2ecef.h"

// https://www.mathworks.com/help/aerotbx/ug/lla2ecef.html


namespace jly_tutorials
{
	/*
	* // https://geodesy.noaa.gov/cgi-bin/xyz_getxyz.prl
	=============================================================
		   Latitude           Longitude      Ellip_Ht   Ellipsoid
	 INPUT =   N420000.0          W0830000.0     0.0        GRS80
	 =============================================================
	  X (Meters)    Y (Meters)    Z (Meters)    ELLIPSOID
	  ------------- ------------- ------------- ---------
		578513.6474 -4711615.5579  4245603.8360 GRS80

	*/

	/*
	main_llaxyz():
	xyz() constructor.
	x, y, z = 578514, -4.71162e+06, 4.2456e+06
	 main_llaxyz() - constructing an lla object.
	Coord.ecef_to_geo() - constructing an 'lla' object.
	lla() constructor.
	Coord.ecef_to_geo() - returning lla object.
	lla() - move constructor.
	lla() - copy constructor.
	lat, lon, alt = 42, -83, -8.70998e-06
	*/
	void main_llaxyz()
	{
		Coord coord;
		std::cout << "main_llaxyz():" << std::endl;
		xyz pos = coord.geo_to_ecef(42., -83., 0);
		show_xyz(pos);
		std::cout << " main_llaxyz() - copy assignment." << std::endl;
		lla loc = coord.ecef_to_geo(578513.6474, -4711615.5579, 4245603.8360);
		show_lla(loc);
	}
}

