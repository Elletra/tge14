
#ifndef _MFnMessageAttribute
#define _MFnMessageAttribute
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
// CLASS:    MFnMessageAttribute
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnMessageAttribute)
//
// Function set for message attributes.  A message attribute is a
// dependency node attribute that does not transmit data.  Message
// attributes only exist to formally declare relationships between nodes.
// By connecting two nodes via message attributes, a relationship between
// those nodes is expressed.  Message attribute connections can be
// traversed in the same manner as any other connection in the dependency
// graph.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnAttribute.h>

// *****************************************************************************

// DECLARATIONS

// *****************************************************************************

class MString;

// CLASS DECLARATION (MFnMessageAttribute)

/// Message attribute function set
/**
  Function set for message attributes.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MFnMessageAttribute : public MFnAttribute 
{

	declareMFn(MFnMessageAttribute, MFnAttribute);

public:
	///
	MObject    create( const MString& fullName,
					   const MString& briefName,
					   MStatus* ReturnStatus = NULL );

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
#endif /* _MFnMessageAttribute */



