#ifndef _SpatialConstraint_h
#define _SpatialConstraint_h
//#     Filename:       SpatialConstraint.h
//#
//#     Classes defined here: SpatialConstraint SpatialSign
//#
//#
//#     Author:         Peter Z. Kunszt, based on A. Szalay's code
//#     
//#     Date:           October 16, 1998
//#
//#		Copyright (C) 2000  Peter Z. Kunszt, Alex S. Szalay, Aniruddha R. Thakar
//#                     The Johns Hopkins University
//#
//#     Modification History:
//#
//#     Oct 18, 2001 : Dennis C. Dinge -- Replaced ValVec with std::vector
//#

#include "SpatialGeneral.h"
#include "SpatialSign.h"
#include "SpatialVector.h"
//
//########################################################################
//#
//# Spatial Constraint class
//#
/**
   The Constraint is really a cone on the sky-sphere. It is characterized
   by its direction a_, the opening angle s_ and its cosine -- the distance
   of the plane intersecting the sphere and the sphere center.
   If d_ = 0, we have a half-sphere. If it is negative, we have a 'hole'
   i.e. the room angle is larger than 90degrees.

   Example: positive distance
<pre>
.                   ____
.                ---    ---
.               /        /|\
.              /        / |=\
.             |        /  |==|     this side is in the convex.
.            |        /\s |===|
.            |------------|---| -> direction a
.            |        \   |===|
.             |        \  |==|
.              \        \ |=/
.               \        \|/
.                ---____---
.
.
.                     <-d-> is positive (s < 90)

</pre>
 Example: negative distance
<pre>
.                   ____
.                ---====---
.  this side is /========/|\
.  in the      /========/=| \
.  convex     |==== s__/==|  |
.            |===== / /===|   |
.  dir. a <- |------------|---|  'hole' in the sphere
.            |========\===|   |
.             |========\==|  |
.              \========\=| /
.               \========\|/
.                ---____---
.
.
.                     <-d-> is negative (s > 90)
</pre>
 for d=0 we have a half-sphere. Combining such, we get triangles, rectangles
 etc on the sphere surface (pure ZERO convexes)

*/
class LINKAGE SpatialConstraint : public SpatialSign {
public:
  /// Constructor
  SpatialConstraint() {};

  /// Initialization constructor
  SpatialConstraint(SpatialVector, float64);

  /// Copy constructor
  SpatialConstraint(const SpatialConstraint &);

  /// Assignment
  SpatialConstraint & operator =(const SpatialConstraint &);

  /// set vector
  void setVector(SpatialVector &);

  /// set distance
  void setDistance(float64);

  /// Invert
  void invert();

  /// check whether a vector is inside this
  bool contains(const SpatialVector v);

  /// give back vector
  SpatialVector & v() ;

  /// give back distance
  float64 d() const ;

  /// write
  void write(std::ostream &out) const;

public:
  SpatialVector a_;			// normal vector
  float64       d_;			// distance from origin
  float64       s_;			// cone angle in radians

  friend class SpatialIndex;
  friend class SpatialConvex;
  friend class RangeConvex;
  friend class SpatialDomain;
  friend class sxSpatialDomain;
  friend class Htmio;
};

#include "SpatialConstraint.hxx"
#endif
