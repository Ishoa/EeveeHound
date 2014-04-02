//sound frame that uses fmod
//by Tyler van Gastel

#pragma once
#include <fmod.hpp>
#pragma comment(lib,"Fmodex_vc.lib")
//#pragma comment(lib,"fmodex.dll")
#include "Defines.h"
#define maxStreams 20
#define maxSounds 50

class SoundFrame
{
private:
	FMOD::System* f_sys;
	FMOD_RESULT f_res;
	unsigned int f_ver;
	int numdrivers;
	FMOD_SPEAKERMODE speakermode;
	FMOD_CAPS f_caps;
	Sound sounds[maxSounds];
	Sound streams[maxStreams];
	char name[256];

public:
	SoundFrame();
	void Init();
	void Restart();
	void Play(Sound);
	void Play(int);
	void ShutDown();
	void update();
	void load(const char*,Sound*);
	void loadStream(const char* name, Sound *stream);
	bool load(const char*,int);
	bool loadStream(const char* name,int);
	void PlayStream(Sound,bool mute);
	void PlayStream(int,bool mute);
	~SoundFrame();
};