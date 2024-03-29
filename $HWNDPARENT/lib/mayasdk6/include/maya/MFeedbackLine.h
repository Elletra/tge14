
#ifndef _MFeedbackLine
#define _MFeedbackLine
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
// CLASS:    MFeedbackLine
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFeedbackLine)
//
//  The MFeedbackLine is used to display information back to the user.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MTypes.h>

// *****************************************************************************

// DECLARATIONS

class MStatus;
class MString;

// CLASS DECLARATION (MFeedbackLine)

/// Feedback line (OpenMayaUI)
/**
This class provides methods for displaying information to the user.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32


class OPENMAYAUI_EXPORT MFeedbackLine {
public:
	///
	static MStatus	setFormat		(const MString &format);
	///
	static MStatus	setTitle		(const MString &title);
	///
	static MStatus	setValue		(short index, double value);
	///
	static void		clear			();
	///
	static bool		showFeedback	();
	///
	static void		setShowFeedback	(bool showFeedback);

private:
	static const char *className();
};


#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MFeedbackLine */
