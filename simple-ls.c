
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

#include <time.h>
#include <locale.h>
#include <langinfo.h>

#define STRLEN1 128
#define STRLEN2 64


int main(int argc, char *argv[]) 
{
	DIR 		   *p_dir;
	struct dirent  *p_dirent;
	char str[] = 	"---------\0";
	struct stat 	buf;
	struct passwd  *pwd;
	struct tm      *tm;
	char            datestring[256];
	struct group   *grp;
	char 		   *file_name;
	int 			u,c,l; 
	char 		   *link_buf;

	if (argc != 3) {
		printf("Usage: <option> <directory name>\n");
		exit(0);
	}

	if ((p_dir = opendir(argv[2])) == NULL) {
		printf("opendir(%s) failed\n", argv[1]);
		exit(1);
	}

	p_dir = opendir(argv[2]);

	size_t arglen = strlen(argv[2]);

	while ((p_dirent = readdir(p_dir)) != NULL) {
		  char *str_path = malloc(arglen + strlen(p_dirent->d_name) + 2);

		  sprintf(str_path, "%s/%s", argv[2], p_dirent->d_name);

		if (str_path == NULL) {
			printf("Null pointer found!"); 
			exit(2);
		} else {
			if (lstat(str_path, &buf) < 0) {
				perror("lstat error");
				continue;
			}   

			mode_t mode = buf.st_mode;

			str[0] = (mode & S_IRUSR) ? 'r' : '-';
			str[1] = (mode & S_IWUSR) ? 'w' : '-';
			str[2] = (mode & S_IXUSR) ? 'x' : '-';
			str[3] = (mode & S_IRGRP) ? 'r' : '-';
			str[4] = (mode & S_IWGRP) ? 'w' : '-';
			str[5] = (mode & S_IXGRP) ? 'x' : '-';
			str[6] = (mode & S_IROTH) ? 'r' : '-';
			str[7] = (mode & S_IWOTH) ? 'w' : '-';
			str[8] = (mode & S_IXOTH) ? 'x' : '-';

			pwd = getpwuid(buf.st_uid);
			grp = getgrgid(buf.st_gid);
			

			if (S_ISLNK(mode)) {

				link_buf = malloc(buf.st_size + 1);

				readlink(str_path, link_buf, buf.st_size + 1 );

		   		link_buf[buf.st_size] = '\0';

				char * symlink_filename = malloc(strlen(link_buf) + strlen(p_dirent->d_name) + 4);

				sprintf(symlink_filename, "%s -> %s\0", p_dirent->d_name, link_buf);
				
				strcpy(file_name, symlink_filename);

				free(link_buf);
				free(symlink_filename);


			} else {
				file_name = p_dirent->d_name;
			}


			u = strcmp(argv[1], "-u");
			c = strcmp(argv[1], "-c");
			l = strcmp(argv[1], "-l");
						
			if (u == 0){
				tm = localtime(&buf.st_atime);
			}
			else if (c == 0){
				tm = localtime(&buf.st_ctime);
			}
			else if (l  == 0){
				tm = localtime(&buf.st_mtime);
			} else {
				printf("Please enter -u, -c or -l as the option\n");
				exit(1);
			}

			strftime(datestring, sizeof(datestring), "%b   %e:%H:%M\t", tm);			

			printf("%s %s   %s  %zd %s %s \n", str, pwd->pw_name, grp->gr_name, buf.st_size, datestring, file_name);
			free(str_path);
		}

	}

	closedir(p_dir);

	return 0;
}