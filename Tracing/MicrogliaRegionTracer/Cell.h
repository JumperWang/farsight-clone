#ifndef Cell_H
#define Cell_H

#include <deque>

#include "itkImage.h"
#include "itkIntTypes.h"
#include "itkImageRegionIterator.h"
#include "itkImageFileReader.h"

#include "fregl/fregl_roi.h"

#include "itkMaskNegatedImageFilter.h"
#include "itkMaximumEntropyThresholdImageFilter.h"
#include "itkBinaryFillholeImageFilter.h"
#include "itkBinaryThinningImageFilter3D.h"
#include "itkShiftScaleImageFilter.h"
#include "itkRegionOfInterestImageFilter.h"

#include <fstream>
#include <cstring>


class Cell
{
public:
	typedef	unsigned char							InputPixelType;
	typedef fregl_roi< InputPixelType >::ImageType	ImageType;
	
	//typedef ImageType::Pointer					ImageTypePointer;
	//typedef ImageType::SizeType					ImageSizeType;
	//typedef ImageType::IndexType					ImageIndexType;

	typedef itk::Image< float, 3 >						LoGImageType;
	typedef itk::Image< float, 3 >						VesselnessImageType;
	typedef itk::Image< float, 3 >						DistanceImageType;
	typedef itk::Image< unsigned char, 3 >				MaskImageType;
	typedef itk::Image< unsigned char, 3 >				SomaImageType;

public:
	Cell(itk::uint64_t cell_x, itk::uint64_t cell_y, itk::uint64_t cell_z);
	
	itk::uint64_t getX() const;  
	itk::uint64_t getY() const;
	itk::uint64_t getZ() const;

	void SetSize(ImageType::SizeType roi_size);
	ImageType::SizeType GetSize();

	void SetOrigin(ImageType::PointType roi_origin);
	ImageType::PointType GetOrigin();

	void setRequestedSize(ImageType::SizeType cell_requested_size);
	ImageType::SizeType getRequestedSize();

	void setShiftIndex(ImageType::IndexType shift_index);
	ImageType::IndexType getShiftIndex();

	void ComputeCriticalPointsVector(ImageType::Pointer critical_points_image);

	//Various methods to perform filters on image
	void GetMask(std::string soma_filename);
	void ComputeMaskedImage();
	void MaximumEntropyThreshold();
	void Skeletonize();


	//Writes various images
	static void WriteImage(std::string filename, itk::Image< unsigned char, 3>::Pointer image);
	static void WriteImage(std::string filename, itk::Image< unsigned short, 3>::Pointer image);
	static void WriteImage(std::string filename, itk::Image< float , 3 >::Pointer image);
	

public:
	std::deque< ImageType::IndexType > critical_points_queue; //deque is double-ended queue
	
	ImageType::Pointer				image;
	ImageType::Pointer				critical_point_image;
	LoGImageType::Pointer			multiscale_LoG_image;
	VesselnessImageType::Pointer	vesselness_image;
	ImageType::Pointer				masked_image;
	ImageType::Pointer				thresholded_image;
	ImageType::Pointer				skeleton_image;
	DistanceImageType::Pointer		distance_map_image;
	MaskImageType::Pointer			mask;

	float vesselness_image_maximum_intensity;

private:
	itk::uint64_t cell_x;
	itk::uint64_t cell_y;
	itk::uint64_t cell_z;

	ImageType::PointType roi_origin;
	ImageType::SizeType roi_size;

	ImageType::SizeType cell_requested_size;
	ImageType::IndexType shift_index;
};

#endif
