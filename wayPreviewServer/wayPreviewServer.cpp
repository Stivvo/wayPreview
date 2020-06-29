#include "wayPreviewServer.h"

#include <QApplication>
#include <QColorSpace>
#include <QDir>
#include <QImageReader>
#include <QImageWriter>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
#include <QPainter>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QShortcut>
#include <QStandardPaths>

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , imageLabel(new QLabel)
    , scrollArea(new QScrollArea)
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

    wScale = prevWscale = 0.3;
    imgScale = 1;
    infinite = false;

    shortcuts();
    resize(QGuiApplication::primaryScreen()->availableSize() * wScale);
}

void ImageViewer::connection()
{
    server.reset(new QLocalServer(this));

    if (server->listen("wayPreview")) {
        connect(server.get(), &QLocalServer::newConnection, this, &ImageViewer::onNewConnection);
        qDebug() << "starting server";
    } else {
        qDebug() << "NOT " << server->errorString();
    }
}

void ImageViewer::onNewConnection()
{
    client.reset(server->nextPendingConnection());
    client->waitForConnected();
    qDebug() << "starting client: " << client->errorString();
    qDebug() << "full servername" << client->fullServerName();

    connect(client.get(), &QLocalSocket::readyRead, this, [this]() {
        QString command;
        QDataStream reader(client.get());

        reader.startTransaction();
        reader >> command;
        reader.commitTransaction();
        qDebug() << "command: " << command;

        if (command.contains("/"))
            loadFile(command);
        else {
            auto splitC = command.split(" ").toVector();
            int index;
            if (command.contains("quit"))
                closeDisconnect();
            if (command.contains("normal"))
                normalSize();
            if (command.contains("fit"))
                fit();
            if ((index = splitC.indexOf("zoom")) != -1)
                scaleImage(splitC[index + 1].toDouble());
            if ((index = splitC.indexOf("wsize")) != -1)
                setWscale(splitC[index + 1].toDouble());
            if ((index = splitC.indexOf("wzoom")) != -1)
                resizeWindow(splitC[index + 1].toDouble());
            if (command.contains("infinite"))
                toggleInfinite();
        }
    });
}

void ImageViewer::toggleInfinite()
{
    if (infinite)
        wScale = prevWscale;
    else {
        prevWscale = wScale;
        wScale = 1;
    }

    infinite = !infinite;
    setWscale(wScale);
}

void ImageViewer::setWscale(double newScale)
{
    wScale = newScale;
    double height = QGuiApplication::primaryScreen()->availableSize().height() * wScale;
    resize((double) (height * imageRatio), height);
    qDebug() << "width: " << (double) (height * imageRatio) << " height: " << height
             << ", resolution: " << resolution << " ratio: " << imageRatio << ", wScale: " << wScale
             << ", infinite: " << infinite;
    /* fit(); */
}

void ImageViewer::resizeWindow(double factor)
{
    qDebug() << "resizeWindow " << factor;
    wScale *= factor;
    setWscale(wScale);
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

    setWscale(wScale);
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
    scaleImage(1.1);
}

void ImageViewer::zoomOut()
{
    scaleImage(0.9);
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

void ImageViewer::closeDisconnect()
{
    client->disconnectFromServer();
    server->disconnect();
    QWidget::close();
}

void ImageViewer::shortcuts()
{
    QShortcut *closeCut = new QShortcut(QKeySequence(Qt::Key_Q), this);
    QObject::connect(closeCut, &QShortcut::activated, this, &ImageViewer::closeDisconnect);

    QShortcut *normalCut = new QShortcut(QKeySequence(Qt::Key_S), this);
    QObject::connect(normalCut, &QShortcut::activated, this, &ImageViewer::normalSize);

    QShortcut *fitCut = new QShortcut(QKeySequence(Qt::Key_A), this);
    QObject::connect(fitCut, &QShortcut::activated, this, &ImageViewer::fit);

    QShortcut *zinCut = new QShortcut(QKeySequence(Qt::Key_I), this);
    QObject::connect(zinCut, &QShortcut::activated, this, &ImageViewer::zoomIn);

    QShortcut *zoutCut = new QShortcut(QKeySequence(Qt::Key_O), this);
    QObject::connect(zoutCut, &QShortcut::activated, this, &ImageViewer::zoomOut);
}

void ImageViewer::scaleImage(double factor)
{
    qDebug() << "scaleImage " << factor;
    imgScale *= factor;
    imageLabel->resize(imgScale * imageLabel->pixmap(Qt::ReturnByValue).size());
}
