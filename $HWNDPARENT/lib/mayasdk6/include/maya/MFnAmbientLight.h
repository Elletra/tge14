
#ifndef _MFnAmbientLight
#define _MFnAmbientLight
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
// CLASS:    MFnAmbientLight
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnAmbientLight)
//
// MFnAmbientLight facilitates creation and manipulation of ambient light 
// dependency graph nodes.  
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnDagNode.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>
#include <maya/MFnLight.h>

// *****************************************************************************

// DECLARATIONS

class MPoint;
class MColor;
class MDagPath;

// *****************************************************************************

// CLASS DECLARATION (MFnAmbientLight)

/// Manage Ambient Light dependency Nodes
/**
  Facilitate the creation and manipulation of ambient light nodes.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MFnAmbientLight : public MFnLight 
{

	declareDagMFn(MFnAmbientLight,MFnLight);
public:
	///
	MObject     create( bool UIvisible = true, MStatus * ReturnStatus = NULL );
	///
	MObject     create( const MObject& parent, bool UIvisible = true,
											   MStatus * ReturnStatus = NULL );
	///
	float       ambientShade( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus     setAmbientShade( const float& ambient_shade );
	///
	bool        castSoftShadows( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus     setCastSoftShadows( const bool& cast_soft_shadows );
	///
	float       shadowRadius( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus     setShadowRadius( const float& shadow_radius );

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
#endif /* _MFnAmbientLight */
