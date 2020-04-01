#include "STD_TYPES_H.h"
#include "HamadaProtocol.h"
#include "HamadaProtocol_config.h"

#define M3_AIRCR (*((volatile u32*)0xE000ED0C))
#define M3_AIRCR_ENDIAN_OFFSET 15

#define WORD_BYTE_SIZE 					4
#define MAX_DATA_BYTE_LEGTH 			64
#define MAX_DATA_BYTE_LEGTH_PLUS_END 	68
#define NUMBER_OF_BITS_IN_BYTE 			8
#define BYTE_MASK 						0xff
#define MS_BYTE_OFFSET					3
#define STATE_FRAME_BUFFER_SIZE			20
#define DATA_FRAME_BUFFER_SIZE_NO_DATA	20

#define STARTED 				1
#define STATE_FRAME_STARTED 	2
#define DATA_FRAME_STARTED 		3
#define STATE_ID_ACQUIRED 		4
#define DATA_ID_ACQUIRED		5
#define STATE_ACQUIRED			6
#define DATA_LENGTH_ACQUIRED	7

#define FRAME_VIEWER(a)	((frameType*)a)
#define STATE_VIEWER(a)	((Hamada_stateMailBoxType*)a)
#define DATA_VIEWER(a)	((Hamada_dataMailBoxType*)a)

typedef struct stateType
{
	u32 state;
	u32 endWord;
}stateType;

typedef struct dataType
{
	u32 dataLengthWord;
	u32	data[MAX_DATA_BYTE_LEGTH_PLUS_END];
}dataType;

typedef union stateDataUnionType
{
	stateType state;
	dataType data;
}stateDataUnionType;

typedef struct frameType
{
	u32 startWord;
	u32 frameType;
	u32 ID;
	stateDataUnionType stateData;
}frameType;

static u32 bigToLittleEndian(u32 data);

void Hamada_parserObjectInit(Hamada_parserObjectType* object)
{
	object->state=IDLE;
}

Hamada_parserStateType Hamada_frameParse(u8* recivebuffer,Hamada_stateMailBoxType* stateMailbox,Hamada_dataMailBoxType* dataMailbox,Hamada_parserObjectType* object)
{
	u32 temp;
	Hamada_parserStateType currentState;
	/*check if big Endian*/
	/*i=1;*/
	/*if((*((u32*)(&i)))!=1)*/
	if(M3_AIRCR&(1<<M3_AIRCR_ENDIAN_OFFSET))
	{
		temp=bigToLittleEndian(*((u32*)recivebuffer));
	}
	else
	{
		temp=*((u32*)recivebuffer);
	}
	switch(object->state)
	{
	case IDLE:
		if(temp==START_FRAME)
		{
			object->state=STARTED;
			currentState=IDLE;
		}
		else
		{
			currentState=DONE;
		}
		break;
	case STARTED:
		switch(temp)
		{
		case STATE_FRAME:
			object->state=STATE_FRAME_STARTED;
			currentState=IDLE;
			break;
		case DATA_FRAME:
			object->state=DATA_FRAME_STARTED;
			currentState=IDLE;
			break;
		default:
			object->state=IDLE;
			currentState=DONE;
			break;
		}
		break;
	case STATE_FRAME_STARTED:
		stateMailbox->stateID=temp;
		object->state=STATE_ID_ACQUIRED;
		currentState=IDLE;
		break;
	case DATA_FRAME_STARTED:
		dataMailbox->dataID=temp;
		object->state=DATA_ID_ACQUIRED;
		currentState=IDLE;
		break;
	case STATE_ID_ACQUIRED:
		stateMailbox->state=temp;
		object->state=STATE_ACQUIRED;
		currentState=IDLE;
		break;
	case STATE_ACQUIRED:
		if(temp==END_FRAME)
		{
			stateMailbox->flag=MAILBOX_NEMPTY;
		}
		object->state=IDLE;
		currentState=DONE;
		break;
	case DATA_ID_ACQUIRED:
		if(temp>MAX_DATA_BYTE_LEGTH)
		{
			object->state=IDLE;
			currentState=DONE;
		}
		else
		{
			object->dataLengthWord=(u8)temp/WORD_BYTE_SIZE;
			object->state=DATA_LENGTH_ACQUIRED;
			object->dataIndex=0;
			currentState=IDLE;
		}
		break;
	case DATA_LENGTH_ACQUIRED:
		if(object->dataLengthWord==object->dataIndex)
		{
			if(temp==END_FRAME)
			{
				dataMailbox->size=object->dataLengthWord;
			}
			object->state=IDLE;
			currentState=DONE;
		}
		dataMailbox->data[object->dataIndex]=temp;
		object->dataIndex++;
		currentState=IDLE;
		break;
	default:
		currentState=DONE;
	}
	return currentState;
}

