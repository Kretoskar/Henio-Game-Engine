#include "Rendering/Public/Shader.h"

Shader::Shader()
{
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    Generate(vertexShaderPath, fragmentShaderPath);
}

void Shader::Generate(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    int32_t success;

    const GLuint vertexShader = CompileShader(vertexShaderPath, GL_VERTEX_SHADER);
    const GLuint fragShader = CompileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout << "Linking shaders error: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

GLuint Shader::CompileShader(const char* filepath, GLenum type)
{
    int success;

    GLuint ret = glCreateShader(type);
    std::string shaderSrc = LoadShaderSrc(filepath);
    const GLchar* shader = shaderSrc.c_str();
    glShaderSource(ret, 1, &shader, nullptr);
    glCompileShader(ret);

    glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(ret, 512, nullptr, infoLog);
        std::cout << "Vertex shader error: " << infoLog << std::endl;
    }

    return ret;
}

std::string Shader::LoadShaderSrc(const char* filepath)
{
    std::ifstream file;

    std::string ret;

    file.open(filepath);

    if (file.is_open())
    {
        std::stringstream buf;
        buf << file.rdbuf();
        ret = buf.str();
    }
    else
    {
        std::cout << "Couldn't open file: " << filepath << std::endl;
    }

    file.close();

    return ret;
}

void Shader::Activate() const
{
    glUseProgram(id);
}

void Shader::SetBool(const std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::Set3Float(const std::string& name, float v1, float v2, float v3) {
    glUniform3f(glGetUniformLocation(id, name.c_str()), v1, v2, v3);
}

void Shader::Set3Float(const std::string& name, glm::vec3 v) {
    glUniform3f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z);
}

void Shader::Set4Float(const std::string& name, float v1, float v2, float v3, float v4) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), v1, v2, v3, v4);
}

void Shader::Set4Float(const std::string& name, glm::vec4 v) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z, v.w);
}

void Shader::SetMat3(const std::string& name, glm::mat3 val) {
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::SetMat4(const std::string& name, glm::mat4 val) {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}