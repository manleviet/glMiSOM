//
//
// mapsom.h
//
// LE Viet Man
// 28/07/2011
//
//

#include "mapsom.h"

MapSOM::MapSOM(BaseImage *base)
{
    this->base = base;
    extractors.clear();
    gridSOM = 0;
    gridRearr = 0;

    resetToDefaultValues();
}

MapSOM::~MapSOM()
{
    base = 0;
    delete feaChosenList;
    gridSOM = 0;
    gridRearr = 0;

    while (!codes.empty())
    {
        delete codes.takeFirst();
    }
}

void MapSOM::setBaseImage(BaseImage *base)
{
    this->base = base;
}

EntrySOM* MapSOM::getCode(int index)
{
    if ((index < 0) || (index >= numCodes))
        return NULL;
    return codes[index];
}

void MapSOM::addExtractors(QList<ExtractorInterface *> extractors)
{
    this->extractors = extractors;
}

void MapSOM::resetToDefaultValues()
{
    codes.clear();
    dim = 0;
    //xdim = ydim = Util::computeNumberNeurons(base->getSizeOfDB());
    xdim = ydim = Util::computeNumberNeuronsAdapt(base->getSizeOfDB());
    numCodes = xdim * ydim;
    type_neigh = NEIGH_GAUSSIAN;
    type_alpha = ALPHA_LINEAR;
    radiusOrdering = 10;
    radiusConver = 3;
    alphaOrdering = 0.05;
    alphaConver = 0.02;
    lengthOrdering = 1000;
    lengthConver = 10000;
    lengthRearrange = 1;
    next = 1;
    feaChosenList = 0;
}

#include "iostream"
using namespace std;

void MapSOM::init(QProgressDialog &progress, int &count, FeaturesChosenList *chosenList, int xdim, int ydim, NEIGH_TYPE typeNeigh, ALPHA_TYPE typeAlpha, int randomize)
{
    feaChosenList = chosenList;
    this->xdim = xdim;
    this->ydim = ydim;
    numCodes = xdim * ydim;
    type_neigh = typeNeigh;
    type_alpha = typeAlpha;

    int index, numFea, size, sizeFea;
    double value;
    QStringList feaCoded;
    Image *img;
    Feature *fea, *newFea;
    Feature *imgFea, *maFea, *miFea;
    EntrySOM *entry, *maval, *mival;

    // calculer la dimension de vecteur
    progress.setValue(++count);
    progress.show();

    dim = 0;
    numFea = feaChosenList->getSize();
    img = base->getImage(0);
    for (int i = 0; i < numFea; i++)
    {
        fea = img->getFeature(feaChosenList->getIndex(i));
        dim += fea->getSize();
    }

    progress.setValue(++count);
    progress.show();

    codes.clear();
    index = -1;
    feaCoded = base->getFeatureCodedList();
    // initier codes
    for (int i = 0; i < numCodes; i++)
    {
        entry = new EntrySOM(i, dim);

        for (int j = 0; j < numFea; j++)
        {
            index = feaChosenList->getIndex(j);
            fea = img->getFeature(index);

            newFea = new Feature(feaCoded[index], fea->getSize());

            entry->addFeature(index, newFea, feaChosenList->getWeight(j));
        }

        codes << entry;
    }

    init_random(randomize);

    progress.setValue(++count);
    progress.show();

    maval = createEntrySOM(DBL_MIN);
    mival = createEntrySOM(DBL_MAX);

    //cout << "maval" << endl;
    //printEntrySOM(maval);
    //cout << "mival" << endl;
    //printEntrySOM(mival);

    progress.setValue(++count);
    progress.show();

    size = base->getSizeOfDB();
    for (int i = 0; i < size; i++)
    {
        img = base->getImage(i);

        for (int j = 0; j < numFea; j++)
        {
            index = feaChosenList->getIndex(j);
            imgFea = img->getFeature(index);
            maFea = maval->getFeature(j);
            miFea = mival->getFeature(j);

            if (imgFea->getDescriptor() != maFea->getDescriptor())
            {
                dim = 0;
                codes.clear();
                throw std::bad_exception();
            }

            sizeFea = imgFea->getSize();
            for (int k = 0; k < sizeFea; k++)
            {
                if (maFea->getValue(k) < imgFea->getValue(k))
                {
                    maFea->setValue(k, imgFea->getValue(k));
                }
                if (miFea->getValue(k) > imgFea->getValue(k))
                {
                    miFea->setValue(k, imgFea->getValue(k));
                }
            }
        }
    }

    progress.setValue(++count);
    progress.show();

    for (int i = 0; i < numCodes; i++)
    {
        entry = codes[i];

        for (int j = 0; j < numFea; j++)
        {
            fea = entry->getFeature(j);
            miFea = mival->getFeature(j);
            maFea = maval->getFeature(j);

            if (fea->getDescriptor() != miFea->getDescriptor())
            {
                dim = 0;
                codes.clear();
                throw std::bad_exception();
            }

            sizeFea = fea->getSize();
            for (int k = 0; k < sizeFea; k++)
            {
                value = miFea->getValue(k) +
                        (maFea->getValue(k) - miFea->getValue(k)) * ((double) orand() / 32768.0);

                fea->setValue(k, value);
            }
        }
    }

    img = 0;
    fea = newFea = imgFea = miFea = maFea = 0;
    entry = maval = mival = 0;
}

