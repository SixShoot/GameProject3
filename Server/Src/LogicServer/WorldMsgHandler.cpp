﻿#include "stdafx.h"
#include "CommandDef.h"
#include "WorldMsgHandler.h"
#include "Utility/Log/Log.h"
#include "Utility/CommonFunc.h"
#include "Utility/CommonEvent.h"
#include "GameService.h"
#include "PacketHeader.h"
#include "Utility/CommonSocket.h"
#include "PlayerObject.h"
#include "../Message/Msg_ID.pb.h"
#include "../Message/Msg_Login.pb.h"
#include "../Message/Msg_RetCode.pb.h"
#include "RoleModule.h"
#include "SimpleMananger.h"

CWorldMsgHandler::CWorldMsgHandler()
{

}

CWorldMsgHandler::~CWorldMsgHandler()
{

}

BOOL CWorldMsgHandler::Init(UINT32 dwReserved)
{
	

	return TRUE;
}

BOOL CWorldMsgHandler::Uninit()
{
	return TRUE;
}

BOOL CWorldMsgHandler::DispatchPacket(NetPacket *pNetPacket)
{
	switch(pNetPacket->m_dwMsgID)
	{
		PROCESS_MESSAGE_ITEM(MSG_SELECT_SERVER_REQ,		OnMsgSelectServerReq);
		PROCESS_MESSAGE_ITEM(MSG_ROLE_LIST_REQ,			OnMsgRoleListReq);
		PROCESS_MESSAGE_ITEM(MSG_ROLE_LIST_ACK,			OnMsgRoleListAck);
		PROCESS_MESSAGE_ITEM(MSG_ROLE_CREATE_REQ,		OnMsgRoleCreateReq);
		PROCESS_MESSAGE_ITEM(MSG_ROLE_DELETE_REQ,		OnMsgRoleDeleteReq);
		PROCESS_MESSAGE_ITEM(MSG_ROLE_LOGIN_REQ,		OnMsgRoleLoginReq);
		PROCESS_MESSAGE_ITEM(MSG_ROLE_LOGIN_ACK,		OnMsgRoleLoginAck);
		PROCESS_MESSAGE_ITEM(MSG_ROLE_LOGOUT_REQ,		OnMsgRoleLogoutReq);
		PROCESS_MESSAGE_ITEM(MSG_DISCONNECT_NTY,		OnMsgRoleDisconnect);
		PROCESS_MESSAGE_ITEM(MSG_COPY_ABORT_REQ,		OnMsgAbortCopyReq);
		PROCESS_MESSAGE_ITEM(MSG_MAIN_COPY_REQ,			OnMsgMainCopyReq);
        PROCESS_MESSAGE_ITEM(MSG_BACK_TO_CITY_REQ,		OnMsgBackToCityReq);
        
	
	case MSG_LOGIC_REGTO_LOGIN_ACK:
		break;
	default:
		{
			PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();
			
			CPlayerObject *pPlayer = CPlayerManager::GetInstancePtr()->GetPlayer(pHeader->u64TargetID);
			ERROR_RETURN_FALSE(pPlayer != NULL);
			pPlayer->DispatchPacket(pNetPacket);
		}
		break;
	}

	return TRUE;
}



BOOL CWorldMsgHandler::OnMsgSelectServerReq(NetPacket *pNetPacket)
{
	SelectServerReq Req;
	Req.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();
	ERROR_RETURN_TRUE(pHeader->dwUserData != 0);
	SelectServerAck Ack;
	Ack.set_serverid(CGameService::GetInstancePtr()->GetServerID());
	Ack.set_logincode(12345678);
	Ack.set_retcode(MRC_SUCCESSED);
	return ServiceBase::GetInstancePtr()->SendMsgProtoBuf(pNetPacket->m_dwConnID, MSG_SELECT_SERVER_ACK, 0, pHeader->dwUserData, Ack);
}

BOOL CWorldMsgHandler::OnMsgRoleListReq(NetPacket *pNetPacket)
{
	RoleListReq Req;
	Req.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();
	ERROR_RETURN_TRUE(pHeader->dwUserData != 0);
	ServiceBase::GetInstancePtr()->SendMsgProtoBuf(CGameService::GetInstancePtr()->GetDBConnID(),  MSG_ROLE_LIST_REQ, pNetPacket->m_dwConnID, pHeader->dwUserData, Req);
	return TRUE;
}

