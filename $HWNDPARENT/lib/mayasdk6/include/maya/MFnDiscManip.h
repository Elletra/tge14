
#ifndef _MFnDiscManip
#define _MFnDiscManip
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
// CLASS:    MFnDiscManip
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnDiscManip)
//
// Function set for a base manipulator - the DiscManip.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnBase.h>
#include <maya/MFnManip3D.h>
#include <maya/MObject.h>

// *****************************************************************************

// DECLARATIONS

class MPoint;
class MVector;
class MAngle;

// *****************************************************************************

// CLASS DECLARATION (MFnDiscManip)

/// DiscManip function set (OpenMayaUI)
/**
MFnDiscManip is the function set for disc manipulators.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAUI_EXPORT MFnDiscManip : public MFnManip3D
{
	declareDagMFn(MFnDiscManip, MFnManip3D);

public:
	///
	MObject		create(MStatus *ReturnStatus = NULL);
	///
	MObject		create(const MString &manipName,
					   const MString &angleName,
					   MStatus *ReturnStatus = NULL);
	///
	MStatus		connectToAnglePlug(MPlug &anglePlug);
	///
	MStatus		setCenterPoint(const MPoint &centerPoint);
	///
	MStatus		setNormal(const MVector &normal);
	///
	MStatus		setRadius(double radius);
	///
	MStatus		setAngle(MAngle angle);
	///
	unsigned	centerIndex(MStatus *ReturnStatus = NULL) const;
	///
	unsigned	axisIndex(MStatus *ReturnStatus = NULL) const;
	///
	unsigned	angleIndex(MStatus *ReturnStatus = NULL) const;

protected:

private:

};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MFnDiscManip */
