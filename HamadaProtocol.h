#ifndef HAMADAPROTOCOL_H_
#define HAMADAPROTOCOL_H_

#define MAX_DATA_MAIL_BOX_SIZE 	16
#define MAX_FRAME_BYTE_SIZE 	84


#define IDLE 0
#define DONE 1

#define FRAME_CONSTRUCTOR_STATE 0
#define FRAME_CONSTRUCTOR_DATA 	1

#define MAILBOX_EMPTY 	0
#define MAILBOX_NEMPTY 	1

typedef struct Hamada_stateMailBoxType
{
	u32 state;
	u32 stateID;
	u8 flag;
}Hamada_stateMailBoxType;

typedef struct Hamada_dataMailBoxType
{
	u32 data[MAX_DATA_MAIL_BOX_SIZE];
	u32 dataID;
	u8 size;
}Hamada_dataMailBoxType;

typedef u8 Hamada_FrameSizeType;

typedef struct Hamada_parserObjectType
{
	u8 state;
	u8 dataLengthWord;
	u8 dataIndex;
}Hamada_parserObjectType;

typedef u8 Hamada_parserStateType ;

void Hamada_parserObjectInit(Hamada_parserObjectType* object);
Hamada_parserStateType Hamada_frameParse(u8* recivebuffer,Hamada_stateMailBoxType* stateMailbox,Hamada_dataMailBoxType* dataMailbox,Hamada_parserObjectType* object);
Hamada_FrameSizeType Hamada_frameConstructor(u8 *buffer,u8 stateData,void* mailBox);

#endif /* HAMADAPROTOCOL_H_ */
