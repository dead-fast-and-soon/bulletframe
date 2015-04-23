
class Event { public: virtual ~Event() {} };

class EventBus
{
private:
	EventBus() {}

public:
	static EventBus EVENT_BUS;
	void Post(Event* e);

	typedef void(*EventHandler)(Event*);

	void Register(EventHandler handler);
};