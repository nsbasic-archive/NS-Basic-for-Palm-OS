/***************************************************************************
 *  This code in this file is contributed from samples in the Garmin SDK
 *  and from public domain code found on the web.
 ***************************************************************************/
 
#define semiToDeg           (180.0 / 2147483648.0)      /* semicircles to degrees           */
#define minMax              60                          /* max minute value                 */
#define minScale            1000000                     /* minute scaling                   */
#define minDigits           2                           /* 2 digits for whole minutes       */
#define minPrecision        6                           /* 6 digits of minute precision     */
#define degMax              360                         /* max degree value                 */

/*********************************************************************
*
*   PROCEDURE NAME:
*       AppendIntToStr - Append Integer to String with Leading Zeros
*
*   DESCRIPTION:
*       Appends the integer to a string, padding with leading zeros
*       the width specified.
*
*********************************************************************/
static void AppendIntToStr(Int32 number, int width, Char *outStr)
{
	/*----------------------------------------------------------
	Variables
	----------------------------------------------------------*/
	Char    buf[10];  /* temporary buffer             */
	int     padCount;   /* count of characters to pad   */
	int     i;          /* loop counter                 */

	/*----------------------------------------------------------
	Convert number to a string and determine the number of
	characters that need to be padded.
	----------------------------------------------------------*/
	StrIToA(buf, number);
	padCount = width - StrLen(buf);

	/*----------------------------------------------------------
	Write padCount zeros to output string
	----------------------------------------------------------*/
	for (i = 0; i < padCount; ++i) {
	    StrCat(outStr, "0");
    }

	/*----------------------------------------------------------
	Write converted number to output string
	----------------------------------------------------------*/
	StrCat(outStr, buf);

} /* AppendIntToStr() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       LatLonToString - Convert Lat/Lon to String
*
*   DESCRIPTION:
*       Converts the semicircle lat/lon to a string.
*
*********************************************************************/
void LatLonToString(char *neswStr, Boolean showSeconds, Int32 value, Char *outStr)
{
	/*----------------------------------------------------------
	Variables
	----------------------------------------------------------*/
	double      degrees;        /* location in degrees        */
	double      minutes;        /* location in minutes        */
	double      seconds;
	Int32       wholeDeg;       /* whole part of degrees      */
	Int32       wholeMin;       /* whole part of minutes      */
	Int32       wholeSec;
	Int32       fracMin;        /* fractional part of minutes */
	Int32       fracSec;

	/*----------------------------------------------------------
	Write hemisphere character into string
	----------------------------------------------------------*/
	outStr[0] = (value < 0) ? neswStr[1] : neswStr[0];
	outStr[1] = NULL;

	/*----------------------------------------------------------
	Take absolute value and convert to degrees
	----------------------------------------------------------*/
	degrees = Abs(value) * semiToDeg;

	/*----------------------------------------------------------
	Format into DD°MM.MMM': get whole degrees
	----------------------------------------------------------*/
	wholeDeg = (Int32) degrees;

	/*----------------------------------------------------------
	Get minutes from remaining degrees
	----------------------------------------------------------*/
	minutes = (degrees - (double) wholeDeg) * minMax;
	/*----------------------------------------------------------
	Get whole minutes
	----------------------------------------------------------*/
	wholeMin = (Int32) minutes;
    
	if (showSeconds) {
	    seconds = (minutes - (double) wholeMin) * minMax;
	    wholeSec = (Int32) seconds;
	}
	
	/*----------------------------------------------------------
	Get fractional minutes as an integer by rounding
	and scaling.
	----------------------------------------------------------*/
	fracMin = (Int32) ((minutes - (float) wholeMin) * minScale);
    
    if (showSeconds)
	    fracSec = (Int32) ((seconds - (float) wholeSec) * minScale);
	/*----------------------------------------------------------
	Handle possible overflow from rounding
	----------------------------------------------------------*/
	if (fracMin >= minScale) {
	    ++wholeMin;
	    fracMin -= minScale;
	    if (wholeMin >= minMax) {
	        ++wholeDeg;
	        wholeMin -= minMax;
	        if (wholeDeg >= degMax ) {
	            wholeDeg -= degMax;
	        }
	    }
	}
    if (showSeconds)
		if (fracSec >= minScale) {
		    ++wholeSec;
		    fracSec -= minScale;
		    if (wholeSec >= minMax) {
		        ++wholeMin;
		        wholeSec -= minMax;
		        if (wholeMin >= minMax ) {
		            wholeMin -= minMax;
		        }
		    }
		}

	/*----------------------------------------------------------
	Build into string
	----------------------------------------------------------*/
	AppendIntToStr(wholeDeg, 3, outStr);
	StrCat(outStr, "°");
	AppendIntToStr(wholeMin, minDigits, outStr);
	if (showSeconds) {
	    StrCat(outStr, "'");
	    AppendIntToStr(wholeSec, minDigits, outStr);
	    StrCat(outStr, ".");
	    AppendIntToStr(fracSec, minPrecision, outStr);
	    StrCat(outStr, "\"");
    }
	else {
	    StrCat(outStr, ".");
    	AppendIntToStr(fracMin, minPrecision, outStr);
	    StrCat(outStr, "'");
	}

} /* LatLonToString() */




