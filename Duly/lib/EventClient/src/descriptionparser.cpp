#include <QDebug>
#include "descriptionparser.h"

DescriptionParser::DescriptionParser() {
    m_types << TypeParser('I', 4);
    m_types << TypeParser('L', 8);
    m_types << TypeParser('C', 1);
    m_types << TypeParser('F', 4);
    m_types << TypeParser('D', 8);
    m_types << TypeParser('S', 2);

    initReg();
}

void DescriptionParser::initReg() {
    QString regString;

    regString += "([";
    QList<TypeParser>::const_iterator it = m_types.begin();
    while (it != m_types.end()) {
        if (it != m_types.begin()) {
            regString += "|";
        }
        regString += it->firstLetter;
        ++it;
    }

    regString += "][0-9]*)";

    m_rx = QRegExp(regString);
}

void DescriptionParser::parse(QString const &data) {
    QRegExp rx(m_rx);
    int pos = 0;
    m_list.clear();
    m_data.clear();

    while ((pos = rx.indexIn(data, pos)) != -1) {
        QString output = rx.cap(1);
        m_list << output;
        foreach (TypeParser const &type, m_types) {
            if (output[0] == type.firstLetter
                    && output[0] != 'C') {
                QString size = output.remove(0, 1);
                int realSize = size.toInt();
                int i = 0;
                while (i < realSize) {
                    m_data << TypeParser(type.firstLetter, type.size);
                    ++i;
                }
            }
        }
        if (output[0] == 'C') {
            QString size = output.remove(0, 1);
            int realSize = size.toInt();
            m_data << TypeParser('C', realSize);
        }
        pos += rx.matchedLength();
    }
}

QList<DescriptionParser::TypeParser> const &DescriptionParser::getList() const {
    return (m_data);
}
