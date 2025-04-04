#pragma once
#include "room.h"

#define ROOMLIST_FLAG_ROOMNAME			0x1
#define ROOMLIST_FLAG_UNK2				0x2
#define ROOMLIST_FLAG_ISPASSWORDED		0x4
#define ROOMLIST_FLAG_LEVELLIMIT		0x8
#define ROOMLIST_FLAG_GAMEMODEID		0x10
#define ROOMLIST_FLAG_MAPID				0x20
#define ROOMLIST_FLAG_CURRENTPLAYERS	0x40
#define ROOMLIST_FLAG_MAXPLAYERS		0x80
#define ROOMLIST_FLAG_WEAPONLIMIT		0x100
#define ROOMLIST_FLAG_UNK200			0x200
#define ROOMLIST_FLAG_UNK400			0x400
#define ROOMLIST_FLAG_UNK800			0x800
#define ROOMLIST_FLAG_UNK1000			0x1000
#define ROOMLIST_FLAG_UNK2000			0x2000
#define ROOMLIST_FLAG_UNK4000			0x4000
#define ROOMLIST_FLAG_ALL				0xFFFF

enum Packet_RoomType {
	RequestCreate = 0,
	ReplyCreateAndJoin = 0,
	RequestJoin = 1,
	RequestLeave = 2,
	RequestStartGame = 4,
	ReplyLeaveRoom = 4,
	ReplyLeaveRoomInGame = 10
};

enum Packet_RoomListType {
	FullRoomList = 0
};

class Packet_RoomManager {
public:
	void ParsePacket_Room(TCPConnection::Packet::pointer packet);
	void SendPacket_RoomList_FullRoomList(TCPConnection::pointer connection, const vector<Room*>& rooms, unsigned short flag);

private:
	void parsePacket_Room_RequestCreate(User* user, TCPConnection::Packet::pointer packet);
	void parsePacket_Room_RequestStartGame(User* user);
	void parsePacket_Room_RequestLeave(User* user);
	void buildRoomSettings(TCPConnection::Packet::pointer packet, const RoomSettings& roomSettings);
	void sendPacket_Room_ReplyCreateAndJoin(TCPConnection::pointer connection, Room* room, const vector<UserFull>& roomUsers);
	void sendPacket_Room_ReplyLeaveRoom(User* user);
	void sendPacket_Room_ReplyLeaveRoomInGame(TCPConnection::pointer connection);
};

extern Packet_RoomManager packet_RoomManager;