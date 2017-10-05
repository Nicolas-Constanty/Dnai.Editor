#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include <QQuickItem>
#include <QtQuick/qsgnode.h>

class RoundedRectangle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal border READ border WRITE setBorder NOTIFY borderChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)

    Q_PROPERTY(bool topLeft READ topLeft WRITE setTopLeft NOTIFY topLeftChanged)
    Q_PROPERTY(bool topRight READ topRight WRITE setTopRight NOTIFY topRightChanged)
    Q_PROPERTY(bool bottomLeft READ bottomLeft WRITE setBottomLeft NOTIFY bottomLeftChanged)
    Q_PROPERTY(bool bottomRight READ bottomRight WRITE setBottomRight NOTIFY bottomRightChanged)

    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(uint roundedSegments READ roundedSegments WRITE setRoundedSegments NOTIFY roundedSegmentsChanged)

public:
    RoundedRectangle(QQuickItem *parent = nullptr);

	/**
	 * \brief Override updatePaintNode and draw a magnificient rounded rectangle
	 * \return QSGNode *
	 */
	virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

public:
    qreal border() const { return m_border; }
    qreal radius() const { return m_radius; }

    bool topLeft() const { return m_topLeft; }
    bool topRight() const { return m_topRight; }
    bool bottomLeft() const { return m_bottomLeft; }
    bool bottomRight() const { return m_bottomRight; }

    int roundedSegments() const { return m_nbSegments; }
    const QColor &fillColor() const { return m_fillColor; }
    const QColor &borderColor() const { return m_borderColor; }

public:
    void setBorder(qreal b);
    void setRadius(qreal radius);

    void setTopLeft(bool value);
    void setTopRight(bool value);
    void setBottomLeft(bool value);
    void setBottomRight(bool value);

    void setRoundedSegments(uint segments);
    void setFillColor(const QColor &color);
    void setBorderColor(const QColor &color);

signals:
    void borderChanged(qreal b);
    void radiusChanged(qreal radius);

    void topLeftChanged(bool value);
    void topRightChanged(bool value);
    void bottomLeftChanged(bool value);
    void bottomRightChanged(bool value);

    void roundedSegmentsChanged(uint segments);
    void fillColorChanged(const QColor &color);
    void borderColorChanged(const QColor &color);

private:
    qreal m_border;
    qreal m_radius;

    bool m_topLeft;
    bool m_topRight;
    bool m_bottomLeft;
    bool m_bottomRight;

    uint m_nbSegments;
    QColor m_fillColor;
    QColor m_borderColor;

private:
	/**
     * \brief return the number of rounded corner
     * \return int
     */
    int getNumberRoundedCorner() const;
	/**
     * \brief create the border and return the geometryNode
     * \return QSGGeometryNode *
     */
    QSGGeometryNode *createBorder() const;

};

#endif // ROUNDEDRECTANGLE_H
