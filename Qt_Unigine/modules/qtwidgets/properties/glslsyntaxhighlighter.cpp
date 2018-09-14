/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2013-2017 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *********************************************************************************/

#include <modules/qtwidgets/properties/syntaxhighlighter.h>
#include <inviwo/core/common/inviwomodule.h>
#include <inviwo/core/util/filesystem.h>
#include <inviwo/core/common/inviwoapplication.h>
#include <inviwo/core/util/settings/systemsettings.h>

#include <warn/push>
#include <warn/ignore/all>
#include <QTextDocument>
#include <QTextBlock>
#include <warn/pop>


namespace {
enum GLSLSyntaxThins { //rename
    None = 0,
    Type,
    Comment,
    Qualifiers,
    BuiltinVars,
    BuiltinFunc,
    Preprocessor,
    String,
    SIZE_OF_GLSL_SYNTAX_ENUM
};
}

static const char* glsl_types[] = {"\\bfloat", "\\b[bi]?vec[2-4]\\b", "\\bint", "\\bbool\\b",
                                   "\\bmat[2-4]\\b", "\\bvoid\\b", "\\bsampler[1-3]D\\b",
                                   "\\bsamplerCube\\b", "\\bsampler[1-2]DShadow\\b", nullptr};

static const char* glsl_qualifiers[] = {
    "\\bstruct\\b", "\\buniform\\b", "\\battribute\\b", "\\bvarying\\b", "\\bconst\\b",
    "\\bin\\b",     "\\bout\\b",     "\\binout\\b",     "\\bconst\\b",   nullptr};
static const char* glsl_builtins_var[] = {
    "gl_ModelViewMatrix\\b", "\\bgl_ModelViewProjectionMatrix\\b", "\\bgl_ProjectionMatrix\\b",
    "\\bgl_TextureMatrix\\b", "\\bgl_ModelViewMatrixInverse\\b",
    "\\bgl_ModelViewProjectionMatrixInverse\\b", "\\bgl_ProjectionMatrixInverse\\b",
    "\\bgl_TextureMatrixInverse\\b", "\\bgl_ModelViewMatrixTranspose\\b",
    "\\bgl_ModelViewProjectionMatrixTranspose\\b", "\\bgl_ProjectionMatrixTranspose\\b",
    "\\bgl_TextureMatrixTranspose\\b", "\\bgl_ModelViewMatrixInverseTranspose\\b",
    "\\bgl_ModelViewProjectionMatrixInverseTranspose\\b",
    "\\bgl_ProjectionMatrixInverseTranspose\\b", "\\bgl_TextureMatrixInverseTranspose\\b",
    "\\bgl_NormalMatrix\\b", "\\bgl_NormalScale\\b", "\\bgl_DepthRangeParameters\\b",
    "\\bgl_DepthRangeParameters\\b", "\\bgl_DepthRange\\b", "\\bgl_FogParameters\\b",
    "\\bgl_Fog\\b", "\\bgl_LightSourceParameters\\b", "\\bgl_LightSource\\b",
    "\\bgl_LightModelParameters\\b", "\\bgl_LightModel\\b", "\\bgl_LightModelProducts\\b",
    "\\bgl_FrontLightModelProduct\\b", "\\bgl_BackLightModelProduct\\b", "\\bgl_LightProducts\\b",
    "\\b gl_FrontLightProduct\\b", "\\b gl_BackLightProduct\\b", "\\bgl_MaterialParameters\\b",
    "\\bgl_FrontMaterial\\b", "\\bgl_BackMaterial\\b", "\\bgl_PointParameters\\b", "\\bgl_Point\\b",
    "\\bgl_TextureEnvColor\\b", "\\bgl_ClipPlane\\b", "\\bgl_EyePlaneS\\b", "\\bgl_EyePlaneT\\b",
    "\\bgl_EyePlaneR\\b", "\\bgl_EyePlaneQ\\b", "\\bgl_ObjectPlaneS\\b", "\\bgl_ObjectPlaneT\\b",
    "\\bgl_ObjectPlaneR\\b", "\\bgl_ObjectPlaneQ\\b", "\\bgl_Position\\b", "\\bgl_PointSize\\b",
    "\\bgl_ClipVertex\\b", "\\bgl_Vertex\\b", "\\bgl_Normal\\b", "\\bgl_Color\\b",
    "\\bgl_SecondaryColor\\b", "\\bgl_MultiTexCoord[0-7]\\b", "\\bgl_FogCoord\\b",
    "\\bgl_FrontColor\\b", "\\bgl_BackColor\\b", "\\bgl_FrontSecondaryColor\\b",
    "\\bgl_BackSecondaryColor\\b", "\\bgl_TexCoord\\b", "\\bgl_FogFragCoord\\b",
    "\\bgl_FragData\\b", "\\bgl_FragDepth\\b", "\\bgl_FragColor\\b", "\\bgl_FragCoord\\b",
    "\\bgl_FrontFacing\\b", "\\bgl_MaxVertexUniformComponents\\b",
    "\\bgl_MaxFragmentUniformComponents\\b", "\\bgl_MaxVertexAttribs\\b",
    "\\bgl_MaxVaryingFloats\\b", "\\bgl_MaxDrawBuffers \\b", "\\bgl_MaxTextureCoords\\b",
    "\\bgl_MaxTextureUnits\\b", "\\bgl_MaxTextureImageUnits\\b",
    "\\bgl_MaxVertexTextureImageUnits\\b", "\\bgl_MaxCombinedTextureImageUnits\\b",
    "\\bgl_MaxLights\\b", "\\bgl_MaxClipPlanes\\b", nullptr};
