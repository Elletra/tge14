
#ifndef _MDrawRequestQueue
#define _MDrawRequestQueue
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
// CLASS:    MDrawRequestQueue
//
//    This class defines a simple interface for a collection of
//    MDrawRequest objects.
//
//    An MDrawRequestQueue object is passed to the getDrawRequests method
//    of a user defined shape's UI class (MPxSurfaceShapeUI).
//    This queue keeps track of all the things that need to get draw
//    when a refresh of the view occurs.
//
//    Maya will call the getDrawRequest methods of all the visible DAG objects
//    before a refresh happens. Then as the refresh happens, each draw request
//    will be processed and the corresponding draw method for each DAG
//    object will get called. For user defined shapes MPxSurfaceShapeUI::draw
//    will get called.
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MDrawRequestQueue)
//
// *****************************************************************************
//
#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MStatus.h>
#include <maya/MTypes.h>
#include <maya/MObject.h>
#include <maya/MDrawRequest.h>

// *****************************************************************************

// DECLARATIONS

// *****************************************************************************

// CLASS DECLARATION (MDrawRequestQueue)
/// Drawing queue used in MPxSurfaceShapeUI::getDrawRequests (OpenMayaUI)
/**
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAUI_EXPORT MDrawRequestQueue
{
public:
	///
	MDrawRequestQueue();
	///
	~MDrawRequestQueue();

public:
	///
	bool			isEmpty() const;
	///
	void			add( MDrawRequest & );
	///
	MDrawRequest	remove();


protected:
// No protected members

private:
	const char*	 className() const;
    MDrawRequestQueue( void* in );
	void*	 fDrawRequestQueue;
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MDrawRequestQueue */
