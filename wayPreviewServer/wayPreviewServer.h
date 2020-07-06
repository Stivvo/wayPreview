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

public slots:
    bool loadFile(const QString &);
    void quit();
    void normalSize();
    void fit();

private slots:
    void onNewConnection();
    void zoomIn();
    void zoomOut();

public:
    void startServer();
    void setWsize(double newScale);
    void zoomWindow(double factor);
    void toggleInfinite();
    void zoomImage(double factor);

private:
    void shortcuts();
    void setImage(const QImage &newImage);

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
