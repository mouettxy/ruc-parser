#include "parser.h"

Parser::Parser(QObject *parent)
    : QObject{parent}
{

}

QMap<QString, QString> Parser::getRowMap(QList<QString> headers) {
    QMap<QString, QString> map;

    foreach (auto header, headers) {
        map.insert(header, "");
    }

    return map;
}

void Parser::loadFile(QString filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QList<QMap<QString, QString>> mappedRows;
        this->fileContents = file.readAll();
    }
}

void Parser::parseFiredEmployes() {
    if (this->fileContents.length() > 0) {
        QList<QMap<QString, QString>> mappedRows;
        QRegularExpression rxHeaders("(<TD CLASS=\"(R6C0)\">)(.*)(<\/TD>)");
        QRegularExpression rxRows("(<TD CLASS=\"(R7C1|R7C0)\">)(.*)(<\/TD>)");

        QRegularExpressionMatchIterator i = rxHeaders.globalMatch(fileContents);
        QRegularExpressionMatchIterator k = rxRows.globalMatch(fileContents);

        QList<QString> headers;
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            QString word = match.captured(3);
            headers << word;
        }

        QMap<QString, QString> map = this->getRowMap(headers);
        int rowIterator = 0;
        while (k.hasNext()) {
            QRegularExpressionMatch match = k.next();
            QString word = match.captured(3);

            if (rowIterator == headers.length()) {
                rowIterator = 0;
                mappedRows << map;
                map = this->getRowMap(headers);
            }

            map.insert(headers.at(rowIterator), word);
            rowIterator++;

            if (!k.hasNext()) {
                rowIterator = 0;
                mappedRows << map;
            }
        }

        QList<QString> firedEmployes;

        foreach (auto row, mappedRows) {
            if (row.value("Вид события") == "Увольнение") {
                firedEmployes.push_back(row.value("Сотрудник"));
            }
        }

        this->firedEmployes = firedEmployes;
    }
}
