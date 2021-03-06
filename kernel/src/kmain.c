#include <stdint.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "pmm.h"
#include "pl110.h"
#include "pl181.h"
#include "console.h"
#include "vfs.h"
#include "block_device.h"
#include "fat32.h"
#include "bmp.h"

#include "nescart.h"
#include "nes6502.h"
#include "nesbus.h"




void kmain()
{
	init_pmm();
	
	//Init lcd display and console
	init_pl110(0x10120000);
	init_console();
	
	//Initalize mmci
	init_pl181(0x10005000);
	struct BLOCK_DEVICE * sd = (struct BLOCK_DEVICE*) pl181_get_block_device();
	fs_driver * fat_driver =  init_fatfs(sd);
	if(fat_driver != NULL)
	{
		int mval = vfs_mount(NULL,fat_driver);
		if(mval != 0)
		{
			printf("Failed to mount FS! \n");
			return;
		}
	}

	init_nes_bus();
	init_nes_6502();
    int result = nes_load_cart("/roms/nestest.nes");
    nes_reset();
    nes_dissasemble_display();
    
    for(int i =0; i < 10; i++)
    {
        nes_clock();
        nes_dissasemble_display();
    }
}









