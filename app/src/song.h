#ifndef SONG_H
#define SONG_H

#include <QString>

struct Song
{
    QString filename;
    QString title;
    QString artist;
    QString album;
    QString comment;
    QString genre;
    unsigned int track;
    unsigned int year;
};

#endif // SONG_H