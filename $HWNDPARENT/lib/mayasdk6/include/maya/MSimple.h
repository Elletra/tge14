
#ifndef _MSimple
#define _MSimple
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
// CLASS:    MSimple
//
// *****************************************************************************
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MString.h>
#include <maya/MArgList.h>
#include <maya/MFnPlugin.h>
#include <maya/MPxCommand.h>
#include <maya/MObject.h>

///
/**
  This header contains two macros that can be used to simplify the creation
  of plug-in commands.

	DeclareSimpleCommand( className, vendorName, version ) 
	  To use this macro, you provide it with the name of the class that
	  should be derived from MPxCommand, the name of your organisation, and
    the version number of the plug-in.  The macro expands to all the
	  code necessary to create a command except for the command's "doIt"
	  method.  You need to provide a function with the prototype

		MStatus className::doIt( const MArgList& )

	The macro will generate a class with the given classname that is
	  derived from MPxCommand. It will also generate the following methods:

	    void* className::creator()
		
		MStatus initializePlugin( MObject )
		
		MStatus uninitializePlugin( MObject )

	  You can also call methods inherited from MPxCommand such as
	  "setResult", "displayWarning", and "displayError".

	DeclareSingle( functionPtr )
    To use this macro you must write a function with the prototype:
		MStatus functionPtr ( const MArgList& )

	The macro expands to all the code necessary to create a basic non-undoable
	command that calls "functionPtr" from it's doIt method.  One limitation
	of using this macro is that since "functionPtr" is not a member of the
	class derived from MPxCommand, it cannot call methods (like setResult)
	that are inherited from that class.

    The macro will generate a class called _DoItCmd which is derived from
	  MPxCommand. It also generate the following methods:

	     void* _DoItCmd::creator()
	
	     MStatus _DoItCmd::doIt( const MArgList& args )
	
	     MStatus initializePlugin( MObject )
	
	     MStatus uninitializePlugin( MObject )
	
*/

#define DeclareSimpleCommand( _className, _vendor, _version )	\
class _className : public MPxCommand {							\
public:															\
					_className() {};							\
	virtual MStatus	doIt ( const MArgList& );					\
	static void*	creator();									\
};																\
void* _className::creator()										\
{																\
	return new _className;										\
}																\
MStatus initializePlugin( MObject _obj )						\
{																\
	MFnPlugin	plugin( _obj, _vendor, _version );				\
	MStatus		stat;											\
	stat = plugin.registerCommand( #_className,					\
	                                _className::creator );	    \
	if ( !stat )												\
		stat.perror("registerCommand");							\
	return stat;												\
}																\
MStatus uninitializePlugin( MObject _obj )						\
{																\
	MFnPlugin	plugin( _obj );									\
	MStatus		stat;											\
	stat = plugin.deregisterCommand( #_className );				\
	if ( !stat )												\
		stat.perror("deregisterCommand");						\
	return stat;												\
}


#define DeclareSingle( _fnptr )									\
class _DoItCmd : public MPxCommand {							\
public:															\
					_DoItCmd() {};								\
	virtual MStatus	doIt ( const MArgList& );					\
	static void*	creator();									\
};																\
void* _DoItCmd::creator()										\
{																\
	return new _DoItCmd;										\
}																\
MStatus _DoItCmd::doIt( const MArgList& args )					\
{																\
	return _fnptr(args);										\
}																\
MStatus initializePlugin( MObject _obj )						\
{																\
	MFnPlugin	_plugin( _obj );								\
	MStatus		stat;											\
	stat = _plugin.registerCommand( #_fnptr,                    \
	                                _DoItCmd::creator );	    \
	if ( !stat )												\
		stat.perror("registerCommand");							\
	return stat;												\
}																\
MStatus uninitializePlugin( MObject _obj )						\
{																\
	MFnPlugin	plugin( _obj );									\
	MStatus		stat;											\
	stat = plugin.deregisterCommand( #_fnptr );					\
	if ( !stat )												\
		stat.perror("deregisterCommand");						\
	return stat;												\
}

// *****************************************************************************

#endif /* __cplusplus */
#endif /* _MSimple */
