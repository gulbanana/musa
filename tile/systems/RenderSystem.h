#pragma once
#include <core/framework.h>

class RenderSystem : public Identified<ISystem,SYS::Render,ThreadedSystemBase>
{
private:
	void on_wake() final;

public:
	RenderSystem(void);
	~RenderSystem(void);

	std::vector<ISystem::ID> required_systems() const override;
};

