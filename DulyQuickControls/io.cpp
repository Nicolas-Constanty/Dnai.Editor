#include <QtQuick/qsgnode.h>
#include <QtMath>
#include <QSGVertexColorMaterial>

#include "io.h"
#include "beziercurve.h"
#include "dulycanvas.h"
#include "genericnode.h"

BaseIo *Io::CurrentHover = nullptr;

Io::Io(QQuickItem *parent) :
    QQuickItem(parent)
  , m_radius(5)
  , m_borderWidth(3)
  , m_nbSegments(32)
  , m_fillColor(QColor(255, 255, 255))
  , m_borderColor(QColor(0, 255, 0))
  , m_type(DulyResources::IOType::Int)

{
	Io::refreshBackendIo();
    setFlag(ItemHasContents, true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);
    setAntialiasing(true);
}

Io::~Io()
{
}

void Io::refreshBackendIo()
{
}

QSGNode *Io::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    const char r = m_fillColor.red();
    const char g = m_fillColor.green();
    const char b = m_fillColor.blue();
    const char alpha = m_fillColor.alpha();
    if (m_nbSegments != 0 && m_nbSegments % 2 != 0)
        ++m_nbSegments;

    const char rb = m_borderColor.red();
    const char gb = m_borderColor.green();
    const char bb = m_borderColor.blue();
    const char alphab = m_borderColor.alpha();

    const auto aa = antialiasing();
    QSGGeometryNode *node;
    QSGGeometry *geometry;

    setWidth((m_radius + m_radius / 2.5f) * 2);
    setHeight((m_radius + m_radius / 2.5f) * 2);
    const uint nbVertices = (aa?(m_borderWidth > 0 ? 8.0f * (m_nbSegments + 1):4 * (m_nbSegments + 1)):(m_borderWidth > 0?6 * (m_nbSegments + 1):2.5f * (m_nbSegments + 1))) + 1;
    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(),  nbVertices);
        geometry->setLineWidth(1);
        geometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
	    auto material = new QSGVertexColorMaterial;
        material->setFlag(QSGMaterial::Blending);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(nbVertices);
    }
    const auto cx = width() / 2;
    const auto cy = height() / 2;
    const auto a = float(2 * M_PI) / m_nbSegments;
    const qreal aaoffset = 1;
	const auto vertices = geometry->vertexDataAsColoredPoint2D();
	auto idx = -1;
    for (uint i = 0; i <= m_nbSegments; i++)
    {
        if (aa)
        {
            if (i % 2 == 0)
            {
                vertices[++idx].set( cx, cy, r, g, b, alpha);

                vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
                if (m_borderWidth > 0)
                {
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * i), cy +  (m_radius + aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy +  (m_radius + aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);

                    vertices[++idx].set( cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * i), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);

                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * i), cy + (m_radius + m_borderWidth) * qFastSin(a * i), 0, 0, 0, 0);
                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), 0, 0, 0, 0);
                }
                else
                {
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * i), cy +  (m_radius + aaoffset) * qFastSin(a * i), 0, 0, 0, 0);
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy +  (m_radius + aaoffset) * qFastSin(a * (i + 1)), 0, 0, 0, 0);
                }
            }
            else
            {
                if (m_borderWidth > 0)
                {
                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), 0, 0, 0, 0);

                    vertices[++idx].set( cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * i), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);

                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * i), cy +  (m_radius + aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy +  (m_radius + aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
                }
                else
                {
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + aaoffset) * qFastSin(a * (i + 1)), 0, 0, 0, 0);
                }
                vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
            }
        }
        else
        {
            if (i % 2 == 0)
            {
                vertices[++idx].set( cx, cy, r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
                if (m_borderWidth > 0)
                {
                    vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * i), cy + (m_radius + m_borderWidth) * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
                }
            }
            else
            {
                if (m_borderWidth > 0)
                {
                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
                }
                vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
            }
        }
    }

    return node;
}

void Io::setRadius(qreal radius)
{
    if (radius == m_radius)
        return;
    m_radius = radius;
    emit radiusChanged(radius);
    update();
}

void Io::setBorderWidth(qreal w)
{
    if (w == m_borderWidth)
        return;
    m_borderWidth = w;
    emit borderWidthChanged(w);
    update();
}

void Io::setNbSegments(uint n)
{
    if (n == m_nbSegments)
        return;
    m_nbSegments = n;
    emit nbSegmentsChanged(n);
    update();
}

void Io::setFillColor(const QColor &color)
{
    if (color == m_fillColor)
        return;
    m_fillColor = color;
    emit fillColorChanged(color);
    update();
}

void Io::setBorderColor(const QColor &color)
{
    if (color == m_borderColor)
        return;
    m_borderColor = color;
    emit borderColorChanged(color);
    update();
}

void Io::setType(DulyResources::IOType type)
{
    if (type == m_type)
        return;
    m_type = type;
    refreshBackendIo();
    emit typeChanged(type);
    update();
}


void Io::mouseMoveEvent(QMouseEvent *event)
{
	const auto p(mapToItem(DulyCanvas::Instance, event->pos()));
    m_currentCurve->setP4(p);
}

void Io::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && EventUtilities::isHoverCircle(m_radius, event))
    {
        m_holdClick = true;
        auto b = new BezierCurve(DulyCanvas::Instance);
        b->setPosition(mapToItem(DulyCanvas::Instance, position() + QPointF(width() / 2, height() / 2)));
        b->setP1(QPoint(0,0));
        b->setFillColor(m_fillColor);
        QColor c((m_fillColor.red() < 205?m_fillColor.red() + 50:255),
                 (m_fillColor.green() < 205?m_fillColor.green()+50:255),
                 (m_fillColor.blue() < 205?m_fillColor.blue()+50:255),
                 m_fillColor.alpha());

        qDebug() << m_fillColor.red();
        b->setDottedColor(c);
        m_currentCurve = b;
    }
}

void Io::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton || m_currentCurve == nullptr)
        return;
	const auto p(mapToItem(DulyCanvas::Instance, event->pos()));
    auto qlist = DulyCanvas::Instance->focusManager().findFocused(p);
    if (qlist.size() == 0)
    {
        delete(m_currentCurve);
        m_currentCurve = nullptr;
        return;
    }
	const auto node = dynamic_cast<GenericNode *>(qlist.at(0));
    if (node && node != dynamic_cast<GenericNode *>(parentItem()->parentItem()->parentItem()->parentItem()->parentItem()))
    {
	    const auto p1(mapToItem(node, event->pos()));
	    const auto io = findIo(node, p1);
        if (io)
        {
	        const auto c = m_io->connect(io->getBaseIo(), m_currentCurve);
            if (c == nullptr)
                delete(m_currentCurve);
            else
            {
	            const auto p2(
                            io->parentItem()->parentItem()->parentItem()->parentItem()->parentItem()->position() +
                            io->parentItem()->parentItem()->parentItem()->parentItem()->position() +
                            io->parentItem()->parentItem()->parentItem()->position() +
                            io->parentItem()->parentItem()->position() +
                            io->parentItem()->position() + io->position() + QPointF(io->width() / 2, io->height() / 2));
                m_currentCurve->setP4(p2);
                m_currentCurve->setDotted(false);
            }
            m_currentCurve = nullptr;
            return;
        }
    }
    delete(m_currentCurve);
    m_currentCurve = nullptr;
}

