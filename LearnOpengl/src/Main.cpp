#include <iostream>
#include <time.h>
#include <glad/glad.h>
#include <glfw3.h>

//GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//Image loader
#define  STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> 

#include "shaders/Shader.h";


//Esta funcion sirve para que el viewport de opengl se ajuste al tamano de la ventana cuando este sea modificado por el usuario
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

//Esta funcion sirve para recivir lad entradas de teclado
void processInput(GLFWwindow* window);

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 600.0f

#define VERTEX_SHADER_PATH      "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\VertexShaders\\shader.vert"
#define FRAGMENT_SHADER_PATH    "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\shaders\\FragmentShaders\\shader.frag"

#define TEXTURE_BLINK_PATH      "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\TestTexture\\BlinkGuy.png" 
#define TEXTURE_BLINK_2_PATH      "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\TestTexture\\BlinkGuy-2.png"
#define TEXTURE_COBBLE_PATH     "D:\\Dev\\C++\\OpenGL\\LearnOpengl\\LearnOpengl\\src\\textures\\CobblestoneTextures\\cobblestone-diff.jpg"


int main()
{
    
    srand(time(NULL));

    //Inicializar glfw y configurar
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //Se crea una ventana
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My FirstApp In OpenGL :D", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "No se ha podido crear la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    //glad: cargar todos los punteros de funciones de opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    
    Shader basicShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

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
    
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    glm::vec3 randomCubesPositions[10];

    for (unsigned i = 0; i < 10; i++)
    {   
        randomCubesPositions[i] = glm::vec3(
            (float)(rand() % 10 - 5), //X
            (float)(rand() % 10 - 5), //Y
            (float)(rand() % 10 - 5)  //Z
        );
        std::cout << "Cube " << i << " pos(" << randomCubesPositions[i].x << ", " << randomCubesPositions[i].y << ", " << randomCubesPositions[i].z << ")" << std::endl;
    }

    unsigned int VBO, VAO/*, EBO*/;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //Position vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //Color vertex attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    
    //Texture Coordinate
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    //TEXTURES
    //Generamos una textura
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    
    //Agregamos la texture
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int widthTexture, heightTexture, nrChannels;
    //Cargamos una textura con el loader de stb_image.h
    stbi_set_flip_vertically_on_load(false);

    unsigned char* data = stbi_load(TEXTURE_BLINK_2_PATH, &widthTexture, &heightTexture, &nrChannels, 0);
    
    if (data)
    {
        //cargamos la textura
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthTexture, heightTexture, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Textura 1 cargadas correctamente" << std::endl;
    }
    else
        std::cout << "No se a podido cargar la textura 1" << std::endl;
    
    //Se libera la memoria de la imagen cargada
    stbi_image_free(data);

    
    //Textura 2
    glGenTextures(1, &texture2);

    //Agregamos la texture
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    data = stbi_load(TEXTURE_BLINK_PATH, &widthTexture, &heightTexture, &nrChannels, 0);

    if (data)
    {
        //cargamos la textura
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthTexture, heightTexture, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Textura 2 cargadas correctamente" << std::endl;
    }
    else
        std::cout << "No se a podido cargar la textura 2" << std::endl;
    
    //Se libera la memoria de la imagen cargada
    stbi_image_free(data);
   
    basicShader.use();
    glUniform1i(glGetUniformLocation(basicShader.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(basicShader.ID, "texture2"), 1);


    
    //De esta manera agregamos la transformacion al vertex shader
    unsigned int transformLocation = glGetUniformLocation(basicShader.ID, "transform");
    
    
    //PROJECTION MATRIX 4X4: La proyeccion no se suele cambiar frecuentemente por eso es mas eficiente ponerlo fuera del mainloop
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

    basicShader.setUniformMat4("projection", projection);


    //Habilita el Z-Buffer: buffer de profundidad
    glEnable(GL_DEPTH_TEST);


    //RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.14f, 0.15f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //se activa el programa
        basicShader.use();

        glBindVertexArray(VAO);
        
        basicShader.setUniformFloat("time", (float)glfwGetTime());
        
        /*Tranformation
        glm::mat4 transform = glm::mat4(1.0f);
        //glm::rotate(transform, glm::radians(45deg), glm::vec3(0.0, 0.0, ))
        transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
        transform = glm::translate(transform, glm::vec3(sin((float)glfwGetTime()), cos((float)glfwGetTime()), 0.0f));
        transform = glm::rotate(transform, -(float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));*/
        
        //VIEW MATRIX 4X4
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -20.0f));
        
        int viewUniformLocation = glGetUniformLocation(basicShader.ID, "view");
        glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));
        
        

        //MODEL MATRIX 4X4
        glBindVertexArray(VAO);
        for (glm::vec3 cubePosition : randomCubesPositions)
        {
            glm::mat4 model = glm::mat4(1.0f);
            
            model = glm::translate(model, cubePosition);
            
            float angle = cubePosition.x * cubePosition.y * cubePosition.z * (float)glfwGetTime() * 5.0f;
            
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            basicShader.setUniformMat4("model", model);
            
            //REDER QUAD AND TRIANGLE
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        
        //glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    return 0;
}

//Esta funcion sirve para que el viewport de opengl se ajuste al tamano de la ventana cuando este sea modificado por el usuario
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//Esta es el desarrollo de la funcion de entrada de teclado .frgs .vtxs
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    
}