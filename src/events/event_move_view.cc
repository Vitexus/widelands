/*
 * Copyright (C) 2002-2004, 2006-2008 by the Widelands Development Team
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

#include "event_move_view.h"

#include "interactive_player.h"

#include "editor_game_base.h"
#include "filesystem.h"
#include "game.h"
#include "i18n.h"
#include "map.h"
#include "profile.h"
#include "wexception.h"

#define EVENT_VERSION 2

namespace Widelands {

Event_Move_View::Event_Move_View(char const * const Name, State const S)
	: Event(Name, S), m_location(Coords::Null()), m_player(1)
{}


void Event_Move_View::Read(Section & s, Editor_Game_Base & egbase) {
	try {
		int32_t const packet_version = s.get_safe_int("version");
		if (1 <= packet_version and packet_version <= EVENT_VERSION) {
			m_location =
				packet_version == 1 ?
				Coords(s.get_safe_int("point_x"), s.get_safe_int("point_y"))
				:
				s.get_safe_Coords("point");
			m_player = s.get_int("player", 1);
			Map const & map = egbase.map();
			if
				(m_location.x < 0 or map.get_width () <= m_location.x
				 or
				 m_location.y < 0 or map.get_height() <= m_location.y)
				throw wexception
					("illegal coordinates (%i, %i)", m_location.x, m_location.y);
			if (m_player <= 0 or map.get_nrplayers() < m_player)
				throw wexception("illegal player number %u", m_player);
		} else
			throw wexception("unknown/unhandled version %i", packet_version);
	} catch (_wexception const & e) {
		throw wexception("(move view): %s", e.what());
	}
}

void Event_Move_View::Write(Section & s) const {
	s.set_string("type",    "move_view");
	s.set_int   ("version", EVENT_VERSION);
	s.set_Coords("point",   m_location);
}

/*
 * check if trigger conditions are done
 */
Event::State Event_Move_View::run(Game* game) {
	assert(m_location);

	Interactive_Player & ipl = *game->get_ipl();
	if (ipl.get_player_number() == m_player)
		ipl.move_view_to(m_location);

   m_state = DONE;
   return m_state;
}

};
