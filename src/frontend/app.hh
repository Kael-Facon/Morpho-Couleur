#pragma once

#include "env.hh"

class App {
public:
    Env env;

    App();

    void Windows();
    void ColorOptions();
    void Actions();
    void PrintObjInfo() const;
    void Inputs(const ImGuiIO& io, ImVec2 pos);
};