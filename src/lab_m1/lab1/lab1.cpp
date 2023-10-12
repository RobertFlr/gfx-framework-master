#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;

float angle = 0;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!
    r = 0;
    b = 0;
    g = 0;

    obj = "box";

    move_x = 0;
    move_y = 0;
    move_z = 0;

    rotation.x = 1;
    rotation.y = 0;
    rotation.z = 0;
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.
    {
        Mesh* othermesh = new Mesh("pot");
        othermesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[othermesh->GetMeshID()] = othermesh;
    }

    {
        Mesh* otherothermesh = new Mesh("bol");
        otherothermesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[otherothermesh->GetMeshID()] = otherothermesh;
    }
}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(r, g, b, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    //RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

    // Render the object again but with different properties
    
    // Sliding object
    //RenderMesh(meshes["box"], glm::vec3(move_x, move_y, move_z), glm::vec3(0.5f));
    // Changing object
    RenderMesh(meshes[obj], rotation, glm::vec3(0.5f));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.

    //RenderMesh(meshes["box"], glm::vec3(rotation.x, rotation.y, rotation.z), glm::vec3(1));
    

}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.
    if (window->KeyHold(GLFW_KEY_W)) {
        move_z += -0.5 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        move_z += 0.5 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        move_x += -0.5 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        move_x += 0.5 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_E)) {
        move_y += -0.5 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_Q)) {
        move_y += 0.5 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_K)) {
        angle = 3 * deltaTime;
        glm::mat3 rm = glm::mat3
        (cos(angle), 0, sin(angle),
            0, 1, 0,
        -sin(angle), 1, cos(angle));
        rotation = glm::transpose(rm) * rotation;
    }

}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {
        if (r + g + b) {
            r = 0;
            g = 0;
            b = 0;
        } else {
            r = 0.7;
            g = 0.1;
            b = 1.0;
        }
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.

    if (key == GLFW_KEY_G) {
        //obj = (obj == "box") ? "pot" : "box";
        if (obj == "box") { obj = "pot"; return; }
        if (obj == "pot") { obj = "bol"; return; }
        if (obj == "bol") { obj = "box"; return; }
    }
}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
