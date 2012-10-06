#include "ISystem.h"

ISystem::~ISystem() {}

void ISystem::on_frame() {}
bool ISystem::on_event(SDL_Event& event) { return false; }

std::vector<IComponent::ID> ISystem::required_components() const { return std::vector<IComponent::ID>(); }
void ISystem::add_entity(std::weak_ptr<IEntity> new_entity) {}

std::vector<ISystem::ID> ISystem::required_systems() const { return std::vector<ISystem::ID>(); }