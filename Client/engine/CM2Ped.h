/*************************************************************
*
* Solution   : Mafia 2 Multiplayer
* Project    : Client - Game Engine
* File       : CM2Ped.h
* Developers : AaronLad <aaron@m2-multiplayer.com>
*
***************************************************************/

#pragma once

#include "BaseInc.h"

#include "CM2Entity.h"
#include "CM2Enums.h"
#include "CM2SyncObject.h"

class M2Vehicle;
class CM2Vehicle;

enum ePlayerMovementState : BYTE
{
	E_WALK = 0,
	E_JOG = 1,
	E_SPRINT = 2,
	E_IDLE = 3,
	E_STOPPING = 5
};

enum ePhysState : BYTE
{
	E_DYNAMIC = 0,
	E_ENABLED = 1,
	E_KINEMATIC = 2,
	E_DISABLED = 3
};

class M2WeaponData
{
public:
	PAD(M2WeaponData, pad0, 0xE8);							// 0000 - 00E8
	bool m_bInifiniteAmmo;									// 00E8 - 00E9

	void	AddWeapon(DWORD weapon, DWORD ammo);

	void	AddMoney(int money, int unk);
	float	GetMoney();
	void	RemoveMoney(int money, int unk);

	bool	HasItem(DWORD item);

	void	ReloadWeapon(int index, int unk);
	void	RemoveWeapon(DWORD weapon);
};

class M2Inventory
{
public:
	PAD(M2Inventory, pad0, 0x170);							// 0000 - 0170
	DWORD m_dwSelectedWeapon;								// 0170 - 0174
	PAD(M2Inventory, pad1, 0x50);							// 0174 - 01C4
	DWORD m_dwAimType;										// 01C4 - 01C8 (0 = Not aiming, 1 = hip aim, 3 = ADS aim)
};

class M2PlayerControls // 0240 - 02E8
{
public:
	PAD(M2PlayerControls, pad0, 0xA0);						// 0000 - 00A0
	ePlayerMovementState m_playerMovementState;				// 00A0 - 00A1
	BYTE m_byteModifiers;									// 00A1 - 00A2
	bool m_bIsAiming;										// 00A2 - 00A3
	BYTE m_byteMouseFlags;									// 00A3 - 00A4
	BYTE m_byteUnknown1;									// 00A4 - 00A5
	BYTE m_byteUnknown2;									// 00A5 - 00A6
	BYTE m_byteKeyboardFlags;								// 00A6 - 00A7
	BYTE m_byteUnknown3;									// 00A7 - 00A8
	bool m_bIsShooting;										// 00A8 - 00A9
};

/*
class C_PlayerControls // 0x61
{
public:
ePlayerMovementState m_ePlayerMovementState;			// 02E0 - 02E1
BYTE m_byteModifiers;									// 02E1 - 02E2
bool m_bIsAiming;										// 02E2 - 02E3
BYTE m_byteMouseFlags;									// 02E3 - 02E4
BYTE m_byteUnknown1;									// 02E4 - 02E5
BYTE m_byteUnknown2;									// 02E5 - 02E6
BYTE m_byteKeyboardFlags;								// 02E6 - 02E7
PAD(M2PlayerControls, pad0, 0x29);						// 02E7 - 0310
bool m_bIsMoving;										// 0310 - 0311
PAD(M2PlayerControls, pad1, 0x2F);						// 0311 - 0340
bool m_bIsCrouching;									// 0340 - 0341
};
*/

class M2Ped;
class C_HumanWeaponController
{
public:
	PAD(C_HumanWeaponController, pad0, 0x1A0);				// 0000 - 01A0
	void* m_pUnknown;										// 01A0 - 01A4 (wierd, IsUsingFists says this is a bool)

	bool HaveThrowingWeaponInHand();
};

class M2PedUnk001
{
public:
	PAD(M2PedUnk001, pad0, 0x44);							// 0000 - 0044
	void * m_pUnknown;										// 0044 - 004C
};

