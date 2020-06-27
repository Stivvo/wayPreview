#include <QApplication>
#include <QCommandLineParser>

#include "wayPreviewServer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Image Viewer"));
    QCommandLineParser commandLineParser;
    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(ImageViewer::tr("[file]"),
                                            ImageViewer::tr("Image file to open."));

    commandLineParser.process(QCoreApplication::arguments());
    ImageViewer imageViewer;
    imageViewer.show();
    imageViewer.connection();
    return app.exec();
}
