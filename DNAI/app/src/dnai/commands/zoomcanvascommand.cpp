#include "dnai/commands/zoomcanvascommand.h"

namespace dnai {
namespace commands {
	ZoomCanvasCommand::ZoomCanvasCommand(views::DulyCanvas* c, const double& scale, const QPointF& offset):
		Command("ZoomCanvas", false), m_canvas(c), m_scale(scale), m_offset(offset)
	{
	}

	void ZoomCanvasCommand::execute() const
	{
		m_canvas->zoom(m_scale, m_offset);
	}

	void ZoomCanvasCommand::executeSave()
	{
		execute();
	}

	void ZoomCanvasCommand::unExcute() const
	{
	}

	QString ZoomCanvasCommand::infos() const
	{
		QString adresse;
		adresse.sprintf("%p", m_canvas);
        return m_name + "(" + m_canvas->metaObject()->className() + "(" + adresse + ")" + ", " + QString::number(m_scale) + ", QPointF(" + QString::number(m_offset.x()) + ", " + QString::number(m_offset.y()) + "))";
	}
}
}