void MapSOM::training(QProgressDialog &progress, int &count, TRAINING_TYPE typeTraining, long length, double radius, double alpha)
{
    QString message;
    switch (typeTraining)
    {
    case ORDERING:
        radiusOrdering = radius;
        alphaOrdering = alpha;
        lengthOrdering = length;
        message = QString("Ordering phase...");
        break;
    case CONVERGENCE:
        radiusConver = radius;
        alphaConver = alpha;
        lengthConver = length;
        message = QString("Convergence phase...");
        break;
    }

    long le;
    int index, size = base->getSizeOfDB();
    double trad, talp;
    int bxind, byind;
    WinnerInfo *winner;
    Image *img;

    for (le = 0; le < length; le++)
    {
        progress.setLabelText( QString("%1 step %2...").arg(message).arg(le) );
        progress.setValue(++count);
        progress.show();

        // si le nombre de boucles est plus grand que le nombre des images
        // on doit repeter
        index = le % size;
        img = base->getImage(index);

        trad = 1.0 + (radius - 1.0) * (double)(length - le) / (double)length;

        if (type_alpha == ALPHA_LINEAR)
        {
            talp = getAlphaLinear(le, length, alpha);
        }
        else if (type_alpha == ALPHA_INVERSE_T)
        {
            talp = getAlphaInverseT(le, length, alpha);
        }

        // find the best match
        winner = findWinnerEuc(img);

        if (!winner->isNoWinner())
        {
            bxind = winner->getIndex() / ydim;
            byind = winner->getIndex() % ydim;
        }
        else
        {
            continue;
        }

        if (type_neigh == NEIGH_BUBBLE)
        {
            bubble_adapt(img, bxind, byind, trad, talp);
        }
        else if (type_neigh == NEIGH_GAUSSIAN)
        {
            gaussian_adapt(img, bxind, byind, trad, talp);
        }

        delete winner;
    }

    winner = 0;
    img = 0;
}

GridSOM* MapSOM::visual(QProgressDialog &progress, int &count)
{
    // creer un nouveau gridSOM
    gridSOM = new GridSOM(xdim, ydim);

    WinnerInfo *winner;

    int size = base->getSizeOfDB();
    Image *img = 0;
    int x, y;
    double diff;
    for (int i = 0; i < size; i++)
    {
        progress.setValue(++count);
        progress.show();

        img = base->getImage(i);
        winner = findWinnerEuc(img);

        if (!winner->isNoWinner())
        {
            x = winner->getIndex() / ydim;
            y = winner->getIndex() % ydim;
            diff = winner->getDiff();

            gridSOM->addImage(x, y, img, diff);
        }

        delete winner;
    }
    winner = 0;
    img = 0;

    return gridSOM;
}

