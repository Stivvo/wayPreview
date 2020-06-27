#include <QApplication>
#include <QCommandLineParser>
#include <QDataStream>
#include <QLocalSocket>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCommandLineParser commandLineParser;
    commandLineParser.addHelpOption();

    commandLineParser.process(QCoreApplication::arguments());

    if (!commandLineParser.positionalArguments().isEmpty()) {
        QLocalSocket socket;
        socket.connectToServer("wayPreview");

        QString message = commandLineParser.positionalArguments().front();
        QDataStream writer(&socket);
        writer.startTransaction();
        writer << message;
        writer.commitTransaction();
        qDebug() << socket.errorString();

        if (socket.flush())
            qDebug() << "data was written";
        socket.disconnectFromServer();
        socket.disconnect();
        return 0;
    }
    return app.exec();
}
