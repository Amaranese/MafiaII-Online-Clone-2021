/*************************************************************
*
* Solution   : Mafia 2 Multiplayer
* Project    : Client
* File       : CBlipRPC.h
* Developers : AaronLad <aaron@m2-multiplayer.com>
*
***************************************************************/

#pragma once

#include	<RPC4Plugin.h>

class CBlipRPC
{

private:

	static	bool							m_bRegistered;

public:

	static	void		Register			( RakNet::RPC4 * pRPC );
	static	void		Unregister			( RakNet::RPC4 * pRPC );

};