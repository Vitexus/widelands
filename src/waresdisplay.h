/*
 * Copyright (C) 2003 by the Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
// you MUST include ui.h before this

#ifndef include_waresdisplay_h
#define include_waresdisplay_h

#include "ware.h"


class Editor_Game_Base;
class Player;

/*
class WaresDisplay
------------------
Panel that displays the contents of a WareList.
*/
class WaresDisplay : public UIPanel {
public:
	enum {
		Width = 136,	// 5*24 (5 wares icons) + space in between

		WaresPerRow = 5,
	};

public:
	WaresDisplay(UIPanel* parent, int x, int y, Editor_Game_Base* game, Player* player);
	virtual ~WaresDisplay();

	void set_wares(const WareList& wares);

protected:
	virtual void draw(RenderTarget* dst);
	virtual void draw_ware(RenderTarget* dst, int x, int y, uint id, uint stock);

private:
	Editor_Game_Base*	m_game;
	Player*				m_player;
	WareList				m_wares;
};


#endif // include_waresdisplay_h
