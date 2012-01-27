#include "ROIGrabber.h"

ROIGrabber::ROIGrabber(std::string joint_transforms_filename, std::string img_path, std::string anchor_filename)
{
	roi_filter = new fregl_roi(joint_transforms_filename, img_path, anchor_filename, true);
}

ROIGrabber::ImageType::Pointer ROIGrabber::GetROI(Seed* seed, ImageType::SizeType roi_size)
{
	ImageType::PointType roi_origin;

	roi_origin[0] = std::max<int64_t>(0, (int64_t)seed->getX() - roi_size[0]/2);
	roi_origin[1] = std::max<int64_t>(0, (int64_t)seed->getY() - roi_size[1]/2);
	roi_origin[2] = std::max<int64_t>(0, (int64_t)seed->getZ() - roi_size[2]/2);

	std::cout << "Origin: " << roi_origin[0] << "x" << roi_origin[1] << "x" << roi_origin[2] << " Size: " << roi_size[0] << "x" << roi_size[1] << "x" << roi_size[2] << std::endl;

	roi_filter->setROI(roi_origin, roi_size);
	return roi_filter->getROI();
}