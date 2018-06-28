#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define ART_PARTITION_FILE "/bin/art-partition.bin"

/*
* 检查MAC合法性
* 输入：mac_str--MAC字符串，如11:AA:BB:CC:22:11 不区分大小写
* 返回：-1--失败，0--成功
*/
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
/*
* 将MAC字符串转化为数组
* 输入：str--MAC字符串，格式如：11:AA:BB:CC:DD:22
* 输出：mac--MAC数组，6字节
* 返回：-1--失败，0--成功
*/
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
/*
* 实现MAC地址数组中MAC值加1
*/
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

void mac_array_del1(unsigned char *mac)
{
    int i;

    for (i=5; i>=0; i--)
    {   
	if (mac[i] < 255)
	{
	    mac[i]--;
	    break;
	}
	else
	{
	    mac[i] = 0;
	}
						        }   
}

int main(int argc, char *argv[])
{
    unsigned char wan_mac[7], lan_mac[7], wifi_mac[7], mac[7], ch;
    char new_wan_mac[18], new_lan_mac[18], new_wifi_mac[18], macAddr[18];

    int art, count;
    int i, k;
    //printf("New wifi_mac: %s\n", argv[1]);
    printf("new lan mac: %s\n", argv[1]);
    //printf("please input the wifi mac :\n");
    //scanf("%s",macAddr);
    strcpy(new_lan_mac, argv[1]);

    if(mac_str_to_array(argv[1], mac) == 0)
    {
		mac_array_del1(mac);
		sprintf(new_wifi_mac,"%02x:%02x:%02x:%02x:%02x:%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
		printf("new wifi mac:%s\n", new_wifi_mac);
		mac_array_plus1(mac);
		sprintf(new_wan_mac,"%02x:%02x:%02x:%02x:%02x:%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
		printf("new wan mac:%s\n", new_wan_mac);
    }

    art = open(ART_PARTITION_FILE, O_RDWR);

    if(art < 0)
    {
	perror("open.");
    }

/* Write wan mac address */
    for(k = i = 0; i < 6; i++)
    {
	wan_mac[i] = 0;

	//hight bits
	if( isdigit(new_lan_mac[k]) )
	{	
	    wan_mac[i] += (new_lan_mac[k] - 48) * 16;
	}else if(isupper(new_lan_mac[k]))
	{
	    wan_mac[i] += (new_lan_mac[k] - 55) * 16;
	}else if(islower(new_lan_mac[k]))
	{
	    wan_mac[i] += (new_lan_mac[k] -87) * 16;
	}else
	{
	    printf("address wan_mac error.\n");
	}

	//low bits	
	if( isdigit(new_lan_mac[k+1]) )
	{	
	    wan_mac[i] += new_lan_mac[k+1] - 48;
	}else if(isupper(new_lan_mac[k+1]))
	{
	    wan_mac[i] += new_lan_mac[k+1] - 55;
	}else if(islower(new_lan_mac[k+1]))
	{
	    wan_mac[i] += new_lan_mac[k+1] -87;
	}else
	{
	    printf("address wan_mac error.\n");
	}
	k += 3;
    }

    for(i = 0; i < 6 ; i++)
    {
	write(art, &wan_mac[i], 1);
	printf("%x:", wan_mac[i]);
    }
    printf("\n");

/* write lan mac address */
    for(k = i = 0; i < 6; i++)
    {
	lan_mac[i] = 0;

	//hight bits
	if( isdigit(new_wan_mac[k]) )
	{	
	    lan_mac[i] += (new_wan_mac[k] - 48) * 16;
	}else if(isupper(new_wan_mac[k]))
	{
	    lan_mac[i] += (new_wan_mac[k] - 55) * 16;
	}else if(islower(new_wan_mac[k]))
	{
	    lan_mac[i] += (new_wan_mac[k] -87) * 16;
	}else
	{
	    printf("address wan_mac error.\n");
	}

	//low bits	
	if( isdigit(new_wan_mac[k+1]) )
	{	
	    lan_mac[i] += new_wan_mac[k+1] - 48;
	}else if(isupper(new_wan_mac[k+1]))
	{
	    lan_mac[i] += new_wan_mac[k+1] - 55;
	}else if(islower(new_wan_mac[k+1]))
	{
	    lan_mac[i] += new_wan_mac[k+1] -87;
	}else
	{
	    printf("address wan_mac error.\n");
	}
	k += 3;
    }

    for(i = 0; i < 6 ; i++)
    {
	write(art, &lan_mac[i], 1);
	printf("%x:", lan_mac[i]);
    }
    printf("\n");

/* write wifi mac address */
    for(k = i = 0; i < 6; i++)
    {
	wifi_mac[i] = 0;

	//hight bits
	if( isdigit(new_wifi_mac[k]) )
	{	
	    wifi_mac[i] += (new_wifi_mac[k] - 48) * 16;
	}else if(isupper(new_wifi_mac[k]))
	{
	    wifi_mac[i] += (new_wifi_mac[k] - 55) * 16;
	}else if(islower(new_wifi_mac[k]))
	{
	    wifi_mac[i] += (new_wifi_mac[k] -87) * 16;
	}else
	{
	    printf("address wifi_mac error.\n");
	}

	//low bits	
	if( isdigit(new_wifi_mac[k+1]) )
	{	
	    wifi_mac[i] += new_wifi_mac[k+1] - 48;
	}else if(isupper(new_wifi_mac[k+1]))
	{
	    wifi_mac[i] += new_wifi_mac[k+1] - 55;
	}else if(islower(new_wifi_mac[k+1]))
	{
	    wifi_mac[i] += new_wifi_mac[k+1] -87;
	}else
	{
	    printf("address wifi_mac error.\n");
	}
	k += 3;
    }

    lseek(art, 4098, SEEK_SET);

    for(i = 0; i < 6 ; i++)
    {
	write(art, &wifi_mac[i], 1);
	printf("%x:", wifi_mac[i]);
    }
    printf("\n");
    close(art);
}
