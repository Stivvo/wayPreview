#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QImage>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr);
    bool loadFile(const QString &);

private slots:
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fit();

private:
    void cuts();
    void setImage(const QImage &newImage);
    void scaleImage(double factor);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor = 1;
    QSize resolution;
};

#endif
