/*
 * CAudioResources.h
 *
 *  Created on: 23.01.2011
 *      Author: gerstrong
 */

#ifndef CAUDIORESOURCES_H_
#define CAUDIORESOURCES_H_

#include "sdl/sound/CSoundSlot.h"
#include "hardware/COPLEmulator.h"
#include <string>

/** This is the PC Speaker Volume it will set.
  * When the PC Speaker Emulator generates the Sound slots
  * it will do it with that volume.
  * Remember, this is relative to the real Sound volume you can toggle in the Audio Settings
  * Menu of CG
  */
const int PC_Speaker_Volume = 20; // in percent

const Uint64 PCSpeakerTime = 1288634;
//const Uint64 PCSpeakerTime = 0x1234DD;

typedef struct
{
    Instrument      inst;
    byte            block;
} AdLibSound;

// Game Sounds
enum GameSound{
SOUND_KEEN_WALK, SOUND_KEEN_WALK2,
SOUND_KEEN_JUMP, SOUND_KEEN_POGO,
SOUND_KEEN_DIE, SOUND_KEEN_FALL,
SOUND_KEEN_BUMPHEAD,
SOUND_KEENSLEFT,
SOUND_KEEN_FIRE,
SOUND_GUN_CLICK,
SOUND_SHOT_HIT,
SOUND_GET_ITEM,
SOUND_GET_PART,
SOUND_LEVEL_DONE,
SOUND_GAME_OVER,
SOUND_TELEPORT,
SOUND_EXTRA_LIFE,
SOUND_CANNONFIRE,
SOUND_CHUNKSMASH,
SOUND_GOINDOOR,
SOUND_GET_CARD,
SOUND_USE_KEY,
SOUND_DOOR_OPEN,
SOUND_YORP_BUMP,
SOUND_YORP_STUN,
SOUND_YORP_DIE,
SOUND_GARG_DIE,
SOUND_VORT_DIE,
SOUND_KEEN_LAND,
SOUND_GET_BONUS,

SOUND_ENTER_LEVEL,
SOUND_SWITCH_TOGGLE,
SOUND_EARTHPOW,
SOUND_TANK_FIRE,
SOUND_KEEN_BLOK,

SOUND_MEEP,
SOUND_ANKH,
SOUND_MORTIMER,
SOUND_FOOTSLAM
};

class CAudioResources {
public:
	CAudioResources(const SDL_AudioSpec &AudioSpec);

	virtual bool loadSoundData() = 0;
	virtual void unloadSound() = 0;

	template <typename T>
	void generateWave(std::vector<T> &waveform, word sample, T &wave, Uint64 &freqtimer, bool IsSigned, const int& AMP)
	{
		const unsigned int wavetime = m_AudioSpec.freq/136;
		Uint64 changerate = (m_AudioSpec.freq>>1)*Uint64(sample);

		for (unsigned int j=0; j<wavetime; j++)
		{
			if(changerate == 0)
			{
				wave = m_AudioSpec.silence - AMP;
				freqtimer = 0;
			}
			else
			{
				if (freqtimer > changerate)
				{
					freqtimer = 0;

					if (wave == m_AudioSpec.silence - AMP)
						wave = m_AudioSpec.silence + AMP;
					else
						wave = m_AudioSpec.silence - AMP;
				}
				else
					freqtimer += PCSpeakerTime;
			}

			for(Uint8 chnl=0 ; chnl<m_AudioSpec.channels ; chnl++ )
				waveform.push_back(wave);
		}
	}

	bool readISFintoWaveForm( CSoundSlot &soundslot, const byte *imfdata, const unsigned int bytesize );

	CSoundSlot *getSlotPtr() { return m_soundslot; }

protected:
	static const int MAX_SOUNDS = 200;
	CSoundSlot	m_soundslot[MAX_SOUNDS];
	const SDL_AudioSpec &m_AudioSpec;
};

#endif /* CAUDIORESOURCES_H_ */
