#include <QBrush>
#include "anode.h"
#include "qtroundedrectitem.h"
#include <QDebug>

ANode::ANode(int inputNbr, int outputNbr)
    : QGraphicsRectItem(0),
      m_inputNbr(inputNbr),
      m_outputNbr(outputNbr),
      m_maxContainerNbr(inputNbr > outputNbr ? inputNbr : outputNbr),
      m_inputWidth(30),
      m_outputWidth(30),
      m_inputHeight(20),
      m_outputHeight(20),
      m_inputs(),
      m_outputs()
{
    m_yInputOffset = ((m_maxContainerNbr * 30 + 10) - (inputNbr * 30 + 10)) / 2;
    m_yOutputOffset = ((m_maxContainerNbr * 30 + 10) - (outputNbr * 30 + 10)) / 2;

    this->setRect(0, 0, 150, m_maxContainerNbr * 30 + 10);
    setBrush(QBrush(QColor(Qt::cyan)));
    setFlags(QGraphicsItem::ItemIsMovable);

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    generateInputs();
    generateOutputs();
}

#include "ainput.h"
void ANode::generateInputs() {
    int inputNbr = 0;

    while (inputNbr < m_inputNbr) {
        QGraphicsRectItem *subRect1 = new AInput(10,
                                              (m_inputHeight + 10) * inputNbr + 10 + m_yInputOffset,
                                              m_inputWidth,
                                              m_inputHeight,
                                              this,
                                              this);
        subRect1->setBrush(QBrush(QColor(Qt::yellow)));
        subRect1->setFlags(QGraphicsItem::ItemIsSelectable);
        subRect1->setAcceptHoverEvents(true);

        m_inputs.push_back(subRect1);

        ++inputNbr;
    }
}

void ANode::generateOutputs() {
    int outputNbr = 0;

    while (outputNbr < m_outputNbr) {
        QGraphicsRectItem *subRect1 = new AInput(this->rect().width() - m_outputWidth - 10,
                                              (m_outputHeight + 10) * outputNbr + 10 + m_yOutputOffset,
                                              m_outputWidth,
                                              m_outputHeight,
                                              this,
                                              this);
        subRect1->setBrush(QBrush(QColor(Qt::yellow)));
        subRect1->setFlags(QGraphicsItem::ItemIsSelectable);
        subRect1->setAcceptHoverEvents(true);

        m_outputs.push_back(subRect1);

        ++outputNbr;
    }
}

QList<QGraphicsRectItem *> ANode::getInputs() const {
    return (m_inputs);
}

QList<QGraphicsRectItem *> ANode::getOutputs() const {
    return (m_outputs);
}

QVariant ANode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();

        selectInputMoveLineToCenter(newPos);
    }
    return QGraphicsItem::itemChange(change, value);
}

void ANode::selectInputMoveLineToCenter(QPointF newPos) {
    foreach (QGraphicsRectItem *inputA, m_inputs) {
        AInput *input = dynamic_cast<AInput *>(inputA);
        moveLineToCenter(newPos, input);
    }

    foreach (QGraphicsRectItem *inputA, m_outputs) {
        AInput *input = dynamic_cast<AInput *>(inputA);
        moveLineToCenter(newPos, input);
    }
}

void ANode::moveLineToCenter(QPointF &newPos, AInput *input) {

    //foreach (QGraphicsRectItem *inputA, m_inputs) {

      //  AInput *input = dynamic_cast<AInput *>(inputA);
    // Converts the elipse position (top-left)
    // to its center position
    if (input->line) {
        int xOffset = input->rect().x() + input->rect().width()/2;
        int yOffset = input->rect().y() + input->rect().height()/2;

        QPointF newCenterPos = QPointF(newPos.x() + xOffset, newPos.y() + yOffset);

    // Move the required point of the line to the center of the elipse
        QPointF p1 = input->isP1 ? newCenterPos : input->line->line().p1();
        QPointF p2 = input->isP1 ? input->line->line().p2() : newCenterPos;

        input->line->setLine(QLineF(p1, p2));
    }
 //   }
}
