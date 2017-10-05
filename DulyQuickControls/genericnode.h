#ifndef GENERICNODE_H
#define GENERICNODE_H

#include "roundedrectangle.h"
#include "focusmanager.h"

class GenericNode : public QQuickItem
{
	Q_OBJECT

    Q_PROPERTY(RoundedRectangle *header READ header WRITE setHeader NOTIFY headerChanged)
    Q_PROPERTY(RoundedRectangle *content READ content WRITE setContent NOTIFY contentChanged)

public:
	explicit GenericNode(QQuickItem *parent = nullptr);
	/**
	 * \brief Override updatePaintNode and draw a beautifull Node
	 * \return QSGNode *
	 */
	virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

public:
	FocusManagerIo &inputs() { return m_inputs; }
	FocusManagerIo &outputs() { return m_outputs; }
    RoundedRectangle *header() const { return m_header; }
    RoundedRectangle *content() const { return m_content; }

public:
    void setHeader(RoundedRectangle *h);
    void setContent(RoundedRectangle *c);
    
signals:
    void headerChanged(RoundedRectangle *h);
    void contentChanged(RoundedRectangle *c);

private:
    RoundedRectangle *m_header;
    RoundedRectangle *m_content;

private:
    FocusManagerIo m_inputs;
    FocusManagerIo m_outputs;
    QPointF m_offset;

private:
    void updateInputs();
    void updateOutputs();

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

#endif // GENERICNODE_H
