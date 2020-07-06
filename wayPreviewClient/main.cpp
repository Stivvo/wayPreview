#include <QApplication>
#include <QCommandLineParser>
#include <QDataStream>
#include <QLocalSocket>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
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
    QString msg = "";

    if (!parser.positionalArguments().isEmpty())
        msg = parser.positionalArguments().front() + "|";
    if (parser.isSet("quit"))
        msg += " quit";
    if (parser.isSet("wsize") && !parser.value("wsize").isEmpty())
        msg += " wsize " + parser.value("wsize");
    if (parser.isSet("wzoom") && !parser.value("wzoom").isEmpty())
        msg += " wzoom " + parser.value("wzoom");
    if (parser.isSet("infinite"))
        msg += " infinite";
    if (parser.isSet("normal"))
        msg += " normal";
    if (parser.isSet("fit"))
        msg += " fit";
    if (parser.isSet("zoom") && !parser.value("zoom").isEmpty())
        msg += " zoom " + parser.value("zoom");
    msg += " ";

    QLocalSocket socket;
    socket.connectToServer("wayPreview");
    if (!socket.isValid()) {
        qDebug() << "cannot connect: " << socket.errorString();
        return 1;
    }

    QDataStream writer(&socket);
    writer.startTransaction();
    writer << msg;
    writer.commitTransaction();

    socket.flush();
    socket.disconnectFromServer();
    socket.disconnect();
    return 0;
}
