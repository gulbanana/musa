#pragma once
#include <core/framework.h>
#include <core/input.h>

class KBMControlSystem : public Identified<KBMControlSystem, ISystem, EntityManagingSystemBase>
{
private:
   	KeyboardController _keyboard;

public:
    std::string description() const final;
	std::vector<ISystem::ID> required_systems() const override;
    std::vector<IComponent::ID> required_components() const override;

    KBMControlSystem();
    ~KBMControlSystem();

    bool on_event(SDL_Event& event) override;
    void on_frame_entity(std::shared_ptr<IEntity> e) override;
};

