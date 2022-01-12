enum Action
{
    FREINAGE_URGENT,
    FREINER,
    AVANCER

};
typedef struct SysFrein
{
    char frein[10];
    enum Action order;
} SysFrein;

typedef struct MSG
{
    char msg[20];
    int shift;
} MSG;

typedef struct CSC
{
    char msg_detect_in[20];
    char msg_frein_in[20];
    char msg_danger_in[20];
    char msg_danger_out[20];
    char order_out[20];
    enum Action order;
} CSC;

void encrypt(char str[], char str_out[]);
void decrypt(char str[], char str_out[], int shift);
void CSC_control(char danger_info[20], char frein_info[20], char msg_danger_in[20], SysFrein sf, CSC csc);
void CU(CSC csc, MSG msg_danger_out, MSG msg_danger_in);