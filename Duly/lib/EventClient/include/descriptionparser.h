#ifndef DESCRIPTIONPARSER_H
#define DESCRIPTIONPARSER_H

#include <QRegExp>
#include <QString>
#include <QList>

class Q_DECL_EXPORT DescriptionParser {
public:
    typedef struct s_typeParser {
        s_typeParser(char c, int size) : firstLetter(c), size(size) {

        }

        char firstLetter;
        int size;
    } TypeParser;

public:
    DescriptionParser();

private:
    void initReg();

public:
    void parse(QString const &);
    QList<TypeParser> const &getList() const;

private:
    QList<QString> m_list;
    QList<TypeParser> m_types;
    QRegExp     m_rx;
    QList<TypeParser> m_data;
};

#endif // DESCRIPTIONPARSER_H
