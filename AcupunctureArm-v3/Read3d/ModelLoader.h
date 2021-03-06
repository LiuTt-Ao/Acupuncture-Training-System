#if !defined(AFX_STEWARTLOADER_H__17ABC0D5_3A04_4BBA_A078_1115FD40251D__INCLUDED_)
#define AFX_STEWARTLOADER_H__17ABC0D5_3A04_4BBA_A078_1115FD40251D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "glStructures.h"	//数据结构定义
#include "TriList.h"		//CTriList类说明
#include "TriObject.h"		//CTriObject说明
#include "basicRead.h"		//基本的数据读入函数定义

class ModelLoader
{
public:
	ModelLoader();
	virtual ~ModelLoader();
	int ReadKFTrackTag(long fileSize, long tagStart, long tagSize, FILE * fp, char* nodeName, tVector* pivot, Chunk3DS chunk);
	int ReadKFObjectNode(long fileSize, long nodeStart, long nodeSize, FILE* fp);
	int ReadKFDATA(long fileSize, long kfdataStart, long kfdataSize, FILE* fp);
	int Read3DSChunk(FILE* fp, Chunk3DS& chunk);
	int Read3DSString(FILE* fp, char* name, int len = 256);
	int ReadPercentage(FILE* fp, float& value);
	int ReadColor(FILE* fp, float& red, float& green, float& blue);
	int ReadPointArray(CTriObject*	newchild, long fileSize, FILE *fp);
	int ReadFaceArray(CTriObject* newchild, long unsigned fileSize, FILE* fp);
	int ReadMeshMatGroup(CTriObject* newchild, MaterialDict* matdict, long fileSize, FILE* fp);
	int ReadTriObject(MaterialDict* matdict, long fileSize, FILE* fp, long triStart, long triSize, char* groupName);
	int ReadNamedObject(MaterialDict* matdict, long fileSize, long namedStart, long namedSize, FILE* fp);
	int ReadMatEntry(MaterialDict* matdict, long fileSize, long matStart, long matSize, FILE* fp);
	int ReadMDATA(MaterialDict* matdict, long fileSize, long mdataStart, long mdataSize, FILE* fp);
	int Read3DSFile(long fileSize, long fileStart, long fileLen, FILE* fp);
	int Is3DSFile(FILE* fp);
	BOOL Reader(char* filename, CTriList* _list);

private:
	CTriList* DaList;
};


#endif // !defined(AFX_STEWARTLOADER_H__17ABC0D5_3A04_4BBA_A078_1115FD40251D__INCLUDED_)