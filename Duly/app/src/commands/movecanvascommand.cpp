#include "commands/movecanvascommand.h"
#include "views/dulycanvas.h"

namespace duly_gui
{
	namespace commands
	{
		MoveCanvasCommand::MoveCanvasCommand(views::DulyCanvas *canvas,  const QPointF& pos, bool save) : Command("MoveCanvas", save)
		{
			m_canvas = canvas;
			m_pos = pos;
		}

		void MoveCanvasCommand::execute() const
		{
			m_canvas->moveCanvas(m_pos);
		}

		void MoveCanvasCommand::executeSave()
		{
			m_lastPos = m_canvas->totalOffset();
			m_canvas->moveCanvas(m_pos);
			m_pos = m_lastPos;
		}

		void MoveCanvasCommand::unExcute() const
		{
			m_canvas->moveCanvas(-m_lastPos);
		}

		QString MoveCanvasCommand::infos() const
		{
			QString adresse;
			adresse.sprintf("%p", m_canvas);
			return m_name + "(" + m_canvas->metaObject()->className() + "(" + adresse + ")" + ", " + QString::number(m_pos.x()) + ", " + QString::number(m_pos.y()) + ")";
		}
	}
}
