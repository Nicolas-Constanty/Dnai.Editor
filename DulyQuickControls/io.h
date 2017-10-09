#ifndef IO_H
#define IO_H

#include <QtQuick/qsgnode.h>

#include "baseio.h"
#include "resourcesnode.h"
#include "beziercurve.h"
#include "eventutilities.h"
#include "genericnode.h"
#include "linkablebezieritem.h"

class Io : public LinkableBezierItem
{
    Q_OBJECT
    
	Q_PROPERTY(uint nbSegments READ nbSegments WRITE setNbSegments NOTIFY nbSegmentsChanged)
    Q_PROPERTY(DulyResources::IOType type READ type WRITE setType NOTIFY typeChanged)

public:
    static BaseIo *CurrentHover;

public:
	explicit Io (QQuickItem *parent = nullptr);
    ~Io();
	
	/**
	 * \brief Refresh BackendIo
	 */
	virtual void refreshBackendIo();

	/**
     * \brief return the current BaseIO
     * \return BaseIO*
     */
	
	/**
	 * \brief Override updatePaintNode and draw a beautifull IO
	 * \return 
	 */
	virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

    virtual QPointF getCanvasPos() const override;

    virtual GenericNode *getNode() const override;

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
    bool m_holdClick;

    virtual void setHover() override;

    virtual void setLink(Link *l) override;

};
#endif // IO_H