GridSOM* MapSOM::rearrange(QProgressDialog &progress, int &count, long length, GridSOM *grid)
{
    if ((grid->getXDim() != xdim) || (grid->getYDim() != ydim)) return NULL;

    lengthRearrange = length;
    // 1. Initialisation
    gridRearr = new GridSOM(xdim, ydim);
    gridRearr->copy(grid);
    bool** S = createStableTable();
    bool* p = createPrioriteTable();

    StableInfo *stable;
    EntrySOM *entry;
    CellSOM *cell;
    int l; // quantite des images
    int x, y;
    QList<Image*> imgs;
    QList<Image*> P; // un ensemble des images de priorite
    QList<Image*> R; // un ensemble des images de sans priorite
    WinnerInfo *winner;
    QList<EntrySOM*> neighs;
    double d;
    int max;
    while (true)
    {
    // 2. Chercher une case qui peut devenir stable
        stable = findCasesStable(gridRearr, S);

        if (stable == NULL) break;

        max = progress.maximum() + 1;
        progress.setMaximum(max);
        progress.setValue(++count);
        progress.show();

    // 3. Choisir l'image a conserver
        entry = stable->getEntry();
        cell = stable->getCell();
        x = stable->getX();
        y = stable->getY();

        l = cell->getQuantityOfImages();
        imgs = cell->getAllImage();

        getImagePriorite(imgs, p, P, R);

        if (P.isEmpty())
        {
            winner = findWinnerEuc(entry, R);

            if (winner->isNoWinner())
            {
                throw std::bad_exception();
                return NULL;
            }

            removeWinnerOutR(winner, R);
        }
        else
        {
            winner = findWinnerEuc(entry, P);
            if (winner->isNoWinner())
            {
                throw std::bad_exception();
                return NULL;
            }

            addRemainInPToR(winner, P, R);
        }

        // reserver l'image gagnee
        // effacer le reste d'images dans cette casse
        cell->removeAllExceptWinner(winner);
        // mettre true a la table S
        S[x][y] = true;

    // 4. Rearranger les images de reste
        neighs = getNeighbours(x, y, S);

        if (neighs.isEmpty())
        {
            foreach (Image *img, R)
            {
                d = distanceEuc(img, entry);
                cell->addImage(img, d);
            }
        }
        else
        {
            foreach(Image *img, R)
            {
                winner = findWinnerEuc(img, neighs);

                if (winner->isNoWinner())
                {
                    throw std::bad_exception();
                    return NULL;
                }
                else
                {
                    x = winner->getIndex() / ydim;
                    y = winner->getIndex() % ydim;
                    d = winner->getDiff();

                    gridRearr->addImage(x, y, img, d);
                    p[img->getId()] = true;
                }
            }
        }

        delete stable;
        stable = 0;
    }
    stable = 0;
    entry = 0;
    cell = 0;

    //printGridSOM(newgrid);
    //printGridSOMtoFile(gridRearr);

    // bien re-arranger ?
    resetStableTable(S);

    stable = findCasesStable(gridRearr, S);

    if ((stable != NULL) && (--length > 0))
    {
        progress.setValue(++count);
        progress.show();

        gridRearr = rearrange(progress, count, length, gridRearr);
    }

    deleteStableTable(S);
    deletePrioriteTable(p);
    return gridRearr;
}

void MapSOM::init_random(int seed)
{
    if (!seed)
        osrand((int) time(NULL));
    else
        osrand(seed);
}

void MapSOM::osrand(int i)
{
    next = i;
}

int MapSOM::orand()
{
    return (int)((next = (next * 23) % 100000001) % RND_MAX);
}

EntrySOM* MapSOM::createEntrySOM(double value)
{
    EntrySOM *entry = new EntrySOM(0, dim);

    int index, size;
    int numFea = feaChosenList->getSize();
    Feature *fea, *newFea;
    Image *img = base->getImage(0);
    double *tmp;
    QStringList feaCoded = base->getFeatureCodedList();
    for (int j = 0; j < numFea; j++)
    {
        index = feaChosenList->getIndex(j);
        fea = img->getFeature(index);
        size = fea->getSize();

        // initier entry avec value
        tmp = (double*)malloc(sizeof(double) * size);
        memset(tmp, 0, sizeof(double) * size);

        for (int i = 0; i < size; i++)
        {
            tmp[i] = value;
        }

        newFea = new Feature(feaCoded[index], size, tmp);
        free(tmp);
        tmp = 0;

        entry->addFeature(index, newFea);
    }
    fea = newFea = 0;
    img = 0;

    return entry;
}

WinnerInfo* MapSOM::findWinnerEuc(Image *img)
{
    WinnerInfo *winner = new WinnerInfo();

    double diffsf, difference;
    diffsf = DBL_MAX;
    EntrySOM *entry;
    Feature *fea, *imgFea;
    for (int i = 0; i < numCodes; i++)
    {
        entry = codes[i];

        difference = distanceEuc(img, entry);

        if (difference < diffsf)
        {
            winner->setWinner(entry, i, difference);

            diffsf = difference;
        }
    }
    entry = 0;
    fea = imgFea = 0;

    return winner;
}

double MapSOM::distanceEuc(Feature *fea1, Feature *fea2)
{
    double diff;

    foreach (ExtractorInterface *ext, extractors)
    {
        if (ext->isMyDescriptor(fea1->getDescriptor()))
            diff = ext->calDistanceEuc(fea1, fea2);
    }

    return diff;
}

double MapSOM::distanceEuc(Image *img1, Image *img2)
{
    double diff, difference = 0;
    Feature *fea1, *fea2;
    int index;

    for (int j = 0; j < feaChosenList->getSize(); j++)
    {
        index = feaChosenList->getIndex(j);
        fea1 = img1->getFeature(index);
        fea2 = img2->getFeature(index);

        if (fea1->getDescriptor() != fea2->getDescriptor())
        {
            throw std::bad_exception();
        }

        diff = qSqrt(distanceEuc(fea1, fea2));

        difference += feaChosenList->getWeight(j) * diff;
    }

    return difference;
}

