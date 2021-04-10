#include <iostream>
#include <time.h>
#include <glad/glad.h>
#include <glfw3.h>
#include <string.h>
#include <filesystem>
#include <stb_image.h>

//GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#include "shaders/Shader.h"
#include "camera/Camera.h"
#include "textures/ImageTexture.h"
#include "mesh/Mesh.h"
#include "mesh/Model.h"
#include "lights/PointLight.h"
#include "lights/SpotLight.h"
#include "lights/DirectionalLight.h"

//TODO:: HACER LAS CLASES DE LUCES

//Esta funcion sirve para que el viewport de opengl se ajuste al tamano de la ventana cuando este sea modificado por el usuario
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

//Esta funcion sirve para recibir lad entradas de teclado
void processInput(GLFWwindow* window);

//mouse callback
void mouseCallBack(GLFWwindow* window, double xpos, double ypos);

//Scroll callback
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);


const float WINDOW_WIDTH = 1280.0f;
const float WINDOW_HEIGHT = 720.0f;

#define VERTEX_SHADER_PATH               "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\VertexShaders\\shader.vert"
#define FRAGMENT_SHADER_PATH             "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\FragmentShaders\\shader.frag"

#define DEPTH_BUFFER_TEST                "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\FragmentShaders\\depthBufferTestShader.frag"  

#define VERTEX_LIGHTSHADER_PATH          "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\VertexShaders\\lightCube.vert"
#define FRAGMENT_LIGHTSHADER_PATH        "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\FragmentShaders\\lightShader.frag"

#define FRAGMENT_MODEL_SHADER_PATH       "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\FragmentShaders\\model.frag"
                                             
const std::string TEXTURE_BLINK_PATH   = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\TestTexture\\BlinkGuy.png"; 
const std::string TEXTURE_BLINK_2_PATH = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\TestTexture\\BlinkGuy-2.png";
const std::string TEXTURE_COBBLE_PATH  = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\CobblestoneTextures\\cobblestone-diff.jpg";
const std::string TEXTURE_WOODBOX      = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\WoodBox\\container2.png";
const std::string TEXTURE_WOODBOX_SPEC = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\WoodBox\\container2_specular.png";
const std::string TEXTURE_GRASS        = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\Grass\\grassTexture.jpg";
const std::string TEXTURE_GRASS_SPEC   = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\Grass\\grassTextureSpecular.jpg";
const std::string TEXTURE_FLASHLIGHT   = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\FlashLightTexture\\flashLightTexture.png";
const std::string MODEL_PATH_LOAD      = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\mesh\\Models\\Primitives\\suzane.obj";

//CAMERA
Camera mainCamera(glm::vec3(1.0f, 1.0f, 1.0f));

float lastX = WINDOW_WIDTH / 2; 
float lastY = WINDOW_HEIGHT / 2;
bool firstMouseMove = true;

