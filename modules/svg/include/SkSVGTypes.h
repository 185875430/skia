/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGTypes_DEFINED
#define SkSVGTypes_DEFINED

#include "include/core/SkColor.h"
#include "include/core/SkMatrix.h"
#include "include/core/SkPath.h"
#include "include/core/SkPoint.h"
#include "include/core/SkRect.h"
#include "include/core/SkScalar.h"
#include "include/core/SkString.h"
#include "include/core/SkTypes.h"
#include "include/private/SkTDArray.h"

using SkSVGColorType     = SkColor;
using SkSVGIntegerType   = int;
using SkSVGNumberType    = SkScalar;
using SkSVGStringType    = SkString;
using SkSVGViewBoxType   = SkRect;
using SkSVGTransformType = SkMatrix;
using SkSVGPointsType    = SkTDArray<SkPoint>;

class SkSVGLength {
public:
    enum class Unit {
        kUnknown,
        kNumber,
        kPercentage,
        kEMS,
        kEXS,
        kPX,
        kCM,
        kMM,
        kIN,
        kPT,
        kPC,
    };

    constexpr SkSVGLength()                    : fValue(0), fUnit(Unit::kUnknown) {}
    explicit constexpr SkSVGLength(SkScalar v, Unit u = Unit::kNumber)
        : fValue(v), fUnit(u) {}
    SkSVGLength(const SkSVGLength&)            = default;
    SkSVGLength& operator=(const SkSVGLength&) = default;

    bool operator==(const SkSVGLength& other) const {
        return fUnit == other.fUnit && fValue == other.fValue;
    }
    bool operator!=(const SkSVGLength& other) const { return !(*this == other); }

    const SkScalar& value() const { return fValue; }
    const Unit&     unit()  const { return fUnit;  }

private:
    SkScalar fValue;
    Unit     fUnit;
};

struct SkSVGIRI {
    SkSVGStringType fIRI;
};

class SkSVGPaint {
public:
    enum class Type {
        kNone,
        kCurrentColor,
        kColor,
        kInherit,
        kIRI,
    };

    SkSVGPaint() : fType(Type::kInherit), fColor(SK_ColorBLACK) {}
    explicit SkSVGPaint(Type t) : fType(t), fColor(SK_ColorBLACK) {}
    explicit SkSVGPaint(const SkSVGColorType& c) : fType(Type::kColor), fColor(c) {}
    explicit SkSVGPaint(const SkString& iri)
        : fType(Type::kIRI), fColor(SK_ColorBLACK), fIRI(iri) {}

    SkSVGPaint(const SkSVGPaint&)            = default;
    SkSVGPaint& operator=(const SkSVGPaint&) = default;

    bool operator==(const SkSVGPaint& other) const {
        return fType == other.fType && fColor == other.fColor && fIRI == other.fIRI;
    }
    bool operator!=(const SkSVGPaint& other) const { return !(*this == other); }

    Type type() const { return fType; }
    const SkSVGColorType& color() const { SkASSERT(fType == Type::kColor); return fColor; }
    const SkString& iri() const { SkASSERT(fType == Type::kIRI); return fIRI; }

private:
    Type fType;

    // Logical union.
    SkSVGColorType fColor;
    SkString       fIRI;
};

class SkSVGClip {
public:
    enum class Type {
        kNone,
        kInherit,
        kIRI,
    };

    SkSVGClip() : fType(Type::kNone) {}
    explicit SkSVGClip(Type t) : fType(t)           {}
    explicit SkSVGClip(const SkString& iri) : fType(Type::kIRI), fIRI(iri) {}

    SkSVGClip(const SkSVGClip&)            = default;
    SkSVGClip& operator=(const SkSVGClip&) = default;

    bool operator==(const SkSVGClip& other) const {
        return fType == other.fType && fIRI == other.fIRI;
    }
    bool operator!=(const SkSVGClip& other) const { return !(*this == other); }

    Type type() const { return fType; }
    const SkString& iri() const { SkASSERT(fType == Type::kIRI); return fIRI; }

private:
    Type           fType;
    SkString       fIRI;
};

class SkSVGLineCap {
public:
    enum class Type {
        kButt,
        kRound,
        kSquare,
        kInherit,
    };

    constexpr SkSVGLineCap() : fType(Type::kInherit) {}
    constexpr explicit SkSVGLineCap(Type t) : fType(t) {}

