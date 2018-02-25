#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QQuickItem>

namespace dnai {
namespace models {
class QFontSettings : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal pixelSize READ pixelSize WRITE setPixelSize NOTIFY pixelSizeChanged)
    Q_PROPERTY(QString family READ family WRITE setFamily NOTIFY familyChanged)

public:
    explicit QFontSettings(QQuickItem *parent = nullptr) : QQuickItem(parent), m_pixelSize(14)
    {
    }

signals:
    void pixelSizeChanged(qreal s);
    void familyChanged(const QString &f);

public:
    void setPixelSize(qreal s);
    qreal pixelSize() const { return m_pixelSize; }
    void setFamily(const QString &s);
    QString family() const { return m_family;  }

private:
    QString m_family;
    qreal m_pixelSize;

};

class QTextSettings : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor darkColor READ darkColor WRITE setDarkColor NOTIFY darkColorChanged)
    Q_PROPERTY(QColor lightColor READ lightColor WRITE setLightColor NOTIFY lightColorChanged)
    Q_PROPERTY(QColor disableColor READ disableColor WRITE setDisableColor NOTIFY disableColorChanged)
    Q_PROPERTY(QColor linkColor READ linkColor WRITE setLinkColor NOTIFY linkColorChanged)
    Q_PROPERTY(QColor selectionColor READ selectionColor WRITE setSelectionColor NOTIFY selectionColorChanged)
    Q_PROPERTY(QColor accentColor READ accentColor WRITE setAccentColor NOTIFY accentColorChanged)

public:
    explicit QTextSettings(QQuickItem *parent = nullptr) : QQuickItem(parent) {}

signals:
    void colorChanged(const QColor &);
    void darkColorChanged(const QColor &);
    void lightColorChanged(const QColor &);
    void disableColorChanged(const QColor &);
    void linkColorChanged(const QColor &);
    void selectionColorChanged(const QColor &);
    void accentColorChanged(const QColor &);


public:
    void setColor(const QColor& color);
    const QColor &color() const { return m_color; }
    void setDarkColor(const QColor& color);
    const QColor &darkColor() const { return m_darkColor; }
    void setLightColor(const QColor& color);
    const QColor &lightColor() const { return m_lightColor; }
    void setDisableColor(const QColor& color);
    const QColor &disableColor() const { return m_disableColor; }
    void setLinkColor(const QColor& color);
    const QColor &linkColor() const { return m_linkColor; }
    void setSelectionColor(const QColor& color);
    const QColor &selectionColor() const { return m_selectionColor; }
    void setAccentColor(const QColor& color);
    const QColor &accentColor() const { return m_accentColor; }

private:
    QColor m_color;
    QColor m_darkColor;
    QColor m_lightColor;
    QColor m_disableColor;
    QColor m_linkColor;
    QColor m_selectionColor;
    QColor m_accentColor;
};

class QBorder  : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

signals:
    void colorChanged(const QColor &);

public:
    void setColor(const QColor& color);
    const QColor &color() const { return m_color; }

public:
    explicit QBorder(QQuickItem *parent = nullptr) : QQuickItem(parent) {}

private:
    QColor m_color;
};

class QGrid  : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal step READ step WRITE setStep NOTIFY stepChanged)
    Q_PROPERTY(qreal accentStep READ accentStep WRITE setAccentStep NOTIFY accentStepChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor selectColor READ selectColor WRITE setSelectColor NOTIFY selectColorChanged)
    Q_PROPERTY(QColor accentColor READ accentColor WRITE setAccentColor NOTIFY accentColorChanged)

signals:
    void stepChanged(qreal nb);
    void accentStepChanged(qreal nb);
    void colorChanged(const QColor &color);
    void selectColorChanged(const QColor &color);
    void accentColorChanged(const QColor &color);

public:
    void setStep(qreal nb);
    void setAccentStep(qreal nb);
    void setColor(const QColor &color);
    void setSelectColor(const QColor &color);
    void setAccentColor(const QColor &color);

    qreal step() const { return m_step; }
    qreal accentStep() const { return m_accentStep; }
    QColor color() const { return m_color; }
    QColor accentColor() const { return m_accentColor; }
    QColor selectColor() const { return m_selectColor; }

