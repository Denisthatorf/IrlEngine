#include "opengl_backend.hpp"
#include "opengl_platform.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool opengl_renderer_backend_initialize(renderer_backend* backend, const char* application_name, struct window* window)
{
    window_set_opengl_context(window);

    glewExperimental = GL_FALSE;
    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
        return false;

    GLenum glewinit = glewInit();
    if (glewinit != GLEW_OK) 
        return false;

    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    return true;
}

void opengl_renderer_backend_shutdown(renderer_backend* backend)
{

}

void opengl_renderer_backend_on_resized(renderer_backend* backend, uint16_t width, uint16_t height)
{

}

bool opengl_renderer_backend_begin_frame(renderer_backend* backend, float delta_time)
{
    return false;
}
bool opengl_renderer_backend_end_frame(renderer_backend* backend, float delta_time)
{
    return false;
}