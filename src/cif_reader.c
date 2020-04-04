#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define LEXEME_COUNT 26 // Number of members in cifLexemes minus 1
#define CIF_RESULT_FILENAME "cif_result.txt"


char * get_arguments(int argc, char * argv[])
{
	return (argc > 1) ? argv[1] : NULL; // Return the cifFileName of NULL
}


char * get_cif_lex_value(char * inputStr)
{
	char * str = inputStr;

	while( *str && !isspace( (unsigned char) * str) ) ++str; // Ignore lexeme like _cell_length_a
	while( *str && isspace( (unsigned char) * str) ) ++str; // Ignore spaces after lexeme before its value

	return str;
}


void write_data(FILE * file1, FILE * file2, char * lexeme, char * value)
{
	fprintf(file1, "%s", value); // Write lexValue to CIF_RESULT_FILENAME
	fprintf(file2, "%35s\t%s", lexeme, value); // Write data to command line
}


void read_cif_file(char * cifFileName)
{
	FILE * cifFile = fopen(cifFileName, "r");
	FILE * outFile = fopen(CIF_RESULT_FILENAME, "w");

	char str[128];
	char * lexValue = "";

	char *cifLexemes[] = {
		"_chemical_formula_moiety", //string like 'C24 H22 F3 N O3'
		"_chemical_formula_weight", //float, like 429.42
		"_cell_measurement_temperature", //int like 120
		"_space_group_crystal_system", //string like 'monoclinic'
		"_space_group_name_H-M_alt", // string like 'P 1 21/c 1' => P21/c
		"_cell_formula_units_Z", // int like 4 or float ???
		"_cell_length_a", //string like 13.9693(14)
		"_cell_length_b", //string like 16.7422(15)
		"_cell_length_c", //string like 9.3739(8)
		"_cell_angle_alpha", //string like 90 or float 103.524(2)
		"_cell_angle_beta", //string like 90 or float 103.524(2)
		"_cell_angle_gamma", //string like 90 or float 103.524(2)
		"_cell_volume", //string like 2131.5(3)
		"_exptl_crystal_density_diffrn", //float like 1.338
		"_exptl_absorpt_coefficient_mu", //float like 0.105
		"_exptl_crystal_F_000", //int like 896
		"_2thetha", //int like 56
		"_diffrn_reflns_number", //int like 19309
		"_reflns_number_total", //int like 6507
		"_reflns_number_gt", //int like 3852
		"_refine_ls_number_parameters", //int like 310
		"_refine_ls_R_factor_all", //float like 0.1064
		"_refine_ls_wR_factor_gt", //float like 0.1147
		"_refine_ls_restrained_S_all", //float like 1.013
		"_refine_diff_density_max", //float like 0.317
		"_refine_diff_density_min" //float like -0.280
	};

	if (cifFile)
	{
		for (int i = 0; i < LEXEME_COUNT - 1; i++)
		{
			lexValue = "";

			while(!feof(cifFile))
			{
				if (fgets(str, 127, cifFile))
					if ( strncmp(cifLexemes[i], str, strlen(cifLexemes[i])) == 0 ) // Found the lexeme in cifFile
					{
						lexValue = get_cif_lex_value(str);
						write_data(outFile, stdout, cifLexemes[i], lexValue);
					}
			}
			if (strcmp(lexValue, "") == 0)
				write_data(outFile, stdout, cifLexemes[i], "!No value!\n");

			fseek(cifFile, 0, SEEK_SET); // Start from the beginning of cifFile
		}
	}
	else
	{
		fprintf(outFile, "Error! No CIF file!\n");
	}

	fclose(cifFile);
	fclose(outFile);
}


int main(int argc, char * argv[])
{
	char * cifFileName = get_arguments(argc, argv);
	read_cif_file(cifFileName);

	return 0;
}
