#include "Renderer.h"
#include "Matrix4.h"
#include "GameWindow.h"
#include "Transform.h"
#include "Node.h"
#include "Mesh.h"
#include "ObjectMesh.h"
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

void Renderer::drawTriangle(Vector3 point1, Vector3 point2, Vector3 point3)
{
    Mesh *mesh = new Mesh (point1, point2, point3, color, alpha);
    ObjectMesh* objectMesh = new ObjectMesh(mesh);

    shader->Activate();
    mesh->draw();
    mesh->cleanup();
    shader->Delete();
}

void Renderer::setColor(Vector3 color, float alpha)
{
    this->color = color;
    this->alpha = alpha;
}

void Renderer::updateCamera()
{
    angle += 0.05f*0.05f;

    Node node;
    Transform transform = node.getTransform();
    transform.setPosition(Vector3(0.0f, 2.0f, 0.0f));
    transform.setRotation(Vector3(0.0f, angle, 0.0f));
    transform.setScale(Vector3(2.0f, 2.0f, 2.0f));

    Matrix4<float> modelMatrix = transform.getModelMatrix();
    
    Matrix4<float> viewMatrix = camera.getViewMatrix();

    float aspectRatio = (game_window.getHeight() != 0) ?
        static_cast<float>(game_window.getWidth()) / static_cast<float>(game_window.getHeight()) : 1.0f;

    Matrix4<float> projectionMatrix = camera.getProjectionMatrix(45.0f * 3.14159f / 180.0f, aspectRatio, 1.0f, 100.0f);

    GLint modelMatrixLoc = glGetUniformLocation(shader->ID, "ModelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix.getData());

    GLint viewMatrixLoc = glGetUniformLocation(shader->ID, "ViewMatrix");
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrix.getData());

    GLint projectionMatrixLoc = glGetUniformLocation(shader->ID, "ProjectionMatrix");
    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, projectionMatrix.getData());
}

Renderer::~Renderer()
{
    delete shader;
    delete VAO1;
}