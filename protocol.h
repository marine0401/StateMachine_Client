#ifndef PROTOCOL_H
#define PROTOCOL_H
#define SYNC 0x57
struct packet{
    unsigned char sync;
    unsigned short length;
    unsigned char cmdID;
    unsigned char data[0];
}__attribute__((gcc_struct,packed));
typedef struct packet Packet;



#endif // PROTOCOL_H
