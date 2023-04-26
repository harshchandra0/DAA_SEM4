#include <stdio.h>
#include <string.h>

#define d 256

void search(char pat[], char txt[], int q)
{
	int M = strlen(pat);
	int N = strlen(txt);
	int i, j;
	int p = 0; // hash value for pattern
	int t = 0; // hash value for txt
	int h = 1;

	for (i = 0; i < M - 1; i++)
		h = (h * d) % q;

	for (i = 0; i < M; i++) {
		p = (d * p + pat[i]) % q;
		t = (d * t + txt[i]) % q;
	}

	for (i = 0; i <= N - M; i++) {

		if (p == t) {
			for (j = 0; j < M; j++) {
				if (txt[i + j] != pat[j])
					break;
			}

			// if p == t and pat[0...M-1] = txt[i, i+1,
			// ...i+M-1]
			if (j == M)
				printf("Pattern found at index %d \n", i);
		}

		// Calculate hash value for next window of text:
		// Remove leading digit, add trailing digit
		if (i < N - M) {
			t = (d * (t - txt[i] * h) + txt[i + M]) % q;

			if (t < 0)
				t = (t + q);
		}
	}
}

int main()
{
	char txt[50];
	char pat[50];
	printf("Enter txt string.\n");
    scanf("%s", txt);

    printf("Enter pattern string.\n");
    scanf("%s", pat);
	int q = 101;
	search(pat, txt, q);
	return 0;
}
