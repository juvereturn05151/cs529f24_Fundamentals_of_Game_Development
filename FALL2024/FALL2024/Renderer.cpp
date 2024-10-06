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

    /*camera = new Camera(viewMatrixLoc, projectionMatrixLoc);

    Mesh* mesh = new Mesh(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), 0.1f);
    objectMesh = new ObjectMesh(mesh, modelMatrixLoc);

    Mesh* mesh2 = new Mesh(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), 0.5f);
    objectMesh2 = new ObjectMesh(mesh2, modelMatrixLoc);*/

    shader->Activate();
}

GLint Renderer::GetModelMatrixLoc()
{
    return modelMatrixLoc;
}

GLint Renderer::GetViewMatrixLoc()
{
    return viewMatrixLoc;
}

GLint Renderer::GetProjectionMatrixLoc()
{
    return projectionMatrixLoc;
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

    objectMesh->getTransform()->setPosition(Vector3(0.0f, 2.0f, 0.0f));
    objectMesh->getTransform()->setRotation(Vector3(0.0f, angle, 0.0f));
    objectMesh->getTransform()->setScale(Vector3(2.0f, 2.0f, 2.0f));

    objectMesh2->getTransform()->setPosition(Vector3(3.0f, 1.0f, -2.0f));  // Different position from object1
    objectMesh2->getTransform()->setRotation(Vector3(0.0f, -angle, 0.0f));  // Different rotation
    objectMesh2->getTransform()->setScale(Vector3(1.0f, 1.0f, 1.0f));      // Different scale

    objectMesh->draw();

    objectMesh2->draw();
}

void Renderer::updateCamera()
{
    camera->updateAspectRatio(game_window.getHeight(), game_window.getWidth());
}

Renderer::~Renderer()
{
    delete objectMesh;
    delete shader;
    delete camera;
}