
#ifndef _MPxLocatorNode
#define _MPxLocatorNode
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
// CLASS:    MPxLocatorNode
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MPxNode)
//
// MPxLocatorNode allows the creation of user-defined locators.  A locator
// is a DAG shaped that is drawn on the screen, but that has is not
// rendered.  Locators are full dependency nodes and can have attributes
// and a compute method.
//
// To create a locator, derive off of this class and override the draw
// method.  The draw method can be overridden to draw custom geometry
// using standard OpenGL calls.  The other methods of the parent class
// MPxNode may also be overridded to perform dependency node capabilities
// as well.
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

// *****************************************************************************

// DECLARATIONS

class MDagPath;

// *****************************************************************************

// CLASS DECLARATION (MPxNode)

/// Base class for user defined locators (OpenMayaUI)
/**
  Create user defined locators.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAUI_EXPORT MPxLocatorNode : public MPxNode
{
public:
    ///
	MPxLocatorNode();
    ///
	virtual ~MPxLocatorNode();
	///
	virtual MPxNode::Type type() const;

	// Methods to overload

	///
	virtual void draw( M3dView & view, const MDagPath & path,
			    	   M3dView::DisplayStyle style, M3dView:: DisplayStatus );
	///
	virtual bool isBounded() const;
	///
	virtual MBoundingBox boundingBox() const;


	// Color methods

	///
	unsigned                  color( M3dView::DisplayStatus displayStatus );
	///
	MColor                    colorRGB( M3dView::DisplayStatus displayStatus );

	///
	virtual bool			excludeAsLocator() const;

	// Inherited attributes

	/// under world attribute
	static MObject underWorldObject;
	/// local position attribute
	static MObject localPosition;
		/// X component of localPosition
		static MObject localPositionX;
		/// Y component of localPosition
		static MObject localPositionY;
		/// Z component of localPosition
		static MObject localPositionZ;
	/// world position attribute
	static MObject worldPosition;
	    /// X component of worldPosition
	    static MObject worldPositionX;
	    /// Y component of worldPosition
	    static MObject worldPositionY;
	    /// Z component of worldPosition
	    static MObject worldPositionZ;
	/// bounding box attribute
	static MObject nodeBoundingBox;
	    /// bounding box minimum point
	    static MObject nodeBoundingBoxMin;
	        /// X component of boundingBoxMin
	        static MObject nodeBoundingBoxMinX;
	        /// Y component of boundingBoxMin
	        static MObject nodeBoundingBoxMinY;
	        /// Z component of boundingBoxMin
	        static MObject nodeBoundingBoxMinZ;
	    ///  bounding box maximum point
	    static MObject nodeBoundingBoxMax;
	        /// X component of boundingBoxMax
	        static MObject nodeBoundingBoxMaxX;
	        /// Y component of boundingBoxMax
	        static MObject nodeBoundingBoxMaxY;
	        /// Z component of boundingBoxMax
	        static MObject nodeBoundingBoxMaxZ;
	    ///  bounding box size vector
	    static MObject nodeBoundingBoxSize;
	        /// X component of boundingBoxSize
	        static MObject nodeBoundingBoxSizeX;
	        /// Y component of boundingBoxSize
	        static MObject nodeBoundingBoxSizeY;
	        /// Z component of boundingBoxSize
	        static MObject nodeBoundingBoxSizeZ;
	/// object center attribute
	static MObject center;
	    /// X component of boundingBoxCenter
	    static MObject boundingBoxCenterX;
	    /// Y component of boundingBoxCenter
	    static MObject boundingBoxCenterY;
	    /// Z component of boundingBoxCenter
	    static MObject boundingBoxCenterZ;
	/// matrix attribute
	static MObject matrix;
	/// inverse matrix attribute
	static MObject inverseMatrix;
	/// world matrix attribute
	static MObject worldMatrix;
	/// inverse world matrix attribute
	static MObject worldInverseMatrix;
	/// parent matrix attribute
	static MObject parentMatrix;
	/// inverse parent matrix attribute
	static MObject parentInverseMatrix;
	/// visibility attribute
	static MObject visibility;
	/// intermediate object attribute
	static MObject intermediateObject;
	/// template attribute
	static MObject isTemplated;
	/// instances object group info attribute
	static MObject instObjGroups;
	    /// object groups attributes
	    static MObject objectGroups;
	        /// component in object groups attribute
	        static MObject objectGrpCompList;
	        /// group id attribute
	        static MObject objectGroupId;
	        /// group id attribute
	        static MObject objectGroupColor;
	/// controls choice of wireframe dormant object color
	static MObject useObjectColor;
	/// the per object dormant wireframe color
	static MObject objectColor;

protected:

private:
	static void				initialSetup();
	static const char*	    className();
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MPxLocatorNode */
