
#ifndef _MFnField
#define _MFnField
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
// CLASS:    MFnField
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnField)
//
// Function set for Dynamic Fields
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnDagNode.h>

// *****************************************************************************

// DECLARATIONS

class MPointArray;
class MVectorArray;
class MDoubleArray;

// *****************************************************************************

// CLASS DECLARATION (MFnField)

/// Function set for Dynamic Fields (OpenMayaFX)
/**

*/

#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAFX_EXPORT MFnField : public MFnDagNode
{

    declareDagMFn(MFnField, MFnDagNode);

public:
    ///
    MStatus getForceAtPoint(const MPointArray&   point,
                            const MVectorArray&  velocity,
                            const MDoubleArray&  mass,
                            MVectorArray&        force,
							double deltaTime = 1.0 / 24.0 );
    ///
    MStatus getForceAtPoint(const MVectorArray&  point,
                            const MVectorArray&  velocity,
                            const MDoubleArray&  mass,
                            MVectorArray&        force,
							double deltaTime = 1.0 / 24.0 );
    ///
    double       magnitude          ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setMagnitude       ( double mag );
    ///
    double       attenuation        ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setAttenuation     ( double atten );
    ///
    double       maxDistance        ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setMaxDistance     ( double maxDist );
    ///
    bool         perVertex          ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setPerVertex       ( bool enable );
    ///
    bool         useMaxDistance     ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setUseMaxDistance  ( bool enable );



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
#endif /* _MFnField */
