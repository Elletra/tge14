
#ifndef _MFnSubdData
#define _MFnSubdData
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
// CLASS:    MFnSubdData
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnSubdData)
//
// MFnSubdData allows the creation and manipulation of subdivision surface
// data objects for use in the dependency graph.
// 
// If a user written dependency node either accepts or produces subdivision
// surfaces, then this class is used to extract or create the data that
// comes from or goes to other dependency graph nodes. The
// MDataHandle::type method will return kSubdSurface when data of this type
// is present.
//
// If a node is receiving a subdivision surface via an input attribute, the
// asSubdSurface method of MDataHandle can be used to access that input 
// Subdivision Surface.
//
// If a node is to create a Subdivision Surface and send it via an output
// attribute, a
// new MFnSubdData must be instantiated and then the create method
// called to build the actual data block as an MObject.  This MObject should
// be passed to the MFnSubd::create method as the parentOrOwner parameter
// so that the Subdivision Surface will be constructed inside the data
// block.  The MDataHandle::set routine is then used to pass the data block
// down the connection.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnGeometryData.h>

// *****************************************************************************

// DECLARATIONS

// *****************************************************************************

// CLASS DECLARATION (MFnSubdData)

/// Subdiv Surface function set for dependency node data
/**
  Create and manipulate Subdiv Surface dependency node data
*/

#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MFnSubdData : public MFnGeometryData 
{

	declareMFn(MFnSubdData, MFnGeometryData);

public:
	///
	MObject		create( MStatus* ReturnStatus = NULL );

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
#endif /* _MFnSubdData */
