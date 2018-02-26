#include <stdio.h>
#include <stdlib.h> /* don't feel like making malloc */

/* _TEST:  structure for message data and address. */
struct _TEST {
	char *vidmem;
	char *msg;
};
typedef struct _TEST test_t;

/* Normal functions prototypes */
void pzero(void *s, long size);
int pcopy(char *from, char *to);
int pstrlen(char *s);
char *pstr(char *s);

/* Function prototypes for the above structure. */
test_t startup(char *msg);
void cleanup(test_t *t);

/* main:  program to print text to the screen. */
int main(void)
{
	test_t t;
	t = startup("Hello world!");
/*	pcopy(t.msg, t.vidmem); / doesn't work currently. */
	puts(t.msg);
	cleanup(&t);
	return 0;
}

/* pzero:  zeros a constant memory block. */
void pzero(void *s, long size)
{
	char *p = (char*)s;

	for (p = s; p != (p+(size*sizeof(char))) && *p != 0; ++p)
		*p = 0;
}

/* pcopy:  copies a string to another, returns total chars copied. */
int pcopy(char *from, char *to)
{
	int i;

	if (from == NULL || to == NULL)
		return -1;
	for (i = 0; (*to = *from) != 0; to++,from++)
		i++;
	return i;
}

/* pstrlen:  returns the amount of characters present in a string. */
int pstrlen(char *s)
{
	int i;

	if (s == NULL)
		return -1;
	for (; *s != 0; s++,i++);
	return i;
}

/* pstr: creates a new string. */
char *pstr(char *s)
{
	char *msg = malloc(pstrlen(s)*sizeof(char));
	if (pcopy(s, msg) < 0)
		return NULL;
	return msg;
}

/* startup:  starts the test_t struct and rest of the program. */
test_t startup(char *msg)
{
	test_t t;
	pzero(&t, sizeof(test_t));
	t.vidmem = (char*)0xb8000;
	t.msg = pstr(msg);
	return t;
}

/* cleanup:  cleans up after everything, used when program finishes. */
void cleanup(test_t *t)
{
	if (t->msg) free(t->msg);
	pzero(&t, sizeof(test_t));
}
