// Automatically generated file do not change!
#include "inviwomodulefactoryobject.h"
#ifdef REG_INVIWOOPENGLMODULE
#include <opengl/openglmodule.h>
#endif
#ifdef REG_INVIWOBASEMODULE
#include <base/basemodule.h>
#endif
#ifdef REG_INVIWOBASEGLMODULE
#include <basegl/baseglmodule.h>
#endif
#ifdef REG_INVIWOABUFFERGLMODULE
#include <abuffergl/abufferglmodule.h>
#endif
#ifdef REG_INVIWOANIMATIONMODULE
#include <animation/animationmodule.h>
#endif
#ifdef REG_INVIWOQTWIDGETSMODULE
#include <qtwidgets/qtwidgetsmodule.h>
#endif
#ifdef REG_INVIWOANIMATIONQTMODULE
#include <animationqt/animationqtmodule.h>
#endif
#ifdef REG_INVIWOASSIMPMODULE
#include <assimp/assimpmodule.h>
#endif
#ifdef REG_INVIWOOPENGLQTMODULE
#include <openglqt/openglqtmodule.h>
#endif
#ifdef REG_INVIWOOPENCLMODULE
#include <opencl/openclmodule.h>
#endif
#ifdef REG_INVIWOBASECLMODULE
#include <basecl/baseclmodule.h>
#endif
#ifdef REG_INVIWOBRUSHINGANDLINKINGMODULE
#include <brushingandlinking/brushingandlinkingmodule.h>
#endif
#ifdef REG_INVIWOCIMGMODULE
#include <cimg/cimgmodule.h>
#endif
#ifdef REG_INVIWOEIGENUTILSMODULE
#include <eigenutils/eigenutilsmodule.h>
#endif
#ifdef REG_INVIWOEXAMPLEMODULE
#include <example/examplemodule.h>
#endif
#ifdef REG_INVIWOFONTRENDERINGMODULE
#include <fontrendering/fontrenderingmodule.h>
#endif
#ifdef REG_INVIWOGLFWMODULE
#include <glfw/glfwmodule.h>
#endif
#ifdef REG_INVIWOHDF5MODULE
#include <hdf5/hdf5module.h>
#endif
#ifdef REG_INVIWONIFTIMODULE
#include <nifti/niftimodule.h>
#endif
#ifdef REG_INVIWOPLOTTINGMODULE
#include <plotting/plottingmodule.h>
#endif
#ifdef REG_INVIWOPLOTTINGGLMODULE
#include <plottinggl/plottingglmodule.h>
#endif
#ifdef REG_INVIWOPOSTPROCESSINGMODULE
#include <postprocessing/postprocessingmodule.h>
#endif
#ifdef REG_INVIWOPVMMODULE
#include <pvm/pvmmodule.h>
#endif
#ifdef REG_INVIWOPYTHON3MODULE
#include <python3/python3module.h>
#endif
#ifdef REG_INVIWOPYTHON3QTMODULE
#include <python3qt/python3qtmodule.h>
#endif
#ifdef REG_INVIWOUSERINTERFACEGLMODULE
#include <userinterfacegl/userinterfaceglmodule.h>
#endif
#ifdef REG_INVIWOVECTORFIELDVISUALIZATIONMODULE
#include <vectorfieldvisualization/vectorfieldvisualizationmodule.h>
#endif
#ifdef REG_INVIWOVECTORFIELDVISUALIZATIONGLMODULE
#include <vectorfieldvisualizationgl/vectorfieldvisualizationglmodule.h>
#endif


