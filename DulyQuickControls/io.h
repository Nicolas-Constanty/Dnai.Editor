#ifndef IO_H
#define IO_H

#include <QtQuick/qsgnode.h>

#include "baseio.h"
#include "resourcesnode.h"
#include "beziercurve.h"
#include "eventutilities.h"
#include "genericnode.h"

class Io : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)

    Q_PROPERTY(uint nbSegments READ nbSegments WRITE setNbSegments NOTIFY nbSegmentsChanged)
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)

    Q_PROPERTY(DulyResources::IOType type READ type WRITE setType NOTIFY typeChanged)

public:
    static BaseIo *CurrentHover;

public:
	explicit Io (QQuickItem *parent = nullptr);
    ~Io();
	
    virtual void updateLink() = 0;
	/**
	 * \brief Refresh BackendIo
	 */
	virtual void refreshBackendIo();
	
	/**
	 * \brief Make componentComplete Abstract
	 */
	virtual void componentComplete() override = 0;

	/**
     * \brief return the current BaseIO
     * \return BaseIO*
     */
    BaseIo *getBaseIo() const { return m_io; }
	
	/**
     * \brief return the IO under the point p of the Node n
     * \param n 
     * \param p 
     * \return Io *
     */
    virtual Io *findIo(GenericNode *n, const QPointF &p) = 0;
	
	/**
	 * \brief Override updatePaintNode and draw a beautifull IO
	 * \return 
	 */
	virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

public:
    qreal radius() const { return m_radius; }
    qreal borderWidth() const { return m_borderWidth; }

    uint nbSegments() const { return m_nbSegments; }
    const QColor &fillColor() const { return m_fillColor; }
    const QColor &borderColor() const { return m_borderColor; }

    DulyResources::IOType type() const { return m_type; }

public:
    void setRadius(qreal radius);
    void setBorderWidth(qreal w);

    void setNbSegments(uint n);
    void setFillColor(const QColor &color);
    void setBorderColor(const QColor &color);

    void setType(DulyResources::IOType type);

signals:
    void radiusChanged(qreal radius);
    void borderWidthChanged(qreal w);

    void nbSegmentsChanged(uint n);
    void fillColorChanged(const QColor &color);
    void borderColorChanged(const QColor &color);

    void typeChanged(DulyResources::IOType type);


protected:
    qreal m_radius;
    qreal m_borderWidth;

    uint m_nbSegments;
    QColor m_fillColor;
    QColor m_borderColor;

    DulyResources::IOType m_type;

protected:
    BaseIo *m_io;
    bool m_holdClick;
    BezierCurve *m_currentCurve;

protected:
	/**
	 * \brief Override mouseMoveEvent
	 * \param event 
	 */
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	/**
	 * \brief Override mousePressEvent
	 * \param event 
	 */
	virtual void mousePressEvent(QMouseEvent *event) override;
	/**
	 * \brief Override mouseReleaseEvent
	 * \param event 
	 */
	virtual void mouseReleaseEvent(QMouseEvent *event) override;

};
#endif // IO_H
