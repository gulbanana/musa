#pragma once
#include <core/framework.h>

class BlitSystem : public Identified<ISystem,SYS::Render,ThreadedSystemBase>
{
private:
	void on_wake() final;

public:
	BlitSystem(void);
	~BlitSystem(void);

	std::vector<ISystem::ID> required_systems() const override;
};

