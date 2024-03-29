
#ifndef _MFnDagNode
#define _MFnDagNode
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
// CLASS:    MFnDagNode
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnDagNode)
// 
// The MFnDagNode function set is used to query and set the attributes of 
// nodes in the DAG (Directed Acyclic Graph).  The DAG is a graph that 
// describes the hierarchy of the objects in the model.  At each level of
// the hierarchy there is a four by four transformation matrix that 
// affects all of the objects beneath it in the DAG.
// 
// In the DAG, geometry objects (also known as shapes) do not have 
// transformation information associated with them.  Only transform
// nodes have actual transform matrices (see MFnTransform).
// 
// Each node that exists in the DAG is also a dependency node that
// exists in the dependency graph.  This makes it possible to control
// the attributes of a DAG node based on calculations performed by
// dependency nodes.
// 
// There are two ways to specify a DAG node in Maya.  The first is
// to use an MObject handle, which acts as a pointer to a specific 
// node in the DAG.  Given only an MObject, it is not possible to do
// world space operations on a DAG node because there may be more 
// than one path through the DAG to any given node.  In other words,
// it is not possible to identify a particular instance only given 
// an MObject.
// 
// In many cases it is preferable to use a DAG path (MDagPath) to specify
// a DAG node.  A DAG path always refers to a specific instance of an
// object.  This makes it possible to perform unambiguous world space
// transformations.
// 
// It is also possible to iterate over the nodes in the DAG using a
// DAG iterator (MItDag).
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnDependencyNode.h>
#include <maya/MObject.h>
#include <stdlib.h>

// *****************************************************************************

// DECLARATIONS

class MMatrix;
class MDagPath;
class MDagPathArray;
class MBoundingBox;

// *****************************************************************************

// CLASS DECLARATION (MFnDagNode)

///  DAG Node Function Set
/**

Provides methods for attaching Function Sets to, querying, and adding
children to DAG Nodes.  Particularly useful when used in conjunction
with the DAG Iterator class (MItDag).

*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MFnDagNode : public MFnDependencyNode 
{
#ifdef DISALLOW_COPY_CONSTRUCTOR
	declareMinimalMFnDisallowCopyConstructor( MFnDagNode );
#else
	declareMinimalMFn( MFnDagNode );
#endif

public:

	enum {
		/// used by addChild to indicate the next empty position in the list. 
		kNextPos = 0xff
	};

    ///
	MFnDagNode();
    ///
	MFnDagNode( MObject & object, MStatus * ret = NULL );
    ///
	MFnDagNode( const MObject & object, MStatus * ret = NULL );
    ///
	MFnDagNode( const MDagPath & object, MStatus * ret = NULL );

    ///
    MObject         create( const MTypeId &typeId,
							MObject &parent = MObject::kNullObj,
							MStatus* ReturnStatus = NULL );
    ///
    MObject         create( const MTypeId &typeId,
							const MString &name,
							MObject &parent = MObject::kNullObj,
							MStatus* ReturnStatus = NULL );

    ///
    MObject         create( const MString &type,
							MObject &parent = MObject::kNullObj,
							MStatus* ReturnStatus = NULL );
    ///
    MObject         create( const MString &type,
							const MString &name,
							MObject &parent = MObject::kNullObj,
							MStatus* ReturnStatus = NULL );

    ///
	unsigned int	parentCount( MStatus * ReturnStatus = NULL ) const;
    ///
	MObject 		parent( unsigned int i,
							MStatus * ReturnStatus = NULL ) const;
    ///
	MStatus	        addChild( MObject & child, unsigned int index = kNextPos, 
							  bool keepExistingParents = false );
    ///
	MStatus			removeChild( MObject & child );
    ///
	MStatus			removeChildAt( unsigned int index );
	///
	unsigned int    childCount(  MStatus * ReturnStatus = NULL ) const;
    ///
	MObject 	    child( unsigned int i,
						   MStatus * ReturnStatus = NULL ) const;
    ///
	MObject  		dagRoot( MStatus * ReturnStatus = NULL );
    ///
	bool			hasParent( const MObject & node,
							   MStatus * ReturnStatus = NULL ) const;
	///
	bool			hasChild (const MObject& node,
							  MStatus * ReturnStatus = NULL ) const;
	///
	bool			isChildOf (const MObject& node,
							   MStatus * ReturnStatus = NULL ) const;
	///
	bool			isParentOf (const MObject& node,
								MStatus * ReturnStatus = NULL ) const;
	///
	bool			inUnderWorld ( MStatus * ReturnStatus = NULL ) const;
	///
	bool			inModel ( MStatus * ReturnStatus = NULL ) const;
    ///
	bool			isInstanced( bool indirect = true,
						           MStatus * ReturnStatus = NULL ) const;
	///
	bool			isInstancedAttribute( const MObject& attr,
									MStatus * ReturnStatus = NULL ) const;
    ///
	unsigned int	instanceCount( bool total,
						           MStatus * ReturnStatus = NULL ) const;
	///
	MObject			duplicate( bool instance = false,
					           bool instanceLeaf = false,
					           MStatus * ReturnStatus = NULL ) const;
    ///
	MStatus		    getPath( MDagPath& path );
    ///
	MStatus		    getAllPaths( MDagPathArray& paths );
    ///
	MString         fullPathName(MStatus *ReturnStatus = NULL);
    ///
    MString         partialPathName(MStatus *ReturnStatus = NULL);
    ///
	MMatrix			transformationMatrix( MStatus * ReturnStatus = NULL ) const;

	///
	bool            isIntermediateObject( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus         setIntermediateObject( bool isIntermediate );

	///
	int				objectColor( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus			setObjectColor( int color );
	///
	bool			usingObjectColor ( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus			setUseObjectColor( bool useObjectColor );

	///
	MBoundingBox	boundingBox( MStatus * ReturnStatus = NULL ) const;

	///
	MDagPath		dagPath( MStatus * ReturnStatus = NULL ) const;
	///
	virtual MStatus setObject( const MDagPath & path );
    ///
 	virtual MStatus setObject( MObject & object );
    ///
 	virtual MStatus setObject( const MObject & object );

	/// OBSOLETE
	MObject         model( MStatus * ReturnStatus = NULL ) const;

protected:

	void * f_path; 
	void * f_xform;

	void * f_data1; 
	void * f_data2; 

private:
// No private members

};
#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

#define declareDagMFn( MFnClass, MFnParentClass )			  	 	\
	declareMinimalMFn( MFnClass );								 	\
	public:	        											 	\
		MFnClass();											     	\
		MFnClass( MObject & object, MStatus * ret = NULL );	   	 	\
		MFnClass( const MObject & object, MStatus * ret = NULL );	\
		MFnClass( const MDagPath & object, MStatus * ret = NULL )

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MFnDagNode */
