#include "Renderer.h"
#include "Matrix4.h"
#include "GameWindow.h"
#include "Transform.h"
#include "Node.h"
#include "Mesh.h"

#include<vector>

Renderer::Renderer(GameWindow &game_window) : game_window(game_window)
{
    if (!initializeLibraries()) 
    {
        return;
    }

    GLFWwindow* window = game_window.createWindow();
    if (!window) 
    {
        shutdownLibraries();
        return;
    }

    if (!game_window.setupGraphicsContext())
    {
        game_window.shutdownWindow();
        shutdownLibraries();
        return;
    }

    if (!loadGraphicsAPIFunctions()) 
    {
        game_window.shutdownWindow();
        shutdownLibraries();
        return;
    }

    this->game_window = game_window;

    setupCallbacks();

    initShader();

    glEnable(GL_DEPTH_TEST);

    modelMatrixLoc = glGetUniformLocation(shader->ID, "ModelMatrix");
    viewMatrixLoc = glGetUniformLocation(shader->ID, "ViewMatrix");
    projectionMatrixLoc = glGetUniformLocation(shader->ID, "ProjectionMatrix");

    Mesh* mesh = new Mesh(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), 0.1f);
    objectMesh = new ObjectMesh(mesh);

    Mesh* mesh2 = new Mesh(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), 0.5f);
    objectMesh2 = new ObjectMesh(mesh2);

    shader->Activate();
}


void Renderer::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::swapBuffers()
{
    if (game_window.getWindow() != nullptr)
    {
        glfwSwapBuffers(game_window.getWindow());
    }
}

bool Renderer::initializeLibraries() 
{
    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    return true;
}

bool Renderer::loadGraphicsAPIFunctions() 
{
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    return true;
}

void Renderer::setupCallbacks() 
{
    game_window.setResizeCallback([this](GLFWwindow* window, int width, int height)
    {
        this->frameBufferSizeCallback(window, width, height);
    });
}

void Renderer::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    //Additional Rendering Can Be Made Here
}

void Renderer::shutdownLibraries()
{
    glfwTerminate();
}

void Renderer::initShader()
{
    shader = new Shader("default.vert", "default.frag");
}

void Renderer::draw()
{
    angle += 0.05f * 0.05f;

    Transform transform = objectMesh->getTransform();
    transform.setPosition(Vector3(0.0f, 2.0f, 0.0f));
    transform.setRotation(Vector3(0.0f, angle, 0.0f));
    transform.setScale(Vector3(2.0f, 2.0f, 2.0f));

    Transform transform2 = objectMesh2->getTransform();
    transform2.setPosition(Vector3(3.0f, 1.0f, -2.0f));  // Different position from object1
    transform2.setRotation(Vector3(0.0f, -angle, 0.0f));  // Different rotation
    transform2.setScale(Vector3(1.0f, 1.0f, 1.0f));      // Different scale

    Matrix4<float> modelMatrix = transform.getModelMatrix();
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix.getData());
    objectMesh->draw();

    Matrix4<float> modelMatrix2 = transform2.getModelMatrix();
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix2.getData());
    objectMesh2->draw();
}

void Renderer::setColor(Vector3 color, float alpha)
{
    this->color = color;
    this->alpha = alpha;
}

void Renderer::updateCamera()
{
    Matrix4<float> viewMatrix = camera.getViewMatrix();

    float aspectRatio = (game_window.getHeight() != 0) ?
        static_cast<float>(game_window.getWidth()) / static_cast<float>(game_window.getHeight()) : 1.0f;

    Matrix4<float> projectionMatrix = camera.getProjectionMatrix(45.0f * 3.14159f / 180.0f, aspectRatio, 1.0f, 100.0f);

    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrix.getData());

    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, projectionMatrix.getData());
}

Renderer::~Renderer()
{
    delete objectMesh;
    delete shader;
}