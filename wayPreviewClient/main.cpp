#include <QApplication>
#include <QCommandLineParser>
#include <QDataStream>
#include <QLocalSocket>

QLocalSocket socket;

void sendMsg(QString msg)
{
    QDataStream writer(&socket);
    writer.startTransaction();
    writer << msg;
    writer.commitTransaction();
    qDebug() << socket.errorString();

    if (socket.flush())
        qDebug() << "data was written";
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument("[file]",
                                 "Image file to open. If set, all double dash options are ignored");

    socket.connectToServer("wayPreview");
    if (!socket.isValid())
        return 1;

    parser.addOptions(
        {QCommandLineOption("quit", "close and disconnect the server"),
         QCommandLineOption("normal", "image real size, 1:1 pixel"),
         QCommandLineOption("fit", "fit image to window"),
         QCommandLineOption(
             "infinite",
             "assing the window the max possible size (\"tiling\" or \"fullscreen\" mode). If "
             "is "
             "already set, it will return to \"floating\" mode, with previous window size"),
         QCommandLineOption("zoom",
                            "zoom the image by a <factor> (< 1 zoomin, > 1 zoomout)",
                            "factor"),
         QCommandLineOption("wzoom",
                            "resize window by a <factor> (< 1 smaller, > 1 bigger)",
                            "factor"),
         QCommandLineOption("wsize",
                            "set the <ratio>, between window height and screen height (0.5 uses "
                            "half of the screen height), 0.3 is default if not set",
                            "ratio")});

    parser.process(QCoreApplication::arguments());

    if (!parser.positionalArguments().isEmpty())
        sendMsg(parser.positionalArguments().front());
    else {
        if (parser.isSet("quit"))
            sendMsg("quit");
        if (parser.isSet("normal"))
            sendMsg("normal");
        if (parser.isSet("fit"))
            sendMsg("fit");
        if (parser.isSet("infinite"))
            sendMsg("infinite");
        if (parser.isSet("zoom") && !parser.value("zoom").isEmpty())
            sendMsg("zoom " + parser.value("zoom"));
        if (parser.isSet("wzoom") && !parser.value("wzoom").isEmpty())
            sendMsg("wzoom " + parser.value("wzoom"));
        if (parser.isSet("wsize") && !parser.value("wsize").isEmpty())
            sendMsg("wsize " + parser.value("wsize"));
    }

    socket.disconnectFromServer();
    socket.disconnect();
    return 0;
}
