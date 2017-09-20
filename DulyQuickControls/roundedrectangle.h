#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include <QQuickItem>
#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>

class RoundedRectangle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(int roundedSegments READ roundedSegments WRITE setRoundedSegments NOTIFY roundedSegmentsChanged)
public:
    RoundedRectangle(QQuickItem *parent = 0);
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

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

signals:
    void roundedSegmentsChanged(int segments);
    void radiusChanged(double radius);

protected:

private:
    int m_roundedSegments;
    double m_radius;

    QSGGeometryNode *DrawCorner(Corner type);

};

#endif // ROUNDEDRECTANGLE_H
