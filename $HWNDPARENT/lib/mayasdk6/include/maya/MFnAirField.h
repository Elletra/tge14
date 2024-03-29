
#ifndef _MFnAirField
#define _MFnAirField
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
// CLASS:    MFnAirField
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnAirField)
//
// Function set for Air Fields
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnField.h>
#include <maya/MVector.h>

// *****************************************************************************

// DECLARATIONS

// *****************************************************************************

// CLASS DECLARATION (MFnAirField)

/// Function set for Air Fields (OpenMayaFX)
/**

*/

#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAFX_EXPORT MFnAirField : public MFnField
{

    declareDagMFn(MFnAirField, MFnField);

public:
    ///
    MVector      direction          ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setDirection       ( const MVector & airDirection );
    ///
    double       speed              ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setSpeed           ( double value );
    ///
    double       inheritVelocity    ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setInheritVelocity ( double velocity );
    ///
    bool         inheritRotation    ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setInheritRotation ( bool enable );
    ///
    bool         componentOnly      ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setComponentOnly   ( bool enable );
    ///
    double       spread             ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setSpread          ( double value );
    ///
    bool         enableSpread       ( MStatus *ReturnStatus = NULL ) const;
    ///
    MStatus      setEnableSpread    ( bool enable );


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
#endif /* _MFnAirField */
