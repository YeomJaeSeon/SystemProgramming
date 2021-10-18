#include <grp.h>
#include <uuid/uuid.h>
#include <stdio.h>

int main(void){
	struct group *grp;
	char* member;

	while((grp = getgrent()) != NULL){
		printf("group name : %s\n", grp->gr_name);
		printf("gid : %d\n", (int)grp->gr_gid);
		printf("Member : ");
		while(*(grp->gr_mem) != NULL){
			printf("%s ", *(grp->gr_mem));
			(grp->gr_mem)++;
		}
		printf("\n");
	}

	return 0;
}
