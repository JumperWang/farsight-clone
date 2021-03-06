
/* 
 * Copyright 2009 Rensselaer Polytechnic Institute
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkMorphologicalWatershedFromMarkersImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2007-03-27 16:05:43 $
  Version:   $Revision: 1.2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

    This software is distributed WITHOUT ANY WARRANTY; without even 
    the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
    PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkMorphologicalWatershedFromMarkersImageFilter_h
#define __itkMorphologicalWatershedFromMarkersImageFilter_h

#include "itkImageToImageFilter.h"

namespace itk {

/** \class MorphologicalWatershedFromMarkersImageFilter
 * \brief Morphological watershed transform from markers
 *
 * The watershed transform is a tool for image segmentation that is fast
 * and flexible and potentially fairly parameter free. It was originally
 * derived from a geophysical model of rain falling on a terrain and a variety
 * of more formal definitions have been devised to allow development of
 * practical algorithms. If an image is considered as a terrain and divided
 * into catchment basins then the hope is that each catchment basin would
 * contain an object of interest.
 * 
 * The output is a label image. A label image, sometimes referred to as a
 * categorical image, has unique values for each region. For example, if a
 * watershed produces 2 regions, all pixels belonging to one region would have
 * value A, and all belonging to the other might have value B. Unassigned
 * pixels, such as watershed lines, might have the background value (0 by
 * convention).
 *
 * The simplest way of using the watershed is to preprocess the image we
 * want to segment so that the boundaries of our objects are bright (e.g
 * apply an edge detector) and compute the watershed transform of the
 * edge image. Watershed lines will correspond to the boundaries and our
 * problem will be solved. This is rarely useful in practice because
 * there are always more regional minima than there are objects, either
 * due to noise or natural variations in the object surfaces. Therefore,
 * while many watershed lines do lie on significant boundaries, there are
 * many that don't.
 * Various methods can be used to reduce the number of minima in the image,
 * like thresholding the smallest values, filtering the minima and/or
 * smoothing the image.
 *
 * This filter use another approach to avoid the problem of over segmentation:
 * it let the user provide a marker image which mark the minima in the input
 * image and give them a label. The minima are imposed in the input image by
 * the markers. The labels of the output image are the label of the marker
 * image.
 *
 * The morphological watershed transform algorithm is described in
 * Chapter 9.2 of Pierre Soille's book "Morphological Image Analysis:
 * Principles and Applications", Second Edition, Springer, 2003.
 *
 * \author Ga�tan Lehmann. Biologie du D�veloppement et de la Reproduction, INRA de Jouy-en-Josas, France.
 * \author Richard Beare. Department of Medicine, Monash University, Melbourne, Australia.
 *
 * \sa WatershedImageFilter, MorphologicalWatershedImageFilter
 * \ingroup ImageEnhancement  MathematicalMorphologyImageFilters
 */
template<class TInputImage, class TLabelImage>
class ITK_EXPORT MorphologicalWatershedFromMarkersImageFilter : 
    public ImageToImageFilter<TInputImage, TLabelImage>
{
public:
  /** Standard class typedefs. */
  typedef MorphologicalWatershedFromMarkersImageFilter Self;
  typedef ImageToImageFilter<TInputImage, TLabelImage> Superclass;
  typedef SmartPointer<Self>                           Pointer;
  typedef SmartPointer<const Self>                     ConstPointer;

  /** Some convenient typedefs. */
  typedef TInputImage                             InputImageType;
  typedef TLabelImage                             LabelImageType;
  typedef typename InputImageType::Pointer        InputImagePointer;
  typedef typename InputImageType::ConstPointer   InputImageConstPointer;
  typedef typename InputImageType::RegionType     InputImageRegionType;
  typedef typename InputImageType::PixelType      InputImagePixelType;
  typedef typename LabelImageType::Pointer        LabelImagePointer;
  typedef typename LabelImageType::ConstPointer   LabelImageConstPointer;
  typedef typename LabelImageType::RegionType     LabelImageRegionType;
  typedef typename LabelImageType::PixelType      LabelImagePixelType;
  
  typedef typename LabelImageType::IndexType      IndexType;
  
  /** ImageDimension constants */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  /** Standard New method. */
  itkNewMacro(Self);  

  /** Runtime information support. */
  itkTypeMacro(MorphologicalWatershedFromMarkersImageFilter, 
               ImageToImageFilter);
  

   /** Set the marker image */
  void SetMarkerImage(TLabelImage *input)
    {
    // Process object is not const-correct so the const casting is required.
    this->SetNthInput( 1, const_cast<TLabelImage *>(input) );
    }

  /** Get the marker image */
  const LabelImageType * GetMarkerImage() const
    {
    return static_cast<LabelImageType*>(
      const_cast<DataObject *>(this->ProcessObject::GetInput(1)));
    }

  /** Set the input image */
  void SetInput1(TInputImage *input)
    {
    this->SetInput( input );
    }

  /** Set the marker image */
  void SetInput2(TLabelImage *input)
    {
    this->SetMarkerImage( input );
    }

  /**
   * Set/Get whether the connected components are defined strictly by
   * face connectivity or by face+edge+vertex connectivity.  Default is
   * FullyConnectedOff.  For objects that are 1 pixel wide, use
   * FullyConnectedOn.
   */
  itkSetMacro(FullyConnected, bool);
  itkGetConstReferenceMacro(FullyConnected, bool);
  itkBooleanMacro(FullyConnected);

  /**
   * Set/Get whether the watershed pixel must be marked or not. Default
   * is true. Set it to false do not only avoid writing watershed pixels,
   * it also decrease algorithm complexity.
   */
  itkSetMacro(MarkWatershedLine, bool);
  itkGetConstReferenceMacro(MarkWatershedLine, bool);
  itkBooleanMacro(MarkWatershedLine);

protected:
  MorphologicalWatershedFromMarkersImageFilter();
  ~MorphologicalWatershedFromMarkersImageFilter() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** MorphologicalWatershedFromMarkersImageFilter needs to request the
   * entire input images.
   */
  void GenerateInputRequestedRegion();

  /** This filter will enlarge the output requested region to produce
   * all of the output.
   * \sa ProcessObject::EnlargeOutputRequestedRegion() */
  void EnlargeOutputRequestedRegion(DataObject *itkNotUsed(output));

  /** The filter is single threaded. */
  void GenerateData();
  
private:
  //purposely not implemented
  MorphologicalWatershedFromMarkersImageFilter(const Self&);
  void operator=(const Self&); //purposely not implemented

  bool m_FullyConnected;

  bool m_MarkWatershedLine;

}; // end of class

} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMorphologicalWatershedFromMarkersImageFilter.txx"
#endif

#endif
