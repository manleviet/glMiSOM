//
//
// winnerinfo.h
//
// LE Viet Man
// 28/07/2011
//
//

#ifndef WINNERINFO_H
#define WINNERINFO_H

#include "entrysom.h"
#include "Core/image.h"

class WinnerInfo
{
public:
    WinnerInfo();
    ~WinnerInfo();

    bool isNoWinner();

    void setWinner(EntrySOM *w, long ind, double d);
    void setWinner(Image *img, long ind, double d);

    Image* getImage() { return image; }
    EntrySOM* getWinner() { return winner; }
    long getIndex() { return index; }
    double getDiff() { return diff; }

private:
    // for rearrange
    Image *image;
    // for SOM
    EntrySOM *winner;
    // for both
    long index;
    double diff;
};

#endif // WINNERINFO_H
