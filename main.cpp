#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <parser.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser cmdParser;

    cmdParser.addPositionalArgument("source", "Path to file with table to parse");
    cmdParser.process(app);

    QStringList args = cmdParser.positionalArguments();
    QString filePath = args.at(0);

    Parser *parser = new Parser();

    parser->loadFile(filePath);

    parser->parseFiredEmployes();

    QList<QString> firedEmployes = parser->firedEmployes;

    foreach (auto firedEmployee, firedEmployes) {
        qDebug() << firedEmployee;
    }

    return 0;
}


