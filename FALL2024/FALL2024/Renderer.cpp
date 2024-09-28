#include "Renderer.h"

const char* vertextShaderSource =
"#version 330 core"
"layout (location = 0) in vec3 aPos;"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
"}\0";
const char* fragmentShaderSource =
"#version 330 core"
"out vec4 FragColor;"
"void main()\n"
"{\n"
"FragColor = vec4(0.8f, 0.3f, 0.4f, 1.0);"
"}\n\0";

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

Renderer::~Renderer()
{
    delete shader;
    delete VAO1;
}