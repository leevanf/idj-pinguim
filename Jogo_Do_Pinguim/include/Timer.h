#ifndef TIMER
#define TIMER
class Timer{
	private:
		float timer;
	public:
		Timer() { timer = 0; };
		void Update(float dt) { timer += dt; };
		void Restart() { timer = 0; };
		float Get() { return timer; };
};

#endif // TIMER