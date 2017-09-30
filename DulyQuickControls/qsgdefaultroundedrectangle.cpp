#include "qsgdefaultroundedrectangle.h"

class SmoothColorMaterialShader : public QSGMaterialShader
{
public:
    SmoothColorMaterialShader();

    void updateState(const RenderState &state, QSGMaterial *newEffect, QSGMaterial *oldEffect) override;
    char const *const *attributeNames() const override;

private:
    void initialize() override;

    int m_matrixLoc;
    int m_opacityLoc;
    int m_pixelSizeLoc;
};

SmoothColorMaterialShader::SmoothColorMaterialShader()
    : QSGMaterialShader()
{
    setShaderSourceFile(QOpenGLShader::Vertex, QStringLiteral(":/qt-project.org/scenegraph/shaders/smoothcolor.vert"));
    setShaderSourceFile(QOpenGLShader::Fragment, QStringLiteral(":/qt-project.org/scenegraph/shaders/smoothcolor.frag"));
}

void SmoothColorMaterialShader::updateState(const RenderState &state, QSGMaterial *, QSGMaterial *oldEffect)
{
    if (state.isOpacityDirty())
        program()->setUniformValue(m_opacityLoc, state.opacity());

    if (state.isMatrixDirty())
        program()->setUniformValue(m_matrixLoc, state.combinedMatrix());

    if (oldEffect == 0) {
        // The viewport is constant, so set the pixel size uniform only once.
        QRect r = state.viewportRect();
        program()->setUniformValue(m_pixelSizeLoc, 2.0f / r.width(), 2.0f / r.height());
    }
}

char const *const *SmoothColorMaterialShader::attributeNames() const
{
    static char const *const attributes[] = {
        "vertex",
        "vertexColor",
        "vertexOffset",
        0
    };
    return attributes;
}

void SmoothColorMaterialShader::initialize()
{
    m_matrixLoc = program()->uniformLocation("matrix");
    m_opacityLoc = program()->uniformLocation("opacity");
    m_pixelSizeLoc = program()->uniformLocation("pixelSize");
}

QSGSmoothColorMaterial::QSGSmoothColorMaterial()
{
    setFlag(RequiresFullMatrixExceptTranslate, true);
    setFlag(Blending, true);
}

int QSGSmoothColorMaterial::compare(const QSGMaterial *) const
{
    return 0;
}

QSGMaterialType *QSGSmoothColorMaterial::type() const
{
    static QSGMaterialType type;
    return &type;
}

QSGMaterialShader *QSGSmoothColorMaterial::createShader() const
{
    return new SmoothColorMaterialShader;
}

QSGDefaultRoundedRectangle::QSGDefaultRoundedRectangle()
{
    setMaterial(&m_material);
}

void QSGDefaultRoundedRectangle::updateMaterialAntialiasing()
{
    if (m_antialiasing)
        setMaterial(&m_smoothMaterial);
    else
        setMaterial(&m_material);
}

void QSGDefaultRoundedRectangle::updateMaterialBlending(QSGNode::DirtyState *state)
{
    // smoothed material is always blended, so no change in material state
    if (material() == &m_material) {
        bool wasBlending = (m_material.flags() & QSGMaterial::Blending);
        bool isBlending = (m_gradient_stops.size() > 0 && !m_gradient_is_opaque)
                           || (m_color.alpha() < 255 && m_color.alpha() != 0)
                           || (m_pen_width > 0 && m_border_color.alpha() < 255);
        if (wasBlending != isBlending) {
            m_material.setFlag(QSGMaterial::Blending, isBlending);
            *state |= QSGNode::DirtyMaterial;
        }
    }
}
