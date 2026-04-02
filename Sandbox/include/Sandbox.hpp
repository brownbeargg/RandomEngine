#pragma once

#include "Random.hpp"

class SandboxLayer : public Rand::Layer
{
  public:
    SandboxLayer();

    void onUpdate() override;
    void onEvent(Rand::Event& event) override;
};

class Sandbox : public Rand::Application
{
  public:
    Sandbox();
    ~Sandbox();
};
