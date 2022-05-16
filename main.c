#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<locale.h> 
						
						
bool isLeftCurlyBracket(char* ch) {    // ch = { ise true de�ilse false
	if (ch == "{" )
		return true;
	else return false;	
}
bool isRightCurlyBracket(char* ch) {   // ch = } ise true de�ilse false  	
	if (ch == "}" )
		return true;
	else return false;	
}
bool isEndOfLine(char* ch){				// ch = . ise true de�ilse false
	if (ch == "." )
		return true;	
	else return false;
}
bool isOpenBlock(char* ch){				// ch = [ ise true de�ilse false
	if (!strcmp(ch,"[")) return true;
	else return false;
}
bool isCloseBlock(char* ch){			// ch = ] ise true de�ilse false
	if (!strcmp(ch,"]")) return true;
	else return false;
}
bool isSeparator(char* ch){				// ch = , ise true de�ilse false
	if (ch == ",")
		return true;
	else 
		return false;
}


bool isKeyword(char* ch){		// strcmp parametre olarak girilen iki stringi kar��la�t�r�yor. e�er ayn� ise 0 de�erini d�nd�r�yor bu y�zden ba��na ! koyduk
	if (!strcmp(ch,"int") || !strcmp(ch,"move") || !strcmp(ch,"add") || !strcmp(ch,"to") || !strcmp(ch,"sub") || !strcmp(ch,"out") || 
	!strcmp(ch,"from") || !strcmp(ch,"loop") || !strcmp(ch,"newline") || !strcmp(ch,"times")){
		return true;
	}
	else{
		return false;
	}	
}

bool isInteger(char* ch){
	if ( ch[0] == '-') {			// e�er - bir say� ise en fazla 101 uzunlu�unda olabilir. ��nk� en fazla 100 basamakl� olabiliyor. - i�areti de eklenince 101.
		if (strlen(ch) > 101){		// e�er 101den uzun ise false de�erini d�nd�r�r.
			return false;
		}
		else {
			int i;	
			for (i = 0 ; i < strlen(ch) ; i++){  // tek tek her basama��n kontrol�n� yap�yoruz 
				if(i>0){
					if(ch[i] == '.'){			// e�er i�erisinde . varsa yani ondal�kl� say� ise false de�erini d�nd�r�yor.
						return false;
					}
					else if (!isdigit(ch[i])){	// e�er her basamak say� de�il ise false de�erini d�nd�r�yor.
						return false;
					}
					
				}
			}
			return true;
		}
	}
	else if (isdigit(ch[0])){				// e�er - de�ilse yani ilk basama�� da say� ise
		if (strlen(ch) > 100){				// en fazla 100 basamakl� olabilir. 100den fazlaysa false
			return false;
		}
		else{
			int i;
			for (i = 0 ; i < strlen(ch) ; i++){	// yine i�erisinde . var m� ve b�t�n basamaklar say� m� diye kontrol ediyoruz.
				if(ch[i] == '.'){
					return false;
				}
				else if (!isdigit(ch[i])){
					return false;
				}
			}
			return true;
		}
	}
	else {
		return false;
	}
}

bool isVariables(char* ch){
	
	if (strlen(ch) > 20)						//20den b�y�k uzunlukta olamaz.
		return false;
	int i;
	for (i = 0 ; i < strlen(ch) ; i++ ){
		if (isalpha(ch[0]) == 0 )  // isalpha alfabede bulunan harflerden de�il ise 0 d�nd�r�yor
			return false;
		
		if (i > 0)
			if (isalpha(ch[i]) == 0)	// ilk harf harici di�er harfler ya alfabedeki karakterler ya da _ olabilir.
				if (ch[i] == '_')
					continue;
				else
					return false;	
	}   		
	return true;
}
bool isDoubleQuotes(char* ch){
	if (ch== "\"") return true;
	else return false;
}


