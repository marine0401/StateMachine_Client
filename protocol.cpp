
#include <QDebug>

#include "protocol.h"

/**
 * @brief getMacAddress
 * @param errorMsg{@link eErrorMsg}
 * @return
 */
QByteArray getMacAddress(eErrorMsg *errorMsg)
{
    int packetLen = sizeof(Packet) + 1; // 1个字节给 data
    Packet *protocolPacket = (Packet * )malloc(packetLen);
    memset(protocolPacket, 0 , packetLen);
    if(nullptr == protocolPacket)
    {
        if(errorMsg != nullptr)
        {
           *errorMsg = MALLOC_ERROR;
        }
        return nullptr;
    }
    protocolPacket->sync = SYNC;
    protocolPacket->length = packetLen;
    protocolPacket->cmdID = GET_MESSAGE;
    protocolPacket->data[0] = MAC_ADDRESS;
    QByteArray packet((char *)protocolPacket, packetLen);
    free(protocolPacket); // 记得释放内存
    if(errorMsg != nullptr)
    {
        *errorMsg = MALLOC_SUCCESS;
    }

    return packet;
}

