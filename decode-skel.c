#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Program developed for NWEN243, Victoria University of Wellington
   Author: Kris Bubendorfer (c) 2014-15 & Raphael Namay 2018.
   Uses a modified caeser I & II (in 2015)

   Compile:  gcc -o decode decode.c

   See encode for  examples on using it
 */

char upcase(char ch){
  if(islower(ch))
    ch -= 'a' - 'A';
  return ch;
}

char* fixkey(char* s){
  int i, j;
  char plain[26]; // assume key < length of alphabet, local array on stack, will go away!

  for(i = 0, j = 0; i < strlen(s); i++){
    if(isalpha(s[i])){
      plain[j++] = upcase(s[i]);
    }
  }
  plain[j] = '\0';
  return strcpy(s, plain);
}


int in(char c, char* s, int pos){
  // Assume everything is already in the same case
  int i;

  for(i = 0; i < pos; i++)
    if(c == s[i]) return 1;

  return 0;
}


void buildtable (char* key, char* decode){ // this changed from encode

  // This function needs to build an array of mappings in 'encode' from plaintext characters
  // to encihered characters.

  // You are implementing a Caesar 1 & 2 combo Cypher as given in the lab handout.
  // Your code here:

  // probably need to declare some stuff here!

  int keyLength = strlen(key);

  //printf("original key length: %d\n", keyLength);

  char* originalKey = key;

  key = fixkey(key); // fix the key, i.e., uppercase and remove whitespace and punctuation

  // Do some stuff here to make a translation between plain and cypher maps.

  //remove duplicates from key
  char keyArray[keyLength];
  strcpy(keyArray, key);

  char finalKeyArray[strlen(key)+1];

  int i;
  int j = 0;
  for (i = 0; i < strlen(key); i++) {
    if (strchr(finalKeyArray, keyArray[i]) == NULL) {
      finalKeyArray[j++] = keyArray[i];
    }
  }
  finalKeyArray[j] = '\0';
  //end of remove duplicates from key

char finalEncode[27] = "__________________________\0";



int l = 0;
for (int k = keyLength-1; k < strlen(finalEncode) - strlen(finalKeyArray) + 2; k++) {
  finalEncode[k] = finalKeyArray[l++];
  }


char currentLetter = finalKeyArray[strlen(finalKeyArray)-1];
for (int myIndex = keyLength + strlen(finalKeyArray)-1; myIndex < 26; myIndex++) {
  if (currentLetter > 'Z') {
    currentLetter = 'A';
  }
  while (strchr(finalKeyArray, currentLetter) != NULL) {
    currentLetter++;
  }
  finalEncode[myIndex] = currentLetter;
  currentLetter++;
}

char endLetter = finalEncode[25]+1;
int addIndex = 0;
//printf("%c\n", endLetter);
while (addIndex != keyLength-1) {
if (strchr(key, endLetter) == NULL) {
  finalEncode[addIndex] = endLetter;
  addIndex++;
}
endLetter++;
}


int keyTranscribeIndex = 0;
char* keyPointer;
for (keyPointer = key; keyPointer < key + strlen(finalKeyArray); keyPointer++) {
  (*keyPointer) = finalKeyArray[keyTranscribeIndex++];
}
(*keyPointer) = '\0';

char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
char* alphabetPtr;
char* finalEncodePtr;


int finalEncodeIndex = 0;
int alphabetIndex = 0;
char finalDecode[] = "__________________________\0";
int finalDecodeIndex = 0;
for (alphabetIndex = 0; alphabetIndex < 26; alphabetIndex++) {
if (strchr(finalEncode, alphabet[alphabetIndex]) != NULL) {
  finalEncodeIndex = strchr(finalEncode, alphabet[alphabetIndex]) - finalEncode;
  finalDecode[finalDecodeIndex++] = alphabet[finalEncodeIndex];
}

}

int encodeTranscribeIndex = 0;
char* encodePointer;
for (encodePointer = decode; encodePointer < decode + strlen(finalDecode); encodePointer++) {
  (*encodePointer) = finalDecode[encodeTranscribeIndex++];
}
(*encodePointer) = '\0';

  // the simplest way to do this is to do exactly the same as you did when creating the
  // encode table, and then look up the encode table to get the translations, and build the
  // decode table from this.  This isn't the most efficient approach, but it will get the
  // job done unless you want to be fancy.


}

int main(int argc, char **argv){
  // format will be: 'program' key {encode|decode}
  // We'll be using stdin and stdout for files to encode and decode.

  // first allocate some space for our translation table.

  char* decode = (char*)malloc(sizeof(char)*26); // this changed from encode
  char ch;

  if(argc != 2){
    fprintf(stderr,"format is: '%s' key", argv[0]);
    exit(1);
  }

  // Build translation tables, and ensure key is upcased and alpha chars only.

  buildtable(argv[1], decode); // this changed from encode

  // write the key to stderr (so it doesn't break our pipes)

  fprintf(stderr,"key: %s - %d\n", decode, strlen(decode));


  // the following code does the translations.  Characters are read
  // one-by-one from stdin, translated and written to stdout.

    ch = fgetc(stdin);
    while (!feof(stdin)) {
      if(isalpha(ch))          // only decrypt alpha chars
	fputc(decode[ch-'A'], stdout);
     else
	fputc(ch, stdout);
      ch = fgetc(stdin);      // get next char from stdin
    }
}
