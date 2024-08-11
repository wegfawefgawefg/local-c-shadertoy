#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shader_utils.h"
#include "state.h"
#include "input.h"

// const of the dims
const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow(
        "Full Screen Shader",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_OPENGL);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    GLuint shader_program = createShaderProgram();
    if (shader_program == 0)
    {
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set up vertex data for a full-screen quad
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f};

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Main loop
    struct State state = {.quit = false};
    while (!state.quit)
    {
        process_input(&state);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shader_program);

        // pass in dims of window
        GLint dims_location = glGetUniformLocation(shader_program, "dims");
        glUniform2f(dims_location, WIDTH, HEIGHT);

        // pass in time
        GLint time_location = glGetUniformLocation(shader_program, "time");
        glUniform1f(time_location, SDL_GetTicks() / 1000.0f);

        // pass in mouse
        int x, y;
        SDL_GetMouseState(&x, &y);
        GLint location = glGetUniformLocation(shader_program, "mouse");
        float mouse_norm_x = (float)x / (float)WIDTH;
        float mouse_norm_y = (float)y / (float)HEIGHT;
        glUniform2f(location, mouse_norm_x, mouse_norm_y);

        // Draw the full-screen quad
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader_program);
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}