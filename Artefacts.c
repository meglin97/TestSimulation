
#include <stdbool.h>
#include <CUnit.h>

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

void decrypt(char str[], char str_out[], int shift)
{
    char ch;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        ch = str[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - shift;
            if (ch < 'a')
            {
                ch = ch + 'z' - 'a' + 1;
            }
            str_out[i] = ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch - shift;
            if (ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
            str_out[i] = ch;
        }
    }
}

void CSC_control(char danger_info[20], char frein_info[20], char msg_danger_in[20], SysFrein sf, CSC csc)
{
    if (strcmp(danger_info, "danger") || strcmp(msg_danger_in, "danger"))
    {
        sf.order = FREINAGE_URGENT;
    }
    else if (strcmp(danger_info, "obstacle"))
    {
        sf.order = FREINER;
    }
    else
    {
        sf.order = AVANCER;
    }
}
void CU(CSC csc, MSG msg_danger_out, MSG msg_danger_in)
{
    msg_danger_out.shift = 5;

    encrypt(csc.msg_detect_in, msg_danger_out.msg);
    decrypt(msg_danger_in.msg, csc.order_out, msg_danger_in.shift);
}
/*
enum MSG
{
    DANGER,
    OBSTACLE,
    FREINAGE,
    FREINAGE_URGENT,
    FREINER,
    AVANCER

};

bool is_danger(bool danger, enum MSG detection)
{
    if (danger == true && detection == DANGER)
    {
        return true;
    }
    return false;
}

bool is_obstacle(bool obstable, enum MSG detection)
{
    if (obstable == true && detection == OBSTACLE)
    {
        return true;
    }
    return false;
}

bool freinage(enum MSG order)
{
    return order == FREINER ? true : false;
}

enum MSG CSC(bool danger, enum MSG msg_detect, enum MSG msg_frein, enum MSG msg_danger_in)
{
    if (is_danger(danger, msg_detect) && msg_danger_in == DANGER)
    {
        return FREINAGE_URGENT;
    }
    else if (is_obstacle(danger, msg_detect) && msg_danger_in == OBSTACLE)
    {
        return FREINER;
    }
    else
    {
        return msg_frein;
    }
}*/
