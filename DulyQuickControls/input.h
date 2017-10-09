#ifndef INPUT_H
#define INPUT_H

#include <QtQuick/QQuickItem>

#include "baseio.h"
#include "io.h"

class InputBackend : public BaseIo
{
public:
    explicit InputBackend(DulyResources::IOType t, QQuickItem *parent);
	
	/**
	* \brief Connect linkable together, create a link, and keep a reference on the visual curve
	* \param linkable
	* \param curve
	* \return Link *
	*/
    Link *connect(ALinkable *linkable, BezierCurve *curve) override;
};

class Input : public Io
{
public:
	explicit Input (QQuickItem *parent = nullptr);

	/**
	* \brief Refresh BackendIO for Input
	*/
	virtual void refreshBackendIo() override;

	/**
	 * \brief Override componentComplete, and init some values
	 */
	virtual void componentComplete() override;

	/**
	* \brief Override findIo, return the IO under the point p of the Node n
	* \param n
	* \param p
	* \return Io *
	*/
	virtual LinkableBezierItem *findLinkableBezierItem(GenericNode *n, const QPointF &p) override;
    virtual void updateLink() override;

protected:
    virtual void afterRealease(Link *l) override;

};
#endif // INPUT_H
