#include "state.h"

void initializeGrid(struct State *state)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            state->grid[i][j] = 0.0f; // Initialize all offsets to 0
        }
    }
}

void generateMesh(float *vertices, struct State *state)
{
    int vertex = 0;
    for (int i = 0; i < GRID_SIZE - 1; i++)
    {
        for (int j = 0; j < GRID_SIZE - 1; j++)
        {
            // First triangle
            vertices[vertex++] = (float)i / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = (float)j / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = state->grid[i][j];

            vertices[vertex++] = (float)(i + 1) / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = (float)j / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = state->grid[i + 1][j];

            vertices[vertex++] = (float)i / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = (float)(j + 1) / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = state->grid[i][j + 1];

            // Second triangle
            vertices[vertex++] = (float)(i + 1) / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = (float)j / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = state->grid[i + 1][j];

            vertices[vertex++] = (float)(i + 1) / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = (float)(j + 1) / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = state->grid[i + 1][j + 1];

            vertices[vertex++] = (float)i / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = (float)(j + 1) / (GRID_SIZE - 1) * 2 - 1;
            vertices[vertex++] = state->grid[i][j + 1];
        }
    }
}