#pragma once
#include <core/framework.h>
#include <core/GameState.h>
#include <SDL_gamecontroller.h>

class PadControlSystem : public Identified<PadControlSystem, ISystem, EntityManagingSystemBase>
{
private:
    GameState* _state;
    float _deadzone;
    float _speed;
    SDL_GameController* _controller;

public:
    std::string description() const final;
   	std::vector<ISystem::ID> required_systems() const override;
    std::vector<IComponent::ID> required_components() const override;

    PadControlSystem(GameState* state);
    ~PadControlSystem();

    bool on_event(SDL_Event& event) override;
    void on_frame_start() override;
    void on_frame_entity(std::shared_ptr<IEntity> e) override;
};