double MapSOM::distanceEuc(Image *img, EntrySOM *entry)
{
    double diff, difference = 0;
    Feature *fea, *imgFea;
    int index;
    for (int j = 0; j < feaChosenList->getSize(); j++)
    {
        index = feaChosenList->getIndex(j);
        fea = entry->getFeature(j);
        imgFea = img->getFeature(index);

        if (fea->getDescriptor() != imgFea->getDescriptor())
        {
            throw std::bad_exception();
        }

        diff = qSqrt(distanceEuc(fea, imgFea));

        difference += feaChosenList->getWeight(j) * diff;
    }

    return difference;
}

double MapSOM::distanceEuc(EntrySOM *entry1, EntrySOM *entry2)
{
    double diff, difference = 0;
    Feature *fea1, *fea2;
    for (int j = 0; j < feaChosenList->getSize(); j++)
    {
        fea1 = entry1->getFeature(j);
        fea2 = entry2->getFeature(j);

        if (fea1->getDescriptor() != fea2->getDescriptor())
        {
            throw std::bad_exception();
        }

        diff = qSqrt(distanceEuc(fea1, fea2));

        difference += feaChosenList->getWeight(j) * diff;
    }

    return difference;
}

// FONCTIONS POUR L'APPRENTISSAGE

double MapSOM::getAlphaLinear(long iter, long length, double alpha)
{
    return (alpha * (double) (length - iter) / (double) length);
}

#define INV_ALPHA_CONSTANT 100.0

double MapSOM::getAlphaInverseT(long iter, long length, double alpha)
{
    double c;

    c = length / INV_ALPHA_CONSTANT;

    return (alpha * c / (c + iter));
}

void MapSOM::bubble_adapt(Image *img, int bx, int by, double radius, double alpha)
{
    int tx, ty;
    EntrySOM *entry;
    for (int i = 0; i < numCodes; i++)
    {
        tx = i / ydim;
        ty = i % ydim;

        if (rect_dis(bx, by, tx, ty) <= radius)
        {
            entry = codes[i];

            adapt_vector(entry, img, alpha);
        }
    }
    entry = 0;
}

void MapSOM::gaussian_adapt(Image *img, int bx, int by, double radius, double alpha)
{
    int tx, ty;
    double dd, alp;
    EntrySOM *entry;
    for (int i = 0; i < numCodes; i++)
    {
        tx = i / ydim;
        ty = i % ydim;

        dd = rect_dis(bx, by, tx, ty);

        alp = alpha * (double) qExp((double) (-dd * dd / (2.0 * radius * radius)));

        entry = codes[i];

        adapt_vector(entry, img, alp);
    }
    entry = 0;
}

double MapSOM::rect_dis(int bx, int by, int tx, int ty)
{
    double ret, diff;

    diff = bx - tx;
    ret = diff * diff;
    diff = by - ty;
    ret += diff * diff;
    ret = (double) qSqrt((double) ret);

    return ret;
}

void MapSOM::adapt_vector(EntrySOM *entry, Image *img, double alpha)
{
    int size = feaChosenList->getSize();
    Feature *fea, *imgFea;
    int index;

    for (int i = 0; i < size; i++)
    {
        index = feaChosenList->getIndex(i);
        fea = entry->getFeature(i);
        imgFea = img->getFeature(index);

        if (fea->getDescriptor() != imgFea->getDescriptor())
        {
            throw std::bad_exception();
        }

        foreach (ExtractorInterface *ext, extractors)
        {
            if (ext->isMyDescriptor(fea->getDescriptor()))
                ext->adapt(fea, imgFea, alpha);
        }
    }
    fea = imgFea = 0;
}

// FONCTIONS POUR LE RE-ARRANGEMENT

bool** MapSOM::createStableTable()
{
    bool** s;
    s = (bool**)malloc(sizeof(bool*) * xdim);
    for (int i = 0; i < xdim; i++)
    {
        s[i] = (bool*)malloc(sizeof(bool) * ydim);
        memset(s[i], false, sizeof(bool) * ydim);
    }
    return s;
}

void MapSOM::resetStableTable(bool **S)
{
    for (int i = 0; i < xdim; i++)
    {
        memset(S[i], false, sizeof(bool) * ydim);
    }
}

void MapSOM::deleteStableTable(bool **s)
{
    if (s != 0)
    {
        for (int i = 0; i < xdim; i++)
        {
            free(s[i]);
        }
        free(s);
    }
    s = 0;
}

bool* MapSOM::createPrioriteTable()
{
    bool* p;
    p = (bool*)malloc(sizeof(bool) * base->getSizeOfDB());
    memset(p, false, sizeof(bool) * base->getSizeOfDB());
    return p;
}

void MapSOM::deletePrioriteTable(bool *p)
{
    if (p != 0)
    {
        free(p);
    }
    p = 0;
}