namespace inviwo {

std::vector<std::unique_ptr<InviwoModuleFactoryObject>> registerAllModules() {
    std::vector<std::unique_ptr<InviwoModuleFactoryObject>> modules;

    #ifdef REG_INVIWOOPENGLMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<OpenGLModule>(
        "OpenGL",
        "",
        {}
        )
    );
    #endif

    #ifdef REG_INVIWOBASEMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<BaseModule>(
        "Base",
        "All default processors",
        {}
        )
    );
    #endif

    //#ifdef REG_INVIWOBASEGLMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<BaseGLModule>(
    //    "BaseGL",
    //    "",
    //    {"opengl", "base"}
    //    )
    //);
    //#endif

    #ifdef REG_INVIWOABUFFERGLMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<ABufferGLModule>(
        "ABufferGL",
        "",
        {"basegl"}
        )
    );
    #endif

    #ifdef REG_INVIWOANIMATIONMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<AnimationModule>(
        "Animation",
        "description of the Animation module",
        {}
        )
    );
    #endif

    //#ifdef REG_INVIWOQTWIDGETSMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<QtWidgetsModule>(
    //    "QtWidgets",
    //    "",
    //    {}
    //    )
    //);
    //#endif

    #ifdef REG_INVIWOANIMATIONQTMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<AnimationQtModule>(
        "AnimationQt",
        "description of the AnimationQt module",
        {"animation", "qtwidgets"}
        )
    );
    #endif

    //#ifdef REG_INVIWOASSIMPMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<AssimpModule>(
    //    "Assimp",
    //    "Assimp wrapper module to load various meshes",
    //    {}
    //    )
    //);
    //#endif

    //#ifdef REG_INVIWOOPENGLQTMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<OpenGLQtModule>(
    //    "OpenGLQt",
    //    "",
    //    {"opengl", "qtwidgets"}
    //    )
    //);
    //#endif

    #ifdef REG_INVIWOOPENCLMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<OpenCLModule>(
        "OpenCL",
        "",
        {"opengl", "openglqt"}
        )
    );
    #endif

    #ifdef REG_INVIWOBASECLMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<BaseCLModule>(
        "BaseCL",
        "",
        {"opengl", "opencl"}
        )
    );
    #endif

	/* #ifdef REG_INVIWOBRUSHINGANDLINKINGMODULE
	 modules.emplace_back(new InviwoModuleFactoryObjectTemplate<BrushingAndLinkingModule>(
		 "BrushingAndLinking",
		 "description of the BrushingAndLinking module",
		 {}
		 )
	 );
	 #endif

	 #ifdef REG_INVIWOCIMGMODULE
	 modules.emplace_back(new InviwoModuleFactoryObjectTemplate<CImgModule>(
		 "CImg",
		 "",
		 {}
		 )
	 );
	 #endif

	 #ifdef REG_INVIWOEIGENUTILSMODULE
	 modules.emplace_back(new InviwoModuleFactoryObjectTemplate<EigenUtilsModule>(
		 "EigenUtils",
		 "",
		 {}
		 )
	 );
	 #endif*/

    #ifdef REG_INVIWOEXAMPLEMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<ExampleModule>(
        "Example",
        "",
        {"opengl"}
        )
    );
    #endif

    //#ifdef REG_INVIWOFONTRENDERINGMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<FontRenderingModule>(
    //    "FontRendering",
    //    "",
    //    {"opengl"}
    //    )
    //);
    //#endif

    #ifdef REG_INVIWOGLFWMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<GLFWModule>(
        "GLFW",
        "",
        {"opengl"}
        )
    );
    #endif

    #ifdef REG_INVIWOHDF5MODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<HDF5Module>(
        "HDF5",
        "Adds basic support for loading datasets from HDF5 datasets. Needs a system HDF5 installation. \n"
        "At the moment only 1.8.* is supported not 1.10.* ",
        {"base"}
        )
    );
    #endif

    //#ifdef REG_INVIWONIFTIMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<NiftiModule>(
    //    "Nifti",
    //    "Niftilib is a set of i/o libraries for reading and writing files in the NIfTI-1 data format (.nii, .hdr, .img). NIfTI-1 is a binary file format for storing medical image data, e.g. magnetic resonance image (MRI) and functional MRI (fMRI) brain images.",
    //    {}
    //    )
    //);
    //#endif

    #ifdef REG_INVIWOPLOTTINGMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<PlottingModule>(
        "Plotting",
        "# Plotting Module\n"
        "\n"
        "This module provides the basic data structures, properties, and processors necessary for plotting, for example, a CVS source processor and a generic DataFrame for holding data.\n"
        "\n"
        "The PlottingGL module is required for the actual plotting of the data.\n"
        "\n"
        "---\n"
        "**Important;**\n"
        "This module contains ongoing work and is more likely to change more frequently than the Inviwo core.\n"
        "",
        {"fontrendering"}
        )
    );
    #endif

    #ifdef REG_INVIWOPLOTTINGGLMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<PlottingGLModule>(
        "PlottingGL",
        "# PlottingGL Module\n"
        "\n"
        "The PlottingGL module provides processors for plotting DataFrames with OpenGL functionality. Among other things it contains a scatter plot, a scatter plot matrix, a parallel coordinate plot, and both 2D and 3D axes.\n"
        "\n"
        "The Plotting Module is necessary for providing the data structures, i.e. the DataFrame.\n"
        "\n"
        "---\n"
        "**Important;**\n"
        "This module contains ongoing work and is more likely to change more frequently than the Inviwo core.\n"
        "",
        {"plotting", "opengl", "base", "brushingandlinking", "fontrendering"}
        )
    );
    #endif

    //#ifdef REG_INVIWOPOSTPROCESSINGMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<PostProcessingModule>(
    //    "PostProcessing",
    //    "The idea is to bundle up some useful postprocessing techniques in this module that can be applied to just about anything.",
    //    {"opengl", "basegl"}
    //    )
    //);
    //#endif

    //#ifdef REG_INVIWOPVMMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<PVMModule>(
    //    "PVM",
    //    "",
    //    {}
    //    )
    //);
    //#endif

    //#ifdef REG_INVIWOPYTHON3MODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<Python3Module>(
    //    "Python3",
    //    "",
    //    {}
    //    )
    //);
    //#endif

    //#ifdef REG_INVIWOPYTHON3QTMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<Python3QtModule>(
    //    "Python3Qt",
    //    "",
    //    {"python3", "qtwidgets"}
    //    )
    //);
    //#endif

    #ifdef REG_INVIWOUSERINTERFACEGLMODULE
    modules.emplace_back(new InviwoModuleFactoryObjectTemplate<UserInterfaceGLModule>(
        "UserInterfaceGL",
        "# UserInterfaceGL Module\n"
        "\n"
        "This module contains a selection of various processors providing on-screen interfaces for user interactions within an OpenGL canvas. For example, it includes a widget for camera manipulation (Camera Widget), widgets for volume cropping (Cropping Widget), and a presentation mode (Presentation Processor).\n"
        "\n"
        "The Presentation Processor can be used, e.g. during demonstrations, as it allows to show images in a PowerPoint fashion instead of its regular image input.\n"
        "\n"
        "The [Assimp](http;//assimp.sourceforge.net/) library is used for handling the meshes used in the widgets. \n"
        "",
        {"opengl", "basegl", "assimp"}
        )
    );
    #endif

    //#ifdef REG_INVIWOVECTORFIELDVISUALIZATIONMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<VectorFieldVisualizationModule>(
    //    "VectorFieldVisualization",
    //    "",
    //    {"base", "eigenutils", "brushingandlinking"}
    //    )
    //);
    //#endif

    //#ifdef REG_INVIWOVECTORFIELDVISUALIZATIONGLMODULE
    //modules.emplace_back(new InviwoModuleFactoryObjectTemplate<VectorFieldVisualizationGLModule>(
    //    "VectorFieldVisualizationGL",
    //    "",
    //    {"opengl", "basegl"}
    //    )
    //);
    //#endif



    return modules;
}

}  //namespace
