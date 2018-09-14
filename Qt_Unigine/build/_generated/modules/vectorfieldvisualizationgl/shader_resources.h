#ifndef VECTORFIELDVISUALIZATIONGL_SHADER_RESOURCE
#define VECTORFIELDVISUALIZATIONGL_SHADER_RESOURCE

#include <modules/opengl/shader/shadermanager.h>



namespace inviwo {

namespace vectorfieldvisualizationgl {

inline void addGeneratedShaderResources(ShaderManager* manager) {

}

inline void addShaderResources(ShaderManager* manager, std::vector<std::string> includePaths) {
#ifdef VECTORFIELDVISUALIZATIONGL_INCLUDE_SHADER_RESOURCES
    addGeneratedShaderResources(manager);
#else
    for (auto& includePath : includePaths) {
        manager->addShaderSearchPath(includePath);
    }
#endif
}

}  // namespace

}  // namespace

#endif
