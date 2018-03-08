#ifndef MODEL_OUTPUT_H
#define MODEL_OUTPUT_H

#include "dnai/models/variable.h"
#include "dnai/models/identity.h"
#include "dnai/models/imodel.h"

namespace dnai {
namespace models {
//class Output: public Variable, Identity, virtual public IModel
//{
////public:
////	Output(qint32 uid, QString const& name, QString const& description, QString const& type, bool internal,
////	       QString const& linked_uid, QObject* parent = nullptr);
////    virtual ~Output() = default;

////    // IModel interface
////public:
////	void serialize(QJsonObject &) const override;
////	void declare() const override;
////	const QList<QString>& editableProperties() override;

////    // IClone interface
////private:
////    IClone *clone() const override;
////	static QList<QString> m_editableProperties;
//};
}
}

#endif // MODEL_OUTPUT_H