BOOL CWorldMsgHandler::OnMsgRoleListAck(NetPacket *pNetPacket)
{
	RoleListAck Ack;
	Ack.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();
	ERROR_RETURN_TRUE(pHeader->dwUserData != 0);
	return ServiceBase::GetInstancePtr()->SendMsgProtoBuf((UINT32)pHeader->u64TargetID,  MSG_ROLE_LIST_ACK, 0, pHeader->dwUserData, Ack);
}



BOOL CWorldMsgHandler::OnMsgRoleCreateReq(NetPacket *pNetPacket)
{
	RoleCreateReq Req;
	Req.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();
	ERROR_RETURN_TRUE(pHeader->dwUserData != 0);
	//检验名字是否可用
    ERROR_RETURN_TRUE(Req.accountid() !=0);
    CLog::GetInstancePtr()->LogError("OnMsgRoleCreateReq Name:%s", Req.name().c_str());


	UINT64 u64RoleID = CSimpleManager::GetInstancePtr()->MakeNewRoleID();
    ERROR_RETURN_TRUE(u64RoleID != 0);
    
	CSimpleInfo *pSimpleInfo = CSimpleManager::GetInstancePtr()->CreateSimpleInfo(u64RoleID, Req.accountid(), Req.name(), Req.actorid());
	ERROR_RETURN_TRUE(pSimpleInfo != NULL);
	CPlayerObject *pPlayer  = CPlayerManager::GetInstancePtr()->CreatePlayer(u64RoleID);
    ERROR_RETURN_TRUE(pPlayer != NULL);
	ERROR_RETURN_TRUE(pPlayer->Init(u64RoleID));
	CRoleModule *pRoleModule = (CRoleModule *)pPlayer->GetModuleByType(MT_ROLE);
	pRoleModule->InitBaseData(u64RoleID, Req.name(), Req.actorid(), Req.accountid(), 1);
	pPlayer->OnCreate(u64RoleID);
	pPlayer->SetConnectID(pNetPacket->m_dwConnID, pHeader->dwUserData);
	pPlayer->OnAllModuleOK();

	RoleCreateAck Ack;
    Ack.set_retcode(MRC_SUCCESSED);
	Ack.set_accountid(Req.accountid());
	Ack.set_roleid(u64RoleID);
	Ack.set_actorid(Req.actorid());
	Ack.set_name(Req.name());
	ServiceBase::GetInstancePtr()->SendMsgProtoBuf(pNetPacket->m_dwConnID,  MSG_ROLE_CREATE_ACK, 0, pHeader->dwUserData, Ack);
	return TRUE;
}

BOOL CWorldMsgHandler::OnMsgRoleDeleteReq(NetPacket *pNetPacket)
{
	RoleDeleteReq Req;
	Req.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();
	ERROR_RETURN_TRUE(pHeader->u64TargetID != 0);

	CPlayerManager::GetInstancePtr()->DeletePlayer(Req.roleid());

	RoleDeleteAck Ack;
	Ack.set_retcode(MRC_SUCCESSED);
	return ServiceBase::GetInstancePtr()->SendMsgProtoBuf(pNetPacket->m_dwConnID, MSG_ROLE_DELETE_REQ, pHeader->u64TargetID, 0, Ack);
}

BOOL CWorldMsgHandler::OnMsgRoleLoginReq(NetPacket *pNetPacket)
{
	RoleLoginReq Req;
	Req.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();
	ERROR_RETURN_TRUE(pHeader->dwUserData != 0);
	CPlayerObject *pPlayer = CPlayerManager::GetInstancePtr()->GetPlayer(Req.roleid());
	if(pPlayer == NULL)
	{
        ServiceBase::GetInstancePtr()->SendMsgProtoBuf(CGameService::GetInstancePtr()->GetDBConnID(), MSG_ROLE_LOGIN_REQ, pNetPacket->m_dwConnID, pHeader->dwUserData, Req);
        return TRUE;
	}

	pPlayer->SetConnectID(pNetPacket->m_dwConnID, pHeader->dwUserData);
    pPlayer->OnLogin();
	pPlayer->OnAllModuleOK();
	return TRUE;
}

