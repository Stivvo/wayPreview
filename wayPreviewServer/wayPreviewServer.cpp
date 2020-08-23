#include "wayPreviewServer.h"

#include <QApplication>
#include <QColorSpace>
#include <QImageReader>
#include <QLabel>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QShortcut>

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , imageLabel(new QLabel(this))
    , scrollArea(new QScrollArea(this))
{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);
    setCentralWidget(scrollArea);
    scrollArea->setWidgetResizable(false);

    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");

    wSize = prevWsize = 0.3;
    imgScale = 1;
    infinite = false;

    shortcuts();
    resize(QGuiApplication::primaryScreen()->availableSize() * wSize);
}

void ImageViewer::startServer(QString socketN)
{
    server = std::make_unique<QLocalServer>();
    if (server->listen("wayPreview" + socketN))
        connect(server.get(), &QLocalServer::newConnection, this, &ImageViewer::onNewConnection);
    else
        qDebug() << "issues starting server: " << server->errorString();
}

void ImageViewer::onNewConnection()
{
    client.reset(server->nextPendingConnection());
    if (!client->isValid())
        qDebug() << "client error: " << client->errorString();

    connect(client.get(), &QLocalSocket::readyRead, this, [this]() {
        QString command;
        QDataStream reader(client.get());

        reader.startTransaction();
        reader >> command;
        reader.commitTransaction();

        if (command.contains("|")) {
            auto splitC = command.split("|").toVector();
            loadFile(splitC[0]);
            command = splitC[1];
        }

        auto splitC = command.split(" ").toVector();
        int index, index2;
        if (command.contains("quit"))
            quit();
        if ((index = splitC.indexOf("wsize")) != -1)
            setWsize(splitC[index + 1].toDouble());
        if ((index = splitC.indexOf("wzoom")) != -1)
            zoomWindow(splitC[index + 1].toDouble());
        if (command.contains("infinite"))
            toggleInfinite();
        if (command.contains("normal"))
            normalSize();
        if (command.contains("fit"))
            fit();
        if ((index = splitC.indexOf("zoom")) != -1)
            zoomImage(splitC[index + 1].toDouble());
        if ((index = splitC.indexOf("wx")) != -1 && (index2 = splitC.indexOf("wy")) != -1)
            setWpos(splitC[index + 1].toDouble(), splitC[index2 + 1].toDouble());
    });
}

void ImageViewer::toggleInfinite()
{
    if (infinite)
        wSize = prevWsize;
    else {
        prevWsize = wSize;
        wSize = 1;
    }

    infinite = !infinite;
    setWsize(wSize);
}

void ImageViewer::setWsize(double newScale)
{
    wSize = newScale;
    double height = QGuiApplication::primaryScreen()->availableSize().height() * wSize;
    QSize newSize((double) (height * imageRatio), height);
    qDebug() << "newsize: " << newSize << ", wSize: " << wSize << ", infinite: " << infinite;
    resize(newSize);
}

void ImageViewer::zoomWindow(double factor)
{
    qDebug() << "zoomWindow " << factor;
    wSize *= factor;
    setWsize(wSize);
}

void ImageViewer::setWpos(double x, double y)
{
    if (x == -1 || y == -1) {
        system(QString("wrapSetPos.sh \"-1\" \"-1\" 2> /dev/null &").toLocal8Bit().data());
        qDebug() << "just focusing tiling";
    } else {
        QPoint newPoint(x, y);
        QMainWindow::move(newPoint);

        system(QString("wrapSetPos.sh %1 %2 2> /dev/null &").arg(x).arg(y).toLocal8Bit().data());
        qDebug() << "new position: " << newPoint;
    }
}

bool ImageViewer::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        qDebug() << fileName << " not found in filesystem";
        return false;
    }

    setImage(newImage);
    setWindowFilePath(fileName);

    resolution = image.size();
    imageRatio = (double) ((double) resolution.width() / (double) resolution.height());
    qDebug() << "filename: " << fileName << ", resolution: " << resolution
             << " ratio: " << imageRatio;
    setWsize(wSize);
    return true;
}

void ImageViewer::setImage(const QImage &newImage)
{
    image = newImage;
    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imgScale = 1.0;

    scrollArea->setVisible(true);
}

void ImageViewer::zoomIn()
{
    zoomImage(1.1);
}

void ImageViewer::zoomOut()
{
    zoomImage(0.9);
}

void ImageViewer::normalSize()
{
    imageLabel->adjustSize();
    imgScale = 1.0;
}

void ImageViewer::fit()
{
    normalSize();
    image = image.scaled(scrollArea->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    imgScale = (double) scrollArea->width() / resolution.width();
    imageLabel->resize(image.size());
}

void ImageViewer::quit()
{
    if (client)
        client->disconnectFromServer();
    if (server)
        server->disconnect();

    QWidget::close();
}

void ImageViewer::shortcuts()
{
    QShortcut *closeCut = new QShortcut(QKeySequence(Qt::Key_Q), this);
    QObject::connect(closeCut, &QShortcut::activated, this, &ImageViewer::quit);

    QShortcut *normalCut = new QShortcut(QKeySequence(Qt::Key_S), this);
    QObject::connect(normalCut, &QShortcut::activated, this, &ImageViewer::normalSize);

    QShortcut *fitCut = new QShortcut(QKeySequence(Qt::Key_A), this);
    QObject::connect(fitCut, &QShortcut::activated, this, &ImageViewer::fit);

    QShortcut *zinCut = new QShortcut(QKeySequence(Qt::Key_I), this);
    QObject::connect(zinCut, &QShortcut::activated, this, &ImageViewer::zoomIn);

    QShortcut *zoutCut = new QShortcut(QKeySequence(Qt::Key_O), this);
    QObject::connect(zoutCut, &QShortcut::activated, this, &ImageViewer::zoomOut);
}

void ImageViewer::zoomImage(double factor)
{
    qDebug() << "zoomImage " << factor;
    imgScale *= factor;
    imageLabel->resize(imgScale * imageLabel->pixmap(Qt::ReturnByValue).size());
}
