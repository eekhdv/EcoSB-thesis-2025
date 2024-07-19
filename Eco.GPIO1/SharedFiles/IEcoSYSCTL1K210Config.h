/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoSYSCTL1K210Config
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoSYSCTL1K210Config
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_SYSCTL_1_K210_CONFIG_H__
#define __I_ECO_SYSCTL_1_K210_CONFIG_H__

#include "IEcoBase1.h"

/* PLL0 controller - No. 2 Register pll0 (Map Address Offset: 0x08) */
typedef struct ECO_SYSCTL_PLL0_CONTROLLER_REGISTER {
    uint32_t clkr0          : 4;
    uint32_t clkf0          : 6;
    uint32_t clkod0         : 4;
    uint32_t bwadj0         : 6;
    uint32_t pll_reset0     : 1;
    uint32_t pll_pwrd0      : 1;
    uint32_t pll_intfb0     : 1;
    uint32_t pll_bypass0    : 1;
    uint32_t pll_test0      : 1;
    uint32_t pll_out_en0    : 1;
    uint32_t pll_test_en    : 1;
    uint32_t reserved       : 5;
} ECO_SYSCTL_PLL0_CONTROLLER_REGISTER;

/* PLL1 controller - No. 3 Register pll1 (Map Address Offset: 0x0C) */
typedef struct ECO_SYSCTL_PLL1_CONTROLLER_REGISTER {
    uint32_t clkr1          : 4;
    uint32_t clkf1          : 6;
    uint32_t clkod1         : 4;
    uint32_t bwadj1         : 6;
    uint32_t pll_reset1     : 1;
    uint32_t pll_pwrd1      : 1;
    uint32_t pll_intfb1     : 1;
    uint32_t pll_bypass1    : 1;
    uint32_t pll_test1      : 1;
    uint32_t pll_out_en1    : 1;
    uint32_t reserved       : 6;
} ECO_SYSCTL_PLL1_CONTROLLER_REGISTER;

/* PLL2 controller - No. 4 Register pll2 (Map Address Offset: 0x10) */
typedef struct ECO_SYSCTL_PLL2_CONTROLLER_REGISTER {
    uint32_t clkr2          : 4;
    uint32_t clkf2          : 6;
    uint32_t clkod2         : 4;
    uint32_t bwadj2         : 6;
    uint32_t pll_reset2     : 1;
    uint32_t pll_pwrd2      : 1;
    uint32_t pll_intfb2     : 1;
    uint32_t pll_bypass2    : 1;
    uint32_t pll_test2      : 1;
    uint32_t pll_out_en2    : 1;
    uint32_t pll_ckin_sel2  : 2;
    uint32_t reserved       : 4;
} ECO_SYSCTL_PLL2_CONTROLLER_REGISTER;

typedef struct ECO_SYSCTL_CENTRAL_CLOCK_ENABLE
{
    uint32_t cpu_clk_en     : 1;
    uint32_t sram0_clk_en   : 1;
    uint32_t sram1_clk_en   : 1;
    uint32_t apb0_clk_en    : 1;
    uint32_t apb1_clk_en    : 1;
    uint32_t apb2_clk_en    : 1;
    uint32_t reserved       : 26;
} ECO_SYSCTL_CENTRAL_CLOCK_ENABLE;

