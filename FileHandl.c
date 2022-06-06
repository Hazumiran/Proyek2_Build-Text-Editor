#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "linkedlist.H"
#include "editor.H"
#include "PulDown.h"
#include <dirent.h>
#include <corecrt.h> 

void driver(){
		int tamp = 0;
		Baris_Kolom  position;
		position.x = 1;
		position.y = 1;

		
		char fname[20];
		
		List *content = CreateHead();
		system("cls");
		
        Point *CursorPos = pointCtor();
		PullDownDisplay();
		
		do{
			tamp = KursorHandl(content, CursorPos, &position);
			if (tamp == 2){
				PullDown(content, fname, &position);
			}
		}while(tamp != 0);
        deleteList(content);
}

bool txt_exe(char const *name){
	size_t len = strlen(name);
	return len > 4 && strcmp(name + len - 4, ".txt")== 0;
}

void CreateFile(List *list){
	
	char tamp_name[20];
	TextBox(5,  40);
    printf("Masukkin nama filenya gan : ");
    scanf("%s",tamp_name);
    
	FILE *fp;
	fp = fopen(tamp_name, "w");
    saveToFile(fp, list);
    fclose(fp);
    
}

void OpenFile(List *list){
	deleteList(list);
	list = CreateHead();
		
	char fname[20];
	 
		int tamp =1;
	int x = 7;
	
    TextBox(11,45);
    
    	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d) {
	while ((dir = readdir(d)) != NULL) {
		if(txt_exe(dir->d_name)){ 
			goto_xy(30+2,x+1);
			tamp+=1;
			x+=1;   	
			printf("%s\n", dir->d_name);
		}	
    }
    closedir(d);
	}
	
	goto_xy(32,x+2);
    printf("Masukkin nama filenya gan : ");
	scanf("%s",fname);
		
    FILE *fp = fopen(fname, "r");
    Point *CursorPos = pointCtor();
    system("cls");
	PullDownDisplay();
    readFile(fp, list, CursorPos);
    fclose(fp);
}

void Delete(){
	int tamp =1;
	int x = 7;
    TextBox(15, 50);
    goto_xy(30,6);
    
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d) {
	while ((dir = readdir(d)) != NULL) {
		if(txt_exe(dir->d_name)){ 
			goto_xy(30+2,x+1);
			tamp+=1;
			x+=1;   	
			printf("%s\n", dir->d_name);
		}	
    }
    closedir(d);
	}
	
	FILE *fp;
	char fn[15];
	fp=fopen("temp.txt","r");
	
	goto_xy(32,x+1);
	printf("\n");
	goto_xy(32,x+2);
	printf("pilih file yang akan dihapus: ");
	scanf("%s",fn);
	
	fp=fopen(fn,"r");
	
	if(fp==NULL){

		goto_xy(32,x+4);
		printf("File not found!");

	}
	
	fclose(fp);
	
	remove(fn);
	goto_xy(32,x+4);
	printf("File has been deleted successfully!");

}	

void rename(){

	char oldName[100], newName[100];
	int tamp =1;
	int x = 7;
	
    TextBox(11,45);
    
    	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d) {
	while ((dir = readdir(d)) != NULL) {
		if(txt_exe(dir->d_name)){ 
			goto_xy(30+2,x+1);
			tamp+=1;
			x+=1;   	
			printf("%s\n", dir->d_name);
		}	
    }
    closedir(d);
	}
	goto_xy(32,x+2);
    printf("Nama File Yang ingin Dirubah : ");
    scanf("%s", oldName);
	goto_xy(32,x+4);

    printf("masukan nama file baru: ");
    scanf("%s", newName);

    if (rename(oldName, newName) == 0)
    {
    	goto_xy(32,x+5);
        printf("sukses mengubah nama file \n");
    }
    else
    {
    	goto_xy(32,x+5);
        printf("gagal merubah nama file.\n");

}
}