#ifndef ARTEFACTS_H
#define ARTEFACTS_H

#include <time.h>
#include <string.h>
#include <stdlib.h>
typedef struct Position {
	float latitude;
	float longitude;
} Position;

typedef struct SysFrein {
	char frein[10];
	Position pos;
	float vitesse;
} SysFrein;

typedef struct MSG {
	char msg[20];
	int shift;
	time_t send;
	time_t receive;
} MSG;

typedef struct CSC {
	char msg_detect_in[20];
	char msg_frein_in[20];
	char msg_danger_in[20];
	char msg_danger_out[20];
	char order_out[20];
} CSC;

char* encrypt(char *str);
char* decrypt(char *str, int shift);

void CSC_control(MSG danger_info, MSG msg_danger_in, CSC csc);
void CU(MSG msg_danger_out, MSG msg_danger_in, CSC csc);

char* SystemFrein_control(MSG danger_info, MSG msg_danger_in, CSC csc,
		SysFrein sf);
int msg_size(char *msg_info);

#endif