    SkSVGLineCap(const SkSVGLineCap&)            = default;
    SkSVGLineCap& operator=(const SkSVGLineCap&) = default;

    bool operator==(const SkSVGLineCap& other) const { return fType == other.fType; }
    bool operator!=(const SkSVGLineCap& other) const { return !(*this == other); }

    Type type() const { return fType; }

private:
    Type fType;
};

class SkSVGLineJoin {
public:
    enum class Type {
        kMiter,
        kRound,
        kBevel,
        kInherit,
    };

    constexpr SkSVGLineJoin() : fType(Type::kInherit) {}
    constexpr explicit SkSVGLineJoin(Type t) : fType(t) {}

    SkSVGLineJoin(const SkSVGLineJoin&)            = default;
    SkSVGLineJoin& operator=(const SkSVGLineJoin&) = default;

    bool operator==(const SkSVGLineJoin& other) const { return fType == other.fType; }
    bool operator!=(const SkSVGLineJoin& other) const { return !(*this == other); }

    Type type() const { return fType; }

private:
    Type fType;
};

class SkSVGSpreadMethod {
public:
    // These values must match Skia's SkShader::TileMode enum.
    enum class Type {
        kPad,       // kClamp_TileMode
        kRepeat,    // kRepeat_TileMode
        kReflect,   // kMirror_TileMode
    };

    constexpr SkSVGSpreadMethod() : fType(Type::kPad) {}
    constexpr explicit SkSVGSpreadMethod(Type t) : fType(t) {}

    SkSVGSpreadMethod(const SkSVGSpreadMethod&)            = default;
    SkSVGSpreadMethod& operator=(const SkSVGSpreadMethod&) = default;

    bool operator==(const SkSVGSpreadMethod& other) const { return fType == other.fType; }
    bool operator!=(const SkSVGSpreadMethod& other) const { return !(*this == other); }

    Type type() const { return fType; }

private:
    Type fType;
};

class SkSVGFillRule {
public:
    enum class Type {
        kNonZero,
        kEvenOdd,
        kInherit,
    };

    constexpr SkSVGFillRule() : fType(Type::kInherit) {}
    constexpr explicit SkSVGFillRule(Type t) : fType(t) {}

    SkSVGFillRule(const SkSVGFillRule&)            = default;
    SkSVGFillRule& operator=(const SkSVGFillRule&) = default;

    bool operator==(const SkSVGFillRule& other) const { return fType == other.fType; }
    bool operator!=(const SkSVGFillRule& other) const { return !(*this == other); }

    Type type() const { return fType; }

    SkPathFillType asFillType() const {
        SkASSERT(fType != Type::kInherit); // should never be called for unresolved values.
        return fType == Type::kEvenOdd ? SkPathFillType::kEvenOdd : SkPathFillType::kWinding;
    }

private:
    Type fType;
};

class SkSVGVisibility {
public:
    enum class Type {
        kVisible,
        kHidden,
        kCollapse,
        kInherit,
    };

    constexpr SkSVGVisibility() : fType(Type::kVisible) {}
    constexpr explicit SkSVGVisibility(Type t) : fType(t) {}

    SkSVGVisibility(const SkSVGVisibility&)            = default;
    SkSVGVisibility& operator=(const SkSVGVisibility&) = default;

    bool operator==(const SkSVGVisibility& other) const { return fType == other.fType; }
    bool operator!=(const SkSVGVisibility& other) const { return !(*this == other); }

    Type type() const { return fType; }

private:
    Type fType;
};

class SkSVGDashArray {
public:
    enum class Type {
        kNone,
        kDashArray,
        kInherit,
    };

    SkSVGDashArray()                : fType(Type::kNone) {}
    explicit SkSVGDashArray(Type t) : fType(t) {}
    explicit SkSVGDashArray(SkTDArray<SkSVGLength>&& dashArray)
        : fType(Type::kDashArray)
        , fDashArray(std::move(dashArray)) {}

    SkSVGDashArray(const SkSVGDashArray&)            = default;
    SkSVGDashArray& operator=(const SkSVGDashArray&) = default;

    bool operator==(const SkSVGDashArray& other) const {
        return fType == other.fType && fDashArray == other.fDashArray;
    }
    bool operator!=(const SkSVGDashArray& other) const { return !(*this == other); }