kelime_test_Et(char* ch){
	FILE *dosya = fopen("myscript.lx","a");
	
	if (isKeyword(ch)){						
		fprintf(dosya,"Keyword %s\n",ch);			
	}
	else if (isInteger(ch)){
		fprintf(dosya,"IntConstant %s\n",ch);
	}
	else if (isEndOfLine(ch)){
		fprintf(dosya,"EndOfLine\n");
	}
	else if(isVariables(ch)){
		fprintf(dosya,"Identifier %s\n",ch);			
	}
	else if (isOpenBlock(ch) || ch[0] == '['){
		fprintf(dosya,"OpenBlock\n");
	}	
	else if (isCloseBlock(ch) || ch[0] == ']'){
		fprintf(dosya,"CloseBlock\n");
		ch = strtok(ch,"]");
	}
	else if(isSeparator(ch)){
		fprintf(dosya,"Seperator\n");
	}
	
	else if (ch[0] == '"'){
		fprintf(dosya,"Stringconstant %s \n",ch);	
	}
	else{
		fprintf(dosya,"Tan�mlanamayan kelime\n");
	}
}


int parse(char* str , int satir_sayisi,int comment,int stringsayac)
{
	FILE *dosya = fopen("myscript.lx","a");
	char *word[999];
    int kelime_sayisi = 0 ;
	char *piece = strtok(str," ");
	char *stringconstant[100];
    while(piece != NULL){
    	word[kelime_sayisi] = piece;
		piece = strtok(NULL," ");	
		kelime_sayisi++;
	}
	if (word[kelime_sayisi - 1][strlen(word[kelime_sayisi - 1 ]) -2 ] == '.' ){
		word[kelime_sayisi -1 ] = strtok(word[kelime_sayisi - 1 ],".");
		word[kelime_sayisi++] = "." ;
	}
	else if (word[kelime_sayisi - 1][strlen(word[kelime_sayisi - 1 ]) -1 ] == '.' ){
		word[kelime_sayisi -1 ] = strtok(word[kelime_sayisi - 1 ],".");
		word[kelime_sayisi++] = "." ;
	}

	int i;
	for (i = 0 ; i < kelime_sayisi; i++){
		int kelime_uzunlugu;					// kelimenin uzunlu�unu tutuyoruz.
		if (i == (kelime_sayisi - 1) ){
				kelime_uzunlugu = strlen(word[i]) - 1;
			}
		else kelime_uzunlugu = strlen(word[i]);
	
		
		if (isLeftCurlyBracket(word[i]) || word[i][0] == '{' || word[i][kelime_uzunlugu - 1 ] == '{'){
			comment = 1;
			if (word[i][kelime_uzunlugu - 1] == '{'){  // e�er kelime{ ise kelime analiz edilir ve commente girilir. 
				word[i] = strtok(word[i],"{");
				kelime_test_Et(word[i]);
			}
			else if(word[i][0] && word[i][kelime_uzunlugu - 1] == '}'){ // e�er tek kelimelik comment ise {comment} olabilir
				comment = 0;
			}
		}
		else if(isRightCurlyBracket(word[i]) || word[i][0] == '}' || word[i][kelime_uzunlugu - 1] == '}'){		
			if(comment = 1){	// e�er comment a��kken } gelmi�se ka� tane { oldu�unun bir �nemi olmad��� i�in { }yap�s� sa�land��� i�in comment=0 olur
				comment = 0;
				if (word[i][0] == '}'){
					word[i]=strtok(word[i],"}");
				}
				else{
					continue;
				}		
			}
			else{
				fprintf(dosya,"Comment a�madan kapat�lamaz");
			}
		}
		else{
			comment = comment;
		}
		
		if (comment == 0){
			if (word[i][kelime_uzunlugu - 1 ] == ','){		// kelimenin sonu virg�l ise virg�lden ayr�l�r ve analiz edilir.
					word[i] = strtok(word[i],",");
					kelime_test_Et(word[i]);
					kelime_test_Et(","); 
				}
			else{
					kelime_test_Et(word[i]);
			}	
			
		}
		
	}
	
	return comment;
	
}


int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Turkish");
	FILE *fp = fopen("deneme.ba", "r"); ;
	FILE *dosya = fopen("myscript.lx", "w");
	int satir_sayisi = 1 ;
    int wordCount = 0 ;
    char *arrayOfWords[9999];
    char str[60];
    int comment = 0 ;
    int stringsayac = 0;
    if(fp != NULL) {
        while(!feof(fp)) {
            fgets (str, 60, fp);
			arrayOfWords[wordCount] = str;       
			int a = parse(arrayOfWords[wordCount],satir_sayisi,comment,stringsayac);
			comment = a ;
			satir_sayisi++;
			wordCount++;	
		}        
}	
	if (comment == 1 ){
		fprintf(dosya,"Comment kapat�lmad�\n");
	}
	fclose(fp);
	return 0;
}