public:
    explicit QGrid(QQuickItem *parent = nullptr) : QQuickItem(parent), m_step(15), m_accentStep(150)
    {
    }

private:
    qreal m_step;
    qreal m_accentStep;
    QColor m_color;
    QColor m_accentColor;
    QColor m_selectColor;
};

class QCanvas : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(dnai::models::QGrid *grid READ grid WRITE setGrid NOTIFY gridChanged)

signals:
    void backgroundChanged(const QColor &color);
    void gridChanged(QGrid *g);

public:
    const QColor &background() const { return m_background; }
    void setBackground(const QColor &color);
    QGrid *grid() const { return m_grid; }
    void setGrid(QGrid *g);

public:
    explicit QCanvas(QQuickItem *parent = nullptr) : QQuickItem(parent), m_grid(new QGrid(this)) {}
    ~QCanvas();
private:
    QGrid *m_grid;
    QColor m_background;
};

class QNode : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(dnai::models::QBorder *border READ border WRITE setBorder NOTIFY borderChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

signals:
    void colorChanged(const QColor &color);
    void borderChanged(QBorder *);

public:
    QBorder *border() const { return m_border; }
    void setBorder(QBorder *b);
    const QColor &color() const { return m_color; }
    void setColor(const QColor &color);

public:
    explicit QNode(QQuickItem *parent = nullptr) : QQuickItem(parent), m_border(new QBorder(this)) {}
    ~QNode();
private:
    QBorder *m_border;
    QColor m_color;
};

class QNodes : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
    Q_PROPERTY(dnai::models::QNode *genericNode READ genericNode WRITE setGenericNode NOTIFY genericNodeChanged)
    Q_PROPERTY(dnai::models::QNode *intNode READ intNode WRITE setIntNode NOTIFY intNodeChanged)
    Q_PROPERTY(dnai::models::QNode *stringNode READ stringNode WRITE setStringNode NOTIFY stringNodeChanged)
    Q_PROPERTY(dnai::models::QNode *boolNode READ boolNode WRITE setBoolNode NOTIFY boolNodeChanged)
    Q_PROPERTY(dnai::models::QNode *functionNode READ functionNode WRITE setFunctionNode NOTIFY functionNodeChanged)
    Q_PROPERTY(dnai::models::QNode *classNode READ classNode WRITE setClassNode NOTIFY classNodeChanged)
    Q_PROPERTY(dnai::models::QNode *listNode READ listNode WRITE setListNode NOTIFY listNodeChanged)

signals:
    void borderWidthChanged(qreal width);
    void genericNodeChanged(QNode *);
    void intNodeChanged(QNode *);
    void stringNodeChanged(QNode *);
    void boolNodeChanged(QNode *);
    void functionNodeChanged(QNode *);
    void classNodeChanged(QNode *);
    void listNodeChanged(QNode *);

public:
    QNode *genericNode() const { return m_genericNode; }
    void setGenericNode(QNode *n);
    QNode *intNode() const { return m_intNode; }
    void setIntNode(QNode *n);
    QNode *stringNode() const { return m_stringNode; }
    void setStringNode(QNode *n);
    QNode *boolNode() const { return m_boolNode; }
    void setBoolNode(QNode *n);
    QNode *functionNode() const { return m_functionNode; }
    void setFunctionNode(QNode *n);
    QNode *classNode() const { return m_classNode; }
    void setClassNode(QNode *n);
    QNode *listNode() const { return m_listNode; }
    void setListNode(QNode *n);
    qreal borderWidth() const { return m_borderWidth; }
    void setBorderWidth(qreal width);

public:
    explicit QNodes(QQuickItem *parent = nullptr) : QQuickItem(parent)
      , m_genericNode(new QNode(this))
      , m_intNode(new QNode(this))
      , m_stringNode(new QNode(this))
      , m_boolNode(new QNode(this))
      , m_functionNode(new QNode(this))
      , m_classNode(new QNode(this))
      , m_listNode(new QNode(this))
      , m_borderWidth(1)
    {
    }
    ~QNodes();

