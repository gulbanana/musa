#pragma once
#include <core/framework.h>

class PadControlSystem : public Identified<PadControlSystem, ISystem, EntityManagingSystemBase>
{
public:
    std::string description() const final;
   	std::vector<ISystem::ID> required_systems() const override;
    std::vector<IComponent::ID> required_components() const override;

    PadControlSystem(void);
    ~PadControlSystem(void);

    bool on_event(SDL_Event& event) override;
};

