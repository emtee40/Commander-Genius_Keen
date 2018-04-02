/*
 * CControlsettings.h
 *
 *  Created on: 28.11.2009
 *      Author: gerstrong
 */

#ifndef CCONTROLSETTINGS_H_
#define CCONTROLSETTINGS_H_

#include <widgets/GsBaseMenu.h>

#include <base/utils/StringUtils.h>
#include <base/GsEvent.h>
#include "widgets/Button.h"
#include "widgets/Switch.h"
#include <vector>
#include <map>


#include "SelectionMenu.h"

namespace galaxy
{

// Main Class for Controller Config
class CControlsettings : public GalaxyMenu
{
public:
	CControlsettings(const int selectedPlayer);

    void refresh();

	void release();

private:

	int mSelectedPlayer;

    Switch *mpTwoButtonSwitch;
    Switch *mpAnalogSwitch;
    Switch *mpSuperPogoSwitch;
    Switch *mpImpPogoSwitch;
    Switch *mpAutoGunSwitch;
};


class CControlSettingsBase : public GalaxyMenu
{
public:
    CControlSettingsBase(const int selectedPlayer);

    virtual void ponder(const float deltaT);
    virtual void release();

protected:
    int mSelectedPlayer;

<<<<<<< HEAD:src/engine/keen/galaxy/menu/ControlSettings.h
    std::vector<GalaxyButton*> mpButtonList;
    std::map<InputCommands, std::string> mCommandName;
=======
    std::vector<GameButton*> mpButtonList;
    std::map<InputCommand, std::string> mCommandName;
>>>>>>> ce7f64a6... Cleanups, fixes:src/engine/core/menu/ControlSettings.h

    bool mapping;
};


// Movement config Part
class CControlSettingsMovement : public CControlSettingsBase
{
public:
    CControlSettingsMovement(const int selectedPlayer) :
        CControlSettingsBase(selectedPlayer) {}

    void refresh();
};



// Buttons config Part
class CControlSettingsButtons : public CControlSettingsBase
{
public:
    CControlSettingsButtons(const int selectedPlayer) :
        CControlSettingsBase(selectedPlayer) {}

    void refresh();
};

// Create the Control-Menu for the indicated Player



struct OpenControlMenuEvent : SelectionEvent
{
	OpenControlMenuEvent(const int players) :
        SelectionEvent(players) {}
};


struct OpenButtonsControlMenuEvent : OpenControlMenuEvent
{
	OpenButtonsControlMenuEvent(const int option) :
        OpenControlMenuEvent(option) {}
};

struct OpenMovementControlMenuEvent : OpenControlMenuEvent
{
	OpenMovementControlMenuEvent(const int option) :
        OpenControlMenuEvent(option) {}
};

}

#endif /* CCONTROLSETTINGS_H_ */
