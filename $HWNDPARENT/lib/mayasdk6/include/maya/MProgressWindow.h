
#ifndef _MProgressWindow
#define _MProgressWindow
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
// CLASS:    MProgressWindow
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MProgressWindow)
//
// The MProgressWindow class manages a window containing a status message, a 
// graphical progress gauge, and optionally a "Hit ESC to Cancel" label for 
// interruptable operations.
//
// Only a single progress window may be displayed at any time.  To reserve the 
// use of the progress window, use the reserve() method in this class.  Any 
// methods that change the state of the progress window will fail unless the 
// progress window has first been successfully reserved.
//
// The startProgress() and endProgress() functions show and hide the progress 
// window.  endProgress() also has the effect of unreserving the progress 
// window, allowing it to be reserved for another use.
//
// The MEL command "progressWindow" provides equivalent functionality to this 
// class.  Attempting to manipulate a progress window that is in use by MEL 
// will cause the methods in this class to fail.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES



#include <maya/MStatus.h>

// *****************************************************************************

// DECLARATIONS

class MString;
class MStatus;

// *****************************************************************************

// CLASS DECLARATION (MProgressWindow)

/// Create and manipulate progress windows. (OpenMayaUI)
/**
*/

#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAUI_EXPORT MProgressWindow
{
public:

	///
	static bool reserve();
	///
	static MStatus startProgress();
	///
	static MStatus endProgress();

	///
	static MStatus setProgressRange(const int minValue, const int maxValue);
	///
	static MStatus setProgressMin(const int minValue);
	///
	static MStatus setProgressMax(const int maxValue);

	///
	static int progressMin();
	///
	static int progressMax();
	
	///
	static MStatus setProgress(const int progress);
	///
	static MStatus advanceProgress(const int amount);
	///
	static int progress();
	
	///
	static MStatus setTitle(const MString &title);
	///
	static MString title();
	
	///
	static MStatus setProgressStatus(const MString &progressStatus);
	///
	static MString progressStatus();
	
	///
	static MStatus setInterruptable(const bool value);
	///
	static bool isInterruptable();
	///
	static bool isCancelled();

protected:
	// No protected members
private:
	static const char* 		className();

	static bool reserved;
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************

#endif /* __cplusplus */
#endif /* _MProgressWindow */
