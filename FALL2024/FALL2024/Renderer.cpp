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
}


void Renderer::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
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
        point1.x, point1.y, point1.z,
        point2.x, point2.y, point2.z,
        point3.x, point3.y, point3.z
    };

    GLint indices[] =
    {
        0,1,2
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Introduce the vertices to the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enable the Vertex Attribute so that OpenGL knows how to use it
    glEnableVertexAttribArray(0);

    shader->Activate();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader->Delete();
}

Renderer::~Renderer()
{
    delete shader;
}