#ifndef MODEL_FLOW_H
#define MODEL_FLOW_H

#include "dnai/models/identity.h"
#include "dnai/models/imodel.h"
#include "dnai/models/common.h"

namespace dnai {
namespace models {
class Flow: public Common, public Identity, virtual public IModel
{
public:
    Flow(const qint32 uid, QString const &name, QString const &description, QString const &linked_uid, QObject *parent = nullptr);
    virtual ~Flow() = default;

    // IModel interface
public:
	void serialize(QJsonObject &) const override;
	void declare() const override;
	const QList<QString>& editableProperties() override;

    // IClone interface
private:
    IClone *clone() const override;
	static QList<QString> m_editableProperties;
};
}
}

#endif // MODEL_FLOW_H
