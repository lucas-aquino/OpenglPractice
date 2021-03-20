#include "Camera.h"

//Constructor de la camara con vectores
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
    Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM),
    Position(position),
    WorldUp(up),
    Yaw(yaw),
    Pitch(pitch)
{
    
    updateCameraVectors();
}

//constructor de la camara con valores escalares
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
    Front(glm::vec3(0.0f, 0.0f,-1.0f)),
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM),
    Position(glm::vec3(posX, posY, posZ)),
    WorldUp(glm::vec3(posX, posY, posZ)),
    Yaw(yaw),
    Pitch(pitch)
{

    updateCameraVectors();
}

//Retorna la matriz de vista calculada por los angulos euler y la matriz de LookAt
glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

//Se procesa el input del teclado
void Camera::processKeyInput(CameraMovement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if(direction == CameraMovement::FORWARD)
        Position += Front * velocity;
    if(direction == CameraMovement::BACKWARD)
        Position -= Front * velocity;
    if(direction == CameraMovement::LEFT)
        Position -= Right * velocity;
    if(direction == CameraMovement::RIGHT)
        Position += Right * velocity;
}

//Se porcesa el movimiento del mouse 
void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    
    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if(Pitch > 89.0f)
            Pitch = 89.0f;
        if(Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}

//Se procesa el scroll del mouse
void Camera::processMouseScroll(double yoffset)
{
    Zoom -= (float)yoffset;
    if(Zoom < 1.0f)
        Zoom = 1.0f;
    if(Zoom > 45.0f)
        Zoom = 45.0f;
}

//Se usa para calcular el vector frontal de los angulos euler actualizados de la camara
void Camera::updateCameraVectors()
{
    //Se calcula el vector frontal
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(front);
    
    //  Y se optiene los vectores de derecha y arriba a partir del producto cruz de los vectores front y worldUp para el vector derecha 
    //  y Right y Front para el vector de arriba
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));

}