/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod Sample Extension
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include "extension.h"
#include "natives.h"
#include <unordered_set>
#include <string>

SMSet g_Set;		/**< Global singleton for extension's main interface */

HandleType_t g_StringSet = BAD_HANDLE;
HandleType_t g_CellSet = BAD_HANDLE;

bool SMSet::SDK_OnLoad(char *error, size_t maxlen, bool late)
{
	HandleError err;
	g_StringSet = handlesys->CreateType("StringSet", this, 0, NULL, NULL, myself->GetIdentity(), &err);
	if (g_StringSet == BAD_HANDLE)
	{
		snprintf(error, maxlen, "Could not create StringSet handle (err: %d)", err);
		return false;
	}

	g_CellSet = handlesys->CreateType("CellSet", this, 0, NULL, NULL, myself->GetIdentity(), &err);
	if (g_CellSet == BAD_HANDLE)
	{
		snprintf(error, maxlen, "Could not create CellSet handle (err: %d)", err);
		return false;
	}

	sharesys->RegisterLibrary(myself, "SMSets");
	sharesys->AddNatives(myself, g_Natives);
	return true;
}

void SMSet::SDK_OnUnload()
{
	handlesys->RemoveType(g_StringSet, myself->GetIdentity());
	handlesys->RemoveType(g_CellSet, myself->GetIdentity());
}

void SMSet::OnHandleDestroy(HandleType_t type, void *object)
{
	if (type == g_CellSet)
		delete (std::unordered_set< cell_t > *)object;
	else if (type == g_StringSet)
		delete (std::unordered_set< std::string > *)object;
}

SMEXT_LINK(&g_Set);
