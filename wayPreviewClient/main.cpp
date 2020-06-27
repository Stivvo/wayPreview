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
    parser.addPositionalArgument("[file]", "Image file to open.");

    QVector<QString> optionNames
        = {"zin", "zout", "fit", "normal", "win", "wout", "infinite", "quit"};
    QVector<QString> optionDesc
        = {"zoom in the image",
           "zoom out the image",
           "fit image to window",
           "image real size, 1:1 pixel",
           "increase window size (floating window only)",
           "decrease window size (floating window only)",
           "assing the window the max possible size (useful if the server is tiling or "
           "fullscreen)",
           "close and disconnect the server"};

    socket.connectToServer("wayPreview");
    if (!socket.isValid())
        return 1;

    for (int i = 0; i < optionNames.size(); ++i)
        parser.addOption(QCommandLineOption(optionNames.at(i), optionDesc.at(i)));

    parser.process(QCoreApplication::arguments());

    if (!parser.positionalArguments().isEmpty())
        sendMsg(parser.positionalArguments().front());

    for (QString optionName : optionNames) {
        if (parser.isSet(optionName))
            sendMsg(optionName);
    }

    socket.disconnectFromServer();
    socket.disconnect();
    return 0;
}