StableInfo* MapSOM::findCasesStable(GridSOM *grid, bool** s)
{
    // chercher le maximum nombre d'images dans une casse
    int max = grid->getMaxNumImages(s);

    if (max == 1)
    {
        return NULL;
    }

    // chercher des stables casses
    QList<StableInfo*> list = grid->getStableCell(max, s, this);

    // choisir aleatoire une stable casse
    int size = list.size();
    int index = qrand() % size;

    return list[index];
}

void MapSOM::getImagePriorite(QList<Image *> imgs, bool *p, QList<Image *> &P, QList<Image *> &R)
{
    int index;
    QList<Image*> tP, tR;
    foreach (Image *img, imgs)
    {
        index = img->getId();

        if (p[index]) tP << img;
        else tR << img;
    }
    P = tP;
    R = tR;
}

WinnerInfo* MapSOM::findWinnerEuc(EntrySOM *entry, QList<Image *> imgs)
{
    WinnerInfo *winner = new WinnerInfo();

    double diffsf, difference;
    diffsf = DBL_MAX;
    Feature *fea, *imgFea;
    foreach (Image *img, imgs)
    {
        difference = distanceEuc(img, entry);

        if (difference < diffsf)
        {
            winner->setWinner(img, img->getId(), difference);

            diffsf = difference;
        }
    }
    entry = 0;
    fea = imgFea = 0;

    return winner;
}

void MapSOM::addRemainInPToR(WinnerInfo *winner, QList<Image *> P, QList<Image *> &R)
{
    foreach (Image *img, P)
    {
        if (!img->isEqual(winner->getImage()))
        {
            R << img;
        }
    }
}

void MapSOM::removeWinnerOutR(WinnerInfo *winner, QList<Image *> &R)
{
    QList<Image*> tR;
    foreach (Image *img, R)
    {
        if (!img->isEqual(winner->getImage()))
        {
            tR << img;
        }
    }
    R = tR;
}

QList<EntrySOM*> MapSOM::getNeighbours(int x, int y, bool** s)
{
    QList<EntrySOM*> list;
    long index, i, j;

    int X[] = { -1, -1, -1,  0, 0,  1, 1, 1 };
    int Y[] = { -1,  0,  1, -1, 1, -1, 0, 1 };

    for (int k = 0; k < 8; k++)
    {
        i = x + X[k];
        if ((i == -1) || (i == xdim)) continue;
        j = y + Y[k];
        if ((j == -1) || (j == ydim)) continue;

        if (!s[i][j])
        {
            index = i * ydim + j;
            list << codes[index];
        }
    }

    return list;
}

WinnerInfo* MapSOM::findWinnerEuc(Image *img, QList<EntrySOM *> entries)
{
    WinnerInfo *winner = new WinnerInfo();

    double diffsf, difference;
    diffsf = DBL_MAX;
    Feature *fea, *imgFea;
    foreach (EntrySOM *entry, entries)
    {
        difference = distanceEuc(img, entry);

        if (difference < diffsf)
        {
            winner->setWinner(entry, entry->getId(), difference);

            diffsf = difference;
        }
    }
    fea = imgFea = 0;

    return winner;
}

// FONCTIONS POUR LE TEST

void MapSOM::printEntrySOM(EntrySOM *entry)
{
    int numFea = feaChosenList->getSize();
    Feature *fea;
    for (int i = 0; i < numFea; i++)
    {
        fea = entry->getFeature(i);
        cout << fea->getFeature().toStdString() << endl;
    }
}

void MapSOM::printGridSOM(GridSOM *grid)
{
    CellSOM *cell;
    QList<Image*> imgs;
    Image *img;
    for (int i = 0; i < grid->getXDim(); i++)
    {
        for (int j = 0; j < grid->getYDim(); j++)
        {
            cell = grid->getCell(i, j);
            imgs = cell->getAllImage();

            cout << "<" << i << "," << j << "> ";

            for (int k = 0; k < imgs.size(); k++)
            {
                img = imgs[k];
                cout << img->getName().toStdString() << " ";
            }
            cout << endl;
        }
    }
    cell = 0;
    img = 0;
}

void MapSOM::printGridSOMtoFile(GridSOM *grid)
{
    QFile file(Util::getPathFileSOM());
    bool append = false;
    if (file.exists())
    {
        append = true;
        if (!file.open(QFile::Append | QFile::Text))
            throw std::bad_exception();
    }
    else
    {
        if (!file.open(QFile::WriteOnly | QFile::Text))
            throw std::bad_exception();
    }

    QTextStream out(&file);

    CellSOM *cell;
    QList<Image*> imgs;
    Image *img;
    for (int i = 0; i < grid->getXDim(); i++)
    {
        for (int j = 0; j < grid->getYDim(); j++)
        {
            cell = grid->getCell(i, j);
            imgs = cell->getAllImage();

            out << "<" << i << "," << j << "> ";

            for (int k = 0; k < imgs.size(); k++)
            {
                img = imgs[k];
                out << img->getName() << " ";
            }
            out << endl;
        }
        flush(out);
    }
    cell = 0;
    img = 0;
}

