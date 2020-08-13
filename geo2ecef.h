#pragma once
#include <cmath>

// https://www.mathworks.com/help/aerotbx/ug/lla2ecef.html

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

namespace jly_tutorials
{
	typedef struct {
		double lat, lon, alt;
	} lla;

	typedef struct {
		double x, y, z;
	} xyz;

	void show_xyz(xyz pos);
	void show_lla(lla loc);

	class Coord2 {
	public:
		static double a;              //WGS-84 semi-major axis
		static double e2;  //WGS-84 first eccentricity squared
		static double a1;  //a1 = a*e2
		static double a2;  //a2 = a1*a1
		static double a3;  //a3 = a1*e2/2
		static double a4;  //a4 = 2.5*a2
		static double a5;  //a5 = a1+a3
		static double a6;  //a6 = 1-e2
		static double deg2rad;
		static double rad2deg;

		static double zp, w2, w, r2, r, s2, c2, s, c, ss;
		static double g, rg, rf, u, v, m, f, p;
		static double n;

		//Convert Earth-Centered-Earth-Fixed (ECEF) to lat, Lon, Altitude
		//Input is a three element array containing x, y, z in meters
		//Returned array contains lat and lon in degrees, and altitude in meters
		static lla ecef_to_geo(double x, double y, double z) {
			lla geo;   //Results go here (Lat, Lon, Altitude)
			zp = std::abs(z);
			w2 = x * x + y * y;
			w = std::sqrt(w2);
			r2 = w2 + z * z;
			r = std::sqrt(r2);
			geo.lon = std::atan2(y, x);       //Lon (final)
			s2 = z * z / r2;
			c2 = w2 / r2;
			u = a2 / r;
			v = a3 - a4 / r;
			if (c2 > 0.3) {
				s = (zp / r) * (1.0 + c2 * (a1 + u + s2 * v) / r);
				geo.lat = std::asin(s);      //Lat
				ss = s * s;
				c = std::sqrt(1.0 - ss);
			}
			else {
				c = (w / r) * (1.0 - s2 * (a5 - u - c2 * v) / r);
				geo.lat = std::acos(c);      //Lat
				ss = 1.0 - c * c;
				s = std::sqrt(ss);
			}
			g = 1.0 - e2 * ss;
			rg = a / std::sqrt(g);
			rf = a6 * rg;
			u = w - rg * c;
			v = zp - rf * s;
			f = c * u + s * v;
			m = c * v - s * u;
			p = m / (rf / g + f);
			geo.lat = geo.lat + p;      //Lat
			geo.alt = f + m * p / 2.0;     //Altitude
			if (z < 0.0) {
				geo.lat *= -1.0;     //Lat
			}
			geo.lat *= rad2deg;
			geo.lon *= rad2deg;
			return(geo);    //Return Lat, Lon, Altitude in that order
		}

		//Convert Lat, Lon, Altitude to Earth-Centered-Earth-Fixed (ECEF)
		//Input is a three element array containing lat, lon (degrees) and alt (m)
		//Returned array contains x, y, z in meters
		static xyz geo_to_ecef(double lat, double lon, double alt) {
			xyz ecef;
			lat = lat * deg2rad;
			lon = lon * deg2rad;
			n = a / std::sqrt(1 - e2 * std::sin(lat) * std::sin(lat));
			ecef.x = (n + alt) * std::cos(lat) * std::cos(lon);    //ECEF x
			ecef.y = (n + alt) * std::cos(lat) * std::sin(lon);    //ECEF y
			ecef.z = (n * (1 - e2) + alt) * std::sin(lat);          //ECEF z
			return(ecef);     //Return x, y, z in ECEF
		}
	};
}
