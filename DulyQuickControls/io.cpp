#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>
#include <QSGSimpleRectNode>

#include "io.h"
#include "beziercurve.h"

IO::IO(QQuickItem *parent) :
    QQuickItem(parent)
  , m_type(DulyResources::IOType::Int)
{
	IO::refreshBackendIO();
    setFlag(ItemHasContents, true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);
}

IO::~IO()
{
    qDebug() << "Hey";
}

bool IO::CheckCircle(const QPoint &p)
{
    //https://stackoverflow.com/questions/481144/equation-for-testing-if-a-point-is-inside-a-circle
    const double r = m_radius + m_radius / 2.5;
    const double dx = qAbs(p.x() - r);
    if (dx > r) return false;
    const double dy = qAbs(p.y() - r);
    if (dy > r) return false;
    if (dx + dy <= r) return true;
    return ( dx*dx + dy*dy <= r*r );
}

void IO::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && CheckCircle(event->pos()))
    {
        m_holdClick = true;
        auto b = new BezierCurve(this);
        b->setPosition(QPoint(width() / 2, height() / 2));
        b->setP1(QPoint(0,0));
        m_currentCurve = b;
    }
}

void IO::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_holdClick = false;
    }
}

void IO::mouseMoveEvent(QMouseEvent *event)
{
    if (m_holdClick)
    {
        m_currentCurve->setP4(event->pos());
    }
}

void IO::setType(DulyResources::IOType type)
{
    if (type == m_type)
        return;
    m_type = type;
    refreshBackendIO();
    emit typeChanged(type);
    update();
}

void IO::setRadius(double radius)
{
    if (radius == m_radius)
        return;
    m_radius = radius;
    emit radiusChanged(radius);
    update();
}

QSGNode *IO::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGSimpleRectNode *node = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!node) {
       node = new QSGSimpleRectNode();
    }
    setWidth((m_radius + m_radius / 2.5) * 2);
    setHeight((m_radius + m_radius / 2.5) * 2);
    node->setColor(QColor(Qt::transparent));
    node->setRect(boundingRect());
    node->appendChildNode(CreateBorder());
    node->appendChildNode(CreateBackground());

    return node;
}



QSGGeometryNode *IO::CreateBackground() const
{
	QSGGeometryNode *node = new QSGGeometryNode;

	const double nbVertice = 64;
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), nbVertice + 2);
    geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);
    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(QColor(255, 255, 255));

    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
	const double a = qDegreesToRadians( 360.0 / nbVertice );
    const double offset = m_radius + m_radius / 2.5;
    vertices[0].set(offset, offset);
    for (int i = 0; i <= nbVertice; i++)
    {
        vertices[i+1].set(offset + m_radius * qCos(a * i), offset + m_radius * qSin(a * i));
    }
    return node;
}

QSGGeometryNode *IO::CreateBorder() const
{
	QSGGeometryNode *node = new QSGGeometryNode;

	const double nbVertice = 64;
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), nbVertice + 2);
    geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);
    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    switch (m_type) {
        case DulyResources::IOType::Int:
            material->setColor(m_settings.value("IntColor/colorSelected").value<QColor>());
            break;
        case DulyResources::IOType::String:
            material->setColor(m_settings.value("StringColor/colorSelected").value<QColor>());
            break;
        case DulyResources::IOType::Bool:
            material->setColor(m_settings.value("BoolColor/colorSelected").value<QColor>());
            break;
        default:
            material->setColor(m_settings.value("theme/ColorStringNode").value<QColor>());
            break;
    }

    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
	const double a = qDegreesToRadians( 360.0 / nbVertice );
	const double r = m_radius + m_radius / 2.5;
    vertices[0].set(r, r);
    for (int i = 0; i <= nbVertice; i++)
    {
        vertices[i+1].set(r + r * qCos(a * i), r + r * qSin(a * i));
    }

    return node;
}