//class M2EntityData_Unknown_000
//{
//public:
//	unsigned vtable;
//
//
//	// Unknown Method in V table on heX offset 20.
//	void UnknownMethodVX20();
//	int	UnknowMethodVX198();
//};

enum E_HumanMoveMode
{
	HUMAN_MOVE_MODE_NONE = -1,
	HUMAN_MOVE_MODE_BREATH = 0,
	HUMAN_MOVE_MODE_STEP = 1,
	HUMAN_MOVE_MODE_WALK = 2,
	HUMAN_MOVE_MODE_RUN = 3,
	HUMAN_MOVE_MODE_SPRINT = 4,
	HUMAN_MOVE_MODE_END = 5
};

class C_HumanScript
{
public:
	M2Ped* m_pHuman;										// 0000 - 0004 //C_Human ofc
	PAD(C_HumanScript, pad0, 0x18);							// 0004 - 001C
	DWORD m_dwType;											// 001C - 0020
	PAD(C_HumanScript, pad1, 0x88);							// 0020 - 00A8
	M2PedUnk001 * m_pUnknown;								// 00A8 - 00AC

	int				PlayAnim(C_SyncObject **syncObject, const char *const animName, const bool unknown, int, int, float, float, float);
	int				AnimPlayEffect(C_SyncObject **syncObject, const char *const effectName, const bool repeat, int);
	void			AnimEffectStop();

	void			ModelToHand(int unk, int leftModel, int rightModel);
	void			ModelToMouth(int model);

	void			SetAnimStyle(const char *dir, const char *set);

	ePhysState		GetPhysState();
	void			SetPhysState(ePhysState state);

	void			SetSelectedWeapon(DWORD dwWeapon, bool bUseAnimation, int unk);

	void			SetStealthMove(bool enable);

	float			GetRealHealth();

	C_SyncObject	*GetInOutCar(C_SyncObject **syncObject, M2Vehicle *pVehicle, int enter, int seat, bool forced, int unk, int unk2);
	C_SyncObject	*ScrMoveV(C_SyncObject **syncObject, const CVector3 &begin, const E_HumanMoveMode moveMode, const CVector3 &target, const bool smoothStop = true);
	C_SyncObject	*ScrAimAt(C_SyncObject **syncObject, M2Entity *entity, CVector3 const &dir, const bool smooth);
	C_SyncObject	*ScrShootAt(C_SyncObject **syncObject, M2Entity *entity, CVector3 const &dir, const bool smooth);
	C_SyncObject	*ScrShootAtEffect(C_SyncObject **syncObject, CVector3 const &dir, CVector3 const &unk1, CVector3 const &unk2, int unk, bool smooth);
	C_SyncObject	*ScrLookAt(C_SyncObject **syncobject, M2Entity *entity, CVector3 const &dir, const bool smooth);
};

class M2Ped : public M2Entity
{
public:
	// 0000 - 0064
	M2Vehicle * m_pCurrentVehicle;							// 0064 - 0068
	PAD(M2Ped, pad0, 0x10);									// 0068 - 0078
	int m_iSlotSDS;											// 0078 - 007C
	PAD(M2Ped, pad1, 0x24);									// 007C - 00A0
	M2WeaponData * m_pWeaponData;							// 00A0 - 00A4
	C_HumanScript * m_pHumanScript;							// 00A4 - 00A8
	PAD(M2Ped, pad2, 0x4);									// 00A8 - 00AC
	M2Inventory * m_pInventory;								// 00AC - 00B0
	C_HumanWeaponController * m_pWeaponController;			// 00B0 - 00B4
	PAD(M2Ped, pad3, 0x1C);									// 00B4 - 00D0
	float m_fHealth;										// 00D0 - 00D4
	float m_fHealthMax;										// 00D4 - 00D8
	PAD(M2Ped, pad4, 0x10);									// 00D8 - 00E8
	bool m_bInvulnerable;									// 00E8 - 00E9
	// 0xE9 = bool
	// 0xEA = bool
	// 0xEB = bool
	// 0xEC = bool
	// 0xED = bool
	PAD(M2Ped, pad5, 0x157);								// 00E9 - 0240
	M2PlayerControls m_playerControls;						// 0240 - 02E8
	PAD(M2Ped, pad6, 0x3C);									// 02E8 - 0324
	DWORD m_dwAimedAtGUID;									// 0324 - 0328
	PAD(M2Ped, pad7, 0x8);									// 0328 - 0330
	M2Ped * m_pAimedAtPed;									// 0330 - 0334