Hamada_FrameSizeType Hamada_frameConstructor(u8 *buffer,u8 stateData,void* mailBox)
{
	u8 i;

	if(stateData==FRAME_CONSTRUCTOR_STATE)
	{
		if(M3_AIRCR&(1<<M3_AIRCR_ENDIAN_OFFSET))
		{
			FRAME_VIEWER(buffer)->ID= bigToLittleEndian(STATE_VIEWER(mailBox)->stateID);
			FRAME_VIEWER(buffer)->frameType= bigToLittleEndian(STATE_FRAME);
			FRAME_VIEWER(buffer)->startWord= bigToLittleEndian(START_FRAME);
			FRAME_VIEWER(buffer)->stateData.state.state= bigToLittleEndian(STATE_VIEWER(mailBox)->state);
			FRAME_VIEWER(buffer)->stateData.state.endWord= bigToLittleEndian(END_FRAME);
		}
		else
		{
			FRAME_VIEWER(buffer)->ID=STATE_VIEWER(mailBox)->stateID;
			FRAME_VIEWER(buffer)->frameType=STATE_FRAME;
			FRAME_VIEWER(buffer)->startWord=START_FRAME;
			FRAME_VIEWER(buffer)->stateData.state.state=STATE_VIEWER(mailBox)->state;
			FRAME_VIEWER(buffer)->stateData.state.endWord=END_FRAME;
		}
		i=STATE_FRAME_BUFFER_SIZE;
	}
	else
	{
		if(M3_AIRCR&(1<<M3_AIRCR_ENDIAN_OFFSET))
		{
			FRAME_VIEWER(buffer)->ID=bigToLittleEndian(DATA_VIEWER(mailBox)->dataID);
			FRAME_VIEWER(buffer)->frameType=bigToLittleEndian(DATA_FRAME);
			FRAME_VIEWER(buffer)->startWord=bigToLittleEndian(START_FRAME);
			FRAME_VIEWER(buffer)->stateData.data.dataLengthWord=bigToLittleEndian(DATA_VIEWER(mailBox)->size);
			for(i=0;i<DATA_VIEWER(mailBox)->size;i++)
			{
				FRAME_VIEWER(buffer)->stateData.data.data[i]=bigToLittleEndian(DATA_VIEWER(mailBox)->data[i]);
			}
			FRAME_VIEWER(buffer)->stateData.data.data[i]=bigToLittleEndian(END_FRAME);
		}
		else
		{
			FRAME_VIEWER(buffer)->ID=DATA_VIEWER(mailBox)->dataID;
			FRAME_VIEWER(buffer)->frameType=DATA_FRAME;
			FRAME_VIEWER(buffer)->startWord=START_FRAME;
			FRAME_VIEWER(buffer)->stateData.data.dataLengthWord=DATA_VIEWER(mailBox)->size;
			for(i=0;i<DATA_VIEWER(mailBox)->size;i++)
			{
				FRAME_VIEWER(buffer)->stateData.data.data[i]=DATA_VIEWER(mailBox)->data[i];
			}
			FRAME_VIEWER(buffer)->stateData.data.data[i]=END_FRAME;
		}
		i=(u8)(((u8)DATA_FRAME_BUFFER_SIZE_NO_DATA)+((u8)(DATA_VIEWER(mailBox)->size*((u8)WORD_BYTE_SIZE))));
	}
	return i;
}

u32 bigToLittleEndian(u32 data)
{
	u32 temp;
	u8 i;

	for(i=0;i<WORD_BYTE_SIZE;i++)
	{
		((u8*)(&temp))[MS_BYTE_OFFSET-i]=((u8*)(&data))[i];
	}
	return temp;
}
