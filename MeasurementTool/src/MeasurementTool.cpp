#include "BinaryRunner.h"


int main(int argc, char *argv[]) {
	BinaryRunner br;
	br.getBinaryRuntime(argv[1], 3);
	br.getBinarySize(argv[1]);
	return 0;
}
