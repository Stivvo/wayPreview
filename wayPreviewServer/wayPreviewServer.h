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
    bool loadFile(const QString &);
    void connection();
    void closeDisconnect();

private slots:
    void onNewConnection();

public slots:
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fit();

private:
    void shortcuts();
    void setImage(const QImage &newImage);
    void scaleImage(double factor);
    void resizeWindow(double factor);
    void setWscale(double newScale);
    void toggleInfinite();

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
