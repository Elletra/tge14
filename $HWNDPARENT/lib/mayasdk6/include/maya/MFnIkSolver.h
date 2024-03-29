
#ifndef _MFnIkSolver
#define _MFnIkSolver
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
// CLASS:    MFnIkSolver
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnIkSolver)
//
//  This is the function set for inverse kinematics (IK) solvers.
//  This function set is used for setting and querying attached
//  ik solvers.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnDependencyNode.h>
#include <maya/MFnTransform.h>

// *****************************************************************************

// DECLARATIONS

// *****************************************************************************

// CLASS DECLARATION (MFnIkSolver)

/// Function set for inverse kinematics (IK) solvers (OpenMayaAnim)
/**

*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAANIM_EXPORT MFnIkSolver : public MFnDependencyNode
{
	declareMFn( MFnIkSolver, MFn::kIkSolver );

public:
	///
	unsigned maxIterations( MStatus * ReturnStatus = NULL );
	///
	MStatus setMaxIterations( unsigned maxIters );
	///
	double tolerance( MStatus * ReturnStatus = NULL );
	///
	MStatus setTolerance( double tolerance );

protected:
// No protected members

private:
// No private members

};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MFnIkSolver */