// SAVE MAP

//
// Enregistrer le mapSOM sur le fichier map.meta
// il overridera le exite fichier
//
void MapSOM::save()
{
    // ouvrir le fichier map.meta
    QFile file(Util::getFileMapMeta(base->getPathMetadata()));

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        throw std::bad_exception();
    }

    // ecrire les informations sur le fichier
    QTextStream out(&file);

    // header
    saveHeader(out);

    // codes
    if (!codes.isEmpty())
    {
        saveCodes(out);
    }

    // gridSOM
    if (gridSOM != 0)
    {
        out << QString("#4 gridSOM\n");
        saveGrid(out, gridSOM);
    }

    // gridRearr
    if (gridRearr != 0)
    {
        out << QString("#5 gridRearrangement\n");
        saveGrid(out, gridRearr);
    }

    file.close();
}

void MapSOM::saveWeight(QString filename)
{
    if (codes.isEmpty())
    {
        throw std::bad_exception();
    }

    // ouvrir le fichier map.meta
    QFile file(filename);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        throw std::bad_exception();
    }

    // ecrire les informations sur le fichier
    QTextStream out(&file);

    // header
    saveHeader(out);

    // codes
    saveCodes(out);
}

void MapSOM::saveHeader(QTextStream &out)
{
    out << QString("database %1\n").arg(base->getNameOfDB()); // premiere ligne est le nom de base
    out << QString("size %1\n").arg(base->getSizeOfDB()); // deuxieme ligne est le nombre d'images

    if (feaChosenList == 0) return;

    out << QString("#1 Choosen descriptors\n");

    QStringList codedList = base->getFeatureCodedList();
    int index;
    double weight;

    out << QString("%1\n").arg(feaChosenList->getSize());
    for (int i = 0; i < feaChosenList->getSize(); i++)
    {
        index = feaChosenList->getIndex(i);
        weight = feaChosenList->getWeight(i);

        out << QString("%1 %2\n").arg(codedList[index]).arg(weight);
    }

    out << QString("#2 Params of SOM\n");
    out << QString("xdim %1\n").arg(xdim);
    out << QString("ydim %1\n").arg(ydim);
    out << QString("neightype %1\n").arg((type_neigh == NEIGH_BUBBLE) ? QString("bubble") : QString("gaussian"));
    out << QString("radiusOrdering %1\n").arg(radiusOrdering);
    out << QString("alphaOrdering %1\n").arg(alphaOrdering);
    out << QString("lengthOrdering %1\n").arg(lengthOrdering);
    out << QString("radiusConver %1\n").arg(radiusConver);
    out << QString("alphaConver %1\n").arg(alphaConver);
    out << QString("lengthConver %1\n").arg(lengthConver);
    out << QString("alphatype %1\n").arg((type_alpha == ALPHA_LINEAR) ? QString("linear") : QString("inverse_t"));
    out << QString("radomize %1\n").arg(next);
    out << QString("lengthRearrange %1\n").arg(lengthRearrange);
}

void MapSOM::saveCodes(QTextStream &out)
{
    if (codes.isEmpty()) return;

    out << QString("#3 codes\n");
    out << QString("dim %1\n").arg(dim);

    int size = feaChosenList->getSize();
    Feature *fea;
    QString descriptor;
    foreach (EntrySOM *entry, codes)
    {
        descriptor = "";
        for (int i = 0; i < size; i++)
        {
            fea = entry->getFeature(i);
            descriptor += QString("%1;").arg(fea->getFeature());
        }
        descriptor.remove(descriptor.size() - 1, 1);

        out << QString("%1\n").arg(descriptor);
    }
    fea = 0;
}

void MapSOM::saveGrid(QTextStream &out, GridSOM *grid)
{
    int xdim = grid->getXDim();
    int ydim = grid->getYDim();

    CellSOM *cell;
    QList<Image*> imgs;
    QList<double> diffs;
    QColor color;
    for (int i = 0; i < xdim; i++)
    {
        for (int j = 0; j < ydim; j++)
        {
            cell = grid->getCell(i, j);

            imgs = cell->getAllImage();
            diffs = cell->getAllDiff();
            color = cell->getColor();

            for (int k = 0; k < imgs.size(); k++)
            {
                out << QString("%1,%2 %3 %4 %5\n").arg(i)
                                                  .arg(j)
                                                  .arg(imgs[k]->getId())
                                                  .arg(diffs[k])
                                                  .arg(color.name());
            }
        }
    }
}

