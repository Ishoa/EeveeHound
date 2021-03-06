//sound frame that uses fmod
//by Tyler van Gastel

#include "SoundFrame.h"

SoundFrame::SoundFrame()
{
	f_sys = 0;
	f_ver = 0;
	numdrivers = 0;
}

void SoundFrame::Init()
{
	FMOD::System_Create(&f_sys);
	f_sys->getNumDrivers(&numdrivers);
	if(numdrivers == 0)
	{
		f_sys->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
	}
	else
	{
		f_sys->getDriverCaps(0,&f_caps,0,&speakermode);
		f_sys->setSpeakerMode(speakermode);
		if(f_caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			f_sys->setDSPBufferSize(1024,10);
		}
		f_sys->getDriverInfo(0,name,256,0);
		if(name == "SigmaTel")
		{
			f_sys->setSoftwareFormat(48000,FMOD_SOUND_FORMAT_PCMFLOAT, 0,0,FMOD_DSP_RESAMPLER_LINEAR);
		}
	}
	f_res = f_sys->init(100,FMOD_INIT_NORMAL,0);
	if(f_res == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		f_sys->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		f_sys->init(100,FMOD_INIT_NORMAL,0);
	}

	for(int i = 0;i<maxSounds;++i)
	{
		sounds[i]=0;
	}
	for(int i = 0;i<maxStreams;++i)
	{
		streams[i]=0;
	}
}

void SoundFrame::Restart()
{
	ShutDown();
	FMOD::System_Create(&f_sys);
	f_sys->getNumDrivers(&numdrivers);
	if(numdrivers == 0)
	{
		f_sys->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
	}
	else
	{
		f_sys->getDriverCaps(0,&f_caps,0,&speakermode);
		f_sys->setSpeakerMode(speakermode);
		if(f_caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			f_sys->setDSPBufferSize(1024,10);
		}
		f_sys->getDriverInfo(0,name,256,0);
		if(name == "SigmaTel")
		{
			f_sys->setSoftwareFormat(48000,FMOD_SOUND_FORMAT_PCMFLOAT, 0,0,FMOD_DSP_RESAMPLER_LINEAR);
		}
	}
	f_res = f_sys->init(100,FMOD_INIT_NORMAL,0);
	if(f_res == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		f_sys->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		f_sys->init(100,FMOD_INIT_NORMAL,0);
	}
}

void SoundFrame::ShutDown()
{
	f_ver = 0;
	numdrivers = 0;
	for(int i = 0;i<maxSounds;++i)
	{
		if(sounds[i]!=0)
		{
			sounds[i]->release();
		}
	}
	for(int i = 0;i<maxStreams;++i)
	{
		if(streams[i]!=0)
		{
			streams[i]->release();
		}
	}
	if(f_sys != 0)
	{
		f_sys->release();
		f_sys = 0;
	}
}

void SoundFrame::load(const char* name, Sound *sound)
{
	f_sys->createSound(name,FMOD_DEFAULT,0,sound);
}

void SoundFrame::loadStream(const char* name, Sound *stream)
{
	f_sys->createStream(name,FMOD_LOOP_NORMAL|FMOD_2D|FMOD_HARDWARE,0,stream);
}

void SoundFrame::Play(Sound sound)
{
	f_sys->playSound(FMOD_CHANNEL_FREE,sound,false,0);
}

void SoundFrame::PlayStream(Sound sound,bool mute)
{
	f_sys->playSound(FMOD_CHANNEL_FREE,sound,mute,0);
}

bool SoundFrame::load(const char* name,int num)
{
	if(num>=0&&num<maxSounds)
	{
		load(name,&sounds[num]);
		return true;
	}
	return false;
}

bool SoundFrame::loadStream(const char* name, int num)
{
	if(num>=0&&num<maxStreams)
	{
		loadStream(name,&streams[num]);
		return true;
	}
	return false;
}

void SoundFrame::Play(int num)
{
	Play(sounds[num]);
}

void SoundFrame::PlayStream(int num,bool mute)
{
	PlayStream(streams[num],mute);
}

void SoundFrame::update()
{
	f_sys->update();
}


SoundFrame::~SoundFrame()
{
	ShutDown();
}