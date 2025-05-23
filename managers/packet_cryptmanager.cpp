#include "packet_cryptmanager.h"
#include "usermanager.h"
#include "serverconsole.h"

Packet_CryptManager packet_CryptManager;

void Packet_CryptManager::ParsePacket_RecvCrypt(TCPConnection::Packet::pointer packet) {
	User* user = userManager.GetUserByConnection(packet->GetConnection());
	if (!userManager.IsUserLoggedIn(user)) {
		serverConsole.Print(PrefixType::Warn, format("[ Packet_CryptManager ] Client ({}) has sent Packet_RecvCrypt, but it's not logged in!\n", packet->GetConnection()->GetIPAddress()));
		return;
	}

	serverConsole.Print(PrefixType::Info, format("[ Packet_CryptManager ] User ({}) has sent Packet_RecvCrypt\n", user->GetUserLogName()));
}

void Packet_CryptManager::SendPacket_Crypt(TCPConnection::pointer connection, CipherType type, const Cipher& cipher) {
	auto packet = TCPConnection::Packet::Create(PacketSource::Server, connection, { (unsigned char)PacketID::Crypt });

	packet->WriteUInt8(type);
	packet->WriteUInt8(cipher.method);

	if (cipher.method != CipherMethod::CleanUp && cipher.method != CipherMethod::CleanUp2) {
		packet->WriteArray_UInt8(vector<unsigned char>(cipher.key, cipher.key + KEY_SIZE));
		packet->WriteArray_UInt8(vector<unsigned char>(cipher.iv, cipher.iv + BLOCK_SIZE));
	}

	packet->Send();
}