    Type type() const { return fType; }

    const SkTDArray<SkSVGLength>& dashArray() const { return fDashArray; }

private:
    Type fType;
    SkTDArray<SkSVGLength> fDashArray;
};

class SkSVGStopColor {
public:
    enum class Type {
        kColor,
        kCurrentColor,
        kICCColor,
        kInherit,
    };

    SkSVGStopColor() : fType(Type::kColor), fColor(SK_ColorBLACK) {}
    explicit SkSVGStopColor(Type t) : fType(t), fColor(SK_ColorBLACK) {}
    explicit SkSVGStopColor(const SkSVGColorType& c) : fType(Type::kColor), fColor(c) {}

    SkSVGStopColor(const SkSVGStopColor&)            = default;
    SkSVGStopColor& operator=(const SkSVGStopColor&) = default;

    bool operator==(const SkSVGStopColor& other) const {
        return fType == other.fType && fColor == other.fColor;
    }
    bool operator!=(const SkSVGStopColor& other) const { return !(*this == other); }

    Type type() const { return fType; }
    const SkSVGColorType& color() const { SkASSERT(fType == Type::kColor); return fColor; }

private:
    Type fType;
    SkSVGColorType fColor;
};

class SkSVGObjectBoundingBoxUnits {
public:
    enum class Type {
        kUserSpaceOnUse,
        kObjectBoundingBox,
    };

    SkSVGObjectBoundingBoxUnits() : fType(Type::kUserSpaceOnUse) {}
    explicit SkSVGObjectBoundingBoxUnits(Type t) : fType(t) {}

    bool operator==(const SkSVGObjectBoundingBoxUnits& other) const {
        return fType == other.fType;
    }
    bool operator!=(const SkSVGObjectBoundingBoxUnits& other) const {
        return !(*this == other);
    }

    Type type() const { return fType; }

private:
    Type fType;
};

class SkSVGFontFamily {
public:
    enum class Type {
        kFamily,
        kInherit,
    };

    SkSVGFontFamily() : fType(Type::kInherit) {}
    explicit SkSVGFontFamily(const char family[])
        : fType(Type::kFamily)
        , fFamily(family) {}

    bool operator==(const SkSVGFontFamily& other) const {
        return fType == other.fType && fFamily == other.fFamily;
    }
    bool operator!=(const SkSVGFontFamily& other) const { return !(*this == other); }

    Type type() const { return fType; }

    const SkString& family() const { return fFamily; }

private:
    Type     fType;
    SkString fFamily;
};

class SkSVGFontStyle {
public:
    enum class Type {
        kNormal,
        kItalic,
        kOblique,
        kInherit,
    };

    SkSVGFontStyle() : fType(Type::kInherit) {}
    explicit SkSVGFontStyle(Type t) : fType(t) {}

    bool operator==(const SkSVGFontStyle& other) const {
        return fType == other.fType;
    }
    bool operator!=(const SkSVGFontStyle& other) const { return !(*this == other); }

    Type type() const { return fType; }

private:
    Type fType;
};

class SkSVGFontSize {
public:
    enum class Type {
        kLength,
        kInherit,
    };

    SkSVGFontSize() : fType(Type::kInherit), fSize(0) {}
    explicit SkSVGFontSize(const SkSVGLength& s)
        : fType(Type::kLength)
        , fSize(s) {}

    bool operator==(const SkSVGFontSize& other) const {
        return fType == other.fType && fSize == other.fSize;
    }
    bool operator!=(const SkSVGFontSize& other) const { return !(*this == other); }

    Type type() const { return fType; }

    const SkSVGLength& size() const { return fSize; }

private:
    Type        fType;
    SkSVGLength fSize;
};

class SkSVGFontWeight {
public:
    enum class Type {
        k100,
        k200,
        k300,
        k400,
        k500,
        k600,
        k700,
        k800,
        k900,
        kNormal,
        kBold,
        kBolder,
        kLighter,
        kInherit,
    };

    SkSVGFontWeight() : fType(Type::kInherit) {}
    explicit SkSVGFontWeight(Type t) : fType(t) {}

    bool operator==(const SkSVGFontWeight& other) const {
        return fType == other.fType;
    }
    bool operator!=(const SkSVGFontWeight& other) const { return !(*this == other); }

    Type type() const { return fType; }

private:
    Type fType;
};

