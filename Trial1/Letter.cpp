#include "Letter.hpp"
#include <iostream>
#include <fstream>
using namespace std;

void addData(float in[], int size, float *out, int& tail) {
	for (int i = 0; i < size; i++) {
		out[tail+i] = in[i];
	}
	tail += size;
}

void addLetterData(float x, float y, char c, int linesize, float *data, int& tail) {
	float points[50];
	switch (c) {
		case 'A' :
			points[0] = x + 2*linesize;
			points[1] = y + 7*linesize;
			points[2] = x + 6*linesize;
			points[3] = y + 7*linesize;
			
			points[8] = x + 4*linesize;
			points[9] = y;
			points[10] = x;
			points[11] = y + 14*linesize;
			
			points[4] = x + 4*linesize;
			points[5] = y;
			points[6] = x + 8*linesize;
			points[7] = y + 14*linesize;
			
			addData(points, 12, data, tail);
		break;
		case 'B' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 14*linesize;
			
			points[4] = x;
			points[5] = y;
			points[6] = x + 5*linesize;
			points[7] = y;
			
			points[8] = x + 5*linesize;
			points[9] = y;
			points[10] = x + 8*linesize;
			points[11] = y + 2*linesize;
			
			points[12] = x + 8*linesize;
			points[13] = y + 2*linesize;
			points[14] = x + 8*linesize;
			points[15] = y + 5*linesize;
			
			points[16] = x + 8*linesize;
			points[17] = y + 5*linesize;
			points[18] = x + 5*linesize;
			points[19] = y + 7*linesize;
			
			points[20] = x;
			points[21] = y + 7*linesize;
			points[22] = x + 5*linesize;
			points[23] = y + 7*linesize;
			
			points[24] = x + 5*linesize;
			points[25] = y + 7*linesize;
			points[26] = x + 8*linesize;
			points[27] = y + 9*linesize;
			
			points[28] = x + 8*linesize;
			points[29] = y + 9*linesize;
			points[30] = x + 8*linesize;
			points[31] = y + 12*linesize;
			
			points[32] = x + 8*linesize;
			points[33] = y + 12*linesize;
			points[34] = x + 5*linesize;
			points[35] = y + 14*linesize;
			
			points[36] = x;
			points[37] = y + 14*linesize;
			points[38] = x + 5*linesize;
			points[39] = y + 14*linesize;

			addData(points, 40, data, tail);
		break;
		case 'G' :
			points[0] = x + 4 *linesize;
			points[1] = y + 7 *linesize;
			points[2] = x + 8 *linesize;
			points[3] = y + 7 *linesize;
			
			points[4] = x + 8 *linesize;
			points[5] = y + 7 *linesize;
			points[6] = x + 8 *linesize;
			points[7] = y + 12 *linesize;
			
			addData(points, 8, data, tail);
		case 'C' :
			points[0] = x + 8 *linesize;
			points[1] = y + 2 *linesize;
			points[2] = x + 6 *linesize;
			points[3] = y;
			
			points[4] = x + 6 *linesize;
			points[5] = y;
			points[6] = x + 2 *linesize;
			points[7] = y;
			
			points[8] = x + 2 *linesize;
			points[9] = y;
			points[10] = x;
			points[11] = y + 2 *linesize;
			
			points[12] = x;
			points[13] = y + 2 *linesize;
			points[14] = x;
			points[15] = y + 12 *linesize;
			
			points[16] = x;
			points[17] = y + 12 *linesize;
			points[18] = x + 2 *linesize;
			points[19] = y + 14 *linesize;
			
			points[20] = x + 2 *linesize;
			points[21] = y + 14 *linesize;
			points[22] = x + 6 *linesize;
			points[23] = y + 14 *linesize;
			
			points[24] = x + 6 *linesize;
			points[25] = y + 14 *linesize;
			points[26] = x + 8 *linesize;
			points[27] = y + 12 *linesize;
			
			addData(points, 28, data, tail);
		break;
		case 'D' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 14*linesize;
			
			points[4] = x;
			points[5] = y;
			points[6] = x + 5*linesize;
			points[7] = y;
			
			points[8] = x + 5*linesize;
			points[9] = y;
			points[10] = x + 8*linesize;
			points[11] = y + 2*linesize;
			
			points[12] = x + 8*linesize;
			points[13] = y + 2*linesize;
			points[14] = x + 8*linesize;
			points[15] = y + 12*linesize;
			
			points[16] = x + 8*linesize;
			points[17] = y + 12*linesize;
			points[18] = x + 5*linesize;
			points[19] = y + 14*linesize;
			
			points[20] = x;
			points[21] = y + 14*linesize;
			points[22] = x + 5*linesize;
			points[23] = y + 14*linesize;
			addData(points, 24, data, tail);
		break;
		case 'F' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y;
			
			points[4] = x;
			points[5] = y + 7 *linesize;
			points[6] = x + 8 *linesize;
			points[7] = y + 7 *linesize;
			
			points[8] = x;
			points[9] = y;
			points[10] = x;
			points[11] = y + 14 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case 'H' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 14 *linesize;
			
			points[4] = x;
			points[5] = y + 7 *linesize;
			points[6] = x + 8 *linesize;
			points[7] = y + 7 *linesize;
			
			points[8] = x + 8 *linesize;
			points[9] = y;
			points[10] = x + 8 *linesize;
			points[11] = y + 14 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case 'I' :
			points[0] = x;
			points[1] = y + 14 *linesize;
			points[2] = x + 8 *linesize;
			points[3] = y + 14 *linesize;
			
			addData(points, 4, data, tail);
		case 'T' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y;
			
			points[4] = x + 4 *linesize;
			points[5] = y;
			points[6] = x + 4 *linesize;
			points[7] = y + 14 *linesize;
			
			addData(points, 8, data, tail);
		break;
		case 'J' :
			points[0] = x + 1 *linesize;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y;
			
			points[4] = x + 6 *linesize;
			points[5] = y;
			points[6] = x + 6 *linesize;
			points[7] = y + 13 *linesize;
			
			points[8] = x + 6 *linesize;
			points[9] = y + 13 *linesize;
			points[10] = x + 5 *linesize;
			points[11] = y + 14 *linesize;
			
			points[12] = x + 5 *linesize;
			points[13] = y + 14 *linesize;
			points[14] = x + 1 *linesize;
			points[15] = y + 14 *linesize;
			
			points[16] = x + 1 *linesize;
			points[17] = y + 14 *linesize;
			points[18] = x;
			points[19] = y + 13 *linesize;
			
			points[20] = x;
			points[21] = y + 13 *linesize;
			points[22] = x;
			points[23] = y + 10 *linesize;
			
			addData(points, 24, data, tail);
		break;
		case 'K' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 14 *linesize;
			
			points[4] = x + 8 *linesize;
			points[5] = y;
			points[6] = x;
			points[7] = y + 7 *linesize;
			
			points[8] = x;
			points[9] = y + 7 *linesize;
			points[10] = x + 8 *linesize;
			points[11] = y + 14 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case 'E' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y;
			
			points[4] = x;
			points[5] = y + 7 *linesize;
			points[6] = x + 8 *linesize;
			points[7] = y + 7 *linesize;
			
			addData(points, 8, data, tail);
		case 'L' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 14 *linesize;
			
			points[4] = x;
			points[5] = y + 14 *linesize;
			points[6] = x + 8 *linesize;
			points[7] = y + 14 *linesize;
			
			addData(points, 8, data, tail);
		break;
		case 'M' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 14 *linesize;
			
			points[4] = x;
			points[5] = y;
			points[6] = x + 4 *linesize;
			points[7] = y + 14 *linesize;
			
			points[8] = x + 8 *linesize;
			points[9] = y;
			points[10] = x + 4 *linesize;
			points[11] = y + 14 *linesize;
			
			points[12] = x + 8 *linesize;
			points[13] = y;
			points[14] = x + 8 *linesize;
			points[15] = y + 14 *linesize;
			
			addData(points, 16, data, tail);
		break;
		case 'N' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 14 *linesize;
			
			points[4] = x;
			points[5] = y;
			points[6] = x + 8 *linesize;
			points[7] = y + 14 *linesize;
			
			points[8] = x + 8 *linesize;
			points[9] = y;
			points[10] = x + 8 *linesize;
			points[11] = y + 14 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case 'Q' :
			points[0] = x + 5 *linesize;
			points[1] = y + 10 *linesize;
			points[2] = x + 8 *linesize;
			points[3] = y + 14 *linesize;
			
			addData(points, 4, data, tail);
		case 'O' :
			points[0] = x + 2 *linesize;
			points[1] = y;
			points[2] = x + 6 *linesize;
			points[3] = y;
			
			points[4] = x + 2 *linesize;
			points[5] = y;
			points[6] = x;
			points[7] = y + 2 *linesize;
			
			points[8] = x;
			points[9] = y + 2 *linesize;
			points[10] = x;
			points[11] = y + 12 *linesize;
			
			points[12] = x;
			points[13] = y + 12 *linesize;
			points[14] = x + 2 *linesize;
			points[15] = y + 14 *linesize;
			
			points[16] = x + 2 *linesize;
			points[17] = y + 14 *linesize;
			points[18] = x + 6 *linesize;
			points[19] = y + 14 *linesize;
			
			points[20] = x + 6 *linesize;
			points[21] = y;
			points[22] = x + 8 *linesize;
			points[23] = y + 2 *linesize;
			
			points[24] = x + 8 *linesize;
			points[25] = y + 2 *linesize;
			points[26] = x + 8 *linesize;
			points[27] = y + 12 *linesize;
			
			points[28] = x + 8 *linesize;
			points[29] = y + 12 *linesize;
			points[30] = x + 6 *linesize;
			points[31] = y + 14 *linesize;
			
			addData(points, 32, data, tail);
		break;
		case 'R' :
			points[0] = x;
			points[1] = y + 7 *linesize;
			points[2] = x + 8 *linesize;
			points[3] = y + 14 *linesize;
			
			addData(points, 4, data, tail);
		case 'P' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 14*linesize;
			
			points[4] = x;
			points[5] = y;
			points[6] = x + 5*linesize;
			points[7] = y;
			
			points[8] = x + 5*linesize;
			points[9] = y;
			points[10] = x + 8*linesize;
			points[11] = y + 2*linesize;
			
			points[12] = x + 8*linesize;
			points[13] = y + 2*linesize;
			points[14] = x + 8*linesize;
			points[15] = y + 5*linesize;
			
			points[16] = x + 8*linesize;
			points[17] = y + 5*linesize;
			points[18] = x + 5*linesize;
			points[19] = y + 7*linesize;
			
			points[20] = x + 5*linesize;
			points[21] = y + 7*linesize;
			points[22] = x;
			points[23] = y + 7*linesize;
			
			addData(points, 24, data, tail);
		break;
		case 'S' :
			points[0] = x + 2 *linesize;
			points[1] = y;
			points[2] = x + 6 *linesize;
			points[3] = y;
			
			points[4] = x + 6 *linesize;
			points[5] = y;
			points[6] = x + 8 *linesize;
			points[7] = y + 2 *linesize;
			
			points[8] = x + 2 *linesize;
			points[9] = y;
			points[10] = x;
			points[11] = y + 2 *linesize;
			
			points[12] = x;
			points[13] = y + 2 *linesize;
			points[14] = x;
			points[15] = y + 5 *linesize;
			
			points[16] = x;
			points[17] = y + 5 *linesize;
			points[18] = x + 2 *linesize;
			points[19] = y + 7 *linesize;
			
			points[20] = x + 2 *linesize;
			points[21] = y + 7 *linesize;
			points[22] = x + 6 *linesize;
			points[23] = y + 7 *linesize;
			
			points[24] = x + 6 *linesize;
			points[25] = y + 7 *linesize;
			points[26] = x + 8 *linesize;
			points[27] = y + 9 *linesize;
			
			points[28] = x + 8 *linesize;
			points[29] = y + 9 *linesize;
			points[30] = x + 8 *linesize;
			points[31] = y + 12 *linesize;
			
			points[32] = x + 8 *linesize;
			points[33] = y + 12 *linesize;
			points[34] = x + 6 *linesize;
			points[35] = y + 14 *linesize;
			
			points[36] = x + 6 *linesize;
			points[37] = y + 14 *linesize;
			points[38] = x + 2 *linesize;
			points[39] = y + 14 *linesize;
			
			points[40] = x + 2 *linesize;
			points[41] = y + 14 *linesize;
			points[42] = x;
			points[43] = y + 12 *linesize;
			
			addData(points, 44, data, tail);
		break;
		case 'U' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 12 *linesize;
			
			points[4] = x;
			points[5] = y + 12 *linesize;
			points[6] = x + 2 *linesize;
			points[7] = y + 14 *linesize;
			
			points[8] = x + 2 *linesize;
			points[9] = y + 14 *linesize;
			points[10] = x + 6 *linesize;
			points[11] = y + 14 *linesize;
			
			points[12] = x + 8 *linesize;
			points[13] = y;
			points[14] = x + 8 *linesize;
			points[15] = y + 12 *linesize;
			
			points[16] = x + 8 *linesize;
			points[17] = y + 12 *linesize;
			points[18] = x + 6 *linesize;
			points[19] = y + 14 *linesize;
			
			addData(points, 20, data, tail);
		break;
		case 'V' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 4 *linesize;
			points[3] = y + 14 *linesize;
			
			points[4] = x + 8 *linesize;
			points[5] = y;
			points[6] = x + 4 *linesize;
			points[7] = y + 14 *linesize;
			
			addData(points, 8, data, tail);
		break;
		case 'W' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 2 *linesize;
			points[3] = y + 14 *linesize;
			
			points[4] = x + 4 *linesize;
			points[5] = y;
			points[6] = x + 2 *linesize;
			points[7] = y + 14 *linesize;
			
			points[8] = x + 4 *linesize;
			points[9] = y;
			points[10] = x + 6 *linesize;
			points[11] = y + 14 *linesize;
			
			points[12] = x + 8 *linesize;
			points[13] = y;
			points[14] = x + 6 *linesize;
			points[15] = y + 14 *linesize;
			
			addData(points, 16, data, tail);
		break;
		case 'X' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y + 14 *linesize;
			
			points[4] = x + 8 *linesize;
			points[5] = y;
			points[6] = x;
			points[7] = y + 14 *linesize;
			
			addData(points, 8, data, tail);
		break;
		case 'Y' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 4 *linesize;
			points[3] = y + 6 *linesize;
			
			points[4] = x + 8 *linesize;
			points[5] = y;
			points[6] = x + 4 *linesize;
			points[7] = y + 6 *linesize;
			
			points[8] = x + 4 *linesize;
			points[9] = y + 5 *linesize;
			points[10] = x + 4 *linesize;
			points[11] = y + 14 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case 'Z' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y;
			
			points[4] = x + 8 *linesize;
			points[5] = y;
			points[6] = x;
			points[7] = y + 14 *linesize;
			
			points[8] = x;
			points[9] = y + 14 *linesize;
			points[10] = x + 8 *linesize;
			points[11] = y + 14 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case 'a' :
			points[0] = x + 1 *linesize;
			points[1] = y + 3 *linesize;
			points[2] = x + 5 *linesize;
			points[3] = y + 3 *linesize;
			
			points[4] = x + 5 *linesize;
			points[5] = y + 3 *linesize;
			points[6] = x + 7 *linesize;
			points[7] = y + 5 *linesize;
			
			points[8] = x + 7 *linesize;
			points[9] = y + 5 *linesize;
			points[10] = x + 7 *linesize;
			points[11] = y + 11 *linesize;
			
			points[12] = x + 7 *linesize;
			points[13] = y + 7 *linesize;
			points[14] = x + 3 *linesize;
			points[15] = y + 7 *linesize;
			
			points[16] = x + 3 *linesize;
			points[17] = y + 7 *linesize;
			points[18] = x + 1 *linesize;
			points[19] = y + 8 *linesize;
			
			points[20] = x + 1 *linesize;
			points[21] = y + 8 *linesize;
			points[22] = x + 1 *linesize;
			points[23] = y + 10 *linesize;
			
			points[24] = x + 1 *linesize;
			points[25] = y + 10 *linesize;
			points[26] = x + 3 *linesize;
			points[27] = y + 11 *linesize;
			
			points[28] = x + 3 *linesize;
			points[29] = y + 11 *linesize;
			points[30] = x + 7 *linesize;
			points[31] = y + 11 *linesize;
			
			addData(points, 32, data, tail);
		break;
		case 'b' :
			points[0] = x + 1 *linesize;
			points[1] = y;
			points[2] = x + 1 *linesize;
			points[3] = y + 11 *linesize;
			
			points[4] = x + 1 *linesize;
			points[5] = y + 5 *linesize;
			points[6] = x + 6 *linesize;
			points[7] = y + 5 *linesize;
			
			points[8] = x + 6 *linesize;
			points[9] = y + 5 *linesize;
			points[10] = x + 7 *linesize;
			points[11] = y + 6 *linesize;
			
			points[12] = x + 7 *linesize;
			points[13] = y + 6 *linesize;
			points[14] = x + 7 *linesize;
			points[15] = y + 10 *linesize;
			
			points[16] = x + 7 *linesize;
			points[17] = y + 10 *linesize;
			points[18] = x + 6 *linesize;
			points[19] = y + 11 *linesize;
			
			points[20] = x + 1 *linesize;
			points[21] = y + 11 *linesize;
			points[22] = x + 6 *linesize;
			points[23] = y + 11 *linesize;
			
			addData(points, 24, data, tail);
		break;
		case 'c' :
			points[0] = x + 2 *linesize;
			points[1] = y + 3 *linesize;
			points[2] = x + 6 *linesize;
			points[3] = y + 3 *linesize;
			
			points[4] = x + 6 *linesize;
			points[5] = y + 3 *linesize;
			points[6] = x + 7 *linesize;
			points[7] = y + 4 *linesize;
			
			points[8] = x + 2 *linesize;
			points[9] = y + 3 *linesize;
			points[10] = x + 1 *linesize;
			points[11] = y + 4 *linesize;
			
			points[12] = x + 1 *linesize;
			points[13] = y + 4 *linesize;
			points[14] = x + 1 *linesize;
			points[15] = y + 10 *linesize;
			
			points[16] = x + 1 *linesize;
			points[17] = y + 10 *linesize;
			points[18] = x + 2 *linesize;
			points[19] = y + 11 *linesize;
			
			points[20] = x + 2 *linesize;
			points[21] = y + 11 *linesize;
			points[22] = x + 6 *linesize;
			points[23] = y + 11 *linesize;
			
			points[24] = x + 6 *linesize;
			points[25] = y + 11 *linesize;
			points[26] = x + 7 *linesize;
			points[27] = y + 10 *linesize;
			
			addData(points, 28, data, tail);
		break;
		case 'd' :
			points[0] = x + 7 *linesize;
			points[1] = y;
			points[2] = x + 7 *linesize;
			points[3] = y + 11 *linesize;
			
			points[4] = x + 7 *linesize;
			points[5] = y + 5 *linesize;
			points[6] = x + 2 *linesize;
			points[7] = y + 5 *linesize;
			
			points[8] = x + 2 *linesize;
			points[9] = y + 5 *linesize;
			points[10] = x + 1 *linesize;
			points[11] = y + 6 *linesize;
			
			points[12] = x + 1 *linesize;
			points[13] = y + 6 *linesize;
			points[14] = x + 1 *linesize;
			points[15] = y + 10 *linesize;
			
			points[16] = x + 1 *linesize;
			points[17] = y + 10 *linesize;
			points[18] = x + 2 *linesize;
			points[19] = y + 11 *linesize;
			
			points[20] = x + 2 *linesize;
			points[21] = y + 11 *linesize;
			points[22] = x + 7 *linesize;
			points[23] = y + 11 *linesize;
			
			addData(points, 24, data, tail);
		break;
		case 'e' :
			points[0] = x + 2 *linesize;
			points[1] = y + 3 *linesize;
			points[2] = x + 6 *linesize;
			points[3] = y + 3 *linesize;
			
			points[4] = x + 6 *linesize;
			points[5] = y + 3 *linesize;
			points[6] = x + 7 *linesize;
			points[7] = y + 4 *linesize;
			
			points[8] = x + 2 *linesize;
			points[9] = y + 3 *linesize;
			points[10] = x + 1 *linesize;
			points[11] = y + 4 *linesize;
			
			points[12] = x + 1 *linesize;
			points[13] = y + 4 *linesize;
			points[14] = x + 1 *linesize;
			points[15] = y + 10 *linesize;
			
			points[16] = x + 1 *linesize;
			points[17] = y + 10 *linesize;
			points[18] = x + 2 *linesize;
			points[19] = y + 11 *linesize;
			
			points[20] = x + 2 *linesize;
			points[21] = y + 11 *linesize;
			points[22] = x + 7 *linesize;
			points[23] = y + 11 *linesize;
			
			points[24] = x + 7 *linesize;
			points[25] = y + 4 *linesize;
			points[26] = x + 7 *linesize;
			points[27] = y + 7 *linesize;
			
			points[28] = x + 1 *linesize;
			points[29] = y + 7 *linesize;
			points[30] = x + 7 *linesize;
			points[31] = y + 7 *linesize;
			
			addData(points, 32, data, tail);
		break;
		case 'f' :
			points[0] = x + 7 *linesize;
			points[1] = y + 3 *linesize;
			points[2] = x + 4 *linesize;
			points[3] = y + 3 *linesize;
			
			points[4] = x + 4 *linesize;
			points[5] = y + 3 *linesize;
			points[6] = x + 3 *linesize;
			points[7] = y + 4 *linesize;
			
			points[8] = x + 3 *linesize;
			points[9] = y + 4 *linesize;
			points[10] = x + 3 *linesize;
			points[11] = y + 14 *linesize;
			
			points[12] = x + 1 *linesize;
			points[13] = y + 7 *linesize;
			points[14] = x + 7 *linesize;
			points[15] = y + 7 *linesize;
			
			addData(points, 16, data, tail);
		break;
		case 'g' :
			points[0] = x + 2 *linesize;
			points[1] = y + 5 *linesize;
			points[2] = x + 7 *linesize;
			points[3] = y + 5 *linesize;
			
			points[4] = x + 7 *linesize;
			points[5] = y + 5 *linesize;
			points[6] = x + 7 *linesize;
			points[7] = y + 13 *linesize;
			
			points[8] = x + 7 *linesize;
			points[9] = y + 13 *linesize;
			points[10] = x + 6 *linesize;
			points[11] = y + 14 *linesize;
			
			points[12] = x + 6 *linesize;
			points[13] = y + 14 *linesize;
			points[14] = x + 2 *linesize;
			points[15] = y + 14 *linesize;
			
			points[16] = x + 2 *linesize; 
			points[17] = y + 14 *linesize;
			points[18] = x + 1 *linesize;
			points[19] = y + 13 *linesize;
			
			points[20] = x + 2 *linesize;
			points[21] = y + 5 *linesize;
			points[22] = x + 1 *linesize;
			points[23] = y + 6 *linesize;
			
			points[24] = x + 1 *linesize;
			points[25] = y + 6 *linesize;
			points[26] = x + 1 *linesize;
			points[27] = y + 9 *linesize;
			
			points[28] = x + 1 *linesize;
			points[29] = y + 9 *linesize;
			points[30] = x + 2 *linesize;
			points[31] = y + 10 *linesize;
			
			points[32] = x + 2 *linesize;
			points[33] = y + 10 *linesize;
			points[34] = x + 7 *linesize;
			points[35] = y + 10 *linesize;
			
			addData(points, 36, data, tail);
		break;
		case 'h' :
			points[0] = x + 1 *linesize;
			points[1] = y;
			points[2] = x + 1 *linesize;
			points[3] = y + 4 *linesize;
			
			addData(points, 4, data, tail);
		case 'n' :
			points[0] = x + 1 *linesize;
			points[1] = y + 4 *linesize;
			points[2] = x + 1 *linesize;
			points[3] = y + 11 *linesize;
			
			points[4] = x + 1 *linesize;
			points[5] = y + 4 *linesize;
			points[6] = x + 6 *linesize;
			points[7] = y + 4 *linesize;
			
			points[8] = x + 6 *linesize;
			points[9] = y + 4 *linesize;
			points[10] = x + 7 *linesize;
			points[11] = y + 5 *linesize;
			
			points[12] = x + 7 *linesize;
			points[13] = y + 5 *linesize;
			points[14] = x + 7 *linesize;
			points[15] = y + 11 *linesize;
			
			addData(points, 16, data, tail);
		break;
		case 'j' :
			points[0] = x + 4 *linesize;
			points[1] = y + 11 *linesize;
			points[2] = x + 4 *linesize;
			points[3] = y + 13 *linesize;
			
			points[4] = x + 4 *linesize;
			points[5] = y + 13 *linesize;
			points[6] = x + 3 *linesize;
			points[7] = y + 14 *linesize;
			
			points[8] = x + 3 *linesize;
			points[9] = y + 14 *linesize;
			points[10] = x + 1 *linesize;
			points[11] = y + 14 *linesize;
			
			addData(points, 12, data, tail);
		case 'i' :
			points[0] = x + 4 *linesize;
			points[1] = y + 1 *linesize;
			points[2] = x + 4 *linesize;
			points[3] = y + 2 *linesize;
			
			points[4] = x + 4 *linesize;
			points[5] = y + 4 *linesize;
			points[6] = x + 4 *linesize;
			points[7] = y + 11 *linesize;
			
			addData(points, 8, data, tail);
		break;
		case 'k' :
			points[0] = x + 1 *linesize;
			points[1] = y;
			points[2] = x + 1 *linesize;
			points[3] = y + 11 *linesize;
			
			points[4] = x + 7 *linesize;
			points[5] = y + 5 *linesize;
			points[6] = x + 1 *linesize;
			points[7] = y + 8 *linesize;
			
			points[8] = x + 1 *linesize;
			points[9] = y + 8 *linesize;
			points[10] = x + 7 *linesize;
			points[11] = y + 11 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case 'l' :
			points[0] = x + 4 *linesize;
			points[1] = y;
			points[2] = x + 4 *linesize;
			points[3] = y + 11 *linesize;
			
			addData(points, 4, data, tail);
		break;
		case 'm' :
			points[0] = x + 1 *linesize;
			points[1] = y + 3 *linesize;
			points[2] = x + 1 *linesize;
			points[3] = y + 11 *linesize;
			
			points[4] = x + 4 *linesize;
			points[5] = y + 3 *linesize;
			points[6] = x + 4 *linesize;
			points[7] = y + 11 *linesize;
			
			points[8] = x + 6 *linesize;
			points[9] = y + 3 *linesize;
			points[10] = x + 7 *linesize;
			points[11] = y + 4 *linesize;
			
			points[12] = x + 7 *linesize;
			points[13] = y + 4 *linesize;
			points[14] = x + 7 *linesize;
			points[15] = y + 11 *linesize;
			
			points[16] = x + 1 *linesize;
			points[17] = y + 3 *linesize;
			points[18] = x + 6 *linesize;
			points[19] = y + 3 *linesize;
			
			addData(points, 20, data, tail);
		break;
		case 'o' :
			points[0] = x + 2 *linesize;
			points[1] = y + 4 *linesize;
			points[2] = x + 1 *linesize;
			points[3] = y + 5 *linesize;
			
			points[4] = x + 1 *linesize;
			points[5] = y + 5 *linesize;
			points[6] = x + 1 *linesize;
			points[7] = y + 10 *linesize;
			
			points[8] = x + 2 *linesize;
			points[9] = y + 4 *linesize;
			points[10] = x + 6 *linesize;
			points[11] = y + 4 *linesize;
			
			points[12] = x + 6 *linesize;
			points[13] = y + 4 *linesize;
			points[14] = x + 7 *linesize;
			points[15] = y + 5 *linesize;
			
			points[16] = x + 7 *linesize;
			points[17] = y + 5 *linesize;
			points[18] = x + 7 *linesize;
			points[19] = y + 10 *linesize;
			
			points[20] = x + 7 *linesize;
			points[21] = y + 10 *linesize;
			points[22] = x + 6 *linesize;
			points[23] = y + 11 *linesize;
			
			points[24] = x + 1 *linesize;
			points[25] = y + 10 *linesize;
			points[26] = x + 2 *linesize;
			points[27] = y + 11 *linesize;
			
			points[28] = x + 2 *linesize;
			points[29] = y + 11 *linesize;
			points[30] = x + 6 *linesize;
			points[31] = y + 11 *linesize;
			
			addData(points, 32, data, tail);
		break;
		case 'p' :
			points[0] = x + 1 *linesize;
			points[1] = y + 4 * linesize;
			points[2] = x + 1 *linesize;
			points[3] = y + 14 *linesize;
			
			points[4] = x + 1 *linesize;
			points[5] = y + 4 *linesize;
			points[6] = x + 6 *linesize;
			points[7] = y + 4 *linesize;
			
			points[8] = x + 6 *linesize;
			points[9] = y + 4 *linesize;
			points[10] = x + 7 *linesize;
			points[11] = y + 5 *linesize;
			
			points[12] = x + 7 *linesize;
			points[13] = y + 5 *linesize;
			points[14] = x + 7 *linesize;
			points[15] = y + 9 *linesize;
			
			points[16] = x + 7 *linesize;
			points[17] = y + 9 *linesize;
			points[18] = x + 6 *linesize;
			points[19] = y + 10 *linesize;
			
			points[20] = x + 1 *linesize;
			points[21] = y + 10 *linesize;
			points[22] = x + 6 *linesize;
			points[23] = y + 10 *linesize;
			
			addData(points, 24, data, tail);
		break;
		case 'q' :
			points[0] = x + 7 *linesize;
			points[1] = y + 4 * linesize;
			points[2] = x + 7 *linesize;
			points[3] = y + 14 *linesize;
			
			points[4] = x + 7 *linesize;
			points[5] = y + 4 *linesize;
			points[6] = x + 2 *linesize;
			points[7] = y + 4 *linesize;
			
			points[8] = x + 2 *linesize;
			points[9] = y + 4 *linesize;
			points[10] = x + 1 *linesize;
			points[11] = y + 5 *linesize;
			
			points[12] = x + 1 *linesize;
			points[13] = y + 5 *linesize;
			points[14] = x + 1 *linesize;
			points[15] = y + 9 *linesize;
			
			points[16] = x + 1 *linesize;
			points[17] = y + 9 *linesize;
			points[18] = x + 2 *linesize;
			points[19] = y + 10 *linesize;
			
			points[20] = x + 2 *linesize;
			points[21] = y + 10 *linesize;
			points[22] = x + 7 *linesize;
			points[23] = y + 10 *linesize;
			
			addData(points, 24, data, tail);
		break;
		case 'r' :
			points[0] = x + 1 *linesize;
			points[1] = y + 4 * linesize;
			points[2] = x + 1 *linesize;
			points[3] = y + 11 *linesize;
			
			points[8] = x + 1 *linesize;
			points[9] = y + 4 *linesize;
			points[10] = x + 7 *linesize;
			points[11] = y + 4 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case 's' :
			points[0] = x + 2 *linesize;
			points[1] = y + 3 *linesize;
			points[2] = x + 7 *linesize;
			points[3] = y + 3 *linesize;
			
			points[4] = x + 2 *linesize;
			points[5] = y + 3 *linesize;
			points[6] = x + 1 *linesize;
			points[7] = y + 4 *linesize;
			
			points[8] = x + 1 *linesize;
			points[9] = y + 4 *linesize;
			points[10] = x + 1 *linesize;
			points[11] = y + 6 *linesize;
			
			points[12] = x + 1 *linesize;
			points[13] = y + 6 *linesize;
			points[14] = x + 2 *linesize;
			points[15] = y + 7 *linesize;
			
			points[16] = x + 2 *linesize;
			points[17] = y + 7 *linesize;
			points[18] = x + 6 *linesize;
			points[19] = y + 7 *linesize;
			
			points[20] = x + 6 *linesize;
			points[21] = y + 7 *linesize;
			points[22] = x + 7 *linesize;
			points[23] = y + 8 *linesize;
			
			points[24] = x + 7 *linesize;
			points[25] = y + 8 *linesize;
			points[26] = x + 7 *linesize;
			points[27] = y + 10 *linesize;
			
			points[28] = x + 7 *linesize;
			points[29] = y + 10 *linesize;
			points[30] = x + 6 *linesize;
			points[31] = y + 11 *linesize;
			
			points[32] = x + 1 *linesize;
			points[33] = y + 11 *linesize;
			points[34] = x + 6 *linesize;
			points[35] = y + 11 *linesize;
			
			addData(points, 36, data, tail);
		break;
		//Special y case for letter t
		case 't' :
			points[0] = x + 4 *linesize;
			points[1] = y + 2 *linesize;
			points[2] = x + 4 *linesize;
			points[3] = y + 11 *linesize;
			
			points[4] = x + 4 *linesize;
			points[5] = y + 11 *linesize;
			points[6] = x + 7 *linesize;
			points[7] = y + 11 *linesize;
			
			points[8] = x + 1 *linesize;
			points[9] = y + 5 *linesize;
			points[10] = x + 7 *linesize;
			points[11] = y + 5 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case 'u' :
			points[0] = x + 1 *linesize;
			points[1] = y + 4 *linesize;
			points[2] = x + 1 *linesize;
			points[3] = y + 10 *linesize;
			
			points[4] = x + 1 *linesize;
			points[5] = y + 10 *linesize;
			points[6] = x + 2 *linesize;
			points[7] = y + 11 *linesize;
			
			points[8] = x + 2 *linesize;
			points[9] = y + 11 *linesize;
			points[10] = x + 6 *linesize;
			points[11] = y + 11 *linesize;
			
			points[12] = x + 7 *linesize;
			points[13] = y + 4 *linesize;
			points[14] = x + 7 *linesize;
			points[15] = y + 10 *linesize;
			
			points[16] = x + 7 *linesize;
			points[17] = y + 10 *linesize;
			points[18] = x + 6 *linesize;
			points[19] = y + 11 *linesize;
			
			addData(points, 20, data, tail);
		break;
		case 'v' :
			points[0] = x + 1 *linesize;
			points[1] = y + 4 *linesize;
			points[2] = x + 4 *linesize;
			points[3] = y + 11 *linesize;
			
			points[4] = x + 7 *linesize;
			points[5] = y + 4 *linesize;
			points[6] = x + 4 *linesize;
			points[7] = y + 11 *linesize;
			
			addData(points, 8, data, tail);
		break;
		//Special x case w
		case 'w' :
			points[0] = x;
			points[1] = y + 4 *linesize;
			points[2] = x + 2 *linesize;
			points[3] = y + 11 *linesize;
			
			points[4] = x + 4 *linesize;
			points[5] = y + 4 *linesize;
			points[6] = x + 2 *linesize;
			points[7] = y + 11 *linesize;
			
			points[8] = x + 4 *linesize;
			points[9] = y + 4 *linesize;
			points[10] = x + 6 *linesize;
			points[11] = y + 11 *linesize;
			
			points[12] = x + 8 *linesize;
			points[13] = y + 4 *linesize;
			points[14] = x + 6 *linesize;
			points[15] = y + 11 *linesize;
			
			addData(points, 16, data, tail);
		break;
		case 'x' :
			points[0] = x + 1 *linesize;
			points[1] = y + 4 *linesize;
			points[2] = x + 7 *linesize;
			points[3] = y + 11 *linesize;
			
			points[4] = x + 7 *linesize;
			points[5] = y + 4 *linesize;
			points[6] = x + 1 *linesize;
			points[7] = y + 11 *linesize;
			
			addData(points, 8, data, tail);
		break;
		case 'y' :
			points[0] = x + 1 *linesize;
			points[1] = y + 4 *linesize;
			points[2] = x + 1 *linesize;
			points[3] = y + 9 *linesize;
			
			points[4] = x + 1 *linesize;
			points[5] = y + 9 *linesize;
			points[6] = x + 2 *linesize;
			points[7] = y + 10 *linesize;
			
			points[8] = x + 2 *linesize;
			points[9] = y + 10 *linesize;
			points[10] = x + 7 *linesize;
			points[11] = y + 10 *linesize;
			
			points[12] = x + 7 *linesize;
			points[13] = y + 4 *linesize;
			points[14] = x + 7 *linesize;
			points[15] = y + 13 *linesize;
			
			points[16] = x + 7 *linesize;
			points[17] = y + 13 *linesize;
			points[18] = x + 6 *linesize;
			points[19] = y + 14 *linesize;
			
			points[20] = x + 6 *linesize;
			points[21] = y + 14 *linesize;
			points[22] = x + 2 *linesize;
			points[23] = y + 14 *linesize;
			
			points[24] = x + 2 *linesize;
			points[25] = y + 14 *linesize;
			points[26] = x + 1 *linesize;
			points[27] = y + 13 *linesize;
			
			addData(points, 28, data, tail);
		break;
		case 'z' :
			points[0] = x + 1 *linesize;
			points[1] = y + 4 *linesize;
			points[2] = x + 7 *linesize;
			points[3] = y + 4 *linesize;
			
			points[4] = x + 7 *linesize;
			points[5] = y + 4 *linesize;
			points[6] = x + 1 *linesize;
			points[7] = y + 11 *linesize;
			
			points[8] = x + 1 *linesize;
			points[9] = y + 11 *linesize;
			points[10] = x + 7 *linesize;
			points[11] = y + 11 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case '0' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y;
			
			points[4] = x + 8 *linesize;
			points[5] = y;
			points[6] = x + 8 *linesize;
			points[7] = y + 14 *linesize;
			
			points[8] = x;
			points[9] = y;
			points[10] = x;
			points[11] = y + 14 *linesize;
			
			points[12] = x;
			points[13] = y + 14 *linesize;
			points[14] = x + 8 *linesize;
			points[15] = y + 14 *linesize;
			
			addData(points, 16, data, tail);
		break;
		case '8' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 14 *linesize;
			
			addData(points, 4, data, tail);
		case '3' :
			points[0] = x;
			points[1] = y + 7 *linesize;
			points[2] = x + 8 *linesize;
			points[3] = y + 7 *linesize;
			
			points[4] = x;
			points[5] = y + 14 *linesize;
			points[6] = x + 8 *linesize;
			points[7] = y + 14 *linesize;
			
			addData(points, 8, data, tail);
		case '7' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y;
			
			addData(points, 4, data, tail);
		case '1' :
			points[0] = x + 8 *linesize;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y + 14 *linesize;
			
			addData(points, 4, data, tail);
		break;
		case '2' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y;
			
			points[4] = x + 8 *linesize;
			points[5] = y;
			points[6] = x + 8 *linesize;
			points[7] = y + 7 *linesize;
			
			points[8] = x + 8 *linesize;
			points[9] = y + 7 *linesize;
			points[10] = x;
			points[11] = y + 7 *linesize;
			
			points[12] = x;
			points[13] = y + 7 *linesize;
			points[14] = x;
			points[15] = y + 14 *linesize;
			
			points[16] = x;
			points[17] = y + 14 *linesize;
			points[18] = x + 8 *linesize;
			points[19] = y + 14 *linesize;
			
			addData(points, 20, data, tail);
		break;
		case '9' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y;
			
			points[4] = x;
			points[5] = y + 14 *linesize;
			points[6] = x + 8 *linesize;
			points[7] = y + 14 *linesize;
			
			addData(points, 8, data, tail);
		case '4' :
			points[0] = x;
			points[1] = y;
			points[2] = x;
			points[3] = y + 7 *linesize;
			
			points[4] = x;
			points[5] = y + 7 *linesize;
			points[6] = x + 8 *linesize;
			points[7] = y + 7 *linesize;
			
			points[8] = x + 8 *linesize;
			points[9] = y;
			points[10] = x + 8 *linesize;
			points[11] = y + 14 *linesize;
			
			addData(points, 12, data, tail);
		break;
		case '6' :
			points[0] = x;
			points[1] = y + 7 *linesize;
			points[2] = x;
			points[3] = y + 14 *linesize;
			
			addData(points, 4, data, tail);
		case '5' :
			points[0] = x;
			points[1] = y;
			points[2] = x + 8 *linesize;
			points[3] = y;
			
			points[4] = x;
			points[5] = y;
			points[6] = x;
			points[7] = y + 7 *linesize;
			
			points[8] = x + 8 *linesize;
			points[9] = y + 7 *linesize;
			points[10] = x;
			points[11] = y + 7 *linesize;
			
			points[12] = x + 8 *linesize;
			points[13] = y + 7 *linesize;
			points[14] = x + 8 *linesize;
			points[15] = y + 14 *linesize;
			
			points[16] = x;
			points[17] = y + 14 *linesize;
			points[18] = x + 8 *linesize;
			points[19] = y + 14 *linesize;
			
			addData(points, 20, data, tail);
		break;
		case ':' :
			points[0] = x + 4 *linesize;
			points[1] = y + 1 *linesize;
			points[2] = x + 4 *linesize;
			points[3] = y + 2 *linesize;
			
			addData(points, 4, data, tail);
		case '.' :
			points[0] = x + 4 *linesize;
			points[1] = y + 12 *linesize;
			points[2] = x + 4 *linesize;
			points[3] = y + 13 *linesize;
			
			addData(points, 4, data, tail);
		break;
		case '?' :
			points[0] = x + 4 *linesize;
			points[1] = y + 12 *linesize;
			points[2] = x + 4 *linesize;
			points[3] = y + 13 *linesize;
			
			points[4] = x + 4 *linesize;
			points[5] = y + 9 *linesize;
			points[6] = x + 4 *linesize;
			points[7] = y + 7 *linesize;
			
			points[8] = x + 4 *linesize;
			points[9] = y + 7 *linesize;
			points[10] = x + 8 *linesize;
			points[11] = y + 5 *linesize;
			
			points[12] = x + 8 *linesize;
			points[13] = y + 5 *linesize;
			points[14] = x + 8 *linesize;
			points[15] = y + 1 *linesize;
			
			points[16] = x + 8 *linesize;
			points[17] = y + 1 *linesize;
			points[18] = x + 6 *linesize;
			points[19] = y;
			
			points[20] = x + 6 *linesize;
			points[21] = y;
			points[22] = x + 2 *linesize;
			points[23] = y;
			
			points[24] = x + 2 *linesize;
			points[25] = y;
			points[26] = x;
			points[27] = y + 1 *linesize;
			
			addData(points, 28, data, tail);
		break;
		case ' ' :
		break;
		default :
			ofstream File;
			File.open("log.txt");
			File << "Unsupported character called in addLetterData" << endl;
			File.close();
			exit(2);
	}
}

void convertStringToLetterData(string s, float x, float y, int linesize, float *data, int& tail, bool enableOffset) {
	for (unsigned int i = 0; i < s.length(); i++) {
		if (enableOffset && s[i] > 96)
			addLetterData(x+DEFAULT_STRINGWIDTH*i*linesize, y + 3*linesize, s[i], linesize, data, tail);
		else
			addLetterData(x+DEFAULT_STRINGWIDTH*i*linesize, y, s[i], linesize, data, tail);
	}
}

float getStringWidth(string s, int linesize) {
	return DEFAULT_STRINGWIDTH*s.length()*linesize;
}
