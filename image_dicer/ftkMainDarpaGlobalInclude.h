

// ITK INCLUDES
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkExtractImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"
#include "itkMultiThreader.h"
#include "itkRGBPixel.h"

// FTK INCLUDES
#include "../Tracing/MultipleNeuronTracer/MultipleNeuronTracer.h"
#include "../NuclearSegmentation/yousef_core/yousef_seg.h"
#include "../NuclearSegmentation/NucleusEditor/ftkProjectProcessor.h"

// C++ STD
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <limits.h>
#include <stdlib.h>

// OTHER INCLUDES