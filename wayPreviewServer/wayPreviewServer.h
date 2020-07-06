#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <QImage>
#include <QLocalServer>
#include <QLocalSocket>
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

private slots:
    bool loadFile(const QString &);
    void onNewConnection();
    void closeDisconnect();
    void normalSize();
    void fit();
    void zoomIn();
    void zoomOut();

private:
    void shortcuts();
    void setImage(const QImage &newImage);
    void setWscale(double newScale);
    void resizeWindow(double factor);
    void toggleInfinite();
    void scaleImage(double factor);

    bool infinite;
    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double imgScale;
    QSize resolution;
    double wScale;
    double prevWscale;
    double imageRatio;

    std::unique_ptr<QLocalServer> server;
    std::unique_ptr<QLocalSocket> client;
};

#endif
