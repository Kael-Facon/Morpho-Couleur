#pragma once

#include "env.hh"

class App {
public:
    Env env;

    App();
    explicit App(const char* filename);

    void Windows();
    void ColorOptions();
    void PrintObjInfo() const;
    void Inputs(const ImGuiIO& io, ImVec2 pos);
};