//Delta time 
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main()
{
    
    srand((unsigned int)time(NULL));

    //Inicializar glfw y configurar
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //Se crea una ventana
    GLFWwindow* window = glfwCreateWindow((int)WINDOW_WIDTH, (int)WINDOW_HEIGHT, "My FirstApp In OpenGL :D", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "No se ha podido crear la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << std::filesystem::current_path() << std::endl;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    //Sirve para bloquear el cursor a la pantalla
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //seteamos el mouse position callback
    glfwSetCursorPosCallback(window, mouseCallBack);
    //set scroll callback
    glfwSetScrollCallback(window, mouseScrollCallback);


    //glad: cargar todos los punteros de funciones de opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    
    Shader cubeShader(VERTEX_SHADER_PATH, DEPTH_BUFFER_TEST);
    Shader planeShader(VERTEX_SHADER_PATH, DEPTH_BUFFER_TEST);
    Shader marioShader(VERTEX_SHADER_PATH, DEPTH_BUFFER_TEST);

    Shader lightShader(VERTEX_LIGHTSHADER_PATH, DEPTH_BUFFER_TEST);


    //VERTEX DATA
    float planeVertices[] = {
        //Position             //Normals             //Texture Coordinate
         1.0f,  0.0f,  1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // top right
         1.0f,  0.0f, -1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -1.0f,  0.0f, -1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
        -1.0f,  0.0f,  1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left    
    };

    unsigned int planeVerticesIndex[] = {
        0, 1, 3,
        1, 2, 3
    };

    float cubeVertices[] = {
        //Vertex                  //Normals                //Texture Coordinate 
        -0.5f, -0.5f, -0.5f,      0.0f,  0.0f, -1.0f,      0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,      0.0f,  0.0f, -1.0f,      1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,      0.0f,  0.0f, -1.0f,      1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,      0.0f,  0.0f, -1.0f,      1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,      0.0f,  0.0f, -1.0f,      0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,      0.0f,  0.0f, -1.0f,      0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,      0.0f,  0.0f,  1.0f,      0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,      0.0f,  0.0f,  1.0f,      1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,      0.0f,  0.0f,  1.0f,      1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,      0.0f,  0.0f,  1.0f,      1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,      0.0f,  0.0f,  1.0f,      0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,      0.0f,  0.0f,  1.0f,      0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f,  0.0f,      1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     -1.0f,  0.0f,  0.0f,      1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f,  0.0f,      0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f,  0.0f,      0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,     -1.0f,  0.0f,  0.0f,      0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f,  0.0f,      1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,      1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,      1.0f,  0.0f,  0.0f,      1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,      0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,      0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,      1.0f,  0.0f,  0.0f,      0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,      1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,      0.0f, -1.0f,  0.0f,      0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,      0.0f, -1.0f,  0.0f,      1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,      0.0f, -1.0f,  0.0f,      1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,      0.0f, -1.0f,  0.0f,      1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,      0.0f, -1.0f,  0.0f,      0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,      0.0f, -1.0f,  0.0f,      0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,      0.0f,  1.0f,  0.0f,      0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,      0.0f,  1.0f,  0.0f,      1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,      0.0f,  1.0f,  0.0f,      1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,      0.0f,  1.0f,  0.0f,      1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,      0.0f,  1.0f,  0.0f,      0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,      0.0f,  1.0f,  0.0f,      0.0f, 1.0f
    };

    float octahedronVertices[] = {
        //Vertex                //Normals                //Texture Coordinate
        -0.5f,  0.0f,  0.5f,
         0.0f,  0.7f,  0.0f,
         0.5f,  0.0f,  0.5f,

         0.0f, -0.7f,  0.0f,
        -0.5f,  0.0f,  0.5f,
         0.5f,  0.0f,  0.5f,
        
         0.5f,  0.0f,  0.5f,
         0.0f,  0.7f,  0.0f,
         0.5f,  0.0f, -0.5f,
        
         0.0f, -0.7f,  0.0f,
         0.5f,  0.0f,  0.5f,
         0.5f,  0.0f, -0.5f,

         0.5f,  0.0f, -0.5f,
         0.0f,  0.7f,  0.0f,
        -0.5f,  0.0f, -0.5f,

         0.0f, -0.7f,  0.0f,
         0.5f,  0.0f, -0.5f,
        -0.5f,  0.0f, -0.5f,

        -0.5f,  0.0f, -0.5f,
         0.0f,  0.7f,  0.0f,
        -0.5f,  0.0f,  0.5f,

         0.0f, -0.7f,  0.0f,
        -0.5f,  0.0f, -0.5f,
        -0.5f,  0.0f,  0.5f,
    };

    glm::vec3 planePosition = glm::vec3(0.0f, -0.5f, 0.0f);

    glm::vec3 cubesPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f,  0.0f),
        glm::vec3( 2.0f, 0.0f,  5.0f),
        glm::vec3(-1.5f, 0.0f, -2.5f),
        glm::vec3( 3.8f, 0.0f, -2.3f),
        glm::vec3( 2.4f, 0.0f, -3.5f),
        glm::vec3(-1.7f, 0.0f,  5.5f),
        glm::vec3( 1.3f, 0.0f, -2.5f)
    };

    glm::vec3 lightPosition = glm::vec3(1.0f, 1.0f, -1.0f);

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  1.2f,  2.0f),
        glm::vec3( 2.3f,  3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  4.0f, -3.0f)
    };

    //Plane
    unsigned int planeVBO, planeVAO, planeEBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glGenBuffers(1, &planeEBO);

    glBindVertexArray(planeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeVerticesIndex), planeVerticesIndex, GL_STATIC_DRAW);

    //Position Vertex Atribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Texture coordinate
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    //Cube
    unsigned int cubeVBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //Position vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Texture Coordinate
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    //Light VAO
    unsigned int lightVAO, lightVBO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(octahedronVertices), octahedronVertices, GL_STATIC_DRAW);

    //Position vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //TEXTURES
    ImageTexture cubeDiffuseMap(TEXTURE_WOODBOX);
    ImageTexture cubeSpecularMap(TEXTURE_WOODBOX_SPEC);

    ImageTexture planeDiffuseMap(TEXTURE_GRASS);
    ImageTexture planeSpecularMap(TEXTURE_GRASS_SPEC);

    ImageTexture flashlight(TEXTURE_FLASHLIGHT);
    

    //Lights
    DirectionalLight sunLight;
    PointLight focoLight;
    SpotLight flashLight;
    
    //MODEL LOAD
    Model marioModel((char *)"D://Dev/C++/OpenGL/LearnOpengl/LearnOpengl/src/mesh/Models/Primitives/Mario.obj");

    //Habilita el Z-Buffer: buffer de profundidad
    glEnable(GL_DEPTH_TEST);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  

    //RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        //time delta time

        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        /*Tranformation
        glm::mat4 transform = glm::mat4(1.0f);
        //glm::rotate(transform, glm::radians(45deg), glm::vec3(0.0, 0.0, ))
        transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
        transform = glm::translate(transform, glm::vec3(sin((float)glfwGetTime()), cos((float)glfwGetTime()), 0.0f));
        transform = glm::rotate(transform, -(float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));*/

        //BindTextures
        
        cubeDiffuseMap.bind();
        cubeSpecularMap.bind(1);

        planeDiffuseMap.bind(2);
        planeSpecularMap.bind(3);
        
        flashlight.bind(4);
        
        //Camera

        //PROJECTION MATRIX 4X4: La proyeccion no se suele cambiar frecuentemente por eso es mas eficiente ponerlo fuera del mainloop
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(mainCamera.Zoom), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

        //VIEW MATRIX 4X4
        glm::mat4 view = glm::mat4(1.0f);
        view = mainCamera.getViewMatrix();
        
        glm::mat4 model = glm::mat4(1.0f);

        //MODEL MATRIX 4X4
        // Hacer que la luz gire
        //lightPosition = glm::vec3(sin(glfwGetTime() * 0.5) * 2.0f, sin(glfwGetTime() * 2.0f) + 1.02f, cos(glfwGetTime() * 0.5f) * 2.0f);

        sunLight.setDiffuse(glm::vec3(0.7f));
        sunLight.setDirection(-0.2f, -1.0f, -0.3f);
        sunLight.setSpecular(glm::vec3(0.5f));
        
        flashLight.setPosition(glm::vec3(1.0f));

        //Cube    
        //se activa el programa
        cubeShader.use();
        cubeShader.setUniform("textureValue", glm::vec2(1.0f));

        //Directional light
        sunLight.draw(cubeShader);

        //Point Light
        focoLight.draw(cubeShader);

        //SpotLight
        flashLight.draw(cubeShader);

        //Material
        cubeShader.setUniform("material.diffuse", cubeDiffuseMap.getBindSlot());
        cubeShader.setUniform("material.specular", cubeSpecularMap.getBindSlot());
        cubeShader.setUniform("material.shininess", 32.0f);


        cubeShader.setUniform("viewPosition", mainCamera.Position);

        cubeShader.setUniform("time", (float)glfwGetTime());
        cubeShader.setUniform("projection", projection);
        cubeShader.setUniform("view", view);

        
        for (glm::vec3 cubePosition : cubePositions)
        {
            model = glm::mat4(1.0f);

            model = glm::translate(model, cubePosition);
            
            model = glm::rotate(model, cubePosition.x + cubePosition.y, glm::vec3(0.0f, 1.0f, 0.0f));
            cubeShader.setUniform("model", model);
        
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        
        

        //Plane
        planeShader.use();
        planeShader.setUniform("textureValue", glm::vec2((float)planeDiffuseMap.getHeight() / (float)planeDiffuseMap.getWidth() * 1.0f, 1.0f));

        //Directional light
        sunLight.draw(planeShader);

        //Point Light
        focoLight.draw(planeShader);

        //SpotLight
        flashLight.draw(planeShader);

        
        

        planeShader.setUniform("material.diffuse", planeDiffuseMap.getBindSlot());
        planeShader.setUniform("material.specular", planeSpecularMap.getBindSlot());
        planeShader.setUniform("material.shininess", 32.0f);

        model = glm::mat4(1.0f);
        model = glm::translate(model, planePosition);
        model = glm::scale(model, glm::vec3(6.0f));
        planeShader.setUniform("model", model);

        planeShader.setUniform("viewPosition", mainCamera.Position);

        planeShader.setUniform("time", (float)glfwGetTime());
        planeShader.setUniform("projection", projection);
        planeShader.setUniform("view", view);



        glBindVertexArray(planeVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        
        marioShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 1.5f));
        model = glm::scale(model, glm::vec3(0.3f));
        marioShader.setUniform("textureValue", glm::vec2(1.0f));
        marioShader.setUniform("model", model);

        marioShader.setUniform("time", (float)glfwGetTime());
        marioShader.setUniform("projection", projection);
        marioShader.setUniform("view", view);

        //Directional light
        sunLight.draw(marioShader);

        //Point Light
        focoLight.draw(marioShader);

        //SpotLight
        flashLight.draw(marioShader);

        marioShader.setUniform("material.specular", 1);
        marioShader.setUniform("material.shininess", 128.0f);

        marioModel.draw(marioShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &lightVBO);
    
    glfwTerminate();
    return 0;
}

//Esta funcion sirve para que el viewport de opengl se ajuste al tamano de la ventana cuando este sea modificado por el usuario
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void mouseCallBack(GLFWwindow* window, double xpos, double ypos)
{

    if (firstMouseMove)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouseMove = false;    
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;

    lastX = (float)xpos;    
    lastY = (float)ypos;
    
    mainCamera.processMouseMovement(xoffset, yoffset);
}

void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    mainCamera.processMouseScroll(yoffset);
}

//Esta es el desarrollo de la funcion de entrada de teclado .frgs .vtxs
void processInput(GLFWwindow *window)
{
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        std::cout << "Camera Position: " << mainCamera.Position.x << ", " << mainCamera.Position.y << ", " << mainCamera.Position.z << std::endl;

    //Camera movement

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mainCamera.processKeyInput(CameraMovement::FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mainCamera.processKeyInput(CameraMovement::BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mainCamera.processKeyInput(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mainCamera.processKeyInput(CameraMovement::RIGHT, deltaTime);
}

