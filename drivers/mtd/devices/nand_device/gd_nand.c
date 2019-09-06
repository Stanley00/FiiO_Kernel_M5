#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/mtd/partitions.h>
#include <mach/spinand.h>
#include "../jz_sfc_common.h"
#include "nand_common.h"

#define GD_DEVICES_NUM          6
#define TSETUP		5
#define THOLD		5
#define	TSHSL_R		20
#define	TSHSL_W		20

#define TRD		80
#define TRD_4G		120
#define TPP		700
#define TBE		5

static struct jz_sfcnand_base_param gd_param[GD_DEVICES_NUM] = {

	[0] = {
		/*GD5F1GQ4UB*/
		.pagesize = 2 * 1024,
		.blocksize = 2 * 1024 * 64,
		.oobsize = 128,
		.flashsize = 2 * 1024 * 64 * 1024,

		.tSETUP  = TSETUP,
		.tHOLD   = THOLD,
		.tSHSL_R = TSHSL_R,
		.tSHSL_W = TSHSL_W,

		.tRD = TRD,
		.tPP = TPP,
		.tBE = TBE,

		.ecc_max = 0x8,
		.need_quad = 1,
	},
	[1] = {
		 /*GD5F2GQ4UB*/
		.pagesize = 2 * 1024,
		.blocksize = 2 * 1024 * 64,
		.oobsize = 128,
		.flashsize = 2 * 1024 * 64 * 2048,

		.tSETUP  = TSETUP,
		.tHOLD   = THOLD,
		.tSHSL_R = TSHSL_R,
		.tSHSL_W = TSHSL_W,

		.tRD = TRD,
		.tPP = TPP,
		.tBE = TBE,

		.ecc_max = 0x8,
		.need_quad = 1,
	},
	[2] = {
		/*GD5F4GQ4UB*/
		.pagesize = 4 * 1024,
		.blocksize = 4 * 1024 * 64,
		.oobsize = 256,
		.flashsize = 4 * 1024 * 64 * 2048,

		.tSETUP  = TSETUP,
		.tHOLD   = THOLD,
		.tSHSL_R = TSHSL_R,
		.tSHSL_W = TSHSL_W,

		.tRD = TRD_4G,
		.tPP = TPP,
		.tBE = TBE,

		.ecc_max = 0x8,
		.need_quad = 1,
	},
	[3] = {
		/*GD5F1GQ4UC*/
		.pagesize = 2 * 1024,
		.blocksize = 2 * 1024 * 64,
		.oobsize = 128,
		.flashsize = 2 * 1024 * 64 * 1024,

		.tSETUP  = TSETUP,
		.tHOLD   = THOLD,
		.tSHSL_R = TSHSL_R,
		.tSHSL_W = TSHSL_W,

		.tRD = TRD,
		.tPP = TPP,
		.tBE = TBE,

		.ecc_max = 0x8,
		.need_quad = 1,

	},
	[4] = {
		/*GD5F2GQ4UC*/
		.pagesize = 2 * 1024,
		.blocksize = 2 * 1024 * 64,
		.oobsize = 128,
		.flashsize = 2 * 1024 * 64 * 2048,

		.tSETUP  = TSETUP,
		.tHOLD   = THOLD,
		.tSHSL_R = TSHSL_R,
		.tSHSL_W = TSHSL_W,

		.tRD = TRD,
		.tPP = TPP,
		.tBE = TBE,

		.ecc_max = 0x8,
		.need_quad = 1,
	},
	[5] = {
		/*GD5F4GQ4UC*/
		.pagesize = 4 * 1024,
		.blocksize = 4 * 1024 * 64,
		.oobsize = 256,
		.flashsize = 4 * 1024 * 64 * 2048,

		.tSETUP  = TSETUP,
		.tHOLD   = THOLD,
		.tSHSL_R = TSHSL_R,
		.tSHSL_W = TSHSL_W,

		.tRD = TRD_4G,
		.tPP = TPP,
		.tBE = TBE,

		.ecc_max = 0x3,
		.need_quad = 1,
	},

};

static struct device_id_struct device_id[GD_DEVICES_NUM] = {
	DEVICE_ID_STRUCT(0xD1, "GD5F1GQ4UB",&gd_param[0]),
	DEVICE_ID_STRUCT(0xD2, "GD5F2GQ4UB",&gd_param[1]),
	DEVICE_ID_STRUCT(0xD4, "GD5F4GQ4UB",&gd_param[2]),
	DEVICE_ID_STRUCT(0xB1, "GD5F1GQ4UC",&gd_param[3]),
	DEVICE_ID_STRUCT(0xB2, "GD5F2GQ4UC",&gd_param[4]),
	DEVICE_ID_STRUCT(0xB4, "GD5F4GQ4UC",&gd_param[5]),
};

static void gd_single_read(struct sfc_transfer *transfer, struct flash_operation_message *op_info) {

	struct sfc_flash *flash = op_info->flash;
	struct jz_sfcnand_flashinfo *nand_info = flash->flash_info;
	uint8_t device_id = nand_info->id_device;
	uint8_t addr_len = 0;
	switch(device_id) {
	    case 0xB1 ... 0xB4:
		    addr_len = 3;
		    break;
	    case 0xD1 ... 0xD4:
		    addr_len = 2;
		    break;
	    default:
		    dev_err(flash->dev, "device_id err, please check your  device id: device_id = 0x%02x\n", device_id);
		    addr_len = 2;
		    break;
	}

	transfer->cmd_info.cmd = SPINAND_CMD_FRCH;
	transfer->sfc_mode = TM_STD_SPI;

	transfer->addr = op_info->columnaddr;
	transfer->addr_len = addr_len;

	transfer->cmd_info.dataen = ENABLE;
	transfer->data = op_info->buffer;
	transfer->len = op_info->len;
	transfer->direction = GLB_TRAN_DIR_READ;

	transfer->data_dummy_bits = 8;
	transfer->ops_mode = DMA_OPS;

	return;
}

