#pragma once

class ThreadedSystemBase : public ISystem
{
private:
	virtual void on_wake() = 0;

public:
	ThreadedSystemBase();
	virtual ~ThreadedSystemBase();

	void on_frame() final;
	virtual void on_message();
	virtual bool on_event(SDL_Event& event) override;
	void add_entity(std::weak_ptr<IEntity> new_entity);
};

