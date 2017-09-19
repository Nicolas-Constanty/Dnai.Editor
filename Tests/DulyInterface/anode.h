#ifndef ANODE_H
#define ANODE_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QList>

class AInput;

class ANode : public QGraphicsRectItem
{
public:
    ANode(int inputNbr, int outputNbr);

private:
    void generateInputs();
    void generateOutputs();

public:
    QList<QGraphicsRectItem *> getInputs() const;
    QList<QGraphicsRectItem *> getOutputs() const;

private:
    int m_inputNbr;
    int m_outputNbr;
    int m_maxContainerNbr;
    int m_inputWidth;
    int m_outputWidth;
    int m_inputHeight;
    int m_outputHeight;
    int m_yInputOffset;
    int m_yOutputOffset;

    QList<QGraphicsRectItem *> m_inputs;
    QList<QGraphicsRectItem *> m_outputs;

public:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void selectInputMoveLineToCenter(QPointF newPos);
    void moveLineToCenter(QPointF &newPos, AInput *);

};

#endif // ANODE_H
