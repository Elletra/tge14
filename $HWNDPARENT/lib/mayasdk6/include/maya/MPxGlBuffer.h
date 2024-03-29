
#ifndef _MPxGlBuffer
#define _MPxGlBuffer
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
// CLASS:    MPxGlBuffer
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MPxGlBuffer)
//
//  MPxGlBuffer allows the user to create OpenGL buffers that Maya
//	can draw into.  The base class as is defined will create a hardware
//	accellerated off-screen buffer for use on SGI hardware.
//
//  To create a custom buffer, derive from this class and override at
//	least the open, close, drawable, and context classes.  The customized
//	buffer may also require a constructor and destructor to initialize and
//	free its storage correctly.
//
// *****************************************************************************

#if defined __cplusplus

// ****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MStatus.h>
#include <maya/MTypes.h>

#if defined(__unix) || defined(LINUX)
#include <GL/glx.h>
#endif

// ****************************************************************************

// DECLARATIONS

class MString;
class M3dView;

// ****************************************************************************

// CLASS DECLARATION (MPxGlBuffer)

/// Base class for user defined GL buffers (OpenMayaUI)

/**
  Create user defined (off-screen) GL buffers.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAUI_EXPORT MPxGlBuffer
{
public:
	///
	MPxGlBuffer();
	///
	MPxGlBuffer( M3dView &view );
	///
	virtual ~MPxGlBuffer();

#if defined(__unix) && !defined(LINUX)
	///
	virtual	MStatus			open( short width, short height,
								  GLXContext shareCtx = NULL );

	///
	virtual GLXDrawable	    drawable( MStatus * ReturnStatus = NULL );
	///
	virtual	GLXContext      context( MStatus * ReturnStatus = NULL );
#endif // __unix

	///
	virtual	MStatus			close();

protected:
	///
	bool					hasColorIndex;
	///
	bool					hasAlphaBuffer;
	///
	bool					hasDepthBuffer;
	///
	bool					hasAccumulationBuffer;

private:
	void   setData( void* );
	virtual const char*	className() const;
	void * 	data;

#if defined(LINUX)
public:
	///
	virtual	MStatus			open( short width, short height,
								  GLXContext shareCtx = NULL );

	///
	virtual GLXDrawable	    drawable( MStatus * ReturnStatus = NULL );
	///
	virtual	GLXContext      context( MStatus * ReturnStatus = NULL );
#endif // __linux
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MPxGlBuffer */
