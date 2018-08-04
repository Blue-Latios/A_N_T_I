#ifndef LETTER_HPP
#define LETTER_HPP

#include <iostream>
using namespace std;

#define DEFAULT_STRINGWIDTH 10

//Asumsi ukuran data cukup untuk ditambah point baru
//Size = 9X15 pixels
//big letter: x + 0-8, y + 0-14
//small letter: x + 1-7, y + 3-11
void addLetterData(float x, float y, char c, int linesize, float *data, int& tail);
void convertStringToLetterData(string s, float x, float y, int linesize, float *data, int& tail, bool enableOffset);
float getStringWidth(string s, int linesize); //return panjang string dalam pixel

#endif
