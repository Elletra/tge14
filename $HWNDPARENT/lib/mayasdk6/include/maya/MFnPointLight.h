
#ifndef _MFnPointLight
#define _MFnPointLight
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
// CLASS:    MFnPointLight
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnPointLight)
//
// MFnPointLight facilitates creation and manipulation of dependency graph
// nodes representing point lights.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnDagNode.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>
#include <maya/MFnNonExtendedLight.h>

// *****************************************************************************

// DECLARATIONS

class MVector;

// *****************************************************************************

// CLASS DECLARATION (MFnPointLight)

/// Manage Point Light dependency Nodes
/**
  Facilitate the creation and manipulation of point light nodes.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MFnPointLight : public MFnNonExtendedLight 
{

	declareDagMFn(MFnPointLight,MFnNonExtendedLight);

public:
	///
	MObject     create( bool UIvisible = true, MStatus * ReturnStatus = NULL );
	///
	MObject     create( const MObject& parent, bool UIvisible = true,
						MStatus * ReturnStatus = NULL );

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
#endif /* _MFnPointLight */