void MapSOM::load()
{
    // verifier l'existe de fichier map.meta
    QString filename = Util::getFileMapMeta(base->getPathMetadata());
    if (QFile::exists(filename))
    {
        try
        {
            load(filename);
        }
        catch (std::exception &ex)
        {
            return;
        }
    }
}

void MapSOM::load(QString filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::bad_exception();
    }

    QTextStream in(&file);

    // lire header
    loadHeader(in);

    // load codes, gridSOM, gridRearr neu co
    loadCodes(in);

    QString line;
    QStringList fields;
    while (!in.atEnd())
    {
        line = in.readLine();
        fields = line.split(" ");

        if (fields[0] == "#4")
        {
            // gridSOM
            if (gridSOM != 0)
                delete gridSOM;

            gridSOM = loadGrid(in);
        }
        else if (fields[0] == "#5")
        {
            // gridRearrange
            if (gridRearr != 0)
                delete gridRearr;

            gridRearr = loadGrid(in);
        }
    }

    QString newFilename = Util::getFileMapMeta(base->getPathMetadata());
    if (filename != newFilename)
    {
        if (QFile::exists(newFilename))
            QFile::remove(newFilename);
        QFile::copy(filename, newFilename);
    }
}

void MapSOM::loadWeight(QString filename, FeaturesChosenList *list)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::bad_exception();
    }

    QTextStream in(&file);

    QString name = readParam(in);
    int size = readParam(in).toInt();

    if (!isMyMapMeta(name, size))
    {
        IncorrespondentException incorrespondent(QString("This weight file is not consistent with database"
                                                         "This weight file is own by database %1 with %2 images")
                                                         .arg(name)
                                                         .arg(size));

        throw incorrespondent;
    }

    // load fea
    FeaturesChosenList *feaList = readFeaturesChoosenList(in);

    if (!isEqual(list, feaList))
    {
        IncorrespondentException incorrespondent(QString("This weight file is not consistent with theses choosen descriptors"));

        throw incorrespondent;
    }
    else
    {
        feaChosenList = list;

        readParams(in);

        loadCodes(in);
    }

    delete feaList;
}

void MapSOM::loadHeader(QTextStream &in)
{
    QString name = readParam(in);
    int size = readParam(in).toInt();

    if (!isMyMapMeta(name, size))
    {
        IncorrespondentException incorrespondent(QString("This map is not consistent with database"
                                                         "This map is own by database %1 with %2 images")
                                                         .arg(name)
                                                         .arg(size));

        throw incorrespondent;
    }

    // load fea
    feaChosenList = readFeaturesChoosenList(in);

    // load params
    readParams(in);
}

FeaturesChosenList *MapSOM::readFeaturesChoosenList(QTextStream &in)
{
    QString line = in.readLine(); // #1 descriptors list
    int numCFeas = in.readLine().toInt(); // num choosen features

    FeaturesChosenList *feaList = new FeaturesChosenList();
    QStringList fields;
    QString coded;
    double weight;
    QStringList codeds = base->getFeatureCodedList();
    int j;
    for (int i = 0; i < numCFeas; i++)
    {
        line = in.readLine();
        fields = line.split(" ");

        coded = fields[0];
        weight = fields[1].toDouble();

        for (j = 0; j < codeds.size(); j++)
        {
            if (coded == codeds[j])
                break;
        }

        if (j < codeds.size())
            feaList->addFeature(j, weight);
        else
        {
            delete feaList;
            feaList = 0;
            IncorrespondentException incorrespondent(QString("This map is not consistent with database"
                                                             "This map have a feature %1 is not supported in this database").arg(coded));

            throw incorrespondent;
        }
    }

    return feaList;
}

void MapSOM::readParams(QTextStream &in)
{
    in.readLine(); // #2 Params
    xdim = readParam(in).toInt();
    ydim = readParam(in).toInt();
    numCodes = xdim * ydim;
    type_neigh = (readParam(in) == "gaussian") ? NEIGH_GAUSSIAN : NEIGH_BUBBLE;
    radiusOrdering = readParam(in).toDouble();
    alphaOrdering = readParam(in).toDouble();
    lengthOrdering = readParam(in).toLong();
    radiusConver = readParam(in).toDouble();
    alphaConver = readParam(in).toDouble();
    lengthConver = readParam(in).toLong();
    type_alpha = (readParam(in) == "linear") ? ALPHA_LINEAR : ALPHA_INVERSE_T;
    next = readParam(in).toLong();
    lengthRearrange = readParam(in).toLong();
}

bool MapSOM::isMyMapMeta(QString nameDB, int sizeDB)
{
    if ((nameDB == base->getNameOfDB()) && (sizeDB == base->getSizeOfDB()))
        return true;
    return false;
}

QString MapSOM::readParam(QTextStream &in)
{
    QString line = in.readLine();
    QStringList fields = line.split(" ");

    return fields[1];
}

