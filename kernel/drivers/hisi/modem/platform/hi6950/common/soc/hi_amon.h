#ifndef __HI_AMON_H__
#define __HI_AMON_H__ 
#define HI_AMON_CNT_RESET_OFFSET (0x0)
#define HI_AMON_CNT_CTRL_OFFSET (0x4)
#define HI_AMON_CNT_STATE_INT_OFFSET (0x8)
#define HI_AMON_WIN_COUNTER_OFFSET (0xC)
#define HI_AMON_IDLE_COUNTER_OFFSET (0x14)
#define HI_AMON_PORT_SEL_OFFSET (0x1C)
#define HI_AMON_INT_CLR_OFFSET (0x20)
#define HI_AMON_ID_INT_SRC_OFFSET (0x24)
#define HI_AMON_ID_INT_MASK_OFFSET (0x28)
#define HI_AMON_ID_INT_STAT_OFFSET (0x2C)
#define HI_AMON_RD_WAIT_CYCLE_PORTS_0_OFFSET (0x30)
#define HI_AMON_RD_WAIT_CYCLE_PORTS_1_OFFSET (0x40)
#define HI_AMON_RD_WAIT_CYCLE_PORTS_2_OFFSET (0x50)
#define HI_AMON_RD_WAIT_CYCLE_PORTS_3_OFFSET (0x60)
#define HI_AMON_RD_WAIT_CYCLE_PORTS_4_OFFSET (0x70)
#define HI_AMON_RD_WAIT_CYCLE_PORTS_5_OFFSET (0x80)
#define HI_AMON_RD_WAIT_CYCLE_PORTS_6_OFFSET (0x90)
#define HI_AMON_RD_WAIT_CYCLE_PORTS_7_OFFSET (0xA0)
#define HI_AMON_WR_WAIT_CYCLE_PORTS_0_OFFSET (0x38)
#define HI_AMON_WR_WAIT_CYCLE_PORTS_1_OFFSET (0x48)
#define HI_AMON_WR_WAIT_CYCLE_PORTS_2_OFFSET (0x58)
#define HI_AMON_WR_WAIT_CYCLE_PORTS_3_OFFSET (0x68)
#define HI_AMON_WR_WAIT_CYCLE_PORTS_4_OFFSET (0x78)
#define HI_AMON_WR_WAIT_CYCLE_PORTS_5_OFFSET (0x88)
#define HI_AMON_WR_WAIT_CYCLE_PORTS_6_OFFSET (0x98)
#define HI_AMON_WR_WAIT_CYCLE_PORTS_7_OFFSET (0xA8)
#define HI_AMON_CNT_TYPE_0_OFFSET (0xB0)
#define HI_AMON_CNT_TYPE_1_OFFSET (0xB4)
#define HI_AMON_CNT_TYPE_2_OFFSET (0xB8)
#define HI_AMON_CNT_TYPE_3_OFFSET (0xBC)
#define HI_AMON_CNT_TYPE_4_OFFSET (0xC0)
#define HI_AMON_CNT_TYPE_5_OFFSET (0xC4)
#define HI_AMON_CNT_TYPE_6_OFFSET (0xC8)
#define HI_AMON_CNT_TYPE_7_OFFSET (0xCC)
#define HI_AMON_CNT_ID_0_OFFSET (0x100)
#define HI_AMON_CNT_ID_1_OFFSET (0x200)
#define HI_AMON_CNT_ID_2_OFFSET (0x300)
#define HI_AMON_CNT_ID_3_OFFSET (0x400)
#define HI_AMON_CNT_ID_4_OFFSET (0x500)
#define HI_AMON_CNT_ID_5_OFFSET (0x600)
#define HI_AMON_CNT_ID_6_OFFSET (0x700)
#define HI_AMON_CNT_ID_7_OFFSET (0x800)
#define HI_AMON_ID_ADDR_DES_0_OFFSET (0x104)
#define HI_AMON_ID_ADDR_DES_1_OFFSET (0x204)
#define HI_AMON_ID_ADDR_DES_2_OFFSET (0x304)
#define HI_AMON_ID_ADDR_DES_3_OFFSET (0x404)
#define HI_AMON_ID_ADDR_DES_4_OFFSET (0x504)
#define HI_AMON_ID_ADDR_DES_5_OFFSET (0x604)
#define HI_AMON_ID_ADDR_DES_6_OFFSET (0x704)
#define HI_AMON_ID_ADDR_DES_7_OFFSET (0x804)
#define HI_AMON_ID_ADDR_DES_M_0_OFFSET (0x108)
#define HI_AMON_ID_ADDR_DES_M_1_OFFSET (0x208)
#define HI_AMON_ID_ADDR_DES_M_2_OFFSET (0x308)
#define HI_AMON_ID_ADDR_DES_M_3_OFFSET (0x408)
#define HI_AMON_ID_ADDR_DES_M_4_OFFSET (0x508)
#define HI_AMON_ID_ADDR_DES_M_5_OFFSET (0x608)
#define HI_AMON_ID_ADDR_DES_M_6_OFFSET (0x708)
#define HI_AMON_ID_ADDR_DES_M_7_OFFSET (0x808)
#define HI_AMON_INCR1_ID_0_OFFSET (0x110)
#define HI_AMON_INCR1_ID_1_OFFSET (0x210)
#define HI_AMON_INCR1_ID_2_OFFSET (0x310)
#define HI_AMON_INCR1_ID_3_OFFSET (0x410)
#define HI_AMON_INCR1_ID_4_OFFSET (0x510)
#define HI_AMON_INCR1_ID_5_OFFSET (0x610)
#define HI_AMON_INCR1_ID_6_OFFSET (0x710)
#define HI_AMON_INCR1_ID_7_OFFSET (0x810)
#define HI_AMON_INCR2_ID_0_OFFSET (0x118)
#define HI_AMON_INCR2_ID_1_OFFSET (0x218)
#define HI_AMON_INCR2_ID_2_OFFSET (0x318)
#define HI_AMON_INCR2_ID_3_OFFSET (0x418)
#define HI_AMON_INCR2_ID_4_OFFSET (0x518)
#define HI_AMON_INCR2_ID_5_OFFSET (0x618)
#define HI_AMON_INCR2_ID_6_OFFSET (0x718)
#define HI_AMON_INCR2_ID_7_OFFSET (0x818)
#define HI_AMON_INCR4_ID_0_OFFSET (0x120)
#define HI_AMON_INCR4_ID_1_OFFSET (0x220)
#define HI_AMON_INCR4_ID_2_OFFSET (0x320)
#define HI_AMON_INCR4_ID_3_OFFSET (0x420)
#define HI_AMON_INCR4_ID_4_OFFSET (0x520)
#define HI_AMON_INCR4_ID_5_OFFSET (0x620)
#define HI_AMON_INCR4_ID_6_OFFSET (0x720)
#define HI_AMON_INCR4_ID_7_OFFSET (0x820)
#define HI_AMON_INCR8_ID_0_OFFSET (0x128)
#define HI_AMON_INCR8_ID_1_OFFSET (0x228)
#define HI_AMON_INCR8_ID_2_OFFSET (0x328)
#define HI_AMON_INCR8_ID_3_OFFSET (0x428)
#define HI_AMON_INCR8_ID_4_OFFSET (0x528)
#define HI_AMON_INCR8_ID_5_OFFSET (0x628)
#define HI_AMON_INCR8_ID_6_OFFSET (0x728)
#define HI_AMON_INCR8_ID_7_OFFSET (0x828)
#define HI_AMON_INCR16_ID_0_OFFSET (0x130)
#define HI_AMON_INCR16_ID_1_OFFSET (0x230)
#define HI_AMON_INCR16_ID_2_OFFSET (0x330)
#define HI_AMON_INCR16_ID_3_OFFSET (0x430)
#define HI_AMON_INCR16_ID_4_OFFSET (0x530)
#define HI_AMON_INCR16_ID_5_OFFSET (0x630)
#define HI_AMON_INCR16_ID_6_OFFSET (0x730)
#define HI_AMON_INCR16_ID_7_OFFSET (0x830)
#define HI_AMON_WRAP_ID_0_OFFSET (0x160)
#define HI_AMON_WRAP_ID_1_OFFSET (0x260)
#define HI_AMON_WRAP_ID_2_OFFSET (0x360)
#define HI_AMON_WRAP_ID_3_OFFSET (0x460)
#define HI_AMON_WRAP_ID_4_OFFSET (0x560)
#define HI_AMON_WRAP_ID_5_OFFSET (0x660)
#define HI_AMON_WRAP_ID_6_OFFSET (0x760)
#define HI_AMON_WRAP_ID_7_OFFSET (0x860)
#define HI_AMON_BURST_ID_0_OFFSET (0x190)
#define HI_AMON_BURST_ID_1_OFFSET (0x290)
#define HI_AMON_BURST_ID_2_OFFSET (0x390)
#define HI_AMON_BURST_ID_3_OFFSET (0x490)
#define HI_AMON_BURST_ID_4_OFFSET (0x590)
#define HI_AMON_BURST_ID_5_OFFSET (0x690)
#define HI_AMON_BURST_ID_6_OFFSET (0x790)
#define HI_AMON_BURST_ID_7_OFFSET (0x890)
#define HI_AMON_FINISH_ID_0_OFFSET (0x1A0)
#define HI_AMON_FINISH_ID_1_OFFSET (0x2A0)
#define HI_AMON_FINISH_ID_2_OFFSET (0x3A0)
#define HI_AMON_FINISH_ID_3_OFFSET (0x4A0)
#define HI_AMON_FINISH_ID_4_OFFSET (0x5A0)
#define HI_AMON_FINISH_ID_5_OFFSET (0x6A0)
#define HI_AMON_FINISH_ID_6_OFFSET (0x7A0)
#define HI_AMON_FINISH_ID_7_OFFSET (0x8A0)
#define HI_AMON_READ_WAIT_ID_0_OFFSET (0x1B8)
#define HI_AMON_READ_WAIT_ID_1_OFFSET (0x2B8)
#define HI_AMON_READ_WAIT_ID_2_OFFSET (0x3B8)
#define HI_AMON_READ_WAIT_ID_3_OFFSET (0x4B8)
#define HI_AMON_READ_WAIT_ID_4_OFFSET (0x5B8)
#define HI_AMON_READ_WAIT_ID_5_OFFSET (0x6B8)
#define HI_AMON_READ_WAIT_ID_6_OFFSET (0x7B8)
#define HI_AMON_READ_WAIT_ID_7_OFFSET (0x8B8)
#define HI_AMON_WRITE_WAIT_ID_0_OFFSET (0x1C0)
#define HI_AMON_WRITE_WAIT_ID_1_OFFSET (0x2C0)
#define HI_AMON_WRITE_WAIT_ID_2_OFFSET (0x3C0)
#define HI_AMON_WRITE_WAIT_ID_3_OFFSET (0x4C0)
#define HI_AMON_WRITE_WAIT_ID_4_OFFSET (0x5C0)
#define HI_AMON_WRITE_WAIT_ID_5_OFFSET (0x6C0)
#define HI_AMON_WRITE_WAIT_ID_6_OFFSET (0x7C0)
#define HI_AMON_WRITE_WAIT_ID_7_OFFSET (0x8C0)
#define HI_AMON_WRITE_WAIT_RESP_ID_0_OFFSET (0x1D0)
#define HI_AMON_WRITE_WAIT_RESP_ID_1_OFFSET (0x2D0)
#define HI_AMON_WRITE_WAIT_RESP_ID_2_OFFSET (0x3D0)
#define HI_AMON_WRITE_WAIT_RESP_ID_3_OFFSET (0x4D0)
#define HI_AMON_WRITE_WAIT_RESP_ID_4_OFFSET (0x5D0)
#define HI_AMON_WRITE_WAIT_RESP_ID_5_OFFSET (0x6D0)
#define HI_AMON_WRITE_WAIT_RESP_ID_6_OFFSET (0x7D0)
#define HI_AMON_WRITE_WAIT_RESP_ID_7_OFFSET (0x8D0)
#define HI_AMON_READ_MAX_WAIT_ID_0_OFFSET (0x1D8)
#define HI_AMON_READ_MAX_WAIT_ID_1_OFFSET (0x2D8)
#define HI_AMON_READ_MAX_WAIT_ID_2_OFFSET (0x3D8)
#define HI_AMON_READ_MAX_WAIT_ID_3_OFFSET (0x4D8)
#define HI_AMON_READ_MAX_WAIT_ID_4_OFFSET (0x5D8)
#define HI_AMON_READ_MAX_WAIT_ID_5_OFFSET (0x6D8)
#define HI_AMON_READ_MAX_WAIT_ID_6_OFFSET (0x7D8)
#define HI_AMON_READ_MAX_WAIT_ID_7_OFFSET (0x8D8)
#define HI_AMON_WRITE_MAX_WAIT_ID_0_OFFSET (0x1DC)
#define HI_AMON_WRITE_MAX_WAIT_ID_1_OFFSET (0x2DC)
#define HI_AMON_WRITE_MAX_WAIT_ID_2_OFFSET (0x3DC)
#define HI_AMON_WRITE_MAX_WAIT_ID_3_OFFSET (0x4DC)
#define HI_AMON_WRITE_MAX_WAIT_ID_4_OFFSET (0x5DC)
#define HI_AMON_WRITE_MAX_WAIT_ID_5_OFFSET (0x6DC)
#define HI_AMON_WRITE_MAX_WAIT_ID_6_OFFSET (0x7DC)
#define HI_AMON_WRITE_MAX_WAIT_ID_7_OFFSET (0x8DC)
#define HI_AMON_WRITE_MAX_WAIT_RESP_ID_0_OFFSET (0x1E4)
#define HI_AMON_WRITE_MAX_WAIT_RESP_ID_1_OFFSET (0x2E4)
#define HI_AMON_WRITE_MAX_WAIT_RESP_ID_2_OFFSET (0x3E4)
#define HI_AMON_WRITE_MAX_WAIT_RESP_ID_3_OFFSET (0x4E4)
#define HI_AMON_WRITE_MAX_WAIT_RESP_ID_4_OFFSET (0x5E4)
#define HI_AMON_WRITE_MAX_WAIT_RESP_ID_5_OFFSET (0x6E4)
#define HI_AMON_WRITE_MAX_WAIT_RESP_ID_6_OFFSET (0x7E4)
#define HI_AMON_WRITE_MAX_WAIT_RESP_ID_7_OFFSET (0x8E4)
#define HI_AMON_READ_BYTES_ID_0_OFFSET (0x1E8)
#define HI_AMON_READ_BYTES_ID_1_OFFSET (0x2E8)
#define HI_AMON_READ_BYTES_ID_2_OFFSET (0x3E8)
#define HI_AMON_READ_BYTES_ID_3_OFFSET (0x4E8)
#define HI_AMON_READ_BYTES_ID_4_OFFSET (0x5E8)
#define HI_AMON_READ_BYTES_ID_5_OFFSET (0x6E8)
#define HI_AMON_READ_BYTES_ID_6_OFFSET (0x7E8)
#define HI_AMON_READ_BYTES_ID_7_OFFSET (0x8E8)
#define HI_AMON_WRITE_BYTES_ID_0_OFFSET (0x1F0)
#define HI_AMON_WRITE_BYTES_ID_1_OFFSET (0x2F0)
#define HI_AMON_WRITE_BYTES_ID_2_OFFSET (0x3F0)
#define HI_AMON_WRITE_BYTES_ID_3_OFFSET (0x4F0)
#define HI_AMON_WRITE_BYTES_ID_4_OFFSET (0x5F0)
#define HI_AMON_WRITE_BYTES_ID_5_OFFSET (0x6F0)
#define HI_AMON_WRITE_BYTES_ID_6_OFFSET (0x7F0)
#define HI_AMON_WRITE_BYTES_ID_7_OFFSET (0x8F0)
#define HI_AMON_CAPT_CTRL_OFFSET (0x900)
#define HI_AMON_CAPT_ID_EN_OFFSET (0x904)
#define HI_AMON_CAPT_CONFIG_OFFSET (0x908)
#define HI_AMON_CAPT_ID_0_OFFSET (0x90C)
#define HI_AMON_CAPT_ID_1_OFFSET (0x910)
#define HI_AMON_CAPT_ID_2_OFFSET (0x914)
#define HI_AMON_CAPT_ID_3_OFFSET (0x918)
#define HI_AMON_CAPT_ID_4_OFFSET (0x91C)
#define HI_AMON_CAPT_ID_5_OFFSET (0x920)
#define HI_AMON_CAPT_ID_6_OFFSET (0x924)
#define HI_AMON_CAPT_ID_7_OFFSET (0x928)
#define HI_AMON_CAPT_INT_SRC_OFFSET (0x92C)
#define HI_AMON_CAPT_INT_MASK_OFFSET (0x930)
#define HI_AMON_CAPT_INT_STATE_OFFSET (0x934)
#define HI_AMON_CAPT_INT_CLR_OFFSET (0x938)
#define HI_AMON_AXI_STATE_OFFSET (0x93C)
#define HI_AMON_CAPT_TRANS_WAIT_TIME_OFFSET (0x940)
#define HI_AMON_TRANS_DATA_CNT_OFFSET (0x944)
#define HI_AMON_TRANS_DATA_CNT_HIGH_OFFSET (0xD4)
#define HI_AMON_TRANS_DATA_LEVEL_OFFSET (0x948)
#define HI_AMON_CMD_PKG_SIZE_OFFSET (0x94C)
#define HI_AMON_DATA1_PKG_SIZE_OFFSET (0x950)
#define HI_AMON_DATA2_PKG_SIZE_OFFSET (0x954)
#define HI_AMON_DMA_REQ_EN_OFFSET (0x958)
#endif
