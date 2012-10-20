#pragma once

class ThreadedSystemBase : public ISystem
{
private:
	virtual void on_frame() final;
	virtual void on_message() override;
	virtual bool on_event(SDL_Event& event) override;
	virtual void on_wake() = 0;
	
public:
	ThreadedSystemBase();
	virtual ~ThreadedSystemBase();
	virtual std::vector<ISystem::ID> required_systems() const = 0;
	void add_entity(std::weak_ptr<IEntity> new_entity);
};

