#include "Shader.h"


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    std::string vertexCode;
    std::string fragmentCode; 

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    
    //Nos aseguramos de que el objeto ifstream no tenga errores
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        //Abrimos el archivo
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);
        
        std::stringstream vertexShaderStream;
        std::stringstream fragmentShaderStream;

        //Leemos el buffer del archivo y lo almacenamos en el stream
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        //Cerramos el archivo
        vertexShaderFile.close();
        fragmentShaderFile.close();

        //Le pasamos el codigo del archivo al string 
        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();

    }
    catch(std::ifstream::failure &e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ -> " << e.what() << std::endl;
    }

    const GLchar* vertexShaderCode = vertexCode.c_str();
    const GLchar* fragmentShaderCode = fragmentCode.c_str();


    //SHADERS
    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];
    
    //VERTEX SHADER
    //Creamos el shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    //Agregamos el codigo al shader
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    
    //Compilamos el shader 
    glCompileShader(vertexShader);
    
    //Obtenemos el estado de la compilacion
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    //Verificamos si esta todo bien
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else
        std::cout << "Vertex Shader Compilation success!!" << std::endl;
    

    //FRAGMENT SHADER
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    //Agregamos el codigo al shader
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    
    //compilamos los shader
    glCompileShader(fragmentShader);
    
    //se recibe el estado de la compilacion del shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    //Verificar si el shader se compilo correctamente
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else
        std::cout << "Fragment Shader Compilation success!!" << std::endl;
    

    //SHADER PROGRAM
    //Creamos el programa    
    ID = glCreateProgram();

    std::cout << "ID: " << ID << std::endl;
    
    //Agregamos los shader
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    
    
    //linkeamos el programa
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    else
        std::cout << "Link program success!!" << std::endl;
    

    //Se borran los shader porque no se usan mas
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setUniform(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setUniform(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.r, value.g, value.b);
}

void Shader::setUniform(const std::string& name, glm::vec2 value) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}