
#ifndef _MPxSurfaceShapeUI
#define _MPxSurfaceShapeUI
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
// CLASS:    MPxSurfaceShapeUI
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MPxNode)
//
//
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES



#include <maya/MStatus.h>
#include <maya/MTypes.h>
#include <maya/MObject.h>
#include <maya/MPxNode.h>
#include <maya/M3dView.h>
#include <maya/MBoundingBox.h>
#include <maya/M3dView.h>
#include <maya/MSelectInfo.h>
#include <maya/MDrawRequest.h>
#include <maya/MDrawRequestQueue.h>

// *****************************************************************************

// DECLARATIONS

class MSelectionList;
class MPointArray;
class MPxSurfaceShape;
class MDrawData;
class MMaterial;

// *****************************************************************************

// CLASS DECLARATION (MPxNode)

/// drawing and selection for user defined shapes (OpenMayaUI)
/**
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAUI_EXPORT MPxSurfaceShapeUI
{
public:
    ///
	MPxSurfaceShapeUI();
    ///
	virtual ~MPxSurfaceShapeUI();

	///
	void					getDrawData( void * geom, MDrawData & );

	/////////////////////////////////////////////////////////////////////////
	// Methods to overload

	///
	virtual void			getDrawRequests( const MDrawInfo &,
											 bool objectAndActiveOnly,
											 MDrawRequestQueue & requests );
	///
	virtual void		    draw( const MDrawRequest &, M3dView & view ) const;
	///
	virtual bool		    select( MSelectInfo &selectInfo,
							    	MSelectionList &selectionList,
							    	MPointArray &worldSpaceSelectPts ) const;

	/////////////////////////////////////////////////////////////////////////

	///
	MPxSurfaceShape*		surfaceShape() const;
	///
	MMaterial 				material( MDagPath & path ) const;

protected:

private:
	static const char*	    className();
	friend class MDrawRequest;
	friend class MDrawInfo;
	void * instance;
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MPxSurfaceShapeUI */
