#pragma once

#include "Random.hpp"

class SandboxLayer : public Rand::Layer
{
  public:
    SandboxLayer(const Rand::Application& app);

    void onUpdate() override;
    void onEvent(Rand::Event& event) override;
    void onImGuiRender() override;
};

class Sandbox : public Rand::Application
{
  public:
    Sandbox();
    ~Sandbox();
};
