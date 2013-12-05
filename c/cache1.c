#include "inc.h"


int main() {
    static int x[5000][5000];
	int i;
    for (i = 0; i < 5000; i++) {
		int j;
        for (j = 0; j < 5000; j++) {
            x[i][j]++;
        }
    }
    return 0;
}