/*Reference ellipsoids derived from Peter H. Dana's website- 
http://www.utexas.edu/depts/grg/gcraft/notes/datum/elist.html
Department of Geography, University of Texas at Austin
Internet: pdana@mail.utexas.edu
3/22/95

Source
Defense Mapping Agency. 1987b. DMA Technical Report: Supplement to Department of Defense World Geodetic System
1984 Technical Report. Part I and II. Washington, DC: Defense Mapping Agency
*/


char UTMLetterDesignator(double Lat)
{
//This routine determines the correct UTM letter designator for the given latitude
//returns 'Z' if latitude is outside the UTM limits of 84N to 80S
	//Written by Chuck Gantz- chuck.gantz@globalstar.com
	char LetterDesignator;

	if ((84 >= Lat) && (Lat >= 72)) LetterDesignator = 'X';
	else if ((72 > Lat) && (Lat >= 64)) LetterDesignator = 'W';
	else if ((64 > Lat) && (Lat >= 56)) LetterDesignator = 'V';
	else if ((56 > Lat) && (Lat >= 48)) LetterDesignator = 'U';
	else if ((48 > Lat) && (Lat >= 40)) LetterDesignator = 'T';
	else if ((40 > Lat) && (Lat >= 32)) LetterDesignator = 'S';
	else if ((32 > Lat) && (Lat >= 24)) LetterDesignator = 'R';
	else if ((24 > Lat) && (Lat >= 16)) LetterDesignator = 'Q';
	else if ((16 > Lat) && (Lat >= 8)) LetterDesignator = 'P';
	else if (( 8 > Lat) && (Lat >= 0)) LetterDesignator = 'N';
	else if (( 0 > Lat) && (Lat >= -8)) LetterDesignator = 'M';
	else if ((-8> Lat) && (Lat >= -16)) LetterDesignator = 'L';
	else if ((-16 > Lat) && (Lat >= -24)) LetterDesignator = 'K';
	else if ((-24 > Lat) && (Lat >= -32)) LetterDesignator = 'J';
	else if ((-32 > Lat) && (Lat >= -40)) LetterDesignator = 'H';
	else if ((-40 > Lat) && (Lat >= -48)) LetterDesignator = 'G';
	else if ((-48 > Lat) && (Lat >= -56)) LetterDesignator = 'F';
	else if ((-56 > Lat) && (Lat >= -64)) LetterDesignator = 'E';
	else if ((-64 > Lat) && (Lat >= -72)) LetterDesignator = 'D';
	else if ((-72 > Lat) && (Lat >= -80)) LetterDesignator = 'C';
	else LetterDesignator = 'Z'; //This is here as an error flag to show that the Latitude is outside the UTM limits

	return LetterDesignator;
}

