/*
 * Copyright (C) 2002-2004 by the Widelands Development Team
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

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <map>
#include "building.h"
#include "transport.h"

class Economy;
class Editor_Game_Base;
class Interactive_Player;
class Tribe_Descr;
class Profile;
class WareInstance;
class WareList;
struct EncodeData;


/*
Warehouse
*/
class WarehouseSupply;

class Warehouse_Descr : public Building_Descr {
public:
	enum {
		Subtype_Normal,
		Subtype_HQ,
		Subtype_Port
	};

	Warehouse_Descr(Tribe_Descr *tribe, const char *name);

	virtual void parse(const char *directory, Profile *prof, const EncodeData *encdata);
	virtual Building *create_object();

	inline int get_subtype() const { return m_subtype; }
	virtual int get_conquers(void) const { return m_conquers; }

private:
	int	m_subtype;
	int	m_conquers;		// HQs conquer
};


class Warehouse : public Building {
   friend class Widelands_Map_Buildingdata_Data_Packet;

	MO_DESCR(Warehouse_Descr);

public:
	Warehouse(Warehouse_Descr *descr);
	virtual ~Warehouse();

   virtual int get_building_type(void) { return Building::WAREHOUSE; }
	virtual void init(Editor_Game_Base *g);
	virtual void cleanup(Editor_Game_Base *g);

	virtual void act(Game *g, uint data);

	virtual void set_economy(Economy *e);

	const WareList &get_wares() const;
	const WareList &get_workers() const;
	void insert_wares(int id, int count);
	void remove_wares(int id, int count);
   void insert_workers(int id, int count);
   void remove_workers(int id, int count);
   
	virtual bool fetch_from_flag(Game* g);

	Worker* launch_worker(Game* g, int ware);
	void incorporate_worker(Game *g, Worker *w);

	WareInstance* launch_item(Game* g, int ware);
	void do_launch_item(Game* g, WareInstance* item);
	void incorporate_item(Game* g, WareInstance* item);

	bool can_create_worker(Game *, int worker);
	void create_worker(Game *, int worker);
protected:
	virtual UIWindow *create_options_window(Interactive_Player *plr, UIWindow **registry);

private:
	static void idle_request_cb(Game* g, Request* rq, int ware, Worker* w, void* data);
   void sort_worker_in(Editor_Game_Base*, std::string, Worker*);

private:
	WarehouseSupply*			m_supply;
	std::vector<Request*>	m_requests; // one idle request per ware type
   std::vector<Object_Ptr> m_incorporated_workers; // Workers who live here at the moment
	int m_next_carrier_spawn;		// time of next carrier growth
};

/*
WarehouseSupply is the implementation of Supply that is used by Warehouses.
It also manages the list of wares in the warehouse.
*/
class WarehouseSupply : public Supply {
public:
	WarehouseSupply(Warehouse* wh);
	virtual ~WarehouseSupply();

	void set_economy(Economy* e);

	const WareList &get_wares() const { return m_wares; }
	const WareList &get_workers() const { return m_workers; }
	int stock_wares(int id) const { return m_wares.stock(id); }
	int stock_workers(int id) const { return m_workers.stock(id); }
	void add_wares(int id, int count);
	void remove_wares(int id, int count);
   void add_workers(int id, int count);
   void remove_workers(int id, int count);

public: // Supply implementation
	virtual PlayerImmovable* get_position(Game* g);
	virtual int get_amount(Game* g, int ware);
	virtual bool is_active(Game* g);

	virtual WareInstance* launch_item(Game* g, int ware);
	virtual Worker* launch_worker(Game* g, int ware);

private:
	Economy*		m_economy;
	WareList		m_wares;
	WareList		m_workers;
	Warehouse*	m_warehouse;
};

#endif
