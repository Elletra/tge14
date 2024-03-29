
#ifndef _MPxManipContainer
#define _MPxManipContainer
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
// CLASS:    MPxManipContainer
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MPxManipContainer)
//
// MPxManipContainer is the base class for user defined manipulator
// containers.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MStatus.h>
#include <maya/MTypes.h>
#include <maya/MObject.h>
#include <maya/MPxNode.h>
#include <maya/MPlug.h>
#include <maya/MPoint.h>
#include <maya/MVector.h>
#include <maya/MTypeId.h>
#include <maya/MString.h>
#include <maya/M3dView.h>
#include <maya/MDagPath.h>
#include <maya/MObjectArray.h>

// *****************************************************************************

// DECLARATIONS

class MPxManipContainer;
class MManipData;

typedef MManipData
(MPxManipContainer::*plugToManipConversionCallback)(unsigned index);

typedef MManipData
(MPxManipContainer::*manipToPlugConversionCallback)(unsigned index);

// *****************************************************************************

// CLASS DECLARATION (MPxManipContainer)

/// Base class for user defined manipulator containers (OpenMayaUI)
/**
MPxManipContainer is the base class for user defined manipulator
containers.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAUI_EXPORT MPxManipContainer : public MPxNode
{
public:
    ///
	enum baseType {
        ///
        kFreePointTriadManip,
		///
		kDirectionManip,
        ///
		kDistanceManip,
		///
		kPointOnCurveManip,
		///
		kPointOnSurfaceManip,
		///
		kDiscManip,
		///
		kCircleSweepManip,
		///
		kToggleManip,
		///
		kStateManip,
		///
		kCurveSegmentManip
    };

    ///
	MPxManipContainer();
    ///
	virtual ~MPxManipContainer();
    ///
	virtual MPxNode::Type type() const;
	///
	static  MStatus		initialize();
	///
	static MPxManipContainer * newManipulator(const MString &manipName,
											  MObject &manipObject,
											  MStatus *ReturnStatus = NULL);

	// Methods to overload
	///
	virtual void			draw(M3dView &view,
								 const MDagPath &path,
								 M3dView::DisplayStyle style,
								 M3dView::DisplayStatus status);
    ///
	virtual MStatus			connectToDependNode(const MObject &dependNode);

	// Do not put any of these functions in the constructor.
	///
	virtual MStatus			createChildren();

	///
	MDagPath	addFreePointTriadManip		(const MString &manipName,
											 const MString &pointName);
	///
	MDagPath	addDirectionManip			(const MString &manipName,
											 const MString &directionName);
	///
	MDagPath	addDistanceManip			(const MString &manipName,
											 const MString &distanceName);
	///
	MDagPath	addPointOnCurveManip		(const MString &manipName,
											 const MString &paramName);
	///
	MDagPath	addPointOnSurfaceManip		(const MString &manipName,
											 const MString &paramName);
	///
	MDagPath	addDiscManip				(const MString &manipName,
											 const MString &angleName);
	///
	MDagPath	addCircleSweepManip			(const MString &manipName,
											 const MString &angleName);
	///
	MDagPath	addToggleManip				(const MString &manipName,
											 const MString &toggleName);
	///
	MDagPath	addStateManip				(const MString &manipName,
											 const MString &stateName);
	///
	MDagPath	addCurveSegmentManip		(const MString &manipName,
											 const MString &startParamName,
											 const MString &endParamName);
	///
	MDagPath	addRotateManip				(const MString &manipName,
											 const MString &rotationName);
	///
	MDagPath	addScaleManip				(const MString &manipName,
											 const MString &scaleName);
	///
	MStatus                 finishAddingManips();
	///
    static MStatus          addToManipConnectTable(MTypeId &);
	///
    static MStatus          removeFromManipConnectTable(MTypeId &);

	///
	void addPlugToManipConversionCallback(
	         unsigned manipIndex,
			 plugToManipConversionCallback callback);
	///
	unsigned addManipToPlugConversionCallback(
	             MPlug &plug,
				 manipToPlugConversionCallback callback);

	///
	MStatus	getConverterManipValue(unsigned manipIndex, unsigned &value);
	///
	MStatus	getConverterManipValue(unsigned manipIndex, double &value);
	///
	MStatus	getConverterManipValue(unsigned manipIndex, double &x, double &y);
	///
	MStatus	getConverterManipValue(unsigned manipIndex, MPoint &point);
	///
	MStatus	getConverterManipValue(unsigned manipIndex, MVector &vector);
	///
	MStatus	getConverterManipValue(unsigned manipIndex, MMatrix &matrix);
	///
	MStatus	getConverterManipValue(unsigned manipIndex,
								   MEulerRotation &rotation);
	///
	MStatus	getConverterManipValue(unsigned manipIndex,
								   MTransformationMatrix &xform);

	///
	MStatus	getConverterPlugValue(unsigned plugIndex, double &value);
	///
	MStatus	getConverterPlugValue(unsigned plugIndex, double &x, double &y);
	///
	MStatus	getConverterPlugValue(unsigned plugIndex, MPoint &point);
	///
	MStatus	getConverterPlugValue(unsigned plugIndex, MVector &vector);
	///
	MStatus	getConverterPlugValue(unsigned plugIndex, MMatrix &matrix);
	///
	MStatus	getConverterPlugValue(unsigned plugIndex,
								  MEulerRotation &rotation);

	///
	virtual MStatus	doPress();
	///
	virtual MStatus	doDrag();
	///
	virtual MStatus	doRelease();

protected:

private:
    static const char *     className();
	friend class			MFnPlugin;
	void *					internalData;
};


#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32
// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MPxManipContainer */
