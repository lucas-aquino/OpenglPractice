#include <iostream>
#include <time.h>
#include <glad/glad.h>
#include <glfw3.h>
#include <string.h>

//GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//Image loader
#define STB_IMAGE_IMPLEMENTATION

#include "shaders/Shader.h"
#include "camera/Camera.h"
#include "textures/Texture.h"



//Esta funcion sirve para que el viewport de opengl se ajuste al tamano de la ventana cuando este sea modificado por el usuario
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

//Esta funcion sirve para recibir lad entradas de teclado
void processInput(GLFWwindow* window);

//mouse callback
void mouseCallBack(GLFWwindow* window, double xpos, double ypos);

//Scroll callback
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);


const float WINDOW_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 600.0f;

#define VERTEX_SHADER_PATH          "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\VertexShaders\\shader.vert"
#define FRAGMENT_SHADER_PATH        "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\FragmentShaders\\shader.frag"

#define VERTEX_LIGHTSHADER_PATH     "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\VertexShaders\\lightCube.vert"
#define FRAGMENT_LIGHTSHADER_PATH   "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\FragmentShaders\\lightShader.frag"

const std::string TEXTURE_BLINK_PATH   = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\TestTexture\\BlinkGuy.png"; 
const std::string TEXTURE_BLINK_2_PATH = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\TestTexture\\BlinkGuy-2.png";
const std::string TEXTURE_COBBLE_PATH  = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\CobblestoneTextures\\cobblestone-diff.jpg";
const std::string TEXTURE_WOODBOX      = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\WoodBox\\container2.png";
const std::string TEXTURE_WOODBOX_SPEC = "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\WoodBox\\container2_specular.png";


//CAMERA
Camera mainCamera(glm::vec3(-1.19576f, 1.06076f, 1.1886f));

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
    
    
    Shader basicShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    Shader lightingShader(VERTEX_LIGHTSHADER_PATH, FRAGMENT_LIGHTSHADER_PATH);

    //VERTEX DATA
    /*
    float vertices[] = {
    //Position              //Color             //Texture Coordinate
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };*/



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
         0.0f,  0.8f,  0.0f,
         0.5f,  0.0f,  0.5f,

         0.0f, -0.8f,  0.0f,
        -0.5f,  0.0f,  0.5f,
         0.5f,  0.0f,  0.5f,
        
         0.5f,  0.0f,  0.5f,
         0.0f,  0.8f,  0.0f,
         0.5f,  0.0f, -0.5f,
        
         0.0f, -0.8f,  0.0f,
         0.5f,  0.0f,  0.5f,
         0.5f,  0.0f, -0.5f,

         0.5f,  0.0f, -0.5f,
         0.0f,  0.8f,  0.0f,
        -0.5f,  0.0f, -0.5f,

         0.0f, -0.8f,  0.0f,
         0.5f,  0.0f, -0.5f,
        -0.5f,  0.0f, -0.5f,

        -0.5f,  0.0f, -0.5f,
         0.0f,  0.8f,  0.0f,
        -0.5f,  0.0f,  0.5f,

         0.0f, -0.8f,  0.0f,
        -0.5f,  0.0f, -0.5f,
        -0.5f,  0.0f,  0.5f,
    };

    glm::vec3 cubesPosition =  glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 lightPosition = glm::vec3(1.0f, 1.0f, -1.0f);

    unsigned int VBO, VAO/*, EBO*/;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //Position vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //Color vertex attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

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
    Texture diffuseMap(TEXTURE_WOODBOX);
    Texture specularMap(TEXTURE_WOODBOX_SPEC);

    /*
    //Diffuse Texture
    unsigned int diffuseTexture;
    int diffuseWidthTexture, diffuseHeightTexture, diffuseNrChannelsTexture;

    glGenTextures(1, &diffuseTexture);

    glBindTexture(GL_TEXTURE_2D, diffuseTexture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data = stbi_load(TEXTURE_WOODBOX, &diffuseWidthTexture, &diffuseHeightTexture, &diffuseNrChannelsTexture, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, diffuseWidthTexture, diffuseHeightTexture, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Textura diffuse cargadas correctamente" << std::endl;
    }
    else
        std::cout << "No se a podido cargar la textura diffuse" << std::endl;
    std::cout << "TextureID: " << diffuseTexture << std::endl;

    stbi_image_free(data);
    */

    //De esta manera agregamos la transformacion al vertex shader
    unsigned int transformLocation = glGetUniformLocation(basicShader.ID, "transform");
    

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

        glClearColor(0.04f, 0.05f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        /*Tranformation
        glm::mat4 transform = glm::mat4(1.0f);
        //glm::rotate(transform, glm::radians(45deg), glm::vec3(0.0, 0.0, ))
        transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
        transform = glm::translate(transform, glm::vec3(sin((float)glfwGetTime()), cos((float)glfwGetTime()), 0.0f));
        transform = glm::rotate(transform, -(float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));*/
        
        //Camera

        //PROJECTION MATRIX 4X4: La proyeccion no se suele cambiar frecuentemente por eso es mas eficiente ponerlo fuera del mainloop
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(mainCamera.Zoom), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

        //VIEW MATRIX 4X4
        glm::mat4 view = glm::mat4(1.0f);
        view = mainCamera.getViewMatrix();
        

        //MODEL MATRIX 4X4
        // Hacer que la luz gire
        lightPosition = glm::vec3(sin(glfwGetTime() * 0.5) * 2.0f, sin(glfwGetTime() * 2.0f), cos(glfwGetTime() * 0.5f) * 2.0f);
        //Cube    
        //se activa el programa
        basicShader.use();

        basicShader.setUniformVec3("light.position", lightPosition);
        basicShader.setUniformVec3("light.ambient", glm::vec3(0.1f));
        basicShader.setUniformVec3("light.diffuse", glm::vec3(1.0f));
        basicShader.setUniformVec3("light.specular", glm::vec3(1.0f));


        diffuseMap.bindTexture(GL_TEXTURE0,GL_TEXTURE_2D);
        specularMap.bindTexture(GL_TEXTURE1, GL_TEXTURE_2D);

        basicShader.setUniformInt("material.diffuse", 0);
        basicShader.setUniformInt("material.specular", 1);
        basicShader.setUniformFloat("material.shininess", 128.0f);


        basicShader.setUniformVec3("viewPosition", mainCamera.Position);

        basicShader.setUniformFloat("time", (float)glfwGetTime());
        basicShader.setUniformMat4("projection", projection);
        basicShader.setUniformMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        
        model = glm::translate(model, cubesPosition);
        
        basicShader.setUniformMat4("model", model);
        

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        
        //Light cube
        lightingShader.use();
        lightingShader.setUniformVec3("color", glm::vec3(1.0f));
        lightingShader.setUniformMat4("projection", projection);
        lightingShader.setUniformMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3(0.1f));
        lightingShader.setUniformMat4("model", model);


        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 24);
        
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
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