typedef struct ECO_SYSCTL_REGISTER_MAP {
    uint32_t git_id;        /* SYSCTL Git short commit id,              Address offset: 0x00      */
    uint32_t clk_freq;      /* SYSCTL System clock base frequency,      Address offset: 0x04      */
    uint32_t pll0;          /* SYSCTL PLL0 controller,                  Address offset: 0x08      */
    uint32_t pll1;          /* SYSCTL PLL1 controller,                  Address offset: 0x0C      */
    uint32_t pll2;          /* SYSCTL PLL2 controller,                  Address offset: 0x10      */
    uint32_t resv5;         /* SYSCTL Reserved,                         Address offset: 0x14      */
    uint32_t pll_lock;      /* SYSCTL PLL lock tester,                  Address offset: 0x18      */
    uint32_t rom_error;     /* SYSCTL AXI ROM detector,                 Address offset: 0x1C      */
    uint32_t clk_sel0;      /* SYSCTL Clock select controller0,         Address offset: 0x20      */
    uint32_t clk_sel1;      /* SYSCTL Clock select controller1,         Address offset: 0x24      */
    uint32_t clk_en_cent;   /* SYSCTL Central clock enable,             Address offset: 0x28      */
    uint32_t clk_en_peri;   /* SYSCTL Peripheral clock enable,          Address offset: 0x2C      */
    uint32_t soft_reset;    /* SYSCTL Soft reset ctrl,                  Address offset: 0x30      */
    uint32_t peri_reset;    /* SYSCTL Peripheral reset controller,      Address offset: 0x34      */
    uint32_t clk_th0;       /* SYSCTL Clock threshold controller 0,     Address offset: 0x38      */
    uint32_t clk_th1;       /* SYSCTL Clock threshold controller 1,     Address offset: 0x3C      */
    uint32_t clk_th2;       /* SYSCTL Clock threshold controller 2,     Address offset: 0x40      */
    uint32_t clk_th3;       /* SYSCTL Clock threshold controller 3,     Address offset: 0x44      */
    uint32_t clk_th4;       /* SYSCTL Clock threshold controller 4,     Address offset: 0x48      */
    uint32_t clk_th5;       /* SYSCTL Clock threshold controller 5,     Address offset: 0x4C      */
    uint32_t clk_th6;       /* SYSCTL Clock threshold controller 6,     Address offset: 0x50      */
    uint32_t misc;          /* SYSCTL Miscellaneous controller,         Address offset: 0x54      */
    uint32_t peri;          /* SYSCTL Peripheral controller,            Address offset: 0x58      */
    uint32_t spi_sleep;     /* SYSCTL SPI sleep controller,             Address offset: 0x5C      */
    uint32_t reset_status;  /* SYSCTL Reset source status,              Address offset: 0x60      */
    uint32_t dma_sel0;      /* SYSCTL DMA handshake selector,           Address offset: 0x64      */
    uint32_t dma_sel1;      /* SYSCTL DMA handshake selector,           Address offset: 0x68      */
    uint32_t power_sel;     /* SYSCTL IO Power Mode Select controller,  Address offset: 0x6C      */
    uint32_t resv28;        /* SYSCTL Reserved,                         Address offset: 0x70      */
    uint32_t resv29;        /* SYSCTL Reserved,                         Address offset: 0x74      */
    uint32_t resv30;        /* SYSCTL Reserved,                         Address offset: 0x78      */
    uint32_t resv31;        /* SYSCTL Reserved,                         Address offset: 0x7C      */

} ECO_SYSCTL_REGISTER_MAP;

typedef struct ECO_SYSCTL_CONFIG_DESCRIPTOR {
    union {
        uint32_t BaseAddress;
        struct ECO_SYSCTL_REGISTER_MAP* Map;
    } Register;
} ECO_SYSCTL_CONFIG_DESCRIPTOR;

/* IEcoSYSCTL1K210Config IID = {BEADA64A-CF04-43ED-836D-39A5CDEEF7C0} */
#ifndef __IID_IEcoSYSCTL1K210Config
static const UGUID IID_IEcoSYSCTL1K210Config = { 0x01, 0x10, 0xBE, 0xAD, 0xA6, 0x4A, 0xCF, 0x04, 0x43, 0xED, 0x83, 0x6D, 0x39, 0xA5, 0xCD, 0xEE, 0xF7, 0xC0 };
#endif /* __IID_IEcoSYSCTL1K210Config */

typedef struct IEcoSYSCTL1K210ConfigVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoSYSCTL1K210Config* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct IEcoSYSCTL1K210Config* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct IEcoSYSCTL1K210Config* me);

    /* IEcoSYSCTL1K210Config */
    int16_t (ECOCALLMETHOD *set_ConfigDescriptor)(/* in */ struct IEcoSYSCTL1K210Config* me, /* in */ ECO_SYSCTL_CONFIG_DESCRIPTOR* config);
    ECO_SYSCTL_CONFIG_DESCRIPTOR* (ECOCALLMETHOD *get_ConfigDescriptor)(/* in */ struct IEcoSYSCTL1K210Config* me);

} IEcoSYSCTL1K210ConfigVTbl, *IEcoSYSCTL1K210ConfigVTblPtr;

interface IEcoSYSCTL1K210Config {
    struct IEcoSYSCTL1K210ConfigVTbl *pVTbl;
} IEcoSYSCTL1K210Config;

#endif /* __I_ECO_SYSCTL_1_K210_CONFIG_H__ */