void GetDatumParams(Int32 datumID, UInt32 *equatorialRadius, double *eccentricitySquared)
{
    *equatorialRadius = 0;
    if (datumID == 0) {
        *equatorialRadius = 6378137;
        *eccentricitySquared = 0.00669438;
    }
    else if (datumID == 1) {
        *equatorialRadius = 6377276;
        *eccentricitySquared = 0.006637847;
    }
    else if (datumID == 2) {
        *equatorialRadius = 6377304;
        *eccentricitySquared = 0.006637847;
    }
    else if (datumID == 3) {
        *equatorialRadius = 6377340;
        *eccentricitySquared = 0.00667054;
    }
    else if (datumID == 4) {
        *equatorialRadius = 6377397;
        *eccentricitySquared = 0.006674372;
    }
    else if (datumID == 5) {
        *equatorialRadius = 6377484;
        *eccentricitySquared = 0.006674372;
    }
    else if (datumID == 6) {
        *equatorialRadius = 6377563;
        *eccentricitySquared = 0.00667054;
    }
    else if (datumID == 7) {
        *equatorialRadius = 6378135;
        *eccentricitySquared = 0.006694318;
    }
    else if (datumID == 8) {
        *equatorialRadius = 6378137;
        *eccentricitySquared = 0.00669438;
    }
    else if (datumID == 9) {
        *equatorialRadius = 6378145;
        *eccentricitySquared = 0.006694542;
    }
    else if (datumID == 10) {
        *equatorialRadius = 6378150;
        *eccentricitySquared = 0.006693422;
    }
    else if (datumID == 11) {
        *equatorialRadius = 6378155;
        *eccentricitySquared = 0.006693422;
    }
    else if (datumID == 12) {
        *equatorialRadius = 6378160;
        *eccentricitySquared = 0.006694542;
    }
    else if (datumID == 13) {
        *equatorialRadius = 6378165;
        *eccentricitySquared = 0.006693422;
    }
    else if (datumID == 14) {
        *equatorialRadius = 6378166;
        *eccentricitySquared = 0.006693422;
    }
    else if (datumID == 15) {
        *equatorialRadius = 6378200;
        *eccentricitySquared = 0.006693422;
    }
    else if (datumID == 16) {
        *equatorialRadius = 6378206;
        *eccentricitySquared = 0.006768658;
    }
    else if (datumID == 17) {
        *equatorialRadius = 6378245;
        *eccentricitySquared = 0.006693422;
    }
    else if (datumID == 18) {
        *equatorialRadius = 6378249;
        *eccentricitySquared = 0.006803511;
    }
    else if (datumID == 19) {
        *equatorialRadius = 6378270;
        *eccentricitySquared = 0.00672267;
    }
    else if (datumID == 20) {
        *equatorialRadius = 6378388;
        *eccentricitySquared = 0.00672267;
    }
}

