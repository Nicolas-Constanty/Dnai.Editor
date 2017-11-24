#include "dulysettingsmodel.h"

namespace duly_gui
{
	void QFontSettings::setPixelSize(qreal s)
	{
		if (m_pixelSize == s)
			return;
		m_pixelSize = s;
		emit pixelSizeChanged(s);
	}

	void QFontSettings::setFamily(const QString& s)
	{
		if (m_family == s)
			return;
		m_family = s;
		emit familyChanged(s);
	}

	void QTextSettings::setColor(const QColor& color)
	{
		if (m_color == color)
			return;
		m_color = color;
		emit colorChanged(color);
	}

	void QTextSettings::setDarkColor(const QColor& color)
	{
		if (m_darkColor == color)
			return;
		m_darkColor = color;
		emit darkColorChanged(color);
	}

	void QTextSettings::setLightColor(const QColor& color)
	{
		if (m_lightColor == color)
			return;
		m_lightColor = color;
		emit lightColorChanged(color);
	}

	void QTextSettings::setDisableColor(const QColor& color)
	{
		if (m_disableColor == color)
			return;
		m_disableColor = color;
		emit disableColorChanged(color);
	}

	void QTextSettings::setLinkColor(const QColor& color)
	{
		if (m_linkColor == color)
			return;
		m_linkColor = color;
		emit linkColorChanged(color);
	}

	void QTextSettings::setSelectionColor(const QColor& color)
	{
		if (m_selectionColor == color)
			return;
		m_selectionColor = color;
		emit selectionColorChanged(color);
	}

	void QTextSettings::setAccentColor(const QColor& color)
	{
		if (m_accentColor == color)
			return;
		m_accentColor = color;
		emit accentColorChanged(color);
	}

	void QBorder::setColor(const QColor& color)
	{
		if (m_color == color)
			return;
		m_color = color;
		emit colorChanged(color);
		
	}

	void QGrid::setStep(qreal nb)
	{
		if (nb == m_step)
			return;
		m_step = nb;
		emit stepChanged(nb);
		
	}

	void QGrid::setAccentStep(qreal nb)
	{
		if (nb == m_accentStep)
			return;
		m_accentStep = nb;
		emit accentStepChanged(nb);
		
	}

	void QGrid::setColor(const QColor& color)
	{
		if (m_color == color)
			return;
		m_color = color;
		emit colorChanged(color);
		
	}

	void QGrid::setSelectColor(const QColor& color)
	{
		if (m_selectColor == color)
			return;
		m_selectColor = color;
		emit selectColorChanged(color);
		
	}

	void QGrid::setAccentColor(const QColor& color)
	{
		if (m_accentColor == color)
			return;
		m_accentColor = color;
		emit accentColorChanged(color);
		
	}

	void QCanvas::setBackground(const QColor& color)
	{
		if (m_background == color)
			return;
		m_background = color;
		emit backgroundChanged(color);
		
	}

	void QCanvas::setGrid(QGrid* g)
	{
		if (m_grid == g)
			return;
		m_grid = g;
		emit gridChanged(g);
	}

	void QNode::setBorder(QBorder* b)
	{
		if (m_border == b)
			return;
		m_border = b;
		emit borderChanged(b);
	}

	void QNode::setColor(const QColor& color)
	{
		if (m_color == color)
			return;
		m_color = color;
		emit colorChanged(color);
		
	}

	void QNodes::setGenericNode(QNode* n)
	{
		if (n == m_genericNode)
			return;
		m_genericNode = n;
		emit genericNodeChanged(n);
	}

	void QNodes::setIntNode(QNode* n)
	{
		if (n == m_intNode)
			return;
		m_intNode = n;
		emit intNodeChanged(n);
	}

	void QNodes::setStringNode(QNode* n)
	{
		if (n == m_stringNode)
			return;
		m_stringNode = n;
		emit stringNodeChanged(n);
	}

	void QNodes::setBoolNode(QNode* n)
	{
		if (n == m_boolNode)
			return;
		m_boolNode = n;
		emit boolNodeChanged(n);
	}

