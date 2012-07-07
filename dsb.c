#include <stdio.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

void parse_dir(char *path) {
	DIR *dir = opendir(path);
	struct dirent *dp;

	while ((dp = readdir(dir))) {
		if (!(dp->d_name[0] == '.' && (dp->d_name[1] == '\0' || dp->d_name[1] == '.'))) {
			struct stat sb; 

			char *fullpath = malloc(strlen(path)+strlen(dp->d_name)+2);
			strcat(strcat(strcpy(fullpath, path), "/"), dp->d_name);
			
			if (stat(fullpath, &sb) == -1) continue;

			printf("  %s\t%s", fullpath, ctime(&sb.st_mtime));

			if ((sb.st_mode & S_IFMT) == S_IFDIR) {
				// we need to go deeper
				parse_dir(fullpath);
			} else if ((sb.st_mode & S_IFMT) == S_IFREG) {
				// parse the regular file
				// ToDo: generate content specific html files //
			}
			// ToDo: generate linked list and add all pages ordered by modification time to it //

			free(fullpath);
		}
	}
}

char *root_path;

int main(int argc, char* argv[]) {
	// parse parameters
	// ToDo: nicer options (GNU Longopts like) for input and output dir //
	if (argc == 1) {
		// parse current working directory
		root_path = ".";
	} else if (argc == 2) {
		// use parameter as dir
		root_path = argv[1];
	} else {
		// print usage message and exit
		printf("Usage: %s [input directory]\n", argv[0]);
		return 1;
	}

	// recursively parse root path
	printf("input: %s\n", root_path);
	parse_dir(root_path);

	// ToDo: generate index files from the linked list //

	return 0;
}
