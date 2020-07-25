#include "clogic.h"
#include "stdafx.h"

clogic::clogic()
{
	m_curLevel = 0;
}
clogic::~clogic()
{
}
;
void clogic::InitMap()
{
	for (int i = 0; i < LatticeNum_L; i++)
	{
		for (int j = 0; j < LatticeNum_H; j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
			{
				m_Lattice[i][j] = Type_Num;
			}
			else
			{
				m_Lattice[i][j] = Type_Num;
			}
		}
	}
}
bool IsHaveNum(int* posArray, int iValue)
{
	while (*posArray!='\0')
	{
		if (*posArray == iValue)
		{
			return true;
		}
		posArray++;
	}
	return false;
}

void clogic::UpdateMap()
{
	int brickNum = c_iBrickNum[m_curLevel];
	m_doorPos.x = 0;
	m_doorPos.y = 0;

	int brickPosArray[100] = { 0 };
	int iRandValue = 1;
	for (int i = 0; i < brickNum;)
	{
		srand(GetTickCount()+iRandValue);
		iRandValue = rand() % LatticeNullNum;
		if (IsHaveNum(brickPosArray, iRandValue))
		{
			continue;
		}
		brickPosArray[i] = iRandValue;
		++i;
	}
	srand(GetTickCount());
	int doorPos = rand() % brickNum;

	int numIndex = 0;
	int doorIndex = 0;
	for (int i = 0; i < LatticeNum_L; ++i)
	{
		for (int j = 0; j < LatticeNum_H; j++)
		{
			if (i<=3&&j<=3||m_Lattice[i][j]==Type_Stone)
			{
				continue;
			}
			if (IsHaveNum(brickPosArray, numIndex))
			{
				m_Lattice[i][j] = Type_Brick;
				if (doorPos==doorIndex)
				{
					m_Lattice[i][j] == Type_Brickdoor;
				}
				doorIndex++;
			}
			numIndex++;
		}
	}

	m_Lattice[1][0] = Type_Man;
	m_fireManPos.x = 0;
	m_fireManPos.y = Lattice_Len;
}

void clogic::GameBegin()
{
	m_curLevel = 0;
	InitMap();
	UpdateMap();
}