private:
    QNode *m_genericNode;
    QNode *m_intNode;
    QNode *m_stringNode;
    QNode *m_boolNode;
    QNode *m_functionNode;
    QNode *m_classNode;
    QNode *m_listNode;
    qreal m_borderWidth;

};

class QDeclaration : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(dnai::models::QBorder *border READ border WRITE setBorder NOTIFY borderChanged)

signals:
    void backgroundChanged(const QColor &color);
    void radiusChanged(qreal r);
    void borderChanged(QBorder *);


public:
    QBorder *border() const { return m_border; }
    void setBorder(QBorder *b);
    qreal radius() const { return m_radius; }
    void setRadius(qreal r);
    const QColor &background() const { return m_background; }
    void setBackground(const QColor &color);

public:
    explicit QDeclaration(QQuickItem *parent = nullptr) : QQuickItem(parent)
      , m_radius(5), m_border(new QBorder(this))
    {
    }
    ~QDeclaration();
private:
    QColor m_background;
    qreal m_radius;
    QBorder *m_border;
};

class QDeclarationView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal itemSize READ itemSize WRITE setItemSize NOTIFY itemSizeChanged)
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(dnai::models::QBorder *border READ border WRITE setBorder NOTIFY borderChanged)
    Q_PROPERTY(dnai::models::QDeclaration *declContext READ declContext WRITE setDeclContext NOTIFY declContextChanged)
    Q_PROPERTY(dnai::models::QDeclaration *declClass READ declClass WRITE setDeclClass NOTIFY declClassChanged)
    Q_PROPERTY(dnai::models::QDeclaration *declFunction READ declFunction WRITE setDeclFunction NOTIFY declFunctionChanged)
    Q_PROPERTY(dnai::models::QDeclaration *declVariable READ declVariable WRITE setDeclVariable NOTIFY declVariableChanged)

signals:
    void backgroundChanged(const QColor &color);
    void itemSizeChanged(qreal size);
    void radiusChanged(qreal r);
    void borderChanged(QBorder *);
    void declContextChanged(QDeclaration *c);
    void declClassChanged(QDeclaration *c);
    void declFunctionChanged(QDeclaration *f);
    void declVariableChanged(QDeclaration *v);

public:
    QBorder *border() const { return m_border; }
    void setBorder(QBorder *b);
    qreal itemSize() const { return m_itemSize; }
    void setItemSize(qreal size);
    qreal radius() const { return m_radius; }
    void setRadius(qreal size);
    const QColor &background() const { return m_background; }
    void setBackground(const QColor &color);
    QDeclaration *declContext() const { return m_declContext; }
    void setDeclContext(QDeclaration *d);
    QDeclaration *declClass() const { return m_declClass; }
    void setDeclClass(QDeclaration *d);
    QDeclaration *declFunction() const { return m_declFunction; }
    void setDeclFunction(QDeclaration *d);
    QDeclaration *declVariable() const { return m_declVariable; }
    void setDeclVariable(QDeclaration *d);


public:
    explicit QDeclarationView(QQuickItem *parent = nullptr) : QQuickItem(parent)
      , m_itemSize(50), m_radius(0), m_border(new QBorder(this))
      , m_declContext(new QDeclaration(this))
      , m_declClass(new QDeclaration(this))
      , m_declFunction(new QDeclaration(this))
      , m_declVariable(new QDeclaration(this))
    {
    }
    ~QDeclarationView();

private:
    qreal m_itemSize;
    QColor m_background;
    qreal m_radius;
    QBorder *m_border;
    QDeclaration *m_declContext;
    QDeclaration *m_declClass;
    QDeclaration *m_declFunction;
    QDeclaration *m_declVariable;
};

class QBackground : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor darkColor READ darkColor WRITE setDarkColor NOTIFY darkColorChanged)
    Q_PROPERTY(QColor lightColor READ lightColor WRITE setLightColor NOTIFY lightColorChanged)

public:
    QBackground(QQuickItem *parent = nullptr) :
        QQuickItem(parent)
      , m_color(Qt::magenta)
      , m_darkColor(Qt::magenta)
      , m_lightColor(Qt::magenta)
    {}

