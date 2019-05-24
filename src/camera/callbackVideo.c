// callbackVideo.cpp 
//




#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>


#include <assert.h>
#include <getopt.h>      
#include <fcntl.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>


#include "pgLibDevVideoIn.h"
#include "callbackVideo.h"
#include "hardware_api.h"


int s_iDevID_VideoIn = -1;

#if 0
static void* VideoInputThreadProc(void* lp)
{
	printf("VideoInputThreadProc\n");

	if (pthread_detach(pthread_self()) != 0) {
		printf("VideoInputThreadProc, err=%d", errno);
	}
	fd = open("/dev/video0", O_RDWR, 0);	
	if (fd<0)
	{
		printf("open error\n");
		return  NULL;
	}
	struct v4l2_format fmt;							
	memset( &fmt, 0, sizeof(fmt));
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(uVideoMode == 10){	
		fmt.fmt.pix.width = 1280;							
		fmt.fmt.pix.height =720;
	}
	if(uVideoMode == 3){	
		fmt.fmt.pix.width = 640;							
		fmt.fmt.pix.height =480;
	}
								
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;	
	fmt.fmt.pix.field = V4L2_FIELD_ANY;
	if (ioctl(fd, VIDIOC_S_FMT, &fmt) < 0) 	//���ø�ʽ
	{
		printf("set format failed\n");

	}
	struct v4l2_requestbuffers req;				 //����֡����
	memset(&req, 0, sizeof (req));
	req.count = 1; 						 //�������������ɱ����ͼƬ����
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;			 //���������ͣ���Զ����V4L2_BUF_TYPE_VIDEO_CAPTURE
	req.memory = V4L2_MEMORY_MMAP; 				 //�洢���ͣ�V4L2_MEMORY_MMAP��V4L2_MEMORY_USERPTR
	if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) 		 //ʹ������Ч
	{
		perror("request buffer error \n");
	}
	buffers = (struct buffer *)calloc(req.count, sizeof(*buffers));//�ڴ��н�����Ӧ�ռ�	

	struct v4l2_buffer buf;
	 
	memset( &buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;		 //���������ͣ���Զ����V4L2_BUF_TYPE_VIDEO_CAPTURE
	buf.memory = V4L2_MEMORY_MMAP; 			 //�洢���ͣ�V4L2_MEMORY_MMAP���ڴ�ӳ�䣩��V4L2_MEMORY_USERPTR���û�ָ�룩
	buf.index = 0;
	if (ioctl(fd, VIDIOC_QUERYBUF, &buf) < 0)		 //ʹ������Ч
	{
		printf("VIDIOC_QUERYBUF error\n");
	}
	buffers[0].length = buf.length;
	buffers[0].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset); 		 
	if (buffers[0].start == MAP_FAILED)
	{
		perror("buffers error\n");
	}
	if (ioctl(fd, VIDIOC_QBUF, &buf) < 0)			 //���뻺�����
	{
		printf("VIDIOC_QBUF error\n");
	}
	enum v4l2_buf_type type;					 //��ʼ��Ƶ��ʾ
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;			 //���������ͣ���Զ����V4L2_BUF_TYPE_VIDEO_CAPTURE
	if (ioctl(fd, VIDIOC_STREAMON, &type) < 0)
	{
		printf("VIDIOC_STREAMON error\n");
	}

	unsigned int sps_frm=0;
	unsigned char ucData[10] = {0};

	while (s_uRunning_VideoIn != 0) {
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		ioctl (fd, VIDIOC_DQBUF, &buf); //���вɼ���֡����
		unsigned int uFlag = 1;
		pgDevVideoInCaptureProc(s_iDevID_VideoIn,  buffers[0].start, buf.bytesused, PG_DEV_VIDEO_IN_FMT_MJPEG, uFlag);
		ioctl (fd, VIDIOC_QBUF, &buf); //�ٽ�������	
		usleep(80 * 1000);
	}
	printf("VideoInputThreadProc\n");
	pthread_exit(NULL);
}
#endif
static int HardwareVideoCaptureCallback(void *context, void *data, int len, int is_key_frame)
{	
	unsigned uFlag = 0;
	if (is_key_frame) { 
		uFlag |= PG_DEV_VIDEO_IN_FLAG_KEY_FRAME;
	}
	pgDevVideoInCaptureProc(s_iDevID_VideoIn, data, len, PG_DEV_VIDEO_IN_FMT_H264, uFlag);
	return 0;
}


static int VideoInOpen_xxx(unsigned int uDevNO, unsigned int uPixBytes,
	unsigned int uWidth, unsigned int uHeight, unsigned int uBitRate,
	unsigned int uFrmRate, unsigned int uKeyFrmRate)
{
	printf("=============>VideoInOpen_xxx: uDevNO=%u\n",uDevNO);
	//printf("VideoInOpen: uDevNO=%u, uWidth=%u, uHeight=%u, uBitRate=%u, uFrmRate=%u, uKeyFrmRate=%u\n",
	//	uDevNO, uWidth, uHeight, uBitRate, uFrmRate, uKeyFrmRate);

	rtsp_server_start();

	#if 0
	if (hardware_video_capture_open(0, uDevNO, uWidth, uHeight, (uBitRate * 1024),
		(1000 / uFrmRate), uKeyFrmRate, HardwareVideoCaptureCallback))
	{
		s_iDevID_VideoIn = (uDevNO << 16) | (time(0) & 0xffff);
	}
	#endif
	s_iDevID_VideoIn = (uDevNO << 16) | (time(0) & 0xffff);

	return s_iDevID_VideoIn;
}

static void VideoInClose(int iDevID)
{
	printf("VideoInClose: iDevID=%d\n", iDevID);
	int ret = rtsp_server_stop();
	printf("-------------------------------->>>>>VideoInClose ret = %d\n",ret);
	// Stop capture video ...

}


static void VideoInCtrl(int iDevID, unsigned int uCtrl, unsigned int uParam)
{
	printf("VideoInCtrl: iDevID=%d, uCtrl=%u\n", iDevID, uCtrl);

	if (uCtrl == PG_DEV_VIDEO_IN_CTRL_PULL_KEY_FRAME) {
		//hardware_video_capture_force_key_frame(0);
	}
}

static PG_DEV_VIDEO_IN_CALLBACK_S s_stCallback_VideoIn = {
	VideoInOpen_xxx,
	VideoInClose,
	VideoInCtrl
};

void RegisterVideoCallback(void)
{
	pgDevVideoInSetCallback(&s_stCallback_VideoIn);  
}
