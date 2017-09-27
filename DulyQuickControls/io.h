#ifndef IO_H
#define IO_H

#include <QtQuick/QQuickItem>
#include <QSettings>
#include <QtQuick/qsgnode.h>

#include "baseio.h"
#include "resourcesnode.h"
#include "beziercurve.h"

class IO : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(DulyResources::IOType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    IO (QQuickItem *parent = 0);
    ~IO();

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

    void setType(DulyResources::IOType type);
    void setRadius(double radius);
    DulyResources::IOType type() const { return m_type; }
    double radius() const { return m_radius; }
    virtual void refreshBackendIO() {}

signals:
    void typeChanged(DulyResources::IOType type);
    void radiusChanged(double radius);

private:
    QSGGeometryNode *CreateBorder() const;
    QSGGeometryNode *CreateBackground() const;
    bool CheckCircle(const QPoint &p);


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


    DulyResources::IOType m_type;
    QSettings m_settings;
    double m_radius;
    BaseIO *m_io;

    bool m_holdClick;
    BezierCurve *m_currentCurve;
};
#endif // IO_H
