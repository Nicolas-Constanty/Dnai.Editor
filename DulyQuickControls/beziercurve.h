#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <QtQuick/QQuickItem>
#include <QSettings>

class BezierCurve : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QPointF p1 READ p1 WRITE setP1 NOTIFY p1Changed)
    Q_PROPERTY(QPointF p2 READ p2 WRITE setP2 NOTIFY p2Changed)
    Q_PROPERTY(QPointF p3 READ p3 WRITE setP3 NOTIFY p3Changed)
    Q_PROPERTY(QPointF p4 READ p4 WRITE setP4 NOTIFY p4Changed)

    Q_PROPERTY(bool dotted READ dotted WRITE setDotted NOTIFY dottedChanged)
    Q_PROPERTY(uint lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(uint segmentCount READ segmentCount WRITE setSegmentCount NOTIFY segmentCountChanged)

    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
    Q_PROPERTY(QColor dottedColor READ dottedColor WRITE setDottedColor NOTIFY dottedColorChanged)

public:
	explicit BezierCurve(QQuickItem *parent = nullptr);
    ~BezierCurve();

	/**
	 * \brief Override Base and draw a beautifull bezier curve
	 * \return QSGNode *
	 */
	virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

public:
    QPointF p1() const { return m_p1; }
    QPointF p2() const { return m_p2; }
    QPointF p3() const { return m_p3; }
    QPointF p4() const { return m_p4; }

    bool dotted() const { return m_dotted; }
    uint lineWidth() const { return m_lineWidth; }
    uint segmentCount() const { return m_segmentCount; }

    const QColor &fillColor() const { return m_fillColor; }
    const QColor &dottedColor() const { return m_dottedColor; }

public:
    void setP1(const QPointF &p);
    void setP2(const QPointF &p);
    void setP3(const QPointF &p);
    void setP4(const QPointF &p);

    void setDotted(bool dotted);
    void setLineWidth(uint width);
    void setSegmentCount(uint count);

    void setFillColor(const QColor &color);
    void setDottedColor(const QColor &color);


signals:
    void p1Changed(const QPointF &p);
    void p2Changed(const QPointF &p);
    void p3Changed(const QPointF &p);
    void p4Changed(const QPointF &p);

    void dottedChanged(bool d);
    void lineWidthChanged(uint w);
    void segmentCountChanged(uint count);

    void fillColorChanged(const QColor &color);
    void dottedColorChanged(const QColor &color);

private:
    QPointF m_p1;
    QPointF m_p2;
    QPointF m_p3;
    QPointF m_p4;

    uint m_lineWidth;
    uint m_segmentCount;

    bool m_dotted;
    QColor m_fillColor;
    QColor m_dottedColor;

private:
    bool m_holdClick;
    QVector2D m_scale;
    QVector2D m_lastScale;
    QSettings m_settings;

};
#endif // BEZIERCURVE_H
