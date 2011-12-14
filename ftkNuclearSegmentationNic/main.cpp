// ############################################################################################################################################################################

//#includes goes here

#include "ftkNuclearSegmentationNic.h"

// FTK INCLUDES
#include <ftkObject.h>
#include <ftkImage/ftkImage.h>
#include <ftkCommon/ftkUtils.h>


// STANDARD INCLUES
#include <vector>
#include <iostream>
#include <map>

// ITK INCLUDES
#include <itkImageIOBase.h>


// ############################################################################################################################################################################

int main( int argc, char * argv[] ){

// 	std::cout << std::endl << "	step 1";
// 	std::cout << std::endl << "	step 1";
	ftk::Image::Pointer myImg;
	//std::string inputName = "testImages\Histo_Input.xml";
// 	std::cout << std::endl << "	step 1";
	myImg = ftk::LoadXMLImage( "/home/nicolasreyv/farsight/src/farsight-src/ftkNuclearSegmentationNic/TestImages/Histo_Input.xml" );
	
//	ftk::Image::DataType dataType;
// 	itk::ImageIOBase::UCHAR
// 	std::cout << std::endl << "	step 2";
// 	std::cout << std::endl << "	step 2";
	std::cout << myImg->GetImageInfo()->dataType;
	
// 	switch(myImg->GetImageInfo()->dataType)
// 	{
// 		case itk::ImageIOBase::USHORT:
// 		{
// 			typedef ftk::nucSecNic::ftkNuclearSegmentationNic<unsigned short> my_nucSecNic;
// 			std::cout << "1111111";
// 			
// 		break;
// 		}
// 		case itk::ImageIOBase::UCHAR:
// 		{
// 			typedef ftk::nucSecNic::ftkNuclearSegmentationNic<unsigned char> my_nucSecNic;
// 			std::cout << "2222222";
// 		break;
// 		}
// 	}
	
// 	if( myImg->GetImageInfo()->dataType == itk::ImageIOBase::USHORT)
// 	{
// 		typedef ftk::nucSecNic::ftkNuclearSegmentationNic<unsigned short> my_nucSecNic;
// 	}
// 	else if(myImg->GetImageInfo()->dataType == itk::ImageIOBase::UCHAR)
// 	{
// 		typedef ftk::nucSecNic::ftkNuclearSegmentationNic<unsigned char> my_nucSecNic;
// 	}	
	
	typedef ftk::nucSecNic::ftkNuclearSegmentationNic<unsigned char, unsigned short> my_nucSecNic;
// 	std::cout << std::endl << "	step 3";
// 	std::cout << std::endl << "	step 3";
	my_nucSecNic nucSecNic;
	bool out = nucSecNic.setInput( myImg, "test_data", 0, 0 );
	
// 	std::cout << std::endl << "	step 4";
// 	std::cout << std::endl << "	step 4";
	nucSecNic.ResetRealeaseAll();
	//std::cout << std::endl << "	step 5";
	nucSecNic.ReleaseMemory();
	//std::cout << std::endl << "	step 6";
	nucSecNic.setBinarizeMixPoissonParameters_1(128);
	nucSecNic.runBinarizeMixPoisson_1();
	

	int * nic;
	nic = new int[2];
	delete [] nic;
	
	
	std::cout << std::endl;
	return 0;
};

// ############################################################################################################################################################################