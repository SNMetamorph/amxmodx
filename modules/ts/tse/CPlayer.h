#include "amxxmodule.h"
#pragma once

// AMX Mod X, based on AMX Mod by Aleksander Naszko ("OLO").
// Copyright (C) The AMX Mod X Development Team.
// Copyright (C) 2017, SNMetamorph.
//
// This software is licensed under the GNU General Public License, version 3 or higher.
// Additional exceptions apply. For full license details, see LICENSE.txt or visit:
//     https://alliedmods.net/amxmodx-license

#define Player(i) (&PlayersArray[i])

struct CPlayer {
	// variables
	edict_t *PlayerEdict;
	int PlayerIndex;
	int CurrentWeapon;

	// structures
	struct PlayerWeapon 
	{
		short ammo;
		UINT clip, mode, attachments;
	}; 
	struct HInfo
	{
		byte State, OldState;
		bool IsStateChecked = false, IsPwupTaken = false, PwupFlag = false;
		USHORT PwupType;
		byte PwupDuration;
		float KnockTime = -1.0;
		float KnockDamage = -1.0;
	};
	HInfo HooksInfo;
	PlayerWeapon Weapons[44];

	// pdata methods
	long GetPDataInt(long idx);
	float GetPDataFloat(long idx);
	void SetPDataInt(long idx, long val);
	void SetPDataFloat(long idx, float val);
	long GetWeapPDataInt(long idx);
	float GetWeapPDataFloat(long idx);
	void SetWeapPDataInt(long idx, long val);
	void SetWeapPDataFloat(long idx, float val);

	// player methods
	void Init(edict_t *ple, int plindex);
	void UpdateHUD();
	edict_t *GetWeaponEdict();
	USHORT GetPowerup(int *duration), GetPowerup();
	void GivePowerup(USHORT type, byte duration);
	inline bool IsAlive() { return (this->PlayerEdict->v.deadflag == DEAD_NO && this->PlayerEdict->v.health > 0); };
	inline bool IsOnGround() { return (this->GetPDataInt(27) != 0); };
	inline long GetFreeSlots() { return this->GetPDataInt(333); };
	inline void SetFreeSlots(long val) { this->SetPDataInt(333, val); }
	inline long GetCash() { return this->GetPDataInt(331); }
	inline void SetCash(long val) { this->SetPDataInt(331, val); }
	inline float GetTime() { return this->GetPDataFloat(605); }
	inline void SetTime(float val) { this->SetPDataFloat(605, val); }
	inline float GetMeleeStamina() { return this->GetPDataFloat(472); }
	inline void SetMeleeStamina(float val) { this->SetPDataFloat(472, val); }
	inline float GetPlayerPhysicsSpeed() { return this->GetPDataFloat(85); }
	inline void SetPlayerPhysicsSpeed(float val) { this->SetPDataFloat(85, val); }
	inline float GetEffectsPhysicsSpeed() { return this->GetPDataFloat(87); }
	inline void SetEffectsPhysicsSpeed(float val) { this->SetPDataFloat(87, val); }
};

// other methods
extern CPlayer PlayersArray[33];
edict_t *CreateWeapon(int id, Vector coord, short ttl, USHORT clips, byte atcments);
edict_t *CreatePowerup(USHORT type, Vector coord, short ttl);

inline byte IsPlayerValid(AMX *amx, int pl) {
	if (pl < 1 || pl > gpGlobals->maxClients) {
		MF_LogError(amx, AMX_ERR_NATIVE, "Player out of range (%d)", pl);
		return 0;
	}
	else {
		if (!MF_IsPlayerIngame(pl) || FNullEnt(MF_GetPlayerEdict(pl))) {
			MF_LogError(amx, AMX_ERR_NATIVE, "Invalid player %d", pl);
			return 0;
		}
	}
	return 1;
}


