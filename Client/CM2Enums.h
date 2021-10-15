/*************************************************************
*
* Solution   : Mafia 2 Multiplayer
* Project    : Client
* File       : CM2Enums.h
* Developers : AaronLad <aaron@m2-multiplayer.com>
			   Hopkins
*
***************************************************************/

#pragma once

namespace M2Enums
{
	enum eHumanMessages
	{
		ON_VEHICLE_START_ENTER	= 851995,	// Enter vehicle start
		ON_VEHICLE_ENTER		= 851997,	// Enter vehicle done
		ON_VEHICLE_START_EXIT	= 851996,	// Exit vehicle start
		ON_VEHICLE_EXIT			= 851998,	// Exit vehicle done
		ON_DOOR_KICK			= 852054,	// Kicking open doors
		ON_USE_DOOR				= 852055,	// Open / Closing doors
		ON_SHOOT				= 851971,	// Spraying
		ON_SHOT_HIT_ENTITY		= 852071,	// Shot hits another entity
		ON_DAMAGE				= 851984,	// Take damage
		ON_DEATH				= 851988,	// Die
		ON_AIM_ENTER			= 852041,	// Start aiming
		ON_AIM_LEAVE			= 852042,	// Stop aiming
		ON_ACTION				= 851987,	// Using the action (e) key
		ON_USE_PHONE			= 851989,	// Using a phone
		CAR_BREAK_IN			= 852007,	// When break a car and enter - To be tested
		ON_TRIGGER_ENGINE		= 851972	// Trigger on/off engine - To be tested
	};

	enum eMoveType
	{
		E_NONE					= -1,
		E_BREATH,
		E_STEP,
		E_WALK,
		E_JOG,
		E_SPRINT,
		E_UNKNOWN_2
	};

	enum eFadeType
	{
		E_FADE_IN				= 0,
		E_FADE_OUT
	};

	enum eControlStyles
	{
		CONTROLSTYLE_NONE,
		CONTROLSTYLE_ALL,
		CONTROLSTYLE_WEAPON_PICKUP,
		CONTROLSTYLE_FORCECROSSHAIROFF,
		CONTROLSTYLE_FORCECROSSHAIRON,
		CONTROLSTYLE_CROUCH,
		CONTROLSTYLE_ZOOM,
		CONTROLSTYLE_WEAPON_SEL,
		CONTROLSTYLE_WEAPON_MANIP,
		CONTROLSTYLE_OBSTACLES,
		CONTROLSTYLE_COVERS,
		CONTROLSTYLE_CAR_ACCESSORIES,
		CONTROLSTYLE_CAR_DRIVE,
		CONTROLSTYLE_CAR_INOUT,
		CONTROLSTYLE_FIRE,
		CONTROLSTYLE_CLOSECOMBAT,
		CONTROLSTYLE_USE,
		CONTROLSTYLE_SPRINT,
		CONTROLSTYLE_RUN,
		CONTROLSTYLE_WALK
	};

	enum eVehicleSeat
	{
		E_SEAT_DRIVER			= 1,
		E_SEAT_PASSENGER_FRONT,
		E_SEAT_PASSENGER_BACK_1,
		E_SEAT_PASSENGER_BACK_2
	};

	enum eEntityType
	{
		E_ENTITY_PED			= 14,
		E_ENTITY_PLAYER			= 16,
		E_ENTITY_VEHICLE		= 18,
		E_ENTITY_ITEM			= 36
	};

	enum eEntityState
	{
		WALKING					= 0x200,
		JOGGING					= 0x201,
		IDLE					= 0x203,
		STOPPING				= 0x205,
		AIM_FROM_HIP_WALK		= 0x300,
		AIM_FROM_HIP_JOG		= 0x301,
		AIM_FROM_HIP_STAND		= 0x303,
		SPRINTING				= 0x602,
		CLIMBING				= 0x10200201,
		SHOOTING_FROM_HIP		= 0x40000303,
		AIMING					= 0x8001C303,
		SHOOTING				= 0xC001C303
	};

	enum eVehiclePart
	{
		E_REAR_BUMPER			= 1,
		E_FRONT_BUMPER,
		E_BOOT,
		E_HOOD					= 32, // Require testing
		E_TRUNK					= 33, // Require testing
		E_HOOD_HEMI_COVER,
		E_REAR_DOOR_LEFT,
		E_REAR_DOOR_GLASS_LEFT,
		E_REAR_DOOR_RIGHT,
		E_REAR_DOOR_GLASS_RIGHT,
		E_FRONT_DOOR_LEFT,
		E_FRONT_DOOR_GLASS_MAIN_LEFT,
		E_FRONT_DOOR_GLASS_SMALL_LEFT,
		E_FRONT_DOOR_RIGHT,
		E_FRONT_DOOR_GLASS_SMALL_RIGHT,
		E_FRONT_DOOR_GLASS_MAIN_RIGHT,
		E_EXHAUST,
		E_REAR_WINDSCREEN,
		E_FRONT_WINDSCREEN,
		E_ENGINE				= 34, // Require testing
		E_REAR_WHEEL_RIGHT		= 29,
		E_REAR_WHEEL_HUB_RIGHT,
		E_REAR_WHEEL_TYRE_RIGHT,
		E_REAR_WHEEL_LEFT,
		E_REAR_WHEEL_HUB_LEFT,
		E_REAR_WHEEL_TYRE_LEFT,
		E_FRONT_WHEEL_RIGHT,
		E_FRONT_WHEEL_HUB_RIGHT,
		E_FRONT_WHEEL_TYRE_RIGHT,
		E_FRONT_WHEEL_LEFT,
		E_FRONT_WHEEL_HUB_LEFT,
		E_FRONT_WHEEL_TYRE_LEFT
	};
}