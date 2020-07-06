#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

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
    void quit();
    void normalSize();
    void fit();
    void zoomIn();
    void zoomOut();

private:
    void shortcuts();
    void setImage(const QImage &newImage);
    void setWsize(double newScale);
    void resizeWindow(double factor);
    void toggleInfinite();
    void scaleImage(double factor);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;

    double imageRatio;
    QSize resolution;
    double wSize;
    bool infinite;
    double prevWsize;
    double imgScale;

    std::unique_ptr<QLocalServer> server;
    std::unique_ptr<QLocalSocket> client;
};

#endif