	/*M2PlayerControls * m_pControls;						// 0240 - 0244
	PAD(M2Ped, pad6, 0x9C);									// 0244 - 02E0
	C_PlayerControls m_playerControls;						// 02E0 - 0341*/

	// 0x1CC, 0x1D0 = current surface walking on (in czech)
	// 0x12C = GameCamera that is attached to player (M2Camera)

	bool IsCrouch(void) const;
};

class CM2Ped : public CM2Entity
{

private:

	M2Ped					* m_pPed;

public:

	CM2Ped(M2Ped * pPed);
	~CM2Ped(void);

	void					SetPed(M2Ped * pPed) { m_pPed = pPed; }
	M2Ped					* GetPed(void) { return m_pPed; }

	BYTE					GetControlState(void);
	DWORD					GetState(void);

	void					SetInfiniteAmmo(bool bInifiniteAmmo);
	bool					HasInfiniteAmmo(void);

	void					SetSelectedWeapon(DWORD dwWeapon, bool bUseAnimation = false);
	DWORD					GetSelectedWeapon(void);
	int						GetSelectedWeaponBullet(void);

	bool					IsAiming(void);
	bool					IsShooting(void);

	void					SetHealth(float fHealth);
	float					GetHealth(void);

	//void					SetHealthMax					( float fHealthMax );
	float					GetHealthMax(void);
	float					GetRealHealth(void);

	void					SetInvulnerable(bool bInvulnerable);
	bool					IsInvulnerable(void);

	void					GiveWeapon(DWORD dwWeapon, DWORD dwAmmo);
	void					RemoveWeapon(DWORD dwWeapon, DWORD dwWeaponAmmo = 0);
	void					RemoveAllWeapons(void);
	void					ReloadWeapon(void);
	bool					HaveThrowingWeaponInHand(void);

	bool					HasItem(DWORD dwItem);

	C_SyncObject			* GetInOutVehicle(M2Vehicle * pVehicle, int iSeat, bool bEnter = true, bool bForced = false);
	M2Vehicle				* GetCurrentVehicle(void);

	void					AddMoney(int iDollars, int iCents);
	void					RemoveMoney(int iDollars, int iCents);
	float					GetMoney(void);

	// These should only be used on peds that are not localplayer
	C_SyncObject			* MoveVec(const CVector3 &vecPosition, M2Enums::eMoveType moveType, CVector3 vecEndDirection);
	C_SyncObject			* AimAt(CVector3 vecPosition);
	C_SyncObject			* ShootAt(CVector3 vecPosition);
	C_SyncObject			* LookAt(CVector3 vecPosition);

	C_SyncObject			* PlayAnimation(char *strAnimation, bool bRepeat);
	void					StopAnimation(C_SyncObject *obj);
	bool					IsAnimFinished();

	C_SyncObject			* PlayAnimEffect(const char *effectName, bool unknow);
	void					AnimEffectStop(C_SyncObject *obj);

	void					ModelToMouth(int iModel);
	void					ModelToHand(int iHand, int iModel);
	void					ActorItemToHand(int hand, int model);

	void					SetAnimStyle(const char *dir, const char *set);

	void					SetPhysState(ePhysState state);
	ePhysState				GetPhysState(void);

	void					SetStealthMove(bool bStealthMove);
	bool					IsStealthMoving();

};