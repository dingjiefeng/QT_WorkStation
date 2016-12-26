//
// Created by djf on 2016/12/25 0025.
//

#include <iostream>
#include "block.h"

block::block(int theRow, int theCol,int theTotalBomb):
row(theRow),col(theCol),totalBomb(theTotalBomb),curGameState(PLAYING),restNum(theCol*theRow)
{
    for(int i = 0; i<row;++i)
    {
        vector<unit> perRow;
        for(int j=0;j<col;++j)
        {
            unit perUnit;
            perRow.push_back(perUnit);
        }
        map.push_back(perRow);
    }
    //随机生成一定数量的地雷
    uniform_int_distribution<unsigned> uRow(0,theRow-1);
    uniform_int_distribution<unsigned> uCol(0,theCol-1);
    default_random_engine e(time(0));
    for(int num = 0;num<totalBomb;)
    {
        int i = uRow(e);
        int j = uCol(e);
        if( map[i][j].isBomb==0)
        {
            map[i][j].isBomb = 1;
            ++num;
        }
    }
    calBombNum();
}

bool block::isBomb(int theRow, int theCol) const
{
    return (map[theRow][theCol].isBomb);
}

int block::getRow() const
{
    return row;
}

int block::getCol() const
{
    return col;
}

int block::getBombNum() const
{
    return totalBomb;
}

void block::draw() const
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            unit curUnit = map[i][j];
            switch (curUnit.curState)
            {
                case UNDIGGED:
                    cout << '#';
                    break;
                case DIGGED:
                    if(curUnit.isBomb==0)
                        cout << curUnit.bombNum;
                    else
                        cout << '!';
                    break;
                case REDFLAG:
                    cout << '$';
                    break;
            }
        }
        cout << endl;
    }
}

void block::calBombNum()
{
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
        {
            map[i][j].bombNum = calBombnum(i,j);
        }
    }
}

int block::calBombnum(int theRow, int theCol) const
{
    int num = 0;
    for(int i = -1;i<2;++i)
    {
        for(int j=-1;j<2;++j)
        {
            int curRow = theRow + i;
            int curCol = theCol + j;
            if(curRow>=0&&curRow<row &&
               curCol>=0&&curCol<col &&
               !(curRow==theRow&&curCol==theCol) &&
               map[curRow][curCol].isBomb==1 )
                num++;
        }
    }
    return num;
}

void block::mark(int theRow, int theCol)
{
    unit& curUnit = map[theRow][theCol];
    if(curUnit.curState==DIGGED)
        return;
    else if(curUnit.curState==REDFLAG)
    {
        curUnit.curState = UNDIGGED;
    }else{
        curUnit.curState = REDFLAG;
    }
}

void block::dig(int theRow, int theCol)
{
    unit& curUnit = map[theRow][theCol];
    curUnit.curState = DIGGED;
    restNum--;
    if(curUnit.isBomb==1)
    {
        curGameState = LOSE;
        return;
    }
    if(curUnit.bombNum==0)
    {
        for(int i=-1;i<2;++i)
        {
            for(int j = -1;j<2;++j)
            {
                int curRow = theRow + i;
                int curCol = theCol + j;
                if(curRow>=0&&curRow<row &&
                   curCol>=0&&curCol<col &&
                   map[curRow][curCol].curState!=DIGGED)
                        dig(curRow,curCol);
            }
        }
    }
    if(restNum==totalBomb)
    {
        curGameState = WIN;
    }
}

gameState block::checkGame()
{
    return curGameState;
}




