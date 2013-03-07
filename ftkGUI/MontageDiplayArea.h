#ifndef MONTAGE_DISPLAY_H
#define MONTAGE_DISPLAY_H

#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QScrollBar>
#include <QtGui/QScrollArea>
#include <QtGui/QStylePainter>
#include <QtGui/QMouseEvent>
#include <QtCore/QRect>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtCore/QMap>
#include <QtCore/QSettings>

#include <ftkImage/ftkImage.h>

#include <iostream>

#include "LabelImageViewQT.h"
#include "CellTypingDialog.h"

class MontageDiplayArea  : public QWidget
{
  Q_OBJECT

public:
  MontageDiplayArea (QWidget *parent = 0);
  ~MontageDiplayArea();

  void SetChannelImage(ftk::Image::Pointer img);
  std::vector<bool> GetChannelFlags(void){ return channelFlags; };
  void SetChannelFlags(std::vector<bool> chFlags);
  std::vector< int > GetCoordinates();
  bool paintingCentroidClass;

public slots:
 void respondToSlider(
	std::vector< std::pair<itk::SizeValueType,itk::SizeValueType> >&, QColor&, unsigned& );

signals:
//  void boxDrawn(int x1, int y1, int x2, int y2, int z);
  void selectionDrawn(bool);

protected slots:
  void refreshBaseImage(void);
  void initChannelFlags(void);

protected:
  void moveEvent (QMoveEvent * event);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void paintEvent(QPaintEvent *event);
  void writeSettings();
  void readSettings();
  void setupUI(void);
  void CreateRubberBand(void);

  QMap<QString, QColor> * colorItemsMap;
  //UI Widgets:
  QScrollArea *scrollArea;

  QLabel *imageLabel;			//Contains the displayed image

  ftk::Image::Pointer channelImg;
  itk::SizeValueType totalWidth, totalHeight;

  std::vector<bool> channelFlags;	//is channel is visible or not
  std::vector< std::pair<itk::SizeValueType,itk::SizeValueType> > centroidPoints; //Classification
  itk::SizeValueType numPointsToPaint;
  QColor paintCentroidsColor;
  void repaintCentroids( itk::SizeValueType numPointsToPaint );

  QImage displayImage;			//Currently displayed image
  QImage baseImage;			//The intensity image (2D)

  //For Getting a Box:
  QPoint origin;
  MyRubberBand *rubberBand;
  bool mousePress;
  int x1, x2, y1, y2;
};

#endif //MONTAGE_DISPLAY_H
