#pragma once

class PresetArchetype : public IArchetype
{
protected:
	std::vector<std::unique_ptr<IComponent>> _components;

public:
	virtual ~PresetArchetype() = 0;
	std::vector<IComponent*> components() final;
};