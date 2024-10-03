#include "Renderer.h"
#include "Matrix4.h"
#include "GameWindow.h"

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
    GLfloat vertices[] =
    {
        // Vertex                     //Color
        point1.x, point1.y, point1.z, color.x, color.y, color.z, alpha,
        point2.x, point2.y, point2.z, color.x, color.y, color.z, alpha,
        point3.x, point3.y, point3.z, color.x, color.y, color.z, alpha
    };

    GLuint indices[] =
    {
        0,1,2
    };

    VAO1 = new VAO();
    VAO1->Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1->LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(float), (void*)0);
    VAO1->LinkAttrib(VBO1, 1, 4, GL_FLOAT, 7 * sizeof(float), (void*)(3 * sizeof(float)));

    shader->Activate();
    VAO1->Bind(); 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    VAO1->Delete();
    VBO1.Delete();
    EBO1.Delete();
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

    Matrix4<float> modelMatrix = Matrix4<float>::translation(0.0f,2.0f,0.0f) * Matrix4<float>::rotationY(angle) * Matrix4<float>::scale(2.0f,2.0f,2.0f);

    // We only use this for perspective projection
    Vector3 cameraPos(0.0f, 0.0f, -5.0f);
    Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
    Vector3 upVector(0.0f, 1.0f, 0.0f);
    
    Matrix4<float> viewMatrix = Matrix4<float>::lookAt(cameraPos, cameraTarget, upVector);

    float aspectRatio = (game_window.getHeight() != 0) ?
        static_cast<float>(game_window.getWidth()) / static_cast<float>(game_window.getHeight()) : 1.0f;

    Matrix4<float> projectionMatrix = Matrix4<float>::perspective(45.0f * 3.14159f / 180.0f, aspectRatio, 1.0f, 100.0f);

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