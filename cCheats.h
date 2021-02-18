#ifndef CHEATS_H
#define CHEATS_H

#include "stdafx.h"

#define OFFSET_CLIENTGAMECONTEXT    0x1424abd20//0x24a0c00//0x142384108
#define OFFSET_DXRENDERER           0x14242F488 
#define OFFSET_GAMERENDERER         0x142385028
#define OFFSET_ANGLES				0x1420C4AB0
#define OFFSET_WORLDRENDERSETTINGS  0x142384188

#define OFFSET_PLAYERMANAGER 0x60 
#define OFFSET_LOCALPLAYER 0x540
#define OFFSET_PLAYERS_ARRAY 0x548
#define OFFSET_TEAMID 0x13cc
#define OFFSET_SOLDIER 0x14d0



typedef struct D3DXVECTOR3 {
  FLOAT x;
  FLOAT y;
  FLOAT z;
} D3DXVECTOR3, *LPD3DXVECTOR3;

class Player
{
public:
	//Client Player
	DWORD_PTR clientPlayer;
	char Name[0x10];
	unsigned int m_teamId;

	//ClientControllableEntity
	DWORD_PTR clientSoldier;
	BYTE isOccluded;

	//ClientSoldierReplication
	DWORD_PTR clientReplication;
	int state;

	//LifeModule
	DWORD_PTR healthcomponent;
	FLOAT health;
};

class LocalPlayer : public Player
{
public:
	float flYaw;
	float flPitch;

	//Weapon
	DWORD_PTR  m_soldierWeaponsComponent;
	DWORD_PTR  m_currentAnimatedWeaponHandler;
	DWORD_PTR  m_clientSoldierWeapon;
	DWORD_PTR  m_correctedFiring;
	DWORD_PTR  m_weaponSway;

	D3DXVECTOR3 VehicleVelocityA;
	D3DXVECTOR3 VehicleVelocityB;
	D3DXVECTOR3 VehicleVelocityC;

	double VehicleSpeed;

	INT activeSlot;
};

int updateFromGameContext();
bool readPlayer(Player* pPlayer, int id);
int readLocalPlayer(LocalPlayer* localPlayer);
void setJetSpeed();

#endif