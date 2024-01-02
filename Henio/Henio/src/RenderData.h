﻿#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
};

struct Mesh
{
    std::vector<Vertex> vertices;
};