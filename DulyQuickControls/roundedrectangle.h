#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include <QQuickItem>
#include <QtQuick/qsgnode.h>

class RoundedRectangle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal border READ border WRITE setBorder NOTIFY borderChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
    Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(int roundedSegments READ roundedSegments WRITE setRoundedSegments NOTIFY roundedSegmentsChanged)
    Q_PROPERTY(bool topLeft READ topLeft WRITE setTopLeft NOTIFY topLeftChanged)
    Q_PROPERTY(bool topRight READ topRight WRITE setTopRight NOTIFY topRightChanged)
    Q_PROPERTY(bool bottomLeft READ bottomLeft WRITE setBottomLeft NOTIFY bottomLeftChanged)
    Q_PROPERTY(bool bottomRight READ bottomRight WRITE setBottomRight NOTIFY bottomRightChanged)

public:
    RoundedRectangle(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

//    enum Corner {
//        TopLeft,
//        TopRight,
//        BottomLeft,
//        BottomRight
//    };

    qreal border() const { return m_border; }
    const QColor &borderColor() const { return m_borderColor; }
    const QColor &fillColor() const { return m_fillColor; }
    qreal radius() const { return m_radius; }
    int roundedSegments() const { return m_roundedSegments; }

    void setBorder(qreal b);
    void setBorderColor(const QColor &color);
    void setFillColor(const QColor &color);
    void setRadius(qreal radius);
    void setRoundedSegments(int segments);

    bool topLeft() const { return m_topLeft; }
    bool topRight() const { return m_topRight; }
    bool bottomLeft() const { return m_bottomLeft; }
    bool bottomRight() const { return m_bottomRight; }

    void setTopLeft(bool value);
    void setTopRight(bool value);
    void setBottomLeft(bool value);
    void setBottomRight(bool value);

signals:
    void borderChanged(qreal b);
    void borderColorChanged(const QColor &color);
    void fillColorChanged(const QColor &color);
    void roundedSegmentsChanged(int segments);
    void radiusChanged(qreal radius);

    void topLeftChanged(bool value);
    void topRightChanged(bool value);
    void bottomLeftChanged(bool value);
    void bottomRightChanged(bool value);

protected:

private:
    qreal m_border;
    QColor m_borderColor;
    QColor m_fillColor;
    int m_roundedSegments;
    qreal m_radius;

    bool m_topLeft;
    bool m_topRight;
    bool m_bottomLeft;
    bool m_bottomRight;

//    QSGGeometryNode *DrawCorner(Corner type);
    int GetNumberRoundedCorner() const;
    QSGGeometryNode *CreateBorder() const;

};

#endif // ROUNDEDRECTANGLE_H
