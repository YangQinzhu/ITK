/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkImageBoundaryCondition.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkImageBoundaryCondition_h_
#define __itkImageBoundaryCondition_h_

#include "itkImage.h"
#include "itkIndex.h"
#include "itkOffset.h"
#include "itkNeighborhood.h"

namespace itk
{

/**
 *\class ImageBoundaryCondition
 * \brief A virtual base object that defines an interface to a class of
 * boundary condition objects for use by neighborhood iterators.
 *
 * A boundary condition object supplies a phantom pixel value when
 * given a neighborhood of (pointers to) image values, the (ND) index of
 * the phantom pixel, and its (ND) offset from the boundary.  The index
 * of the phantom pixel is relative to the "upper left-hand corner" of
 * the neighborhood (as opposed to its center). 
 *
 * 
 * Associated Types                 Description
 * ----------------                 -----------
 * PixelType                         The data type of the return value.
 * PixelPointerType                  A pointer to PixelType.
 * PixelPointerTypeNeighborhood      A neighborhood of PixelPointerTypes
 *                                   that points to the pixel values in
 *                                   an image neighborhood.
 * 
 * \ingroup DataRepresentation
 * \ingroup ImageObjects
 */
template <class TImageType>
class ITK_EXPORT ImageBoundaryCondition
{
public:
  /** Extract information from the image type */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TImageType::ImageDimension);

  /** Standard typedefs. */
  typedef ImageBoundaryCondition           Self;

  /** Extract information from the image type */
  typedef typename TImageType::PixelType PixelType;
  typedef typename TImageType::InternalPixelType *PixelPointerType;
  typedef Index<itkGetStaticConstMacro(ImageDimension)> IndexType;
  typedef Offset<itkGetStaticConstMacro(ImageDimension)> OffsetType;
  
  /** Type of the data container passed to this function object. */
  typedef Neighborhood<PixelPointerType,
                      itkGetStaticConstMacro(ImageDimension)> NeighborhoodType;

  /** Default constructor. */
  ImageBoundaryCondition() {}
  
  /** Returns a value for a given out-of-bounds pixel.  The arguments are the
   * phantom pixel (ND) index within the neighborhood, the pixel's offset from
   * the nearest image border pixel, and a neighborhood of pointers to pixel
   * values in the image.  */
  virtual PixelType operator()(const OffsetType& point_index,
                               const OffsetType &boundary_offset,
                                 const NeighborhoodType *data) const = 0;
};
  
}// end namespace itk


#endif
