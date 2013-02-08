#ifndef MONTAGE_REGION_SELECTION
#define MONTAGE_REGION_SELECTION

#include "ftkImage/ftkImage.h"
#include "vtkTable.h"
#include "ftkFeatures/ftkObject.h"

/*Utility class for storing the objects related to the current ROI selected
  and all the edits related to it from the Nucleus Editor
*/
class MontageRegionSelection
{
  public:
  MontageRegionSelection();
  ~MontageRegionSelection();

  private:
  ftk::Image::Pointer ChannelImage;
  ftk::Image::Pointer LabelImage;
  vtkSmartPointer<vtkTable> Table;
  std::map<int, ftk::Object::Box> bBoxMap;	//Bounding boxes
  std::map<int, ftk::Object::Point> centerMap;	//Centroids

  public:
  void SetChannelImage( ftk::Image::Pointer Image ) { ChannelImage = Image; }
  void SetLabelImage( ftk::Image::Pointer Image   ) { LabelImage = Image; }
  void SetTable( vtkSmartPointer<vtkTable> table  ) { Table = table; }
  void SetBoundsMap( std::map<int, ftk::Object::Box>& Map   ) { bBoxMap = Map; }
  void SetCenterMap( std::map<int, ftk::Object::Point>& Map ) { centerMap = Map; }

  ftk::Image::Pointer GetChannelImage(void) { return ChannelImage; }
  ftk::Image::Pointer GetLabelImage(void)   { return LabelImage; }
  vtkSmartPointer<vtkTable> GetTable(void)  { return Table; }
  std::map<int, ftk::Object::Point> &GetCenterMap(void) { return centerMap; }
  std::map<int, ftk::Object::Box> &GetBoundBoxMap(void) { return bBoxMap; }

  //Edits returned from the nucleus editor
};

#endif //MONTAGE_REGION_SELECTION