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
#include <QStatusBar>

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

    cuts();
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

bool ImageViewer::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this,
                                 QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                     .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    setImage(newImage);

    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
                                .arg(QDir::toNativeSeparators(fileName))
                                .arg(image.width())
                                .arg(image.height())
                                .arg(image.depth());
    resolution = image.size();
    statusBar()->showMessage(message);
    fit();
    return true;
}

void ImageViewer::setImage(const QImage &newImage)
{
    image = newImage;
    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;

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
    scaleFactor = 1.0;
}

void ImageViewer::fit()
{
    normalSize();
    image = image.scaled(scrollArea->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    scaleFactor = (double) scrollArea->width() / resolution.width();
    imageLabel->resize(image.size());
}

void ImageViewer::cuts()
{
    QShortcut *closeCut = new QShortcut(QKeySequence(Qt::Key_Q), this);
    QObject::connect(closeCut, &QShortcut::activated, this, &QWidget::close);

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
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap(Qt::ReturnByValue).size());
}