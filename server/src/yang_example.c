#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yang_parser.h"

/*
 * utility function - opens a file for reading and checks the result
 * exits the program on failure
 */
FILE* load_file(char* filename);

/*
 * loads a simple .yang file, parses it and prints the internal module structure
 */
int run_example1();

/*
 * loads a simple .yang file, parses it and prints the internal module structure
 */
int run_example2();

/*
 * loads a simple .yang file, parses it and prints the internal module structure
 */
int run_example3();

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Usage: %s <parameter>\nWhere <parameter> is:\n - one of the prepared examples:"
				"\"example1\" up to \"example3\" or\n - a file name denoting a .yang data model\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (!strcmp(argv[1], "example1")) {
		return run_example1();
	} else if (!strcmp(argv[1], "example2")) {
		return run_example2();
	} else if (!strcmp(argv[1], "example3")) {
		return run_example3();
	}

	FILE* file = load_file(argv[1]);
	module* mod = read_module_from_file(file);
	print_module(mod);
	destroy_module(mod);

	return EXIT_SUCCESS;
}

FILE* load_file(char* filename) {
	if (filename == NULL || !strcmp(filename, "")) {
		fprintf(stderr, "Did not receive a file name. Exiting.\n");
		exit(EXIT_FAILURE);
	}

	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Could not open file %s. Exiting.\n", filename);
		exit(EXIT_FAILURE);
	}

	return file;
}

int run_example1() {
	char filename[] = "test-resources/ietf-system.yang";
	FILE* file = load_file(filename);

	printf("This example loads ietf-system yang model -> %s and parses it.\n\n", filename);

	module* mod = read_module_from_file(file);
	print_module(mod);
	destroy_module(mod);

	fclose(file);

	return EXIT_SUCCESS;
}

int run_example2() {
	char filename[] = "test-resources/ietf-system.yang";
	char filename2[] = "test-resources/ietf-system-tls-auth.yang";
	char filename3[] = "test-resources/ietf-x509-cert-to-name.yang";
	FILE* file = load_file(filename);
	FILE* file2 = load_file(filename2);
	FILE* file3 = load_file(filename3);

	printf("This example loads ietf-system yang model augmented by ietf-system-tls-auth and parses it.\n\n");

	module* mod = read_module_from_file(file3);
	module* mod2 = read_module_from_file_with_groupings(file2, mod);

	print_module(mod2);
	destroy_module(mod);
	destroy_module(mod2);

	fclose(file);
	fclose(file2);
	fclose(file3);

	return EXIT_SUCCESS;
}

int run_example3() {
	char filename[] = "test-resources/sample-yang-1.yang";
	FILE* file = load_file(filename);

	printf("This example loads a simple custom made yang model.\n");

//	module* ietf_system_tls_auth_mod = read_module_from_string_with_groupings(ietf_system_tls_auth, cert_to_name_mod);

	module* mod = read_module_from_file(file);
	print_module(mod);
	destroy_module(mod);

	return EXIT_SUCCESS;
}
