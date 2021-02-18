#include "stdafx.h"
#include "cCheats.h"

DWORD_PTR m_GameContext;
DWORD_PTR m_ClientPlayerManager;
DWORD_PTR idToPlayerMapOffset;

extern DWORD pid; //Process ID
extern HANDLE pHandle; //Process handle

static bool IsValid(DWORD_PTR ptr)
{
	if (ptr && HIWORD(ptr) != NULL)
		return true;
	
		return false;
}

int updateFromGameContext() // Update offset, from the ClientGameContext
{ 
	ReadProcessMemory(pHandle, (void*)(OFFSET_CLIENTGAMECONTEXT), &m_GameContext, sizeof(DWORD_PTR), NULL);
		if (!IsValid(m_GameContext)) return 1;
		ReadProcessMemory(pHandle, (void*)(m_GameContext + OFFSET_PLAYERMANAGER), &m_ClientPlayerManager, sizeof(DWORD_PTR), NULL); //ClientPlayerManager	
		if (!IsValid(m_ClientPlayerManager)) return 2;
		//ReadProcessMemory(pHandle, (void*)(m_ClientPlayerManager + 0x548), &idToPlayerMapOffset, sizeof(DWORD_PTR), NULL);
		//if (!IsValid(idToPlayerMapOffset)) return 3;
	return 4;
}

bool readPlayer(Player* pPlayer, int id) //Read Player with his id, if player isn't valid return false. 
{
	memset(pPlayer, 0, sizeof(pPlayer));

	ReadProcessMemory(pHandle, (void*)(m_ClientPlayerManager + (id * OFFSET_LOCALPLAYER)), &pPlayer->clientPlayer, sizeof(DWORD_PTR), NULL);
		if (!IsValid(pPlayer->clientPlayer)) return false;
	ReadProcessMemory(pHandle, (void*)(pPlayer->clientPlayer + 0x40), &pPlayer->Name, sizeof(pPlayer->Name), NULL);
	ReadProcessMemory(pHandle, (void*)(pPlayer->clientPlayer + OFFSET_SOLDIER), &pPlayer->clientSoldier, sizeof(DWORD_PTR), NULL);
	ReadProcessMemory(pHandle, (void*)(pPlayer->clientPlayer + 0x0CBC), &pPlayer->m_teamId, sizeof(pPlayer->m_teamId), NULL);
		if (!IsValid(pPlayer->clientSoldier)) return false;
	ReadProcessMemory(pHandle, (void*)(pPlayer->clientSoldier + 0x591), &pPlayer->isOccluded, sizeof(BYTE), NULL);
	ReadProcessMemory(pHandle, (void*)(pPlayer->clientSoldier + 0x490), &pPlayer->clientReplication, sizeof(DWORD_PTR), NULL);
	ReadProcessMemory(pHandle, (void*)(pPlayer->clientSoldier + 0x0140), &pPlayer->healthcomponent, sizeof(DWORD_PTR), NULL);
		if (!IsValid(pPlayer->healthcomponent)) return false;
	ReadProcessMemory(pHandle, (void*)(pPlayer->healthcomponent + 0x0020), &pPlayer->health, sizeof(pPlayer->health), NULL);
		if (!IsValid(pPlayer->clientReplication)) return false;
//	ReadProcessMemory(pHandle, (void*)(pPlayer->clientReplication + 0x30), &pPlayer->position, sizeof(D3DXVECTOR3), NULL);
//	ReadProcessMemory(pHandle, (void*)(pPlayer->clientReplication + 0x50), &pPlayer->velocity, sizeof(D3DXVECTOR3), NULL);
	ReadProcessMemory(pHandle, (void*)(pPlayer->clientReplication + 0x80), &pPlayer->state, sizeof(pPlayer->state), NULL);
	return true;
}

