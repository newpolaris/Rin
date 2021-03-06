// dev and test spirv-reflect

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>

#include <spirv_reflect.h>
#include "spirv-reflect.h"

int SpirvReflectExample(const void* spirv_code, size_t spirv_nbytes) {
    // Generate reflection data for a shader
    SpvReflectShaderModule module;
    SpvReflectResult result = spvReflectCreateShaderModule(spirv_nbytes, spirv_code, &module);
    assert(result == SPV_REFLECT_RESULT_SUCCESS);

    // Enumerate and extract shader's input variables
    uint32_t var_count = 0;
    result = spvReflectEnumerateInputVariables(&module, &var_count, NULL);
    assert(result == SPV_REFLECT_RESULT_SUCCESS);
    std::vector<SpvReflectInterfaceVariable*> input_vars(var_count);
    result = spvReflectEnumerateInputVariables(&module, &var_count, input_vars.data());
    assert(result == SPV_REFLECT_RESULT_SUCCESS);

    // Output variables, descriptor bindings, descriptor sets, and push constants
    // can be enumerated and extracted using a similar mechanism.

    {
        result = spvReflectEnumerateDescriptorBindings(&module, &var_count, NULL);
        assert(result == SPV_REFLECT_RESULT_SUCCESS);
        std::vector<SpvReflectDescriptorBinding*> input_vars(var_count);
        result = spvReflectEnumerateDescriptorBindings(&module, &var_count, input_vars.data());
    }
    {
        result = spvReflectEnumerateEntryPointDescriptorBindings(&module, "main", &var_count, NULL);
        assert(result == SPV_REFLECT_RESULT_SUCCESS);
        std::vector<SpvReflectDescriptorBinding*> input_vars(var_count);
        result = spvReflectEnumerateEntryPointDescriptorBindings(&module, "main", &var_count, input_vars.data());
    }

    result = spvReflectEnumeratePushConstants(&module, &var_count, NULL);
    // std::vector<SpvReflectInterfaceVariable*> input_vars(var_count);

    // Destroy the reflection data when no longer required.
    spvReflectDestroyShaderModule(&module);

    return 0;
}

std::vector<char> FileRead(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    assert(file.is_open());

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

int main() {
    using namespace spirv;
    {
        std::string filename = "shaders/06.spirv-reflect/vertexinputstate.vert.spv";
        auto code = FileRead(filename);
        SpirvReflectExample(code.data(), code.size());
        ModuleType reflections = ReflectShader(code.data(), code.size());
    }
    {
        std::string filename = "shaders/06.spirv-reflect/pushdescriptor.mesh.spv";
        auto code = FileRead(filename);
        ModuleType reflections = ReflectShader(code.data(), code.size());
    }
    return 0;
}