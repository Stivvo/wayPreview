#include <QApplication>
#include <QCommandLineParser>

#include "wayPreviewServer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Image Viewer"));

    ImageViewer imageViewer;
    imageViewer.show();
    imageViewer.connection();
    return app.exec();
}
