#ifndef FLOW_H
#define FLOW_H

#include <QSGNode>
#include "baselinkable.h"
#include "resourcesnode.h"
#include "customshape.h"

class FlowBackend : public BaseLinkable
{
public:
	explicit FlowBackend(DulyResources::FlowType t, QQuickItem *parent);
	
	/**
	* \brief return the IOType
	*/
	DulyResources::FlowType getType() const;

protected:
	DulyResources::FlowType m_type;
};

class Flow : public CustomShape
{
    Q_OBJECT
    Q_PROPERTY(DulyResources::FlowType type READ type WRITE setType NOTIFY typeChanged)

public:
	explicit Flow(QQuickItem *parent = nullptr);
    virtual QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

public:
	DulyResources::FlowType type() const { return m_type; }

public:
	void setType(DulyResources::FlowType t);

signals:
	void typeChanged(DulyResources::FlowType t);

private:
	DulyResources::FlowType m_type;

private:
	FlowBackend *m_flow;
};

#endif // FLOW_H
