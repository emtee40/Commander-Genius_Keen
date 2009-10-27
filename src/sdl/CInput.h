/*
 * CInput.h
 *
 *  Created on: 20.03.2009
 *      Author: gerstrong
 */

#ifndef CINPUT_H_
#define CINPUT_H_

#include <SDL/SDL.h>
#include <string>

#ifdef WIZGP2X
#include <sys/ioctl.h>
#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#endif

#include "../CSingleton.h"
#define g_pInput	CInput::Get()

// key defines, locations in keytable[]
//#define KEYTABLE_SIZE            54
//#define KEYTABLE_REALKEYS_SIZE   49

// TODO: Change this to enums
enum keys{
KQUIT,
KLEFT,
KRIGHT,
KUP,
KDOWN,
KCTRL,           // simply, CTRL, mapped to JUMP or FIRE
KALT,            // simply, ALT, mapped to POGO or fire
KENTER,
KSPACE,
KF1,
KF2,
KF3,
KF4,
KF5,
KF6,
KF7,
KF8,
KF9,
KF10,

KLEFT2,
KRIGHT2,
KUP2,
KDOWN2,
KCTRL2,
KALT2,

KLEFT3,
KRIGHT3,
KUP3,
KDOWN3,
KCTRL3,
KALT3,

KPLUS,
KMINUS,

KNUM1,
KNUM2,
KNUM3,
KNUM4,
KNUM5,
KNUM6,
KNUM7,
KNUM8,
KNUM9,

KTAB,

KBCKSPCE,

// New keys
KA,
KB,
KC,
KD,
KE,
KF,
KG,
KH,
KI,
KJ,
KK,
KL,
KM,
KN,
KO,
KP,
KQ,
KR,
KS,
KT,
KU,
KV,
KW,
KX,
KY,
KZ,
KSHIFT,
KPGUP,
KPGDN
};

#define KEYTABLE_SIZE   90

enum InputCommands{
IC_JUMP,
IC_POGO,
IC_FIRE,
IC_STATUS,
IC_LEFT,
IC_UP,
IC_RIGHT,
IC_DOWN,
IC_HELP,
IC_QUIT
};

#define NUMBER_OF_COMMANDS	10
#define NUM_INPUTS			1

#define ETYPE_NO_JOYSTICK 	0
#define ETYPE_JOYAXIS 		1
#define ETYPE_JOYBUTTON 	5

typedef struct stInputCommand
{
	bool active;
	bool lastactive;
	//int value;

	SDLKey 	keysym;

	unsigned int joyeventtype;
	int which;
	int joyaxis;
	unsigned short joybutton;
	int joyvalue;
}stInputCommand;

class CInput : public CSingleton<CInput>
{
public:
	CInput();
	virtual ~CInput();

	void pollEvents();

	bool getHoldedKey(int key);
	bool getPressedKey(int key);
	bool getPressedAnyKey(void);
	void sendKey(int key);

	bool getPressedAnyCommand();
	bool getPulsedCommand(int command, int msec);
	bool getPulsedCommand(int player, int command, int msec);
	bool getHoldedCommand(int player, int command);
	bool getHoldedCommand(int command);
	bool getPressedCommand(int command);
	bool getPressedCommand(int player, int command);
	bool getPressedAnyCommand(int player);
	bool getExitEvent(void);
	void cancelExitEvent(void);

	void getEventName(int position, unsigned char input, std::string &buf);
	bool readNewEvent(Uint8 device, int position);

	short loadControlconfig();
	void resetControls();
	bool startJoyDriver();
	short saveControlconfig();

	void flushKeys(void);
	void flushCommands(void);
	void flushAll(void);

private:
	SDL_Event Event;
	SDL_Joystick *mp_Joystick;

	stInputCommand InputCommand[NUM_INPUTS][NUMBER_OF_COMMANDS];
	bool m_exit;
	int m_cmdpulse;
	short m_joydeadzone;

	bool immediate_keytable[KEYTABLE_SIZE];
	bool last_immediate_keytable[KEYTABLE_SIZE];
#ifdef WIZGP2X
	int volume;
	int volume_direction;
#endif

	void processKeys(int value);
	void processJoystickAxis(void);
	void processJoystickButton(int value);
#ifdef WIZGP2X
	void WIZ_EmuKeyboard( int button, int value );
	void WIZ_AdjustVolume( int direction );
#endif
};



#endif /* CINPUT_H_ */
