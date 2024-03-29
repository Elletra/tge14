#ifndef _MTime
#define _MTime
//
//-
// ==========================================================================
// Copyright  (C)  Alias Systems,  a division  of  Silicon Graphics  Limited.
// All rights  reserved.  These coded  instructions,  statements and computer
// programs  contain  unpublished information  proprietary to  Alias Systems,
// a  division  of  Silicon  Graphics  Limited,  which  is  protected by  the
// Canadian  and  US federal copyright law and  may not be disclosed to third
// parties or  copied  or  duplicated,  in  whole  or in part,  without prior
// written  consent  of Alias Systems, a division of Silicon Graphics Limited
// ==========================================================================
//+
//
// CLASS:    MTime
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MTime)
//
// The MTime class provides a fundamental type for the Maya API to hold and
// manipulate animation timing information in various unit systems.  All
// API methods that require or return timing information do so through
// variables of this type.
// 
// If one desires to manipulate time in such a way that integer changes in
// an MTime instance result in integer changes in the frame displayed by
// the timeslider, then an MTime instance should be created that uses UI
// units.  This can be done either by using the default constructor, or by
// passing the return value of the static method uiUnit to the normal
// constructor.  Once such an MTime instance is created, its value will be
// equivalent to a frame on the timeslider.
// 
// It should be noted that while the timeslider displays frames, a
// seemingly unitless value, Maya internally is operating based on the
// desired frameRate (one of those specified by the MTime::Unit enum.  It
// is necessary for the API programmer to be aware of this as MTime
// instances are not unitless and allow the manipulation of time in any
// desired units.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES



#include <maya/MTypes.h>
#include <maya/MStatus.h>

// *****************************************************************************

// DECLARATIONS

// *****************************************************************************

// CLASS DECLARATION (MTime)

///	Set and retrieve animation time values.
/**
 Methods for setting and retreiving animation times in various unit systems.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MTime  
{

public:
	///
	enum Unit {
		///
		kInvalid,
		/// 3600 seconds
		kHours,                             //      3600    sec 
		/// 60 seconds
		kMinutes,                           //      60      sec
		/// 1 second
		kSeconds,                           //      1       sec
		/// 1/1000 of a second
		kMilliseconds,                      //      1/1000  sec
		/// 15 frames per second
		kGames,                             //      1/15    sec
		/// 24 frames per second
		kFilm,                              //      1/24    sec
		/// 25 frames per second
		kPALFrame,                          //      1/25 sec (approx)
		/// 30 frames per second
		kNTSCFrame,                         //      1/30 sec (approx)
		/// twice the speed of film (48 frames per second)
		kShowScan,                          //      1/48    sec
		/// twice the speed of PAL (50 frames per second)
		kPALField,                          //      1/50 sec (approx)
		/// twice the speed of NTSC (60 frames per second)
		kNTSCField,                         //      1/60 sec (approx)
		/// 2 frames per second
		k2FPS,								//		1/2 sec
		/// 3 frames per second
		k3FPS,								//		1/3 sec
		/// 4 frames per second
		k4FPS,								//		1/4 sec
		/// 5 frames per second
		k5FPS,								//		1/5 sec
		/// 6 frames per second
		k6FPS,								//		1/6 sec
		/// 8 frames per second
		k8FPS,								//		1/8 sec
		/// 10 frames per second
		k10FPS,								//		1/10 sec
		/// 12 frames per second
		k12FPS,								//		1/12 sec
		/// 16 frames per second
		k16FPS,								//		1/16 sec
		/// 20 frames per second
		k20FPS,								//		1/20 sec
		/// 40 frames per second
		k40FPS,								//		1/40 sec
		/// 75 frames per second
		k75FPS,								//		1/75 sec
		/// 80 frames per second
		k80FPS,								//		1/80 sec
		/// 100 frames per second
		k100FPS,							//		1/100 sec
		/// 120 frames per second
		k120FPS,							//		1/120 sec
		/// 125 frames per second
		k125FPS,							//		1/125 sec
		/// 150 frames per second
		k150FPS,							//		1/150 sec
		/// 200 frames per second
		k200FPS,							//		1/200 sec
		/// 240 frames per second
		k240FPS,							//		1/240 sec
		/// 250 frames per second
		k250FPS,							//		1/250 sec
		/// 300 frames per second
		k300FPS,							//		1/300 sec
		/// 375 frames per second
		k375FPS,							//		1/375 sec
		/// 400 frames per second
		k400FPS,							//		1/400 sec
		/// 500 frames per second
		k500FPS,							//		1/500 sec
		/// 600 frames per second
		k600FPS,							//		1/600 sec
		/// 750 frames per second
		k750FPS,							//		1/750 sec
		/// 1200 frames per second
		k1200FPS,							//		1/1200 sec
		/// 1500 frames per second
		k1500FPS,							//		1/1500 sec
		/// 2000 frames per second
		k2000FPS,							//		1/2000 sec
		/// 3000 frames per second
		k3000FPS,							//		1/3000 sec
		/// 6000 frames per second
		k6000FPS,							//		1/6000 sec
		/// user defined units (not implemented yet)
		kUserDef,                           //      user defined
		///
		kLast
	};
	///
					MTime();
	///
					MTime( const MTime & );
	///
					MTime( double time_val, Unit = kFilm );
	///
					~MTime();
	///
 	Unit     		unit() const;
	///
 	double   		value() const;
	///
 	MStatus 	 	setUnit( Unit new_unit );
	///
 	MStatus 		setValue( double new_value );
	///
 	double    		as( Unit other_unit ) const;
	///
	static Unit		uiUnit();
	///
	static MStatus	setUIUnit( Unit new_unit);

	///
	MTime&			operator =  ( const MTime& rhs );
	///
	bool			operator == ( const MTime& rhs ) const;
	///
	bool			operator != ( const MTime& rhs ) const;
	///
	bool			operator <= ( const MTime& rhs ) const;
	///
	bool			operator >= ( const MTime& rhs ) const;
	///
	bool			operator <  ( const MTime& rhs ) const;
	///
	bool			operator >  ( const MTime& rhs ) const;
	///
	MTime			operator +  ( const MTime& rhs ) const;
	///
	MTime&			operator += ( const MTime& rhs );
	///
	MTime			operator +  ( double rhs ) const;
	///
	MTime&			operator += ( double rhs );
	///
	MTime&			operator ++ ();
	///
	MTime&			operator ++ (int);
	///
	MTime			operator -  ( const MTime& rhs ) const;
	///
	MTime&			operator -= ( const MTime& rhs );
	///
	MTime			operator -  ( double rhs ) const;
	///
	MTime&			operator -= ( double rhs );
	///
	MTime&			operator -- ();
	///
	MTime&			operator -- (int);
	///
	MTime			operator *  ( double rhs ) const;
	///
	MTime&			operator *= ( double rhs );
	///
	MTime			operator /  ( double rhs ) const;
	///
	MTime&			operator /= ( double rhs );

	///
	friend OPENMAYA_EXPORT IOS_REF(ostream)&	operator << ( IOS_REF(ostream)& os, const MTime& t );

protected:
	// No protected members

private:
	friend class MTimeHelper;
	MTime			( int );
	static const	char* className();
 	int	val;
 	Unit	valUnit;
	void*   data;
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MTime */
