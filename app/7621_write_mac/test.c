#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
int check_mac_valid(char *mac_str)
{
    if (strlen(mac_str) != 17)
    {
        return -1;
    }

    char buf[20];
    strcpy(buf, mac_str);
    char *strtmp = strtok(buf, ":");
    int hexnum = 0;
    while (strtmp != NULL)
    {
        if (strlen(strtmp) != 2)
        {
            return -1;
        }
        if ((strtmp[0] >= '0' && strtmp[0] <= '9') || (strtmp[0] >= 'A' && strtmp[0] <= 'F') || (strtmp[0] >= 'a' && strtmp[0] <= 'f'))
        {
            if ((strtmp[1] >= '0' && strtmp[1] <= '9') || (strtmp[1] >= 'A' && strtmp[1] <= 'F') || (strtmp[1] >= 'a' && strtmp[1] <= 'f'))
            {
                hexnum ++;
                strtmp = strtok(NULL, ":");
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }

    }
    if (hexnum != 6)
    {
        return -1;
    }

    return 0;
}

int mac_str_to_array( char *str, unsigned char *mac)
{
    int i;
    char *s, *e;

    if ((mac == NULL) || (str == NULL))
    {
        return -1;
    }

    if (check_mac_valid(str) == -1)
    {
        return -1;
    }

    s = (char *) str;
    for (i = 0; i < 6; ++i)
    {
        mac[i] = s ? strtoul (s, &e, 16) : 0;
        if (s)
           s = (*e) ? e + 1 : e;
    }

    return 0;
}

void mac_array_plus1(unsigned char *mac)
{
    int i;

    for (i=5; i>=0; i--)
    {
        if (mac[i] < 255)
        {
            mac[i]++;
            break;
        }
        else
        {
            mac[i] = 0;
        }
    }
}

int main(int argc, char **argv)  
{  
    unsigned char macaddr[8] = {0}, wifi_mac[8];
    unsigned char wifi_mac_buf[20];
    char macaddr_str[18] = "8e:b2:cf:89:00:4f";  
    mac_str_to_array(macaddr_str, macaddr);

    mac_array_plus1(macaddr);  
    printf("%02x %02x\n",macaddr[0],macaddr[1]);
    printf("%02x %02x\n",macaddr[2],macaddr[3]);
    printf("%02x %02x\n",macaddr[4],macaddr[5]);
    sprintf(wifi_mac_buf,"%02x:%02x:%02x:%02x:%02x:%02x",macaddr[0],macaddr[1],macaddr[2],macaddr[3],macaddr[4],macaddr[5]);
    printf("wifi_mac:%s\n", wifi_mac_buf); 
  
    return 0;  
}  
