#include "Artefacts.h"

char* encrypt(char *str) {
	int shift = 5;
	char *str_out = malloc(sizeof(str));
	char ch;
	for (int i = 0; str[i] != '\0'; ++i) {
		ch = str[i];
		if (ch >= 'a' && ch <= 'z') {
			ch = ch + shift;
			if (ch > 'z') {
				ch = ch - 'z' + 'a' - 1;
			}
			str_out[i] = ch;
		} else if (ch >= 'A' && ch <= 'Z') {
			ch = ch + shift;
			if (ch > 'Z') {
				ch = ch - 'Z' + 'A' - 1;
			}
			str_out[i] = ch;
		}
	}
	return str_out;
}

char* decrypt(char *str, int shift) {
	char ch;
	char *str_out = malloc(sizeof(str));
	for (int i = 0; str[i] != '\0'; ++i) {
		ch = str[i];
		if (ch >= 'a' && ch <= 'z') {
			ch = ch - shift;
			if (ch < 'a') {
				ch = ch + 'z' - 'a' + 1;
			}
			str_out[i] = ch;
		} else if (ch >= 'A' && ch <= 'Z') {
			ch = ch - shift;
			if (ch < 'A') {
				ch = ch + 'Z' - 'A' + 1;
			}
			str_out[i] = ch;
		}
	}
	return str_out;
}

/*
 * reçoit les informations de radar et du système de frein
 * envoie un ordre au système de frein et les informations de danger au véhicule alentour
 * si danger alors freinager urgent, si obstacle alors freiner sinon avancer
 *
 */
void CSC_control(MSG danger_info, MSG msg_danger_in, CSC csc) {
	if (strcmp(danger_info.msg, "danger")
			|| strcmp(msg_danger_in.msg, "danger")) {
		strcpy(csc.order_out, "FREINAGE_URGENT");
	} else if (strcmp(danger_info.msg, "obstacle")
			|| strcmp(msg_danger_in.msg, "obstacle")) {
		strcpy(csc.order_out, "FREINER");
	} else {
		strcpy(csc.order_out, "AVANCER");
	}
}

/*
 *  reçoit message venant d'autre véhicules et
 *  envoie les messages de danger aux autres véhicules
 *
 */
void CU(MSG msg_danger_out, MSG msg_danger_in, CSC csc) {
	msg_danger_out.shift = 5;
	if (msg_danger_in.msg != NULL) {
		time(&msg_danger_in.receive); // indique l'heure de la réception du message par CSC
		strcpy(csc.order_out, decrypt(msg_danger_in.msg, msg_danger_in.shift));
	}
	if (msg_danger_out.msg != NULL) {
		time(&msg_danger_out.send); // indique l'heure de l'envoie du message par CSC
		strcpy(msg_danger_out.msg, encrypt(csc.msg_detect_in));
	}
}

char* SystemFrein_control(MSG danger_info, MSG msg_danger_in, CSC csc,
		SysFrein sf) {
	char *out = malloc(sizeof(csc.order_out));
	CSC_control(danger_info, msg_danger_in, csc);
	strcpy(out, csc.order_out);
	return out;
}

int msg_size(char *msg_info) {
	return (sizeof(&msg_info) / sizeof(msg_info[0]));
}