	void QNodes::setFunctionNode(QNode* n)
	{
		if (n == m_functionNode)
			return;
		m_functionNode = n;
		emit functionNodeChanged(n);
	}

	void QNodes::setClassNode(QNode* n)
	{
		if (n == m_classNode)
			return;
		m_classNode = n;
		emit classNodeChanged(n);
	}

	void QNodes::setListNode(QNode* n)
	{
		if (n == m_listNode)
			return;
		m_listNode = n;
		emit listNodeChanged(n);
	}

	void QNodes::setBorderWidth(qreal w)
	{
		if (w == m_borderWidth)
			return;
		m_borderWidth = w;
		emit borderWidthChanged(w);
		
	}

	void QDeclaration::setBorder(QBorder* b)
	{
		if (m_border == b)
			return;
		m_border = b;
		emit borderChanged(b);
	}

	void QDeclaration::setRadius(qreal r)
	{
		if (r == m_radius)
			return;
		m_radius = r;
		emit radiusChanged(r);
		
	}

	void QDeclaration::setBackground(const QColor& color)
	{
		if (m_background == color)
			return;
		m_background = color;
		emit backgroundChanged(color);
		
	}

	void QDeclarationView::setBorder(QBorder* b)
	{
		if (m_border == b)
			return;
		m_border = b;
		emit borderChanged(b);
	}

	void QDeclarationView::setItemSize(qreal size)
	{
		if (size == m_itemSize)
			return;
		m_itemSize = size;
		emit itemSizeChanged(size);
		
	}

	void QDeclarationView::setRadius(qreal size)
	{
		if (size == m_radius)
			return;
		m_radius = size;
		emit radiusChanged(size);
		
	}

	void QDeclarationView::setBackground(const QColor& color)
	{
		if (m_background == color)
			return;
		m_background = color;
		emit backgroundChanged(color);
		
	}

	void QDeclarationView::setDeclContext(QDeclaration* d)
	{
		if (m_declContext == d)
			return;
		m_declContext = d;
		emit declContextChanged(d);

	}

	void QDeclarationView::setDeclClass(QDeclaration* d)
	{
		if (m_declClass == d)
			return;
		m_declClass = d;
		emit declClassChanged(d);

	}

	void QDeclarationView::setDeclFunction(QDeclaration* d)
	{
		if (m_declFunction == d)
			return;
		m_declFunction = d;
		emit declFunctionChanged(d);

	}

	void QDeclarationView::setDeclVariable(QDeclaration* d)
	{
		if (m_declVariable == d)
			return;
		m_declVariable = d;
		emit declVariableChanged(d);

	}

	void DulySettingsModel::setBackground(const QColor& color)
	{
		if (m_background == color)
			return;
		m_background = color;
		emit backgroundChanged(color);
	}

	void DulySettingsModel::setShadowColor(const QColor& color)
	{
		if (m_shadowColor == color)
			return;
		m_shadowColor = color;
		emit shadowColorChanged(color);
		
	}

	void DulySettingsModel::setBorder(QBorder *b)
	{
		if (m_border == b)
			return;
		m_border = b;
		emit borderChanged(b);
		
	}

	void DulySettingsModel::setDelegateColor(const QColor& color)
	{
		if (m_delegateColor == color)
			return;
		m_delegateColor = color;
		emit delegateColorChanged(color);
	}

	void DulySettingsModel::setCanvas(QCanvas *c)
	{
		if (m_canvas == c)
			return;
		m_canvas = c;
		emit canvasChanged(c);
		
	}

	void DulySettingsModel::setNodes(QNodes *n)
	{
		if (m_nodes == n)
			return;
		m_nodes = n;
		emit nodesChanged(n);
		
	}

	void DulySettingsModel::setDeclarationView(QDeclarationView *d)
	{
		if (m_declarationView == d)
			return;
		m_declarationView = d;
		emit declarationViewChanged(d);
		
	}

	void DulySettingsModel::setFont(QFontSettings* f)
	{
		if (m_font == f)
			return;
		m_font = f;
		emit fontChanged(f);
		
	}

	void DulySettingsModel::setText(QTextSettings* t)
	{
		if (m_text == t)
			return;
		m_text = t;
		emit textChanged(t);
	}
}
