//----------------------------------------------------------------
//  Play Settings
//----------------------------------------------------------------
//
//  Oblige Level Maker (C) 2006,2007 Andrew Apted
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//----------------------------------------------------------------

#include "headers.h"
#include "hdr_fltk.h"

#include "ui_optlist.h"
#include "ui_themes.h"
#include "ui_window.h"

#include "lib_util.h"


//
// Constructor
//
UI_Play::UI_Play(int x, int y, int w, int h, const char *label) :
    Fl_Group(x, y, w, h, label)
{
  end(); // cancel begin() in Fl_Group constructor
 
  box(FL_THIN_UP_BOX);


  int cy = y + 8;

  Fl_Box *heading = new Fl_Box(FL_FLAT_BOX, x+6, cy, w-12, 24, "Playing Style");
  heading->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  heading->labeltype(FL_NORMAL_LABEL);
  heading->labelfont(FL_HELVETICA_BOLD);

  add(heading);

  cy += 28;


  mons = new Fl_Choice(x+ 82, cy, 112, 24, "Monsters: ");
  mons->align(FL_ALIGN_LEFT);
  mons->selection_color(FL_RED);
  mons->add("Scarce|Normal|Hordes");
  mons->value(1);

  add(mons);

  cy += mons->h() + 6;


  puzzles = new Fl_Choice(x+ 82, cy, 112, 24, "Puzzles: ");
  puzzles->align(FL_ALIGN_LEFT);
  puzzles->selection_color(FL_RED);
  puzzles->add("Few|Normal|Heaps");
  puzzles->value(1);

  add(puzzles);

  cy += puzzles->h() + 6;


  traps = new Fl_Choice(x+ 82, cy, 112, 24, "Traps: ");
  traps->align(FL_ALIGN_LEFT);
  traps->selection_color(FL_RED);
  traps->add("Few|Normal|Heaps");
  traps->value(1);

  add(traps);

  cy += traps->h() + 6;

  cy += 10;


  health = new Fl_Choice(x+82, cy, 112, 24, "Health: ");
  health->align(FL_ALIGN_LEFT);
  health->selection_color(FL_RED);
  health->add("Less|Enough|More");
  health->value(1);

  add(health);

  cy += health->h() + 6;


  ammo = new Fl_Choice(x+82, cy, 112, 24, "Ammo: ");
  ammo->align(FL_ALIGN_LEFT);
  ammo->selection_color(FL_RED);
  ammo->add("Less|Enough|More");
  ammo->value(1);
  
  add(ammo);
  
  cy += ammo->h() + 6;


  DebugPrintf("UI_Play: final h = %d\n", cy - y);
}


//
// Destructor
//
UI_Play::~UI_Play()
{
}

void UI_Play::Locked(bool value)
{
  if (value)
  {
    mons  ->deactivate();
    puzzles->deactivate();
    traps ->deactivate();
    health->deactivate();
    ammo  ->deactivate();
  }
  else
  {
    mons  ->activate();
    puzzles->activate();
    traps ->activate();
    health->activate();
    ammo  ->activate();
  }
}

void UI_Play::UpdateLabels(const char *game, const char *mode)
{
return; //!!!!
  
  if (strcmp(mode, "dm") == 0)
  {
    mons->label("Players: ");
    puzzles->label("Weapons: ");
  }
  else
  {
    mons->label("Monsters: ");

    if (strcmp(game, "wolf3d") == 0 || strcmp(game, "spear") == 0)
      puzzles->label("Bosses: ");
    else
      puzzles->label("Puzzles: ");
  }

  SYS_ASSERT(main_win);

  main_win->theme_box->redraw();
}


//----------------------------------------------------------------

const char * UI_Play::adjust_syms[3] =
{
  "less", "normal", "more"
};

const char *UI_Play::get_Health()
{
  return adjust_syms[health->value()];
}

const char *UI_Play::get_Ammo()
{
  return adjust_syms[ammo->value()];
}

const char *UI_Play::get_Monsters()
{
  return adjust_syms[mons->value()];
}

const char *UI_Play::get_Traps()
{
  return adjust_syms[traps->value()];
}

const char *UI_Play::get_Puzzles()
{
  return adjust_syms[puzzles->value()];
}


//----------------------------------------------------------------

int UI_Play::FindSym(const char *str)
{
  for (int i=0; adjust_syms[i]; i++)
    if (StrCaseCmp(str, adjust_syms[i]) == 0)
      return i;

  return -1; // Unknown
}

bool UI_Play::set_Monsters(const char *str)
{
  int i = FindSym(str);

  if (i >= 0) { mons->value(i); return true; }

  return false;
}

bool UI_Play::set_Puzzles(const char *str)
{
  int i = FindSym(str);

  if (i >= 0) { puzzles->value(i); return true; }

  return false;
}

bool UI_Play::set_Traps(const char *str)
{
  int i = FindSym(str);

  if (i >= 0) { traps->value(i); return true; }

  return false;
}

bool UI_Play::set_Health(const char *str)
{
  int i = FindSym(str);

  if (i >= 0) { health->value(i); return true; }

  return false;
}

bool UI_Play::set_Ammo(const char *str)
{
  int i = FindSym(str);

  if (i >= 0) { ammo->value(i); return true; }

  return false;
}

