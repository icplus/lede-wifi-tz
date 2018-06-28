#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define ART_PARTITION_FILE "/bin/art-partition.bin"

#define  BOOL int  
#define  FALSE 0  
#define  TRUE  1


BOOL macIncrease(char * mac) //INCREASE MAC BY ONE  
{  
    int num=16;  
    while(num>=0)  
    {  
        if('9' == mac[num])  
        {  
            mac[num]='A';  
            break;  
        }  
        else if('F' == mac[num])  
        {  
            mac[num]='0';  
            num--;  
        } 
        else if(':' == mac[num]) 
        { 
            num--; 
        } 
        else  
        {  
            mac[num]++;  
            break;  
        }  
    }  
    if(-1 == num)  
         return FALSE;  //inclease FAIL  
    else  
        return TRUE;  
}

int main(int argc, char *argv[])
{
    //printf("New lan_mac: %s\n", argv[2]);
    //printf("New wan_mac: %s\n", argv[1]);
   // printf("New wifi_mac: %s\n", argv[3]);

    unsigned char wan_mac[7], lan_mac[7], wifi_mac[7], ch;
    char new_wan_mac[18], new_lan_mac[18], new_wifi_mac[18], macAdd[18];

    int art, count;
    int i, k;

    printf("please input the wifi mac :\n");
    scanf("%s",macAdd);

    strcpy(new_wifi_mac,macAdd);

    if(TRUE == macIncrease(macAdd))
    {  
        strcpy(new_lan_mac,macAdd); 
        printf("new_lan_mac:%s\n", new_lan_mac);
    }
    

    if(TRUE == macIncrease(macAdd))
    {  
        strcpy(new_wan_mac,macAdd); 
        printf("new_wan_mac:%s\n", new_wan_mac);
    }
    else
    {
        printf("wrong in increase\n");
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
