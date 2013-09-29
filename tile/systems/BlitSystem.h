#pragma once
#include <core/framework.h>

class BlitSystem : public Identified<ISystem,SYS::Render,ThreadedSystemBase>
{
private:
	std::vector<ISystem::ID> required_systems() const override;
	void on_wake() override;

public:
	BlitSystem(void);
	~BlitSystem(void);
};