bool MapSOM::isEqual(FeaturesChosenList *list1, FeaturesChosenList *list2)
{
    if (list1->getSize() != list2->getSize()) return false;

    int index1, index2, j, size;
    size = list1->getSize();

    bool *check = (bool*)malloc(sizeof(bool) * size);
    memset(check, 0, sizeof(bool) * size);

    for (int i = 0; i < size; i++)
    {
        index2 = list2->getIndex(i);
        for (j = 0; j < size; j++)
        {
            if (check[j]) continue;

            index1 = list1->getIndex(j);
            if (index1 == index2)
                break;
        }

        if (j == size)
            return false;
        else
            check[j] = true;
    }

    return true;
}

void MapSOM::loadCodes(QTextStream &in)
{
    // prendre la dimension
    in.readLine();
    dim = readParam(in).toInt();

    codes.clear();
    double *vecteur;
    int numFea = feaChosenList->getSize();
    Image *img = base->getImage(0);
    Feature *fea, *newFea;
    EntrySOM *entry;
    int index = -1;
    QStringList feaCoded = base->getFeatureCodedList();
    QString line;
    QStringList fields;

    try
    {
        for (int i = 0; i < numCodes; i++)
        {
            line = in.readLine();
            fields = line.split(";");

            entry = new EntrySOM(i, dim);

            for (int j = 0; j < numFea; j++)
            {
                vecteur = convertFromStringToDoubleArr(fields[j]);

                index = feaChosenList->getIndex(j);
                fea = img->getFeature(index);

                newFea = new Feature(feaCoded[index], fea->getSize(), vecteur);

                entry->addFeature(index, newFea, feaChosenList->getWeight(j));

                free(vecteur);
                vecteur = 0;
            }

            codes << entry;
        }
    }
    catch (std::exception &ex)
    {
        codes.clear();
        throw ex;
    }

    img = 0;
    fea = newFea = 0;
    entry = 0;
}

double *MapSOM::convertFromStringToDoubleArr(QString string)
{
    QStringList fields = string.split(" ");

    double *vecteur = (double*)malloc(sizeof(double) * fields.size());
    memset(vecteur, 0, sizeof(double) * fields.size());

    // copy from QStringList to double*
    for (int i = 0; i < fields.size(); i++)
    {
        vecteur[i] = fields[i].toDouble();
    }

    return vecteur;
}

GridSOM *MapSOM::loadGrid(QTextStream &in)
{
    GridSOM *grid = new GridSOM(xdim, ydim);

    int size = base->getSizeOfDB();
    QPoint coord;
    int id;
    double weight;
    QColor color;
    Image *img;

    try
    {
        for (int i = 0; i < size; i++)
        {
            readLineOfGrid(in, coord, id, weight, color);

            img = base->getImage(id);

            grid->addImage(coord.x(), coord.y(), img, weight, color);
        }
    }
    catch (std::exception &ex)
    {
        delete grid;
        grid = 0;
        throw ex;
    }

    return grid;
}

void MapSOM::readLineOfGrid(QTextStream &in, QPoint &coord, int &id, double &weight, QColor &color)
{
    QString line = in.readLine();
    QStringList fields = line.split(" ");

    // coordonnees
    QStringList xy = fields[0].split(",");
    coord.setX(xy[0].toInt());
    coord.setY(xy[1].toInt());
    // id image
    id = fields[1].toInt();
    // weight
    weight = fields[2].toDouble();
    // color
    color.setNamedColor(fields[3]);
}

QPoint MapSOM::search(Image *img)
{
    QPoint point = QPoint(0, 0);
    WinnerInfo *winner = findWinnerEuc(img);

    if (!winner->isNoWinner())
    {
        point.setX(winner->getIndex() / ydim);
        point.setY(winner->getIndex() % ydim);
    }
    delete winner;

    return point;
}

QList<QPoint> MapSOM::classify(GridSOM *grid, QPoint point, double aqe)
{
    QList<QPoint> pointList;
    QPoint newPoint;

    bool** S = createStableTable();
    QList<EntrySOM*> neighbs = getNeighbours(point.x(), point.y(), S);
    deleteStableTable(S);

    int index;
    CellSOM *cell1, *cell2;
    Image *img1, *img2;

    cell1 = grid->getCell(point.x(), point.y());
    img1 = cell1->getImage();

    foreach (EntrySOM *neigh, neighbs)
    {
        index = neigh->getId();
        newPoint.setX(index / ydim);
        newPoint.setY(index % ydim);

        cell2 = grid->getCell(newPoint.x(), newPoint.y());

        if (cell2->getQuantityOfImages() == 0) continue;

        img2 = cell2->getImage();

        if (distanceEuc(img1, img2) < aqe)
        {
            pointList << newPoint;
        }
    }

    return pointList;
}
