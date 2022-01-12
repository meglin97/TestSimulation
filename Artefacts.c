#include <CUnit.h>
#include <Artefacts.h>

void encrypt(char str[], char str_out[])
{
	int shift = 5;
	char ch;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		ch = str[i];
		if (ch >= 'a' && ch <= 'z')
		{
			ch = ch + shift;
			if (ch > 'z')
			{
				ch = ch - 'z' + 'a' - 1;
			}
			str_out[i] = ch;
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			ch = ch + shift;
			if (ch > 'Z')
			{
				ch = ch - 'Z' + 'A' - 1;
			}
			str_out[i] = ch;
		}
	}

}

void decrypt(char str[], char str_out[], int shift) {
	char ch;
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
}

/*
 * reçoit les informations de radar et du système de frein
 * envoie un ordre au système de frein et les informations de danger au véhicule alentour
 */
void CSC_control(char danger_info[20], char frein_info[20],
		char msg_danger_in[20], SysFrein sf, CSC csc) {
	if (strcmp(danger_info, "danger") || strcmp(msg_danger_in, "danger")) {
		sf.order = FREINAGE_URGENT;
	} else if (strcmp(danger_info, "obstacle")) {
		sf.order = FREINER;
	} else {
		sf.order = AVANCER;
	}
}

/*
 *  reçoit message venant d'autre véhicules et
 *  envoie les messages de danger aux autres véhicules
 */
void CU(CSC csc, MSG msg_danger_out, MSG msg_danger_in) {
	msg_danger_out.shift = 5;
	if (msg_danger_in.msg != NULL) {
		time(&msg_danger_in.receive); // indique l'heure de la réception du message par CSC
		decrypt(msg_danger_in.msg, csc.order_out, msg_danger_in.shift);
	}
	if (msg_danger_out.msg != NULL) {
		time(&msg_danger_out.send); // indique l'heure de l'envoie du message par CSC
		encrypt(csc.msg_detect_in, msg_danger_out.msg);
	}
}