BOOL CWorldMsgHandler::OnMsgRoleLoginAck(NetPacket *pNetPacket)
{
	DBRoleLoginAck Ack;
	Ack.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();
	ERROR_RETURN_TRUE(pHeader->dwUserData != 0);
	CPlayerObject *pPlayer = CPlayerManager::GetInstancePtr()->CreatePlayer(Ack.roleid());
	pPlayer->Init(Ack.roleid());
	pPlayer->SetConnectID((UINT32)pHeader->u64TargetID, pHeader->dwUserData);
	pPlayer->ReadFromLoginAck(Ack);
	pPlayer->OnLogin();
	pPlayer->OnAllModuleOK();
	return TRUE;
}

BOOL CWorldMsgHandler::OnMsgRoleLogoutReq(NetPacket *pNetPacket)
{
	RoleLogoutReq Req;
	Req.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();
	ERROR_RETURN_TRUE(pHeader->dwUserData != 0);
	CPlayerManager::GetInstancePtr()->DeletePlayer(Req.roleid());
	CPlayerObject *pPlayer = CPlayerManager::GetInstancePtr()->GetPlayer(Req.roleid());
	ERROR_RETURN_TRUE(pPlayer != NULL);
    pPlayer->OnLogout();
	RoleLogoutAck Ack;
	Ack.set_retcode(MRC_SUCCESSED);
	return ServiceBase::GetInstancePtr()->SendMsgProtoBuf(pNetPacket->m_dwConnID, MSG_ROLE_LOGOUT_ACK, 0, pHeader->dwUserData, Ack);
	return TRUE;
}



BOOL CWorldMsgHandler::OnMsgRoleDisconnect(NetPacket *pNetPacket)
{
	RoleDisconnectReq Req;
	Req.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();
	ERROR_RETURN_TRUE(pHeader->u64TargetID != 0);

	CPlayerObject *pPlayer = CPlayerManager::GetInstancePtr()->GetPlayer(Req.roleid());
    ERROR_RETURN_TRUE(pPlayer != NULL);


	return TRUE;
}

BOOL CWorldMsgHandler::OnMsgMainCopyReq(NetPacket *pNetPacket)
{
	MainCopyReq Req;
	Req.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();

	//创建副本
	ERROR_RETURN_TRUE(CGameSvrMgr::GetInstancePtr()->CreateScene(Req.copytype(), Req.roleid(), 1));
	return TRUE;
}

BOOL CWorldMsgHandler::OnMsgAbortCopyReq(NetPacket *pNetPacket)
{
	AbortCopyReq Req;
	Req.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
	PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();

	CPlayerObject *pPlayer = CPlayerManager::GetInstancePtr()->GetPlayer(Req.roleid());
	ERROR_RETURN_TRUE(pPlayer != NULL);
	ERROR_RETURN_TRUE(pPlayer->m_dwCopyID == Req.copyid());
	
    pPlayer->SendLeaveScene(pPlayer->m_dwCopyID, pPlayer->m_dwCopySvrID);

	UINT32 dwSvrID, dwConnID, dwCopyID;
	CGameSvrMgr::GetInstancePtr()->GetMainScene(dwSvrID, dwConnID, dwCopyID);
    ERROR_RETURN_TRUE(dwSvrID != 0);
    ERROR_RETURN_TRUE(dwConnID != 0);
    ERROR_RETURN_TRUE(dwCopyID != 0);
	CGameSvrMgr::GetInstancePtr()->SendPlayerToCopy(Req.roleid(), 6, dwCopyID, dwSvrID);

	return TRUE;
}

BOOL CWorldMsgHandler::OnMsgBackToCityReq( NetPacket *pNetPacket )
{
    BackToCityReq Req;
    Req.ParsePartialFromArray(pNetPacket->m_pDataBuffer->GetData(), pNetPacket->m_pDataBuffer->GetBodyLenth());
    PacketHeader* pHeader = (PacketHeader*)pNetPacket->m_pDataBuffer->GetBuffer();

    CPlayerObject *pPlayer = CPlayerManager::GetInstancePtr()->GetPlayer(Req.roleid());
    ERROR_RETURN_TRUE(pPlayer != NULL);

    UINT32 dwSvrID, dwConnID, dwCopyID;
    CGameSvrMgr::GetInstancePtr()->GetMainScene(dwSvrID, dwConnID, dwCopyID);
    ERROR_RETURN_TRUE(dwSvrID != 0);
    ERROR_RETURN_TRUE(dwConnID != 0);
    ERROR_RETURN_TRUE(dwCopyID != 0);
    CGameSvrMgr::GetInstancePtr()->SendPlayerToCopy(Req.roleid(), 6, dwCopyID, dwSvrID);

    return TRUE;
}