static void gd_quad_read(struct sfc_transfer *transfer, struct flash_operation_message *op_info) {

	struct sfc_flash *flash = op_info->flash;
	struct jz_sfcnand_flashinfo *nand_info = flash->flash_info;
	uint8_t device_id = nand_info->id_device;
	uint8_t addr_len = 0;
	switch(device_id) {
	    case 0xB1 ... 0xB4:
		    addr_len = 3;
		    break;
	    case 0xD1 ... 0xD4:
		    addr_len = 2;
		    break;
	    default:
		    dev_err(flash->dev, "device_id err, please check your device id: device_id = 0x%02x\n", device_id);
		    addr_len = 2;
		    break;
	}
	transfer->cmd_info.cmd = SPINAND_CMD_RDCH_X4;
	transfer->sfc_mode = TM_QI_QO_SPI;

	transfer->addr = op_info->columnaddr;
	transfer->addr_len = addr_len;

	transfer->cmd_info.dataen = ENABLE;
	transfer->data = op_info->buffer;
	transfer->len = op_info->len;
	transfer->direction = GLB_TRAN_DIR_READ;

	transfer->data_dummy_bits = 8;
	transfer->ops_mode = DMA_OPS;

	return;
}

static int32_t gd_get_f0_register_value(struct sfc_flash *flash) {

	struct sfc_transfer transfer;
	uint32_t buf = 0;

	memset(&transfer, 0, sizeof(transfer));
	sfc_list_init(&transfer);

	transfer.cmd_info.cmd = SPINAND_CMD_GET_FEATURE;
	transfer.sfc_mode = TM_STD_SPI;

	transfer.addr = 0xf0;
	transfer.addr_len = 1;

	transfer.cmd_info.dataen = ENABLE;
	transfer.len = 1;
	transfer.data = (uint8_t *)&buf;
	transfer.direction = GLB_TRAN_DIR_READ;

	transfer.data_dummy_bits = 0;
	transfer.ops_mode = CPU_OPS;

	if(sfc_sync(flash->sfc, &transfer)) {
	        dev_err(flash->dev,"sfc_sync error ! %s %s %d\n",__FILE__,__func__,__LINE__);
		return -EIO;
	}
	return buf;
}

static int32_t gd_get_read_feature(struct flash_operation_message *op_info) {

	struct sfc_flash *flash = op_info->flash;
	struct jz_sfcnand_flashinfo *nand_info = flash->flash_info;
	struct sfc_transfer transfer;
	uint8_t device_id = nand_info->id_device;
	uint8_t ecc_status = 0;
	int32_t ret = 0;

retry:
	ecc_status = 0;
	memset(&transfer, 0, sizeof(transfer));
	sfc_list_init(&transfer);

	transfer.cmd_info.cmd = SPINAND_CMD_GET_FEATURE;
	transfer.sfc_mode = TM_STD_SPI;

	transfer.addr = SPINAND_ADDR_STATUS;
	transfer.addr_len = 1;

	transfer.cmd_info.dataen = ENABLE;
	transfer.data = &ecc_status;
	transfer.len = 1;
	transfer.direction = GLB_TRAN_DIR_READ;

	transfer.data_dummy_bits = 0;
	transfer.ops_mode = CPU_OPS;

	if(sfc_sync(flash->sfc, &transfer)) {
	        dev_err(flash->dev,"sfc_sync error ! %s %s %d\n",__FILE__,__func__,__LINE__);
		return -EIO;
	}

	if(ecc_status & SPINAND_IS_BUSY)
		goto retry;

	switch(device_id) {
		case 0xB1 ... 0xB4:
			switch((ecc_status >> 4) & 0x7) {
				case 0x7:
					ret = -EBADMSG;
					break;
				case 0x6:
					ret = 0x8;
					break;
				case 0x5:
					ret = 0x7;
					break;
				default:
					ret = 0;
					break;
			}
			break;
		case 0xD1 ... 0xD4:
			switch((ecc_status >> 4) & 0x3) {
				case 0x3:
					ret = 0x8;
					break;
				case 0x2:
					ret = -EBADMSG;
					break;
				case 0x1:
					if((ret = gd_get_f0_register_value(flash)) < 0)
						return ret;
					if(((ret >> 4) & 0x3) == 0x3)
						ret = 0x7;
				default:
					ret = 0;
					break;
			}
			break;
		default:
			dev_err(flash->dev, "device_id err,it maybe don`t support this device, please check your device id: device_id = 0x%02x\n", device_id);
			ret = -EIO;   //notice!!!
	}

	return ret;
}

static int __init gd_nand_init(void) {
	struct jz_sfcnand_device *gd_nand;
	gd_nand = kzalloc(sizeof(*gd_nand), GFP_KERNEL);
	if(!gd_nand) {
		pr_err("alloc gd_nand struct fail\n");
		return -ENOMEM;
	}

	gd_nand->id_manufactory = 0xC8;
	gd_nand->id_device_list = device_id;
	gd_nand->id_device_count = GD_DEVICES_NUM;

	gd_nand->ops.nand_read_ops.get_feature = gd_get_read_feature;
	gd_nand->ops.nand_read_ops.single_read = gd_single_read;
	gd_nand->ops.nand_read_ops.quad_read = gd_quad_read;

	return jz_sfcnand_register(gd_nand);
}
module_init(gd_nand_init);
