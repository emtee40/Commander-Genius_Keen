/*
 * CLevelPlay.h
 *
 *  Created on: 06.08.2010
 *      Author: gerstrong
 *
 *  This class will manage the entire gameplay in one level
 */

#ifndef CLEVELPLAY_H_
#define CLEVELPLAY_H_

#include "common/CObject.h"
#include "fileio/CExeFile.h"
#include "engine/galaxy/CInventory.h"
#include "common/CBehaviorEngine.h"
#include <vector>

namespace galaxy {

class CLevelPlay {
public:
	CLevelPlay(CExeFile &ExeFile, CInventory &Inventory);
	bool isActive();
	void setActive(bool value);

	bool loadLevel(const Uint16 level);

	std::string getLevelName();
	void process();

private:
	std::vector<CObject*> m_ObjectPtr;
	bool m_active;

	CMap m_Map;
	CExeFile &m_ExeFile;
	CInventory &m_Inventory;
	stOption *mp_option;
};

}

#endif /* CLEVELPLAY_H_ */
