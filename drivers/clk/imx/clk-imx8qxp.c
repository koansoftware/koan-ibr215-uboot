// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright 2018 NXP
 * Peng Fan <peng.fan@nxp.com>
 */

#include <common.h>
#include <clk-uclass.h>
#include <dm.h>
#include <asm/arch/sci/sci.h>
#include <asm/arch/clock.h>
#include <dt-bindings/clock/imx8qxp-clock.h>
#include <dt-bindings/soc/imx_rsrc.h>
#include <misc.h>
#include <asm/arch/lpcg.h>

#include "clk-imx8.h"

static struct imx8_clks imx8qxp_clks[] = {
	CLK_4( IMX8QXP_A35_DIV, "A35_DIV", SC_R_A35, SC_PM_CLK_CPU ),
	CLK_4( IMX8QXP_I2C0_DIV, "I2C0_DIV", SC_R_I2C_0, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_I2C1_DIV, "I2C1_DIV", SC_R_I2C_1, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_I2C2_DIV, "I2C2_DIV", SC_R_I2C_2, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_I2C3_DIV, "I2C3_DIV", SC_R_I2C_3, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_MIPI0_I2C0_DIV, "MIPI0 I2C0_DIV", SC_R_MIPI_0_I2C_0, SC_PM_CLK_MISC2 ),
	CLK_4( IMX8QXP_MIPI0_I2C1_DIV, "MIPI0 I2C1_DIV", SC_R_MIPI_0_I2C_1, SC_PM_CLK_MISC2 ),
	CLK_4( IMX8QXP_MIPI1_I2C0_DIV, "MIPI1 I2C0_DIV", SC_R_MIPI_1_I2C_0, SC_PM_CLK_MISC2 ),
	CLK_4( IMX8QXP_MIPI1_I2C1_DIV, "MIPI1 I2C1_DIV", SC_R_MIPI_1_I2C_1, SC_PM_CLK_MISC2 ),
	CLK_4( IMX8QXP_CSI0_I2C0_DIV, "CSI0 I2C0_DIV", SC_R_CSI_0_I2C_0, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_SPI0_DIV, "SPI0_DIV", SC_R_SPI_0, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_SPI1_DIV, "SPI1_DIV", SC_R_SPI_1, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_SPI2_DIV, "SPI2_DIV", SC_R_SPI_2, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_SPI3_DIV, "SPI3_DIV", SC_R_SPI_3, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_UART0_DIV, "UART0_DIV", SC_R_UART_0, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_UART1_DIV, "UART1_DIV", SC_R_UART_1, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_UART2_DIV, "UART2_DIV", SC_R_UART_2, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_UART3_DIV, "UART3_DIV", SC_R_UART_3, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_SDHC0_DIV, "SDHC0_DIV", SC_R_SDHC_0, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_SDHC1_DIV, "SDHC1_DIV", SC_R_SDHC_1, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_SDHC2_DIV, "SDHC2_DIV", SC_R_SDHC_2, SC_PM_CLK_PER ),
#if !defined(CONFIG_IMX8DXL)
	CLK_4( IMX8QXP_ENET0_ROOT_DIV, "ENET0_ROOT_DIV", SC_R_ENET_0, SC_PM_CLK_PER ),
#endif
	CLK_4( IMX8QXP_ENET0_RGMII_DIV, "ENET0_RGMII_DIV", SC_R_ENET_0, SC_PM_CLK_MISC0 ),
	CLK_4( IMX8QXP_ENET1_ROOT_DIV, "ENET1_ROOT_DIV", SC_R_ENET_1, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_ENET1_RGMII_DIV, "ENET1_RGMII_DIV", SC_R_ENET_1, SC_PM_CLK_MISC0 ),
	CLK_4( IMX8QXP_USB3_ACLK_DIV, "USB3_ACLK_DIV", SC_R_USB_2, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_USB3_BUS_DIV, "USB3_BUS_DIV", SC_R_USB_2, SC_PM_CLK_MST_BUS ),
	CLK_4( IMX8QXP_USB3_LPM_DIV, "USB3_LPM_DIV", SC_R_USB_2, SC_PM_CLK_MISC ),
	CLK_4( IMX8QXP_LSIO_FSPI0_DIV, "FSPI0_DIV", SC_R_FSPI_0, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_GPMI_BCH_IO_DIV, "GPMI_IO_DIV", SC_R_NAND, SC_PM_CLK_MST_BUS ),
	CLK_4( IMX8QXP_GPMI_BCH_DIV, "GPMI_BCH_DIV", SC_R_NAND, SC_PM_CLK_PER ),

