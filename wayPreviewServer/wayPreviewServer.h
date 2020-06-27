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
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fit();
    void onNewConnection();

private:
    void cuts();
    void setImage(const QImage &newImage);
    void scaleImage(double factor);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor = 1;
    QSize resolution;

    std::unique_ptr<QLocalServer> server;
    std::unique_ptr<QLocalSocket> client;
};

#endif
