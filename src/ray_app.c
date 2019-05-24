#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

#include <assert.h>

#include "ray_module_vr.h"
#include "duilite.h"
#include "asoundlib.h"
#include "ray_app.h"
bool vr_started = false;


int start(app_t app)
{
	switch(app)
	{
		case MUSICPLAYER:
			mozart_musicplayer_startup();
			
			break;
		case VR:
			if (ray_vr_init(process_vr_callback)) {
				printf("init error, vr disabled!!\n");
				return -1;
			}	
			sleep(1);
			if (ray_vr_start()) {  //��Ҫ�ȴ������������翪ʼ���ſ�����Դ�ſ�ʼ
				printf("start error, vr disabled!!\n");
				ray_vr_uninit();
				return -1;
			}
			
			vr_started = true;
			
		default:
			break;
	}

	return 0;
}


int stop(app_t app)
{
	
	switch(app)
	{
		case MUSICPLAYER:
			mozart_musicplayer_shutdown();
			break;
		case VR:

			ray_vr_uninit();
			vr_started = false;
			break;
		default:
			break;
	}


	return 0;
}


int startall()
{
	
	start(MUSICPLAYER);
	start(VR);
	mozart_module_cloud_music_startup();  //������Ҫ   ray_vr_init ע��Ļص�����
	
	
	return 0;
}


int stopall()
{
	printf("======stopall=========\n");
	stop(MUSICPLAYER);
	stop(VR);

	printf("======stopall=========ZZZZZZZZZZZZZZ\n");
	return 0;
}