void LLtoUTM(UInt16 refNum, const UInt32 equatorialRadius, const double eccentricitySquared, 
             const double Lat, const double Long, 
			 double *UTMEasting, double *UTMNorthing, char *UTMZone)
{
// converts lat/long to UTM coords.  Equations from USGS Bulletin 1532 
// East Longitudes are positive, West longitudes are negative. 
// North latitudes are positive, South latitudes are negative
// Lat and Long are in decimal degrees
// Written by Chuck Gantz- chuck.gantz@globalstar.com

	double deg2rad = 0.0174532925;  // PI (3.14159265) / 180;
	double a;
	double eccSquared;
	double k0 = 0.9996;
	double LongOrigin;
	double eccPrimeSquared;
	double N, T, C, A, M;
	double LongTemp;
	double LatRad;
	double LongRad;
	double LongOriginRad;
	Int32  ZoneNumber;
	char   zoneLetter[20];
	THIS_ATTACH_GLOBALS
	
	if (gP->mathLibLoaded) {
	    //Make sure the longitude is between -180.00 .. 179.9
		LongTemp = (Long + 180) - (double) (Int32)((Long + 180) / 360) * 360 - 180;
		LatRad = Lat * deg2rad;
		LongRad =  LongTemp * deg2rad;
	    a =  equatorialRadius;
	    eccSquared = eccentricitySquared;
		
		ZoneNumber = (Int32) ((LongTemp + 180)/6) + 1;
	  
		if(Lat >= 56.0 && Lat < 64.0 && LongTemp >= 3.0 && LongTemp < 12.0)
			ZoneNumber = 32;

	    // Special zones for Svalbard
		if (Lat >= 72.0 && Lat < 84.0) 
		{
		  if (LongTemp >= 0.0  && LongTemp < 9.0) ZoneNumber = 31;
		  else if (LongTemp >= 9.0 && LongTemp < 21.0) ZoneNumber = 33;
		  else if(LongTemp >= 21.0 && LongTemp < 33.0) ZoneNumber = 35;
		  else if(LongTemp >= 33.0 && LongTemp < 42.0) ZoneNumber = 37;
		 }
		LongOrigin = (ZoneNumber - 1)* 6 - 180 + 3;  //+3 puts origin in middle of zone
		LongOriginRad = LongOrigin * deg2rad;

		//compute the UTM Zone from the latitude and longitude
		StrIToA(UTMZone, ZoneNumber);
		zoneLetter[0] = UTMLetterDesignator(Lat);
		zoneLetter[1] = '\0'; 
		StrCat(UTMZone, zoneLetter);

		eccPrimeSquared = (eccSquared) / ( 1 - eccSquared);

		N = a / sqrt(1 - eccSquared * sin(LatRad) * sin(LatRad));
		T = tan(LatRad) * tan(LatRad);
		C = eccPrimeSquared * cos(LatRad) * cos(LatRad);
		A = cos(LatRad) * (LongRad - LongOriginRad);

		M = a * ((1 - eccSquared / 4 - 3 * eccSquared*eccSquared / 64 - 5 * eccSquared * eccSquared * eccSquared / 256) * LatRad 
	      - (3 * eccSquared / 8	+ 3 * eccSquared*eccSquared / 32 + 45 * eccSquared * eccSquared * eccSquared / 1024) * sin(2 * LatRad)
		  + (15 * eccSquared * eccSquared / 256 + 45 * eccSquared * eccSquared * eccSquared / 1024) * sin(4 * LatRad) 
	      - (35 * eccSquared * eccSquared * eccSquared / 3072) * sin(6 * LatRad));
		
		*UTMEasting = (double) (k0 * N *(A + (1 - T + C) * A *A * A / 6
		            + (5 - 18 * T + T * T + 72 * C - 58 * eccPrimeSquared) * A * A * A * A * A / 120)
	                + 500000.0);

		*UTMNorthing = (double) (k0 * (M + N * tan(LatRad) * (A * A / 2 + (5 - T + 9 * C + 4 * C * C) * A * A * A * A / 24
					 + (61 - 58 * T + T * T + 600 * C - 330 * eccPrimeSquared) * A * A * A * A *A * A / 720)));
		if (Lat < 0)
			*UTMNorthing += 10000000.0; //10000000 meter offset for southern hemisphere
    }
    else {
        *UTMEasting = -1;
        *UTMNorthing = -1;
        StrCopy(UTMZone, "");
    }
	THIS_DETACH_GLOBALS
}

