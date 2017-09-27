#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include <QQuickItem>
#include <QtQuick/qsgnode.h>

class RoundedRectangle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(int roundedSegments READ roundedSegments WRITE setRoundedSegments NOTIFY roundedSegmentsChanged)
    Q_PROPERTY(bool topLeft READ topLeft WRITE setTopLeft NOTIFY topLeftChanged)
    Q_PROPERTY(bool topRight READ topRight WRITE setTopRight NOTIFY topRightChanged)
    Q_PROPERTY(bool bottomLeft READ bottomLeft WRITE setBottomLeft NOTIFY bottomLeftChanged)
    Q_PROPERTY(bool bottomRight READ bottomRight WRITE setBottomRight NOTIFY bottomRightChanged)

public:
    RoundedRectangle(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

    double radius() const { return m_radius; }
    void setRadius(double radius);

    int roundedSegments() const { return m_roundedSegments; }
    void setRoundedSegments(int segments);
    enum Corner {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    bool topLeft() const { return m_topLeft; }
    bool topRight() const { return m_topRight; }
    bool bottomLeft() const { return m_bottomLeft; }
    bool bottomRight() const { return m_bottomRight; }

    void setTopLeft(bool value);
    void setTopRight(bool value);
    void setBottomLeft(bool value);
    void setBottomRight(bool value);

signals:
    void roundedSegmentsChanged(int segments);
    void radiusChanged(double radius);

    void topLeftChanged(bool value);
    void topRightChanged(bool value);
    void bottomLeftChanged(bool value);
    void bottomRightChanged(bool value);

protected:

private:
    int m_roundedSegments;
    double m_radius;

    bool m_topLeft;
    bool m_topRight;
    bool m_bottomLeft;
    bool m_bottomRight;

    QSGGeometryNode *DrawCorner(Corner type);
    int GetNumberRoundedCorner() const;

};

#endif // ROUNDEDRECTANGLE_H
