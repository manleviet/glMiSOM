//
//
// winnerinfo.h
//
// LE Viet Man
// 28/07/2011
//
//

#include "winnerinfo.h"

WinnerInfo::WinnerInfo()
{
    image = 0;
    winner = 0;
    index = -1;
    diff = DBL_MAX;
}

WinnerInfo::~WinnerInfo()
{
    image = 0;
    winner = 0;
}

bool WinnerInfo::isNoWinner()
{
    if (index == -1) return true;
    return false;
}

void WinnerInfo::setWinner(EntrySOM *w, long ind, double d)
{
    winner = w;
    index = ind;
    diff = d;
}

void WinnerInfo::setWinner(Image *img, long ind, double d)
{
    image = img;
    index = ind;
    diff = d;
}
