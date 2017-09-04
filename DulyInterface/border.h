#ifndef BORDER_H
#define BORDER_H

#include <QObject>
#include <QColor>
#include <QVector4D>

class Border : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector4D rect READ rect WRITE setRect NOTIFY rectChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit Border(QObject *parent = nullptr);

    const QVector4D &rect() const;
    const QColor &color() const;

    void setRect(const QVector4D &r);
    void setColor(const QColor &c);

signals:
    void rectChanged();
    void colorChanged();

private:
    QVector4D m_rect;
    QColor m_color;

public slots:
};

#endif // BORDER_H
