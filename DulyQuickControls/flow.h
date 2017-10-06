#ifndef FLOW_H
#define FLOW_H

#include <QQuickItem>
#include <QSGNode>
#include "ilinkable.h"

class FlowBackend : public ALinkable
{
public:
    FlowBackend() {}
    /**
    * \brief Connect linkable together, create a link, and keep a reference on the visual curve
    * \param linkable
    * \param curve
    * \return Link *
    */
    virtual Link *connect(ALinkable *linkable, BezierCurve *curve) override;

    /**
    * \brief Break a link between linkable
    * \param linkable
    */
    virtual void unlink(ALinkable *linkable) override;

    /**
    * \brief Break all the links between linkable
    */
    virtual void unlinkAll() override;

    /**
    * \brief Add a link
    * \param l
    */
    virtual void addLink(Link *l) override;

    /**
    * \brief Remove a link
    * \param l
    */
    virtual void removeLink(Link *l) override;

    /**
    * \brief is linkable is actually
    * \return bool
    */
    bool isLink() override;

    /**
    * \brief return the link between this and linkable
    * \param linkable
    * \return Link *
    */
    Link *getLink(ALinkable *linkable) const override;
};

class Flow : QQuickItem
{
    Q_OBJECT

public:
    enum FlowType
    {
        Enter,
        Exit
    };
    Q_ENUM(FlowType)

    Q_PROPERTY(FlowType type READ type WRITE setType NOTIFY typeChanged)
public:
    Flow(QQuickItem *parent = nullptr);
    virtual QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

};

#endif // FLOW_H
