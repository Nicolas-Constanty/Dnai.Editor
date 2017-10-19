#ifndef OUTPUT_H
#define OUTPUT_H

#include "baseio.h"
#include "io.h"

class OutputBackend : public BaseIo
{
public:
    explicit OutputBackend(DulyResources::IOType type, QQuickItem *parent);
	
	/**
	* \brief Connect linkable together, create a link, and keep a reference on the visual curve
	* \param linkable
	* \param curve
	* \return Link *
	*/
    Link *connect(ALinkable *linkable, BezierCurve *curve) override;
};

class Output : public Io
{

public:
	explicit Output (QQuickItem *parent = nullptr);

	/**
	* \brief Refresh BackendIO for Output
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
	virtual LinkableBezierItem *findLinkableBezierItem(GenericNode* n, const QPointF& p) override;

    virtual void updateLink() override;

private:

};
#endif // OUTPUT_H
