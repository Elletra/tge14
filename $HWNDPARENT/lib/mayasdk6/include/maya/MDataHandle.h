
#ifndef _MDataHandle
#define _MDataHandle
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
// CLASS:    MDataHandle
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MDataHandle)
//
//	An MDataHandle is a smart pointer into a data block (MDataBlock).  A data
//	handle corresponds to the data for a particular attribute or plug.  For
//	array data (eg CVs of a curve) use an MArrayDataHandle.  To get a data
//	handle, request it from the data block.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES



#include <maya/MStatus.h>
#include <maya/MTypes.h>
#include <string.h>
#include <maya/MFnNumericData.h>
#include <maya/MFnData.h>
#include <maya/MTypeId.h>
#include <maya/MObject.h>

// *****************************************************************************
// FORWARD DECLARATIONS
class MTime;
class MAngle;
class MDistance;
class MVector;
class MFloatVector;
class MMatrix;
class MFloatMatrix;
class MPlug;
class MPxData;
class MString;
// *****************************************************************************

// CLASS DECLARATION (MDataHandle)

/// Data handle for information contained in a data block
/**
 An MDataHandle is a smart pointer into an MDataBlock.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MDataHandle {

public:  
	///
	MDataHandle();
    ///
	bool                 isNumeric() const;
    ///
    MFnNumericData::Type numericType() const;
    ///
    MFnData::Type        type() const;
    ///
    MTypeId              typeId() const;

    ///
	MObject              data();
	///
	MStatus				 copy( const MDataHandle& src );

    ///
	void                 setClean();

    ///	
	bool&			     asBool()	const;
    ///
	char&			     asChar()	const;
    ///
	unsigned char&       asUChar()	const;
    ///
	short&			     asShort()	const;
    /// OBSOLETE
	int&			     asLong()	const;
    ///
	int&			     asInt()	const;
    ///
	float&			     asFloat()	const;
    ///
	double&		         asDouble()	const; 
    ///
    MDistance            asDistance()	const;
	///
    MAngle               asAngle()	const;
	///
    MTime                asTime()	const;
     
    ///
	short2&              asShort2()	const;
    /// OBSOLETE
	long2&               asLong2()	const;
    ///
	int2&				 asInt2()	const;
    ///
	float2&              asFloat2()	const;
    ///
	double2&             asDouble2()const;
    ///
	short3&              asShort3()	const;
    /// OBSOLETE
	long3&               asLong3()	const;
    ///
	int3&                asInt3()	const;
    ///
	float3&              asFloat3()  const;
    ///
	double3&             asDouble3() const;
    ///
	MVector&             asVector()  const;
    ///
	MFloatVector&        asFloatVector() const;
    ///
    MMatrix&             asMatrix()  const;
    ///
    MFloatMatrix&        asFloatMatrix()  const;
	///
	MString&             asString() const;

    ///
    MObject              asNurbsCurve() const; 
    ///
    MObject              asNurbsSurface() const;
    ///
    MObject              asMesh() const;
    ///
    MObject              asSubdSurface() const; 
    ///
    MObject              asNurbsCurveTransformed() const;
    ///
    MObject              asNurbsSurfaceTransformed() const;
    ///
    MObject              asMeshTransformed() const;
    ///
    MObject              asSubdSurfaceTransformed() const;
    ///
    const MMatrix &      geometryTransformMatrix() const; 
	///
	MPxData *            asPluginData() const;

    ///
    void                 set( bool );
    ///
    void                 set( char );
    ///
    void                 set( short );
    ///
    void                 set( int );
    ///
    void                 set( float );
    ///
    void                 set( double );
    ///
    void                 set( const MMatrix& );
    ///
    void                 set( const MFloatMatrix& );
    ///
    void                 set( const MVector& );
    ///
	void                 set( const MFloatVector& );
    ///
    void                 set( const MDistance& );
    ///
    void                 set( const MAngle& );
    ///
    void                 set( const MTime& );
    ///
	void                 set( short, short );
    ///
	void                 set( int, int );
    ///
	void                 set( float, float );
    ///
	void                 set( double, double );
    ///
	void                 set( short, short, short );
    ///
	void                 set( int, int, int );
    ///
	void                 set( float, float, float );
    ///
	void                 set( double, double, double );
    ///
	void                 set( const MString  &);

	///
	MStatus              set( const MObject &data );
	///
	MStatus              set( MPxData * data );

    ///
    MDataHandle          child( const MPlug & plug );
    ///
    MDataHandle          child( const MObject & attribute );

    ///
	MDataHandle& operator=( const MDataHandle& other );
    ///
    MDataHandle( const MDataHandle & );

protected:
// No protected members

private:
	friend class MDataBlock;
	friend class MArrayDataBuilder;
	friend class MArrayDataHandle;
	friend class MItGeometry;
	const char*	className() const;
	MDataHandle( void* );

	// Anonymous union to force byte-alignment on IRIX machines. 
	// Fixes bug # 158251. In general, MDataHandle should appear
	// before anything of size  8. This is just in case the user 
	// doesn't do this. It forces the data to be on the next 
	// word boundary. 
	//
	union { 
		char	f_data[16];
		int		_force_alignment; 
	}; 
};

inline MDataHandle::MDataHandle( const MDataHandle &other )
{
	memcpy( this, &other, sizeof(MDataHandle) ); 
}

inline MDataHandle& MDataHandle::operator=( const MDataHandle& other )
{
	memcpy( this, &other, sizeof(MDataHandle) );
	return *this;
}

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MDataHandle */