int readLocalPlayer(LocalPlayer* localPlayer) 
{
	memset(localPlayer, 0, sizeof(localPlayer));

	ReadProcessMemory(pHandle, (void*)(m_ClientPlayerManager + OFFSET_LOCALPLAYER), &localPlayer->clientPlayer, sizeof(DWORD_PTR), NULL);
		if (!IsValid(localPlayer->clientPlayer)) return 10;
	//ReadProcessMemory(pHandle, (void*)(localPlayer->clientPlayer + 0x40), &localPlayer->Name, sizeof(localPlayer->Name), NULL);
	ReadProcessMemory(pHandle, (void*)(localPlayer->clientPlayer + OFFSET_SOLDIER), &localPlayer->clientSoldier, sizeof(DWORD_PTR), NULL);
	//ReadProcessMemory(pHandle, (void*)(localPlayer->clientPlayer + 0x0CBC), &localPlayer->m_teamId, sizeof(localPlayer->m_teamId), NULL);
		if (!IsValid(localPlayer->clientSoldier)) return 20;
	/*	ReadProcessMemory(pHandle, (void*)(localPlayer->clientSoldier + 0x490), &localPlayer->clientReplication, sizeof(DWORD_PTR), NULL);
		ReadProcessMemory(pHandle, (void*)(localPlayer->clientSoldier + 0x0140), &localPlayer->healthcomponent, sizeof(DWORD_PTR), NULL);
	ReadProcessMemory(pHandle, (void*)(localPlayer->clientSoldier + 0x4D8), &localPlayer->flYaw, sizeof(FLOAT), NULL);
	ReadProcessMemory(pHandle, (void*)(localPlayer->clientSoldier + 0x4DC), &localPlayer->flPitch, sizeof(FLOAT), NULL);
		if (!IsValid(localPlayer->healthcomponent)) return 2;
	ReadProcessMemory(pHandle, (void*)(localPlayer->healthcomponent + 0x0020), &localPlayer->health, sizeof(localPlayer->health), NULL);
		if (!IsValid(localPlayer->clientReplication)) return 3;
//	ReadProcessMemory(pHandle, (void*)(localPlayer->clientReplication + 0x30), &localPlayer->position, sizeof(D3DXVECTOR3), NULL);
//	ReadProcessMemory(pHandle, (void*)(localPlayer->clientReplication + 0x50), &localPlayer->velocity, sizeof(D3DXVECTOR3), NULL);
	ReadProcessMemory(pHandle, (void*)(localPlayer->clientReplication + 0x80), &localPlayer->state, sizeof(localPlayer->state), NULL);*/


/*	ReadProcessMemory(pHandle, (void*)(localPlayer->clientSoldier + 0x0550), &localPlayer->m_soldierWeaponsComponent, sizeof(DWORD_PTR), NULL);
		if (IsValid(localPlayer->m_soldierWeaponsComponent)) 
	ReadProcessMemory(pHandle, (void*)(localPlayer->m_soldierWeaponsComponent + 0x09A8), &localPlayer->activeSlot, sizeof(localPlayer->activeSlot), NULL);	
	ReadProcessMemory(pHandle, (void*)(localPlayer->m_soldierWeaponsComponent + 0x07A0), &localPlayer->m_currentAnimatedWeaponHandler, sizeof(DWORD_PTR), NULL);
		if (IsValid(localPlayer->m_currentAnimatedWeaponHandler))
			ReadProcessMemory(pHandle, (void*)(localPlayer->m_currentAnimatedWeaponHandler + localPlayer->activeSlot * 0x8), &localPlayer->m_clientSoldierWeapon, sizeof(DWORD_PTR), NULL);
		if (IsValid(localPlayer->m_clientSoldierWeapon)) 
			ReadProcessMemory(pHandle, (void*)(localPlayer->m_clientSoldierWeapon + 0x49c0), (void*)&localPlayer->m_correctedFiring, sizeof(DWORD_PTR), NULL);
		if (IsValid(localPlayer->m_correctedFiring)) 
	ReadProcessMemory(pHandle, (void*)(localPlayer->m_correctedFiring + 0x78), (void*)&localPlayer->m_weaponSway, sizeof(DWORD_PTR), NULL);*/

	ReadProcessMemory(pHandle, (void*)(localPlayer->clientSoldier + 0x0280), &localPlayer->VehicleVelocityA, sizeof(localPlayer->VehicleVelocityA), NULL);
	ReadProcessMemory(pHandle, (void*)(localPlayer->clientSoldier + 0x0284), &localPlayer->VehicleVelocityB, sizeof(localPlayer->VehicleVelocityB), NULL);
	ReadProcessMemory(pHandle, (void*)(localPlayer->clientSoldier + 0x0288), &localPlayer->VehicleVelocityC, sizeof(localPlayer->VehicleVelocityC), NULL);

	double VelocityAX = pow(localPlayer->VehicleVelocityA.x, 2);
	double VelocityBX = pow(localPlayer->VehicleVelocityB.x, 2);
	double VelocityCX = pow(localPlayer->VehicleVelocityC.x, 2);

	localPlayer->VehicleSpeed = 0;
	localPlayer->VehicleSpeed = sqrt(VelocityAX + VelocityBX + VelocityCX) * 3.6f;

	return 999;
}
