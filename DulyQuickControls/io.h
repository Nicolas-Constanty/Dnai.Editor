#ifndef IO_H
#define IO_H

#include <QtQuick/qsgnode.h>

#include "baseio.h"
#include "resourcesnode.h"
#include "beziercurve.h"
#include "eventutilities.h"
#include "genericnode.h"
#include "customshape.h"

class Io : public CustomShape
{
    Q_OBJECT
    
	Q_PROPERTY(uint nbSegments READ nbSegments WRITE setNbSegments NOTIFY nbSegmentsChanged)
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
    uint nbSegments() const { return m_nbSegments; }
    DulyResources::IOType type() const { return m_type; }

public:
    void setNbSegments(uint n);
    void setType(DulyResources::IOType type);

signals:
    void nbSegmentsChanged(uint n);
    void typeChanged(DulyResources::IOType type);


protected:
    uint m_nbSegments;

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
