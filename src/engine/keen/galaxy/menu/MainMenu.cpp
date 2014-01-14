/*
 * CMainMenu.cpp
 *
 *  Created on: 19.02.2012
 *      Author: gerstrong and pizza2004
 */

#include "MainMenu.h"
#include <base/GsApp.h>
#include <widgets/GsMenuController.h>


#include "SettingsMenu.h"
#include "SelectionMenu.h"
#include "LoadMenu.h"
#include "SaveMenu.h"
#include "CHelpMenu.h"
//#include "engine/infoscenes/CHighScores.h"
#include "common/CBehaviorEngine.h"

#include "core/mode/CGameMode.h"

#include "Button.h"


namespace galaxy
{

void MainMenu::createGalaxyMenu( const bool openedGamePlay )
{
#if defined (SINGLEPLAYER)
    g_pBehaviorEngine->mPlayers = 1;
    GsButton *button = new GalaxyButton( "New Game",
                                        new OpenMenuEvent(new CDifficultySelection) );
#else
    GsButton *button = new GalaxyButton( "New Game",
             new OpenMenuEvent( new CPlayersSelection<NewGamePlayersEvent, GalaxyButton>(true) ) );
#endif

	mpMenuDialog->addControl( button );

	// TODO: Some items are still disabled, because those are not yet implemented in Galaxy

    GsButton *loadButton = new GalaxyButton( "Load",
										new OpenMenuEvent( new CLoadMenu() ) );
	mpMenuDialog->addControl( loadButton );
	loadButton->mEnabled = true;

    GsButton *saveButton = new GalaxyButton( "Save",
									new OpenMenuEvent( new CSaveMenu() ) );
	mpMenuDialog->addControl( saveButton );
	saveButton->mEnabled = openedGamePlay;

    mpMenuDialog->addControl(new GalaxyButton( "Configure",
                                                new OpenMenuEvent( new SettingsMenu() ) ) );

/*    GsButton *highscoreButton = new GalaxyButton( "High Scores",
													new StartInfoSceneEvent( new CHighScores ) );
	mpMenuDialog->addControl( highscoreButton );
    highscoreButton->mEnabled = false;*/

    GsButton *infoButton = new GalaxyButton( "Info",
											new OpenMenuEvent( new CHelpMenu() ) );
	mpMenuDialog->addControl( infoButton );
	infoButton->mEnabled = false;

    mpMenuDialog->addControl(new GalaxyButton( "End Game", new EventEndGamePlay() ) );

    mpMenuDialog->addControl(new GalaxyButton( "Quit", new GMQuit() ) );

	setMenuLabel("MAINMENULABEL");

}



MainMenu::MainMenu( const bool openedGamePlay ) :
CBaseMenu( GsRect<float>(0.25f, 0.23f, 0.5f, 0.5f) )
{
	if(g_pBehaviorEngine->getEngine() == ENGINE_GALAXY)
	{
		createGalaxyMenu(openedGamePlay);
	}
	else if(g_pBehaviorEngine->getEngine() == ENGINE_VORTICON)
	{
		createVorticonMenu(openedGamePlay);
	}
}


}
