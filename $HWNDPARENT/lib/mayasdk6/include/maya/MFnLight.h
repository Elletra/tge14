
#ifndef _MFnLight
#define _MFnLight
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
// CLASS:    MFnLight
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnLight)
// 
// MFnLight allows the creation and manipulation of dependency graph nodes 
// representing lights.  This is the top level of a hierarchy of light 
// node function sets.  It permits manipulation of the attributes common to
// all types of lights.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnDagNode.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>

// *****************************************************************************

// DECLARATIONS

class MPoint;
class MFloatVector;
class MColor;
class MDagPath;

// *****************************************************************************

// CLASS DECLARATION (MFnLight)

/// Manage dependency graph nodes representing lights
/**
  MFnLight allows manipulation of dependency graph nodes representing lights.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MFnLight : public MFnDagNode 
{

	declareDagMFn(MFnLight,MFnDagNode);
public:
	///
	MColor       color( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus      setColor( const MColor &col );
	///
	float        intensity( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus      setIntensity( const float& intens );
	///
	bool         useRayTraceShadows( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus      setUseRayTraceShadows( const bool& useRayTraceShadows );
	///
	MColor       shadowColor( MStatus * ReturnStatus = NULL ) const;
	///
    MStatus      setShadowColor( const MColor& shadow_color );
	///
	double       centerOfIllumination( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus      setCenterOfIllumination( const double& dist );
	///
	short        numShadowSamples( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus      setNumShadowSamples( const short& num_shadow_samples );
	///
	short        rayDepthLimit( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus      setRayDepthLimit( const short& rayDepthLimit );
	///
    MColor       opticalFXvisibility( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus      setOpticalFXvisibility( const MColor& visibility );
	///
	MColor       lightIntensity( MStatus * ReturnStatus = NULL ) const;
	///
	MFloatVector lightDirection( int instance, MSpace::Space space = MSpace::kWorld, MStatus * ReturnStatus = NULL ) const;
	///
	MFloatVector lightDirection( MStatus * ReturnStatus = NULL ) const;
	///
	bool         lightAmbient( MStatus * ReturnStatus = NULL ) const;
	///
	bool         lightDiffuse( MStatus * ReturnStatus = NULL ) const;
	///
	bool         lightSpecular( MStatus * ReturnStatus = NULL ) const;



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
#endif /* _MFnLight */
