//sound frame that uses fmod
//by Tyler van Gastel

#pragma once
#include <fmod.hpp>
#pragma comment(lib,"Fmodex_vc.lib")
//#pragma comment(lib,"fmodex.dll")
#include "Defines.h"

class SoundFrame
{
private:
	FMOD::System* f_sys;
	FMOD_RESULT f_res;
	unsigned int f_ver;
	int numdrivers;
	FMOD_SPEAKERMODE speakermode;
	FMOD_CAPS f_caps;
	char name[256];
public:
	SoundFrame();
	void Init();
	void Restart();
	void Play(Sound);
	void ShutDown();
	void update();
	void load(const char*,Sound*);
	void loadStream(const char* name, Sound *stream);
	void PlayStream(Sound,bool mute);
	~SoundFrame();
};