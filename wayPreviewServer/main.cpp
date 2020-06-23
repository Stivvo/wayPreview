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
    if (!commandLineParser.positionalArguments().isEmpty()
        && !imageViewer.loadFile(commandLineParser.positionalArguments().front())) {
        return -1;
    }
    return app.exec();
}