	CLK_4( IMX8QXP_ELCDIF_PLL_DIV, "ELCDIF_PLL_DIV", SC_R_ELCDIF_PLL, SC_PM_CLK_PLL ),
	CLK_4( IMX8QXP_LCD_PXL_DIV, "LCD_PXL_DIV", SC_R_LCD_0, SC_PM_CLK_MISC0 ),
	CLK_4( IMX8QXP_LCD_DIV, "LCD_DIV", SC_R_LCD_0, SC_PM_CLK_PER ),
	CLK_4( IMX8QXP_LCD_PXL_BYPASS_DIV, "LCD_PXL_BYPASS_DIV", SC_R_LCD_0, SC_PM_CLK_BYPASS ),
};

static struct imx8_fixed_clks imx8qxp_fixed_clks[] = {
	CLK_3( IMX8QXP_IPG_CONN_CLK_ROOT, "IPG_CONN_CLK", SC_83MHZ ),
	CLK_3( IMX8QXP_AHB_CONN_CLK_ROOT, "AHB_CONN_CLK", SC_166MHZ ),
	CLK_3( IMX8QXP_AXI_CONN_CLK_ROOT, "AXI_CONN_CLK", SC_333MHZ ),
	CLK_3( IMX8QXP_IPG_DMA_CLK_ROOT, "IPG_DMA_CLK", SC_120MHZ ),
	CLK_3( IMX8QXP_MIPI_IPG_CLK, "IPG_MIPI_CLK", SC_120MHZ ),
	CLK_3( IMX8QXP_LSIO_BUS_CLK, "LSIO_BUS_CLK", SC_100MHZ ),
	CLK_3( IMX8QXP_LSIO_MEM_CLK, "LSIO_MEM_CLK", SC_200MHZ ),
	CLK_3( IMX8QXP_HSIO_PER_CLK, "HSIO_CLK", SC_133MHZ ),
	CLK_3( IMX8QXP_HSIO_AXI_CLK, "HSIO_AXI", SC_400MHZ ),
#if defined(CONFIG_IMX8DXL)
	CLK_3( IMX8QXP_ENET0_ROOT_DIV, "ENET0_ROOT_DIV", SC_250MHZ ),
#endif
};

static struct imx8_gpr_clks imx8qxp_gpr_clks[] = {
	CLK_5( IMX8QXP_ENET0_REF_DIV, "ENET0_REF_DIV", SC_R_ENET_0, SC_C_CLKDIV, IMX8QXP_ENET0_ROOT_DIV ),
	CLK_4( IMX8QXP_ENET0_REF_25MHZ_125MHZ_SEL, "ENET0_REF_25_125", SC_R_ENET_0, SC_C_SEL_125 ),
	CLK_4( IMX8QXP_ENET0_RMII_TX_SEL, "ENET0_RMII_TX", SC_R_ENET_0, SC_C_TXCLK ),
	CLK_4( IMX8QXP_ENET0_REF_25MHZ_125MHZ_CLK, "ENET0_REF_25_125_CLK", SC_R_ENET_0, SC_C_DISABLE_125 ),
	CLK_4( IMX8QXP_ENET0_REF_50MHZ_CLK, "ENET0_REF_50", SC_R_ENET_0, SC_C_DISABLE_50 ),

