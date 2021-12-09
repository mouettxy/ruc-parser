#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = nullptr);
    void loadFile(QString filePath);
    void parseFiredEmployes();
    QList<QString> firedEmployes;

private:
    QString fileContents;
    QMap<QString, QString> getRowMap(QList<QString> headers);
};

#endif // PARSER_H
