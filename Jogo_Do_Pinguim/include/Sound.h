#ifndef SOUND
#define SOUND
#include "SDL_mixer.h"
#include "GameObject.h"
#include <iostream>
#include <string>

class Sound : public Component {
private:
	Mix_Chunk* chunk;
	int channel;
public:
	Sound(GameObject& associated);
	Sound(GameObject& associated, std::string file);
	~Sound();
	void Play(int times = 1);
	void Stop();
	void Open(std::string file);
	bool IsOpen() { return !!chunk; };
	virtual void Update(float dt);
	virtual void Render();
	virtual bool Is(std::string type);
};

#endif // SOUND

