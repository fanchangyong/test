int main() {
    static int x[5000][5000];
	int i,j;
    for (i = 0; i < 5000; i++) {
        for (j = 0; j < 5000; j++) {
            x[j][i]++;
        }
    }
    return 0;
}