struct SkSVGPreserveAspectRatio {
    enum Align : uint8_t {
        // These values are chosen such that bits [0,1] encode X alignment, and
        // bits [2,3] encode Y alignment.
        kXMinYMin = 0x00,
        kXMidYMin = 0x01,
        kXMaxYMin = 0x02,
        kXMinYMid = 0x04,
        kXMidYMid = 0x05,
        kXMaxYMid = 0x06,
        kXMinYMax = 0x08,
        kXMidYMax = 0x09,
        kXMaxYMax = 0x0a,

        kNone     = 0x10,
    };

    enum Scale {
        kMeet,
        kSlice,
    };

    Align fAlign = kXMidYMid;
    Scale fScale = kMeet;
};

class SkSVGTextAnchor {
public:
    enum class Type {
        kStart,
        kMiddle,
        kEnd,
        kInherit,
    };

    SkSVGTextAnchor() : fType(Type::kInherit) {}
    explicit SkSVGTextAnchor(Type t) : fType(t) {}

    bool operator==(const SkSVGTextAnchor& other) const {
        return fType == other.fType;
    }
    bool operator!=(const SkSVGTextAnchor& other) const { return !(*this == other); }

    Type type() const { return fType; }

private:
    Type fType;
};

class SkSVGFilterType {
public:
    enum class Type {
        kNone,
        kIRI,
        kInherit,
    };

    SkSVGFilterType() : fType(Type::kNone) {}
    explicit SkSVGFilterType(Type t) : fType(t) {}
    explicit SkSVGFilterType(const SkString& iri) : fType(Type::kIRI), fIRI(iri) {}

    bool operator==(const SkSVGFilterType& other) const {
        return fType == other.fType && fIRI == other.fIRI;
    }
    bool operator!=(const SkSVGFilterType& other) const { return !(*this == other); }

    const SkString& iri() const {
        SkASSERT(fType == Type::kIRI);
        return fIRI;
    }

    Type type() const { return fType; }

private:
    Type fType;
    SkString fIRI;
};

class SkSVGFeInputType {
public:
    enum class Type {
        kSourceGraphic,
        kSourceAlpha,
        kBackgroundImage,
        kBackgroundAlpha,
        kFillPaint,
        kStrokePaint,
        kFilterPrimitiveReference,
    };

    SkSVGFeInputType() : fType(Type::kSourceGraphic) {}
    explicit SkSVGFeInputType(Type t) : fType(t) {}
    explicit SkSVGFeInputType(const SkSVGStringType& id)
            : fType(Type::kFilterPrimitiveReference), fId(id) {}

    bool operator==(const SkSVGFeInputType& other) const {
        return fType == other.fType && fId == other.fId;
    }
    bool operator!=(const SkSVGFeInputType& other) const { return !(*this == other); }

    const SkString& id() const {
        SkASSERT(fType == Type::kFilterPrimitiveReference);
        return fId;
    }

    Type type() const { return fType; }

private:
    Type fType;
    SkString fId;
};

enum class SkSVGFeColorMatrixType {
    kMatrix,
    kSaturate,
    kHueRotate,
    kLuminanceToAlpha,
};

using SkSVGFeColorMatrixValues = SkTDArray<SkSVGNumberType>;

enum class SkSVGFeCompositeOperator {
    kOver,
    kIn,
    kOut,
    kAtop,
    kXor,
    kArithmetic,
};

class SkSVGFeTurbulenceBaseFrequency {
public:
    SkSVGFeTurbulenceBaseFrequency() : fFreqX(0), fFreqY(0) {}
    SkSVGFeTurbulenceBaseFrequency(SkSVGNumberType freqX, SkSVGNumberType freqY)
            : fFreqX(freqX), fFreqY(freqY) {}

    SkSVGNumberType freqX() const { return fFreqX; }
    SkSVGNumberType freqY() const { return fFreqY; }

private:
    SkSVGNumberType fFreqX;
    SkSVGNumberType fFreqY;
};

struct SkSVGFeTurbulenceType {
    enum Type {
        kFractalNoise,
        kTurbulence,
    };

    Type fType;

    SkSVGFeTurbulenceType() : fType(kTurbulence) {}
    explicit SkSVGFeTurbulenceType(Type type) : fType(type) {}
};

#endif // SkSVGTypes_DEFINED