signals:
    void colorChanged(const QColor &color);
    void darkColorChanged(const QColor &color);
    void lightColorChanged(const QColor &color);

public:
    const QColor &color() const { return m_color; }
    const QColor &darkColor() const { return m_darkColor; }
    const QColor &lightColor() const { return m_lightColor; }

public:
    void setColor(const QColor &color);
    void setDarkColor(const QColor &color);
    void setLightColor(const QColor &color);

private:
    QColor m_color;
    QColor m_darkColor;
    QColor m_lightColor;

};

class MenuSettings : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(dnai::models::QBorder *border READ border WRITE setBorder NOTIFY borderChanged)
    Q_PROPERTY(dnai::models::QBackground *background READ background WRITE setBackground NOTIFY backgroundChanged)
public:
    explicit MenuSettings(QQuickItem *parent = nullptr) : QQuickItem(parent), m_background(new QBackground(this)), m_border(new QBorder(this))
    {}
    ~MenuSettings();

signals:
    void borderChanged(QBorder *);
    void backgroundChanged(QBackground *b);

public:
    QBackground *background() const { return m_background; }
    QBorder *border() const { return m_border; }

public:
    void setBackground(QBackground *b);
    void setBorder(QBorder *b);

private:
    QBackground *m_background;
    QBorder *m_border;
};

class SettingsModel : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(dnai::models::QBackground *background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(dnai::models::MenuSettings *menu READ menu WRITE setMenu NOTIFY menuChanged)
    Q_PROPERTY(QColor shadowColor READ shadowColor WRITE setShadowColor NOTIFY shadowColorChanged)
    Q_PROPERTY(dnai::models::QBorder *border READ border WRITE setBorder NOTIFY borderChanged)
    Q_PROPERTY(dnai::models::QCanvas *canvas READ canvas WRITE setCanvas NOTIFY canvasChanged)
    Q_PROPERTY(dnai::models::QNodes *nodes READ nodes WRITE setNodes NOTIFY nodesChanged)
    Q_PROPERTY(dnai::models::QDeclarationView *declarationView READ declarationView WRITE setDeclarationView NOTIFY declarationViewChanged)
    Q_PROPERTY(dnai::models::QFontSettings *font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(dnai::models::QTextSettings *text READ text WRITE setText NOTIFY textChanged)

signals:
    void backgroundChanged(QBackground *b);
    void menuChanged(MenuSettings *m);
    void shadowColorChanged(const QColor &color);
    void canvasChanged(QCanvas *c);
    void nodesChanged(QNodes *n);
    void declarationViewChanged(QDeclarationView *d);
    void fontChanged(QFontSettings *f);
    void borderChanged(QBorder *);
    void textChanged(QTextSettings *text);


public:
    QBackground *background() const { return m_background; }
    MenuSettings *menu() const { return m_menu; }
    QBorder *border() const { return m_border; }
    const QColor &shadowColor() const { return m_shadowColor; }
    QCanvas *canvas() const { return m_canvas; }
    QNodes *nodes() const { return m_nodes; }
    QDeclarationView *declarationView() const { return m_declarationView; }
    QFontSettings *font() const { return m_font; }
    QTextSettings *text() const { return m_text;  }

public:
    void setBackground(QBackground *b);
    void setMenu(MenuSettings *m);
    void setBorder(QBorder *b);
    void setShadowColor(const QColor &color);
    void setCanvas(QCanvas *c);
    void setNodes(QNodes *n);
    void setDeclarationView(QDeclarationView *d);
    void setFont(QFontSettings *f);
    void setText(QTextSettings *t);


public:
    explicit SettingsModel(QQuickItem *parent = nullptr);
    ~SettingsModel();
private:
    QBackground *m_background;
    MenuSettings *m_menu;
    QColor m_shadowColor;
    QBorder *m_border;
    QCanvas *m_canvas;
    QNodes *m_nodes;
    QDeclarationView *m_declarationView;
    QFontSettings *m_font;
    QTextSettings *m_text;

};
}
}


#endif // SETTINGSMODEL_H
