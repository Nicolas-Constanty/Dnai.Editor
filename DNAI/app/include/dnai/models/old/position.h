#ifndef MODEL_POSITION_H
#define MODEL_POSITION_H

#include "dnai/models/imodel.h"

namespace dnai {
namespace models {
class Position: virtual public IModel
{
public:
	explicit Position(QVector2D const &);

private:
    QVector2D m_position;

public:
    QVector2D position() const;
    void setPosition(const QVector2D &);

    // IClone interface
private:
	virtual IClone *clone() const override;
	void declare() const override;

    // IModel interface
public:
    void serialize(QJsonObject &) const override;
	const QList<QString>& editableProperties() override;

protected:
	static const QList<QString> &m_editableProperties;

};
}
}

#endif // MODEL_POSITION_H
