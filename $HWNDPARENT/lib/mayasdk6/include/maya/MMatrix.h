#ifndef _MMatrix
#define _MMatrix
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
// CLASS:    MMatrix
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MMatrix)
//
//	This class provides access to Maya's internal matrix math library allowing
//	matrices to be handled easily, and in a manner compatible with internal
//	Maya data structures.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES



#include <maya/MStatus.h>
#include <maya/MTypes.h>

// *****************************************************************************

// DECLARATIONS

#define MMatrix_kTol	1.0e-10

// *****************************************************************************

// CLASS DECLARATION (MMatrix)

/// A matrix math class for 4x4 matrices of doubles
/**
  This class provides access to Maya's matrix math library
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MMatrix  
{

public:
	///
					MMatrix();
	///
					MMatrix( const MMatrix & src );
	///
					MMatrix( const double m[4][4] );
	///
					MMatrix( const float m[4][4] );
	///
					~MMatrix();
	///
 	MMatrix&		operator = (const MMatrix &);
	///
	double&			operator()(unsigned row, unsigned col );
	///
	double			operator()(unsigned row, unsigned col ) const;
	///
	double* 		operator[]( unsigned row );
	///
	const double* 	operator[]( unsigned row ) const;
	///
	MStatus			get( double dest[4][4] ) const;
	///
	MStatus			get( float dest[4][4] ) const;
	///
 	MMatrix     	transpose() const;
	///
 	MMatrix &   	setToIdentity();
	///
 	MMatrix &   	setToProduct( const MMatrix & left,
				 		const MMatrix & right );
	///
 	MMatrix &   	operator+=( const MMatrix & right );
	///
 	MMatrix  		operator+ ( const MMatrix & right ) const;
	///
 	MMatrix &   	operator-=( const MMatrix & right );
	///
 	MMatrix  		operator- ( const MMatrix & right ) const;
	///
 	MMatrix &   	operator*=( const MMatrix & right );
	///
 	MMatrix     	operator* ( const MMatrix & right ) const;
	///
 	MMatrix &   	operator*=( double );
	///
 	MMatrix     	operator* ( double ) const;
	///
 	friend OPENMAYA_EXPORT MMatrix operator* ( double, const MMatrix & right );
	///
 	bool          	operator==( const MMatrix & other ) const;
	///
 	bool           	operator!=( const MMatrix & other ) const;
	///
 	MMatrix     	inverse() const;
	///
 	MMatrix     	adjoint() const;
	///
 	MMatrix     	homogenize() const;
	///
 	double       	det4x4() const;
	///
 	double         	det3x3() const;
	///
 	bool           	isEquivalent( const MMatrix & other,
				 		double tolerance = MMatrix_kTol ) const;

	///
	friend OPENMAYA_EXPORT IOS_REF(ostream)&	operator<<(IOS_REF(ostream)& os, const MMatrix& m);

	/// the matrix data
 	double matrix[4][4];
	///
	static const MMatrix identity;

protected:
// No protected members

private:
	static const char* className();
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

inline double& MMatrix::operator()(unsigned row, unsigned col )
{
	return matrix[row][col];
}

inline double MMatrix::operator()(unsigned row, unsigned col ) const
{
	return matrix[row][col];
}

inline double* MMatrix::operator[]( unsigned row )
{
	return matrix[row];
}

inline const double* MMatrix::operator[]( unsigned row ) const
{
	return matrix[row];
}

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MMatrix */
