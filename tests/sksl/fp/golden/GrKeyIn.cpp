

/**************************************************************************************************
 *** This file was autogenerated from GrKeyIn.fp; do not modify.
 **************************************************************************************************/
#include "GrKeyIn.h"

#include "src/core/SkUtils.h"
#include "src/gpu/GrTexture.h"
#include "src/gpu/glsl/GrGLSLFragmentProcessor.h"
#include "src/gpu/glsl/GrGLSLFragmentShaderBuilder.h"
#include "src/gpu/glsl/GrGLSLProgramBuilder.h"
#include "src/sksl/SkSLCPP.h"
#include "src/sksl/SkSLUtil.h"
class GrGLSLKeyIn : public GrGLSLFragmentProcessor {
public:
    GrGLSLKeyIn() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrKeyIn& _outer = args.fFp.cast<GrKeyIn>();
        (void) _outer;
        auto color = _outer.color;
        (void) color;
        fragBuilder->codeAppendf(
R"SkSL(%s = half4(%f, %f, %f, %f);
)SkSL"
, args.fOutputColor, _outer.color.left(), _outer.color.top(), _outer.color.right(), _outer.color.bottom());
    }
private:
    void onSetData(const GrGLSLProgramDataManager& pdman, const GrFragmentProcessor& _proc) override {
    }
};
GrGLSLFragmentProcessor* GrKeyIn::onCreateGLSLInstance() const {
    return new GrGLSLKeyIn();
}
void GrKeyIn::onGetGLSLProcessorKey(const GrShaderCaps& caps, GrProcessorKeyBuilder* b) const {
    uint16_t red = SkFloatToHalf(color.fR);
    uint16_t green = SkFloatToHalf(color.fG);
    uint16_t blue = SkFloatToHalf(color.fB);
    uint16_t alpha = SkFloatToHalf(color.fA);
    b->add32(((uint32_t)red << 16) | green);
    b->add32(((uint32_t)blue << 16) | alpha);
}
bool GrKeyIn::onIsEqual(const GrFragmentProcessor& other) const {
    const GrKeyIn& that = other.cast<GrKeyIn>();
    (void) that;
    if (color != that.color) return false;
    return true;
}
bool GrKeyIn::usesExplicitReturn() const {
    return false;
}
GrKeyIn::GrKeyIn(const GrKeyIn& src)
: INHERITED(kGrKeyIn_ClassID, src.optimizationFlags())
, color(src.color) {
        this->cloneAndRegisterAllChildProcessors(src);
}
std::unique_ptr<GrFragmentProcessor> GrKeyIn::clone() const {
    return std::make_unique<GrKeyIn>(*this);
}
#if GR_TEST_UTILS
SkString GrKeyIn::onDumpInfo() const {
    return SkStringPrintf("(color=half4(%f, %f, %f, %f))", color.left(), color.top(), color.right(), color.bottom());
}
#endif
