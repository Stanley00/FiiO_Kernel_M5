#ifndef __FIIO_CTRL_H__
#define __FIIO_CTRL_H__
/* 定义幻数 */
#define MEMDEV_IOC_MAGIC2  '5'
#define MEMDEV_IOC_MAXNR2 3
/* 定义命令 */
#define MEMDEV_IO_BT_SOURCE_MODE   _IO(MEMDEV_IOC_MAGIC2, 0x1a)
#define MEMDEV_IO_EXIT_BT_SOURCE_MODE   _IO(MEMDEV_IOC_MAGIC2, 0x1b)
#define MEMDEV_IO_BT_POWER_ON   _IO(MEMDEV_IOC_MAGIC2, 0x1c)
#define MEMDEV_IO_GET_DATA_CMD_TEST _IOW(MEMDEV_IOC_MAGIC2, 0x1d, int)
#define MEMDEV_IO_SET_DATA_CMD_TEST _IOR(MEMDEV_IOC_MAGIC2, 0x1e, int)
#define MEMDEV_IO_BT_SINK_MODE   _IO(MEMDEV_IOC_MAGIC2, 0x1f)
#define MEMDEV_IO_EXIT_BT_SINK_MODE   _IO(MEMDEV_IOC_MAGIC2, 0x20)
#define MEMDEV_IO_BT_SINK_MODE_LOW_POWER   _IO(MEMDEV_IOC_MAGIC2, 0x21)
//set lcd rotate
//0 1 2 3(0,90,180,270) default:0
#define MEMDEV_IO_SET_DATA_CMD_LCD_ROTATE _IOW(MEMDEV_IOC_MAGIC2, 0x22, int)
#define MEMDEV_IO_GET_DATA_CMD_LCD_ROTATE _IOR(MEMDEV_IOC_MAGIC2, 0x23, int)
//audio stream
//0:D2P  1:DOP default:0
#define MEMDEV_IO_SET_DATA_CMD_D2P_OR_DOP _IOW(MEMDEV_IOC_MAGIC2, 0x24, int)
#define MEMDEV_IO_GET_DATA_CMD_D2P_OR_DOP _IOR(MEMDEV_IOC_MAGIC2, 0x25, int)

//I2S or spdif
//0:I2S  1:spdif  default:1
#define MEMDEV_IO_SET_DATA_CMD_I2S_OR_SPDIF _IOW(MEMDEV_IOC_MAGIC2, 0x26, int)
#define MEMDEV_IO_GET_DATA_CMD_I2S_OR_SPDIF _IOR(MEMDEV_IOC_MAGIC2, 0x27, int)

//BT sink or source
//0:source 1:sink default:0
#define MEMDEV_IO_SET_DATA_CMD_BT_SINK_OR_SOURCE _IOW(MEMDEV_IOC_MAGIC2, 0x28, int)
#define MEMDEV_IO_GET_DATA_CMD_BT_SINK_OR_SOURCE _IOR(MEMDEV_IOC_MAGIC2, 0x29, int)

//DAC mode
//0:high  1:low power  default:0
#define MEMDEV_IO_SET_DATA_CMD_DAC_MODE _IOW(MEMDEV_IOC_MAGIC2, 0x30, int)
#define MEMDEV_IO_GET_DATA_CMD_DAC_MODE _IOR(MEMDEV_IOC_MAGIC2, 0x31, int)

//usb 
//0:x1000  1:csr8675  2:no default:0
#define MEMDEV_IO_SET_USB_PATH_MODE _IOW(MEMDEV_IOC_MAGIC2, 0x32, int)
#define MEMDEV_IO_GET_USB_PATH_MODE _IOR(MEMDEV_IOC_MAGIC2, 0x33, int)

//changing 
//0:don't change  1:changing default:0
#define MEMDEV_IO_SET_HW_CHANGE _IOW(MEMDEV_IOC_MAGIC2, 0x34, int)
#define MEMDEV_IO_GET_HW_CHANGE _IOR(MEMDEV_IOC_MAGIC2, 0x35, int)

//计步器
#define MEMDEV_IO_SET_PEDOMETER _IOW(MEMDEV_IOC_MAGIC2, 0x36, int)
#define MEMDEV_IO_GET_PEDOMETER _IOR(MEMDEV_IOC_MAGIC2, 0x37, int)

/*
 * 1:local play bt source
 * 0:local play no bt source
 */
#define MEMDEV_IO_SET_PLAY_BT_SOURCE _IOW(MEMDEV_IOC_MAGIC2, 0x38, int)
#define MEMDEV_IO_GET_PLAY_BT_SOURCE _IOR(MEMDEV_IOC_MAGIC2, 0x39, int)


/*
 * pedometer stepthd setting
 */
#define MEMDEV_IO_SET_PEDOMETER_STEPTHD _IOW(MEMDEV_IOC_MAGIC2, 0x40, int)
#define MEMDEV_IO_GET_PEDOMETER_STEPTHD _IOR(MEMDEV_IOC_MAGIC2, 0x41, int)

#define MEMDEV_IO_SET_BT_RESET _IOW(MEMDEV_IOC_MAGIC2, 0x42, int)

#define MEMDEV_IO_SET_DAC_MUTE _IOW(MEMDEV_IOC_MAGIC2, 0x44, int)
#endif