static const char* glsl_builtins_func[] = {
    "\\bsin\\b", "\\bcos\\b", "\\btab\\b", "\\basin\\b", "\\bacos\\b", "\\batan\\b",
    "\\bradians\\b", "\\bdegrees\\b", "\\bpow\\b", "\\bexp\\b", "\\blog\\b", "\\bexp2\\b",
    "\\blog2\\b", "\\bsqrt\\b", "\\binversesqrt\\b", "\\babs\\b", "\\bceil\\b", "\\bclamp\\b",
    "\\bfloor\\b", "\\bfract\\b", "\\bmax\\b", "\\bmin\\b", "\\bmix\\b", "\\bmod\\b", "\\bsign\\b",
    "\\bsmoothstep\\b", "\\bstep\\b",
    "\\bmatrixCompMult\\b"
    "\\bftransform\\b",
    "\\bcross\\b", "\\bdistance\\b", "\\bdot\\b", "\\bfaceforward\\b", "\\blength\\b",
    "\\bnormalize\\b", "\\breflect\\b", "\\brefract\\b", "\\bdFdx\\b", "\\bdFdy\\b", "\\bfwidth\\b",
    "\\ball\\b", "\\bany\\b", "\\bequal\\b", "\\bgreaterThan\\b", "\\bgreaterThanEqual\\b",
    "\\blessThan\\b", "\\blessThanEqual\\b", "\\bnot\\b", "\\bnotEqual\\b", "\\btexture[1-3]D\\b",
    "\\btexture1DProj\\b", "\\btexture[1-3]DProj\\b", "\\btextureCube\\b",
    "\\bshadow[1-2]D\\b"
    "\\bshadow[1-2]DProj\\b",
    "\\btexture[1-3]DProjLod\\b", "\\btexture[1-2]DLod\\b", "\\btextureCubeLod\\b",
    "\\bshadow[1-2]DLod\\b"
    "\\bshadow1DProjLod\\b",
    "\\bshadow2DProjLod\\b", "\\bnoise[1-4]\\b", nullptr};
//static const char* glsl_preprocessor[] = {"#","#define","#include","#if","#ifdef","#ifdef","#else","#elif","#endif","#error","#pragma","#line","__LINE__","__FILE__","__VERSION__",0};


namespace inviwo {

class GLSLCommentFormater : public SyntaxFormater {
public:
    GLSLCommentFormater(const QTextCharFormat& format) :
        format_(format)
        , oneLineComment_("^[\\s\\t]*\\/\\/")
        , blockStart_(QRegExp::escape("/*"))
        , blockEnd_(QRegExp::escape("*/")) {
    }

