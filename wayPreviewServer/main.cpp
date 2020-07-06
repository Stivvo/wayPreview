#include <QApplication>
#include <QCommandLineParser>

#include "wayPreviewServer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("wayPreview Server"));

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument("[file]", "Image file to open");
    parser.addOptions(
        {QCommandLineOption("quit", "close and disconnect the server"),
         QCommandLineOption("wsize",
                            "set the <ratio>, between window height and screen height (0.5 uses "
                            "half of the screen height), 0.3 is default if not set",
                            "ratio"),
         QCommandLineOption("wzoom",
                            "resize window by a <factor> (< 1 smaller, > 1 bigger)",
                            "factor"),
         QCommandLineOption(
             "infinite",
             "assing the window the max possible size (\"tiling\" or \"fullscreen\" mode). If "
             "is "
             "already set, it will return to \"floating\" mode, with previous window size"),
         QCommandLineOption("normal", "image real size, 1:1 pixel"),
         QCommandLineOption("fit", "fit image to window"),
         QCommandLineOption("zoom",
                            "zoom the image by a <factor> (< 1 zoomin, > 1 zoomout)",
                            "factor")});

    parser.process(QCoreApplication::arguments());
    ImageViewer imageViewer;
    imageViewer.show();
    imageViewer.startServer();

    if (!parser.positionalArguments().isEmpty())
        imageViewer.loadFile(parser.positionalArguments().front());
    if (parser.isSet("quit"))
        imageViewer.quit();
    if (parser.isSet("wsize") && !parser.value("wsize").isEmpty())
        imageViewer.setWsize(parser.value("wsize").toDouble());
    if (parser.isSet("wzoom") && !parser.value("wzoom").isEmpty())
        imageViewer.zoomWindow(parser.value("wzoom").toDouble());
    if (parser.isSet("infinite"))
        imageViewer.toggleInfinite();
    if (parser.isSet("normal"))
        imageViewer.normalSize();
    if (parser.isSet("fit"))
        imageViewer.fit();
    if (parser.isSet("zoom") && !parser.value("zoom").isEmpty())
        imageViewer.zoomImage(parser.value("wzoom").toDouble());

    return app.exec();
}
