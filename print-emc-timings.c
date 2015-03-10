#include <stdio.h>

#include "board-ardbeg-memory.c"

#define EMC_MRS_WAIT_CNT	139
#define EMC_XM2DQSPADCTRL2	121
#define EMC_ZCAL_INTERVAL	137
#define MC_EMEM_ARB_CFG		146

static void p4(char *name, unsigned int value)
{
	printf("\t\t\t\t%s = <0x%08x>;\n", name, value);
}

static void print_emc_table(struct tegra12_emc_pdata *board_data)
{
	unsigned int i, j;

	printf("	emc@0,7001b000 {\n");
	/* TODO: Extract the ram-code from the board data */
	printf("		emc-timings-3 {\n");
	printf("			nvidia,ram-code = <3>;\n\n");

	for (i = 0; i < board_data->num_tables; i++) {
		struct tegra12_emc_table *table = &board_data->tables[i];
		printf("\t\t\ttiming-%lu {\n", table->rate * 1000);

		printf("\t\t\t\tclock-frequency = <%lu>;\n\n", table->rate * 1000);

		p4("nvidia,emc-auto-cal-config", table->emc_auto_cal_config);
		p4("nvidia,emc-auto-cal-config2", table->emc_auto_cal_config2);
		p4("nvidia,emc-auto-cal-config3", table->emc_auto_cal_config3);
		p4("nvidia,emc-auto-cal-interval", table->emc_acal_interval);
		p4("nvidia,emc-bgbias-ctl0", table->emc_bgbias_ctl0);
		p4("nvidia,emc-cfg", table->emc_cfg);
		p4("nvidia,emc-cfg-2", table->emc_cfg_2);
		p4("nvidia,emc-ctt-term-ctrl", table->emc_ctt_term_ctrl);
		p4("nvidia,emc-mode-1", table->emc_mode_1);
		p4("nvidia,emc-mode-2", table->emc_mode_2);
		p4("nvidia,emc-mode-4", table->emc_mode_4);
		p4("nvidia,emc-mode-reset", table->emc_mode_reset);
		p4("nvidia,emc-mrs-wait-cnt", table->burst_regs[EMC_MRS_WAIT_CNT]);
		p4("nvidia,emc-sel-dpd-ctrl", table->emc_sel_dpd_ctrl);
		p4("nvidia,emc-xm2dqspadctrl2", table->burst_regs[EMC_XM2DQSPADCTRL2]);
		p4("nvidia,emc-zcal-cnt-long", table->emc_zcal_cnt_long);
		p4("nvidia,emc-zcal-interval", table->burst_regs[EMC_ZCAL_INTERVAL]);

		printf("\n\t\t\t\tnvidia,emc-configuration = <\n");

		for (j = 0; j < MC_EMEM_ARB_CFG; j++) {
			printf("\t\t\t\t\t0x%08x\n", table->burst_regs[j]);
		}

		printf("\t\t\t\t>;\n");

		printf("\t\t\t};\n\n");
	}

	printf("		};\n");
	printf("	};\n\n");
}

static void print_mc_table(struct tegra12_emc_pdata *board_data)
{
	unsigned int i, j;

	printf("	memory-controller@0,70019000 {\n");
	/* TODO: Extract the ram-code from the board data */
	printf("		emc-timings-3 {\n");
	printf("			nvidia,ram-code = <3>;\n\n");

	for (i = 0; i < board_data->num_tables; i++) {
		struct tegra12_emc_table *table = &board_data->tables[i];
		printf("\t\t\ttiming-%lu {\n", table->rate * 1000);

		printf("\t\t\t\tclock-frequency = <%lu>;\n\n", table->rate * 1000);

		printf("\t\t\t\tnvidia,emem-configuration = <\n");

		for (j = MC_EMEM_ARB_CFG; j < table->burst_regs_num; j++) {
			printf("\t\t\t\t\t0x%08x\n", table->burst_regs[j]);
		}

		printf("\t\t\t\t>;\n");

		printf("\t\t\t};\n\n");
	}

	printf("		};\n");
	printf("	};\n");
}

int main(int argc, char *argv[])
{
	struct tegra12_emc_pdata *board_data = &jetson_tk1_2GB_emc_pdata;

	printf("/ {\n");

	print_emc_table(board_data);
	print_mc_table(board_data);

	printf("};\n");

	return 0;
}
