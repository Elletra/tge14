
#ifndef _MAngle
#define _MAngle
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
// CLASS:    MAngle
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MAngle)
//
//	The MAngle class provides a fundamental type for the Maya API to hold
//	and manipulate angular data.  All API methods that require or return
//	angular information do so through variables of this type.
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

// CLASS DECLARATION (MAngle)

/// Manipulate Angular Data
/**
 Methods for setting and retreiving angular data in various unit systems
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MAngle  
{

public:
	/// Available Unit Systems
	enum Unit
	{
		///
		kInvalid,
		/// Radians
		kRadians,
		/// Degrees
		kDegrees,
		/// Minutes of Arc
		kAngMinutes,
		/// Seconds of Arc
		kAngSeconds,
		///
		kLast
	};
	///
	MAngle();
	///
	MAngle( const MAngle & src );
	///
	MAngle( double value, Unit u = kRadians );
 	///
 	~MAngle();
 	///
 	MAngle &     	operator=( const MAngle & other );
 	///
 	Unit    		unit() const;
 	///
 	double  		value() const;
 	///
 	MStatus         setUnit( Unit newUnit );
 	///
 	MStatus         setValue( double newValue );
 	///
 	double         	as( Unit otherUnit, MStatus *ReturnStatus = NULL ) const;
 	///
 	double         	asRadians() const;
 	///
 	double         	asDegrees() const;
 	///
 	double         	asAngMinutes() const;
 	///
 	double         	asAngSeconds() const;
 	///
 	static Unit		uiUnit();
 	///
 	static MStatus	setUIUnit( Unit newUnit );
	///
	static Unit		internalUnit();
	///
	static double	internalToUI( double internalValue );
	///
	static double	uiToInternal( double uiValue );
	///OBSOLETE Changing the internal units is generally not a good idea and using this method may often produce unexpected results.
	static MStatus  setInternalUnit( Unit internalUnit );

protected:
 	double 	val;
	Unit	valUnit;

private:
	static const char* className();

// No private members

};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MAngle */