void UTMtoLL(UInt16 refNum, UInt32 equatorialRadius, double eccentricitySquared,
                            const char *UTMZone, const double UTMEasting, const double UTMNorthing,
			                double *Lat,  double *Long )
{
//converts UTM coords to lat/long.  Equations from USGS Bulletin 1532 
//East Longitudes are positive, West longitudes are negative. 
//North latitudes are positive, South latitudes are negative
//Lat and Long are in decimal degrees. 
	//Written by Chuck Gantz- chuck.gantz@globalstar.com

	double rad2deg = 57.295779578552;  // 180 / PI (3.14159265);
	double k0 = 0.9996;
	double eccSquared;
	double a;
	double eccPrimeSquared;
	double e1;
	double N1, T1, C1, R1, D, M;
	double LongOrigin;
	double mu, phi1, phi1Rad;
	double x, y;
	Int32 ZoneNumber;
	char *ZoneLetter;
	Int32 NorthernHemisphere; //1 for northern hemisphere, 0 for southern
	THIS_ATTACH_GLOBALS
	
	if (gP->mathLibLoaded) {
	    a = equatorialRadius;
	    eccSquared = eccentricitySquared;
	    e1 = (1 - sqrt(1 - eccSquared)) / (1 + sqrt(1 - eccSquared));
		x = UTMEasting - 500000.0; //remove 500,000 meter offset for longitude
		y = UTMNorthing;

        ZoneLetter = (char *) UTMZone;
        while ((*ZoneLetter < 'A' || *ZoneLetter > 'Z') && *ZoneLetter != '\0')
             ZoneLetter++;
		ZoneNumber = StrAToI(UTMZone);
		if(*ZoneLetter >= 'N')
			NorthernHemisphere = 1;//point is in northern hemisphere
		else
		{
			NorthernHemisphere = 0;//point is in southern hemisphere
			y -= 10000000.0;//remove 10,000,000 meter offset used for southern hemisphere
		}

		LongOrigin = (ZoneNumber - 1) * 6 - 180 + 3;  //+3 puts origin in middle of zone

		eccPrimeSquared = (eccSquared) / (1 - eccSquared);

		M = y / k0;
		mu = M / (a * (1 - eccSquared / 4 - 3 * eccSquared * eccSquared / 64 - 5 * eccSquared * eccSquared * eccSquared / 256));

		phi1Rad = mu + (3 * e1 / 2 - 27 * e1 * e1 * e1 / 32) * sin(2 * mu) 
				+ (21 * e1 * e1 / 16 - 55 * e1 * e1 * e1 * e1 / 32) * sin(4 * mu)
				+ (151 * e1 * e1 * e1 / 96) * sin(6 * mu);
		phi1 = phi1Rad * rad2deg;

		N1 = a / sqrt(1 - eccSquared * sin(phi1Rad) * sin(phi1Rad));
		T1 = tan(phi1Rad) * tan(phi1Rad);
		C1 = eccPrimeSquared * cos(phi1Rad) * cos(phi1Rad);
		R1 = a * (1 - eccSquared) / pow(1 - eccSquared * sin(phi1Rad) * sin(phi1Rad), 1.5);
		D = x / (N1 * k0);

		*Lat = phi1Rad - (N1 * tan(phi1Rad) / R1) * (D * D / 2 - (5 + 3 * T1 + 10 * C1 - 4 * C1 * C1 - 9 * eccPrimeSquared) * D * D * D * D / 24
		     + (61 + 90 * T1 + 298 * C1 + 45 * T1 * T1 - 252 * eccPrimeSquared - 3 * C1 * C1) * D * D * D * D * D * D / 720);
		*Lat = *Lat * rad2deg;

		*Long = (D - (1 + 2 * T1 + C1) * D * D * D / 6 + (5 - 2 * C1 + 28 * T1 - 3 * C1 * C1 + 8 * eccPrimeSquared + 24 * T1 * T1)
		      * D * D * D * D * D /120) / cos(phi1Rad);
		*Long = LongOrigin + *Long * rad2deg;
	}
	else {
	    *Lat = -1.0;
	    *Long = -1.0;
	}
	THIS_DETACH_GLOBALS
}