    virtual Result eval(const QString& text, const int& previousBlockState) override {
        Result res;
        res.format = &format_;

        if (oneLineComment_.indexIn(text)!=-1) {
            res.start.push_back(0);
            res.length.push_back(text.size());
            return res;
        }

        int currentFirstNoneCommentCharacter = 0;

        if (previousBlockState != -1 && previousBlockState) {
            res.start.push_back(0);
            int i = blockEnd_.indexIn(text);

            if (i==-1) {
                res.length.push_back(text.size());
                res.outgoingState = 1;
                return res;
            }

            res.length.push_back(i+2);
            currentFirstNoneCommentCharacter = i+2;
        }

        int start;

        while ((start = blockStart_.indexIn(text,currentFirstNoneCommentCharacter))!=-1) {
            res.start.push_back(start);
            int i = blockEnd_.indexIn(text,currentFirstNoneCommentCharacter);

            if (i==-1) {
                res.length.push_back(text.size());
                res.outgoingState = 1;
                return res;
            }

            res.length.push_back(i+2);
            currentFirstNoneCommentCharacter = i+2;
        }

        return res;
    }

private:
    QTextCharFormat format_;
    QRegExp oneLineComment_;
    QRegExp blockStart_;
    QRegExp blockEnd_;
};


class GLSLPreProcessorFormater : public SyntaxFormater {
public:
    GLSLPreProcessorFormater(const QTextCharFormat& format) : format_(format) {
    }

    virtual Result eval(const QString& text, const int& /*previousBlockState*/) override {
        Result res;
        res.format = &format_;

        if (text.size() && text.at(0)== '#') {
            res.start.push_back(0);
            res.length.push_back(text.size());
        }

        return res;
    }

private:
    QTextCharFormat format_;
};

class GLSLKeywordFormater : public SyntaxFormater {
public:
    virtual Result eval(const QString& text, const int& /*previousBlockState*/) override {
        Result result;
        result.format = &format_;
        std::vector<QRegExp>::iterator reg;

        for (reg = regexps_.begin(); reg != regexps_.end(); ++reg) {
            int pos = 0;

            while ((pos = reg->indexIn(text,pos))!=-1) {
                result.start.push_back(pos);
                pos += reg->matchedLength();
                result.length.push_back(reg->matchedLength());
            }
        }

        return result;
    }

    GLSLKeywordFormater(const QTextCharFormat& format,const char** keywords):format_(format) {
        int i = -1;

        while (keywords[++i])
            regexps_.push_back(QRegExp(keywords[i]));
    }

private:
    QTextCharFormat format_;
    std::vector<QRegExp> regexps_;

};

static inline QColor ivec4toQtColor(const ivec4 &i){
    return QColor(i.r, i.g, i.b, i.a);
}

template<>
void SyntaxHighligther::loadConfig<GLSL>() {
    auto sysSettings = InviwoApplication::getPtr()->getSettingsByType<SystemSettings>();
    
    QColor textColor = ivec4toQtColor(sysSettings->glslTextColor_.get());
    QColor bgColor = ivec4toQtColor(sysSettings->glslBackgroundColor_.get());

    defaultFormat_.setBackground(bgColor);
    defaultFormat_.setForeground(textColor);
    QTextCharFormat typeformat,qualifiersformat,builtins_varformat,glsl_builtins_funcformat,commentformat,preprocessorformat;
    typeformat.setBackground(bgColor);
    typeformat.setForeground(ivec4toQtColor(sysSettings->glslTypeColor_.get()));
    qualifiersformat.setBackground(bgColor);
    qualifiersformat.setForeground(ivec4toQtColor(sysSettings->glslQualifierColor_.get()));
    builtins_varformat.setBackground(bgColor);
    builtins_varformat.setForeground(ivec4toQtColor(sysSettings->glslBuiltinsColor_.get()));
    glsl_builtins_funcformat.setBackground(bgColor);
    glsl_builtins_funcformat.setForeground(ivec4toQtColor(sysSettings->glslGlslBuiltinsColor_.get()));
    commentformat.setBackground(bgColor);
    commentformat.setForeground(ivec4toQtColor(sysSettings->glslCommentColor_.get()));
    preprocessorformat.setBackground(bgColor);
    preprocessorformat.setForeground(ivec4toQtColor(sysSettings->glslPreProcessorColor_.get()));

    if (formaters_.empty())
        sysSettings->glslSyntax_.onChange(this, &SyntaxHighligther::loadConfig<GLSL>);
    else{
        while (!formaters_.empty()) {
            delete formaters_.back();
            formaters_.pop_back();
        }
    }

    formaters_.push_back(new GLSLKeywordFormater(typeformat,glsl_types));
    formaters_.push_back(new GLSLKeywordFormater(qualifiersformat,glsl_qualifiers));
    formaters_.push_back(new GLSLKeywordFormater(builtins_varformat,glsl_builtins_var));
    formaters_.push_back(new GLSLKeywordFormater(glsl_builtins_funcformat,glsl_builtins_func));
    formaters_.push_back(new GLSLPreProcessorFormater(preprocessorformat));
    formaters_.push_back(new GLSLCommentFormater(commentformat));
}



} // namespace


