#include <iostream>

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

	void main_llaxyz()
	{
		//Coord coord;
		std::cout << "main_llaxyz():" << std::endl;
		xyz pos = Coord2::geo_to_ecef(42., -83., 0);
		show_xyz(pos);
		lla loc = Coord2::ecef_to_geo(578513.6474, -4711615.5579, 4245603.8360);
		show_lla(loc);
	}
}

