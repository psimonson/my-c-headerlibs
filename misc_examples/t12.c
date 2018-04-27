#include "../common/btree.h"
#include <stdarg.h>

void die(int ecode, const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);
	exit(ecode);
}
#define DIE(M) die(EXIT_FAILURE, "[ERROR] : " M "\n")

int main(int argc, char *argv[])
{
	FILE *fp;

	if (argc < 3 || argc > 4)
		die(0, "Usage: %s [-r <file>]"
			" <file> <key_value> <quoted-data>\n",
			argv[0]);
	if (argc == 3 && (strcompare(argv[1], "-r") == 0)) {
		btree_t *tree;
		char buf[1024];

		if ((fp = fopen(argv[2], "rt")) == NULL)
			DIE("Cannot open file for reading.");
		tree = init_tree();
		if (tree == 0)
			DIE("Cannot allocate tree memory.");
		while (fgets(buf, sizeof buf, fp) != NULL) {
			char data[512];
			int key;

			sscanf(buf, "key_value=%d;data=%[^\t\n];\n",
				&key, data);
			btree_setopt(tree, key, data);
			btree_insert(key+1, &tree);
		}
		fclose(fp);
		btree_print(tree);
		btree_destroy(&tree);
	} else {
		if ((fp = fopen(argv[1], "at")) == NULL)
			DIE("Cannot open file for writing.");
		fprintf(fp, "key_value=%s;data=%s;\n", argv[2], argv[3]);
		fclose(fp);
	}
	return 0;
}