	CLK_5( IMX8QXP_ENET1_REF_DIV, "ENET1_REF_DIV", SC_R_ENET_1, SC_C_CLKDIV, IMX8QXP_ENET1_ROOT_DIV ),
	CLK_4( IMX8QXP_ENET1_REF_25MHZ_125MHZ_SEL, "ENET1_REF_25_125", SC_R_ENET_1, SC_C_SEL_125 ),
	CLK_4( IMX8QXP_ENET1_RMII_TX_SEL, "ENET1_RMII_TX", SC_R_ENET_1, SC_C_TXCLK ),
	CLK_4( IMX8QXP_ENET1_REF_25MHZ_125MHZ_CLK, "ENET1_REF_25_125_CLK", SC_R_ENET_1, SC_C_DISABLE_125 ),
	CLK_4( IMX8QXP_ENET1_REF_50MHZ_CLK, "ENET1_REF_50", SC_R_ENET_1, SC_C_DISABLE_50 ),
};

static struct imx8_lpcg_clks imx8qxp_lpcg_clks[] = {
	CLK_5( IMX8QXP_I2C0_CLK, "I2C0_CLK", 0, LPI2C_0_LPCG, IMX8QXP_I2C0_DIV ),
	CLK_5( IMX8QXP_I2C0_IPG_CLK, "I2C0_IPG", 16, LPI2C_0_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
	CLK_5( IMX8QXP_I2C1_CLK, "I2C1_CLK", 0, LPI2C_1_LPCG, IMX8QXP_I2C1_DIV ),
	CLK_5( IMX8QXP_I2C1_IPG_CLK, "I2C1_IPG", 16, LPI2C_1_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
	CLK_5( IMX8QXP_I2C2_CLK, "I2C2_CLK", 0, LPI2C_2_LPCG, IMX8QXP_I2C2_DIV ),
	CLK_5( IMX8QXP_I2C2_IPG_CLK, "I2C2_IPG", 16, LPI2C_2_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
	CLK_5( IMX8QXP_I2C3_CLK, "I2C3_CLK", 0, LPI2C_3_LPCG, IMX8QXP_I2C3_DIV ),
	CLK_5( IMX8QXP_I2C3_IPG_CLK, "I2C3_IPG", 16, LPI2C_3_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
	CLK_5( IMX8QXP_MIPI0_I2C0_CLK, "MIPI0_I2C0_CLK", 0, DI_MIPI0_LPCG + 0x10, IMX8QXP_MIPI0_I2C0_DIV ),
	CLK_5( IMX8QXP_MIPI0_I2C0_IPG_CLK, "MIPI0_I2C0_IPG", 16, DI_MIPI0_LPCG + 0x10, IMX8QXP_MIPI_IPG_CLK ),
	CLK_5( IMX8QXP_MIPI0_I2C1_CLK, "MIPI0_I2C1_CLK", 0, DI_MIPI0_LPCG + 0x14, IMX8QXP_MIPI0_I2C1_DIV ),
	CLK_5( IMX8QXP_MIPI0_I2C1_IPG_CLK, "MIPI0_I2C1_IPG", 16, DI_MIPI0_LPCG + 0x14, IMX8QXP_MIPI_IPG_CLK ),
	CLK_5( IMX8QXP_MIPI1_I2C0_CLK, "MIPI1_I2C0_CLK", 0, DI_MIPI1_LPCG + 0x10, IMX8QXP_MIPI1_I2C0_DIV ),
	CLK_5( IMX8QXP_MIPI1_I2C0_IPG_CLK, "MIPI1_I2C0_IPG", 16, DI_MIPI1_LPCG + 0x10, IMX8QXP_MIPI_IPG_CLK ),
	CLK_5( IMX8QXP_MIPI1_I2C1_CLK, "MIPI1_I2C1_CLK", 0, DI_MIPI1_LPCG + 0x14, IMX8QXP_MIPI1_I2C1_DIV ),
	CLK_5( IMX8QXP_MIPI1_I2C1_IPG_CLK, "MIPI1_I2C1_IPG", 16, DI_MIPI1_LPCG + 0x14, IMX8QXP_MIPI_IPG_CLK ),
	CLK_5( IMX8QXP_CSI0_I2C0_CLK, "CSI0_I2C0_CLK", 0, MIPI_CSI_0_LPCG + 0x14, IMX8QXP_CSI0_I2C0_DIV ),
	CLK_5( IMX8QXP_CSI0_I2C0_IPG_CLK, "CSI0_I2C0_IPG", 16, MIPI_CSI_0_LPCG + 0x14, IMX8QXP_MIPI_IPG_CLK ),

	CLK_5( IMX8QXP_SPI0_CLK, "SPI0_CLK", 0, LPSPI_0_LPCG, IMX8QXP_SPI0_DIV ),
	CLK_5( IMX8QXP_SPI0_IPG_CLK, "SPI0_IPG", 16, LPSPI_0_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
	CLK_5( IMX8QXP_SPI1_CLK, "SPI1_CLK", 0, LPSPI_1_LPCG, IMX8QXP_SPI1_DIV ),
	CLK_5( IMX8QXP_SPI1_IPG_CLK, "SPI1_IPG", 16, LPSPI_1_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
	CLK_5( IMX8QXP_SPI2_CLK, "SPI2_CLK", 0, LPSPI_2_LPCG, IMX8QXP_SPI2_DIV ),
	CLK_5( IMX8QXP_SPI2_IPG_CLK, "SPI2_IPG", 16, LPSPI_2_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
	CLK_5( IMX8QXP_SPI3_CLK, "SPI3_CLK", 0, LPSPI_3_LPCG, IMX8QXP_SPI3_DIV ),
	CLK_5( IMX8QXP_SPI3_IPG_CLK, "SPI3_IPG", 16, LPSPI_3_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),

	CLK_5( IMX8QXP_UART0_CLK, "UART0_CLK", 0, LPUART_0_LPCG, IMX8QXP_UART0_DIV ),
	CLK_5( IMX8QXP_UART0_IPG_CLK, "UART0_IPG", 16, LPUART_0_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
	CLK_5( IMX8QXP_UART1_CLK, "UART1_CLK", 0, LPUART_1_LPCG, IMX8QXP_UART1_DIV ),
	CLK_5( IMX8QXP_UART1_IPG_CLK, "UART1_IPG", 16, LPUART_1_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
	CLK_5( IMX8QXP_UART2_CLK, "UART2_CLK", 0, LPUART_2_LPCG, IMX8QXP_UART2_DIV ),
	CLK_5( IMX8QXP_UART2_IPG_CLK, "UART2_IPG", 16, LPUART_2_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
	CLK_5( IMX8QXP_UART3_CLK, "UART3_CLK", 0, LPUART_3_LPCG, IMX8QXP_UART3_DIV ),
	CLK_5( IMX8QXP_UART3_IPG_CLK, "UART3_IPG", 16, LPUART_3_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),

	CLK_5( IMX8QXP_SDHC0_CLK, "SDHC0_CLK", 0, USDHC_0_LPCG, IMX8QXP_SDHC0_DIV ),
	CLK_5( IMX8QXP_SDHC0_IPG_CLK, "SDHC0_IPG", 16, USDHC_0_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_SDHC0_AHB_CLK, "SDHC0_AHB", 20, USDHC_0_LPCG, IMX8QXP_AHB_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_SDHC1_CLK, "SDHC1_CLK", 0, USDHC_1_LPCG, IMX8QXP_SDHC1_DIV ),
	CLK_5( IMX8QXP_SDHC1_IPG_CLK, "SDHC1_IPG", 16, USDHC_1_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_SDHC1_AHB_CLK, "SDHC1_AHB", 20, USDHC_1_LPCG, IMX8QXP_AHB_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_SDHC2_CLK, "SDHC2_CLK", 0, USDHC_2_LPCG, IMX8QXP_SDHC2_DIV ),
	CLK_5( IMX8QXP_SDHC2_IPG_CLK, "SDHC2_IPG", 16, USDHC_2_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_SDHC2_AHB_CLK, "SDHC2_AHB", 20, USDHC_2_LPCG, IMX8QXP_AHB_CONN_CLK_ROOT ),

	CLK_5( IMX8QXP_ENET0_IPG_S_CLK, "ENET0_IPG_S", 20, ENET_0_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_ENET0_IPG_CLK, "ENET0_IPG", 16, ENET_0_LPCG, IMX8QXP_ENET0_IPG_S_CLK ),
	CLK_5( IMX8QXP_ENET0_AHB_CLK, "ENET0_AHB", 8, ENET_0_LPCG, IMX8QXP_AXI_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_ENET0_TX_CLK, "ENET0_TX", 4, ENET_0_LPCG, IMX8QXP_ENET0_ROOT_DIV ),
	CLK_5( IMX8QXP_ENET0_PTP_CLK, "ENET0_PTP", 0, ENET_0_LPCG, IMX8QXP_ENET0_ROOT_DIV  ),
	CLK_5( IMX8QXP_ENET0_RGMII_TX_CLK, "ENET0_RGMII_TX", 12, ENET_0_LPCG, IMX8QXP_ENET0_RMII_TX_SEL  ),
	CLK_5( IMX8QXP_ENET0_RMII_RX_CLK, "ENET0_RMII_RX", 0, ENET_0_LPCG + 0x4, IMX8QXP_ENET0_RGMII_DIV  ),

	CLK_5( IMX8QXP_ENET1_IPG_S_CLK, "ENET1_IPG_S", 20, ENET_1_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_ENET1_IPG_CLK, "ENET1_IPG", 16, ENET_1_LPCG, IMX8QXP_ENET1_IPG_S_CLK ),
	CLK_5( IMX8QXP_ENET1_AHB_CLK, "ENET1_AHB", 8, ENET_1_LPCG, IMX8QXP_AXI_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_ENET1_TX_CLK, "ENET1_TX", 4, ENET_1_LPCG, IMX8QXP_ENET1_ROOT_DIV ),
	CLK_5( IMX8QXP_ENET1_PTP_CLK, "ENET1_PTP", 0, ENET_1_LPCG, IMX8QXP_ENET1_ROOT_DIV  ),
	CLK_5( IMX8QXP_ENET1_RGMII_TX_CLK, "ENET1_RGMII_TX", 12, ENET_1_LPCG, IMX8QXP_ENET1_RMII_TX_SEL  ),
	CLK_5( IMX8QXP_ENET1_RMII_RX_CLK, "ENET1_RMII_RX", 0, ENET_1_LPCG + 0x4, IMX8QXP_ENET1_RGMII_DIV  ),

#if defined(CONFIG_IMX8DXL)
	CLK_5( IMX8DXL_EQOS_MEM_CLK, "EQOS_MEM_CLK", 8, ENET_1_LPCG, IMX8QXP_AXI_CONN_CLK_ROOT ),
	CLK_5( IMX8DXL_EQOS_ACLK, "EQOS_ACLK", 16, ENET_1_LPCG, IMX8DXL_EQOS_MEM_CLK ),
	CLK_5( IMX8DXL_EQOS_CSR_CLK, "EQOS_CSR_CLK", 24, ENET_1_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
	CLK_5( IMX8DXL_EQOS_CLK, "EQOS_CLK", 20, ENET_1_LPCG, IMX8QXP_ENET1_ROOT_DIV ),
	CLK_5( IMX8DXL_EQOS_PTP_CLK_S, "EQOS_PTP_S", 8, ENET_1_LPCG, IMX8QXP_ENET0_ROOT_DIV  ),
	CLK_5( IMX8DXL_EQOS_PTP_CLK, "EQOS_PTP", 0, ENET_1_LPCG, IMX8DXL_EQOS_PTP_CLK_S  ),
#endif

	CLK_5( IMX8QXP_LSIO_FSPI0_IPG_S_CLK, "FSPI0_IPG_S", 0x18, FSPI_0_LPCG, IMX8QXP_LSIO_BUS_CLK ),
	CLK_5( IMX8QXP_LSIO_FSPI0_IPG_CLK, "FSPI0_IPG", 0x14, FSPI_0_LPCG, IMX8QXP_LSIO_FSPI0_IPG_S_CLK ),
	CLK_5( IMX8QXP_LSIO_FSPI0_HCLK, "FSPI0_HCLK", 0x10, FSPI_0_LPCG, IMX8QXP_LSIO_MEM_CLK ),
	CLK_5( IMX8QXP_LSIO_FSPI0_CLK, "FSPI0_CLK", 0, FSPI_0_LPCG, IMX8QXP_LSIO_FSPI0_DIV ),

#if !defined(CONFIG_IMX8DXL)
	CLK_5( IMX8QXP_USB2_OH_AHB_CLK, "USB2_OH_AHB", 24, USB_2_LPCG, IMX8QXP_AHB_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_USB2_OH_IPG_S_CLK, "USB2_OH_IPG_S", 16, USB_2_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_USB2_OH_IPG_S_PL301_CLK, "USB2_OH_IPG_S_PL301", 20, USB_2_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
#endif
	CLK_5( IMX8QXP_USB2_PHY_IPG_CLK, "USB2_PHY_IPG", 28, USB_2_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),

	CLK_5( IMX8QXP_USB3_IPG_CLK, "USB3_IPG", 16, USB_3_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_USB3_CORE_PCLK, "USB3_CORE", 20, USB_3_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_USB3_PHY_CLK, "USB3_PHY", 24, USB_3_LPCG, IMX8QXP_USB3_IPG_CLK ),

#if defined(CONFIG_IMX8DXL)
	CLK_5( IMX8DXL_USB2_PHY2_IPG_CLK, "USB3_ACLK", 28, USB_3_LPCG, IMX8QXP_IPG_CONN_CLK_ROOT ),
#endif
	CLK_5( IMX8QXP_USB3_ACLK, "USB3_ACLK", 28, USB_3_LPCG, IMX8QXP_USB3_ACLK_DIV ),
	CLK_5( IMX8QXP_USB3_BUS_CLK, "USB3_BUS", 0, USB_3_LPCG, IMX8QXP_USB3_BUS_DIV ),
	CLK_5( IMX8QXP_USB3_LPM_CLK, "USB3_LPM", 4, USB_3_LPCG, IMX8QXP_USB3_LPM_DIV ),

	CLK_5( IMX8QXP_GPMI_APB_CLK, "GPMI_APB", 16, NAND_LPCG, IMX8QXP_AXI_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_GPMI_APB_BCH_CLK, "GPMI_APB_BCH", 20, NAND_LPCG, IMX8QXP_AXI_CONN_CLK_ROOT ),
	CLK_5( IMX8QXP_GPMI_BCH_IO_CLK, "GPMI_IO_CLK", 4, NAND_LPCG, IMX8QXP_GPMI_BCH_IO_DIV ),
	CLK_5( IMX8QXP_GPMI_BCH_CLK, "GPMI_BCH_CLK", 0, NAND_LPCG, IMX8QXP_GPMI_BCH_DIV ),
	CLK_5( IMX8QXP_APBHDMA_CLK, "GPMI_CLK", 16, NAND_LPCG + 0x4, IMX8QXP_AXI_CONN_CLK_ROOT ),

	CLK_5( IMX8QXP_HSIO_PCIE_MSTR_AXI_CLK, "HSIO_PCIE_A_MSTR_AXI_CLK", 16, HSIO_PCIE_X1_LPCG, IMX8QXP_HSIO_AXI_CLK ),
	CLK_5( IMX8QXP_HSIO_PCIE_SLV_AXI_CLK, "HSIO_PCIE_A_SLV_AXI_CLK", 20, HSIO_PCIE_X1_LPCG, IMX8QXP_HSIO_AXI_CLK ),
	CLK_5( IMX8QXP_HSIO_PCIE_DBI_AXI_CLK, "HSIO_PCIE_A_DBI_AXI_CLK", 24, HSIO_PCIE_X1_LPCG, IMX8QXP_HSIO_AXI_CLK ),
	CLK_5( IMX8QXP_HSIO_PCIE_X1_PER_CLK, "HSIO_PCIE_X1_PER_CLK", 16, HSIO_PCIE_X1_CRR3_LPCG, IMX8QXP_HSIO_PER_CLK ),
	CLK_5( IMX8QXP_HSIO_PHY_X1_PER_CLK, "HSIO_PHY_X1_PER_CLK", 16, HSIO_PHY_X1_CRR1_LPCG, IMX8QXP_HSIO_PER_CLK ),
	CLK_5( IMX8QXP_HSIO_MISC_PER_CLK, "HSIO_MISC_PER_CLK", 16, HSIO_MISC_LPCG, IMX8QXP_HSIO_PER_CLK ),
	CLK_5( IMX8QXP_HSIO_PHY_X1_APB_CLK, "HSIO_PHY_X1_APB_CLK", 16, HSIO_PHY_X1_LPCG, IMX8QXP_HSIO_PER_CLK ),
	CLK_5( IMX8QXP_HSIO_GPIO_CLK, "HSIO_GPIO_CLK", 16, HSIO_GPIO_LPCG, IMX8QXP_HSIO_PER_CLK ),
	CLK_5( IMX8QXP_HSIO_PHY_X1_PCLK, "HSIO_PHY_X1_PCLK", 0, HSIO_PHY_X1_LPCG, 0 ),
	CLK_5( IMX8QXP_LCD_IPG_CLK, "LCD_IPG_CLK", 16, LCD_LPCG, IMX8QXP_IPG_DMA_CLK_ROOT ),
};

struct imx8_mux_clks imx8qxp_mux_clks[] = {
	CLK_MUX( IMX8QXP_SDHC0_SEL, "SDHC0_SEL", IMX8QXP_SDHC0_DIV, IMX8QXP_CLK_DUMMY, IMX8QXP_CONN_PLL0_CLK,
		IMX8QXP_CONN_PLL1_CLK, IMX8QXP_CLK_DUMMY, IMX8QXP_CLK_DUMMY ),
	CLK_MUX( IMX8QXP_SDHC1_SEL, "SDHC1_SEL", IMX8QXP_SDHC1_DIV, IMX8QXP_CLK_DUMMY, IMX8QXP_CONN_PLL0_CLK,
		IMX8QXP_CONN_PLL1_CLK, IMX8QXP_CLK_DUMMY, IMX8QXP_CLK_DUMMY ),
	CLK_MUX( IMX8QXP_SDHC2_SEL, "SDHC2_SEL", IMX8QXP_SDHC2_DIV, IMX8QXP_CLK_DUMMY, IMX8QXP_CONN_PLL0_CLK,
		IMX8QXP_CONN_PLL1_CLK, IMX8QXP_CLK_DUMMY, IMX8QXP_CLK_DUMMY ),

	CLK_MUX( IMX8QXP_LCD_PXL_SEL, "LCD_PXL_SEL", IMX8QXP_LCD_PXL_DIV, IMX8QXP_CLK_DUMMY, IMX8QXP_CLK_DUMMY,
		IMX8QXP_CLK_DUMMY, IMX8QXP_CLK_DUMMY, IMX8QXP_LCD_PXL_BYPASS_DIV ),
	CLK_MUX( IMX8QXP_LCD_SEL, "LCD_SEL", IMX8QXP_LCD_DIV, IMX8QXP_CLK_DUMMY, IMX8QXP_CLK_DUMMY,
		IMX8QXP_CLK_DUMMY, IMX8QXP_CLK_DUMMY, IMX8QXP_ELCDIF_PLL_DIV ),
};

struct imx8_clks_collect imx8qxp_clk_collect = {
	{
		{&imx8qxp_clks, ARRAY_SIZE(imx8qxp_clks)},
		{&imx8qxp_fixed_clks, ARRAY_SIZE(imx8qxp_fixed_clks)},
		{&imx8qxp_gpr_clks, ARRAY_SIZE(imx8qxp_gpr_clks)},
		{&imx8qxp_lpcg_clks, ARRAY_SIZE(imx8qxp_lpcg_clks)},
		{&imx8qxp_mux_clks, ARRAY_SIZE(imx8qxp_mux_clks)},
	},
	FLAG_CLK_IMX8_IMX8QXP,
};
