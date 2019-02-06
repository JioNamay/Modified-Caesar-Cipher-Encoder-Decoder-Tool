#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Program developed for NWEN243, Victoria University of Wellington
Author: Kris Bubendorfer (c) 2015 & Raphael Namay 2018.
Uses a modified caeser I & II

Compile:  gcc -o encode encode.c

// Make a file with a plain aplhabet in it:

% cat > test
ABCDEFGHIJKLMNOPQRSTUVWXYZ
^D

// test it - this should be the correct result when encoding.

% cat test | encode "i came, i saw"
key: HJKLNOPQRTUVICAMESWXYZBDFG - 26
HJKLNOPQRTUVICAMESWXYZBDFG

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

void buildtable (char* key, char* encode){

  // This function needs to build an array of mappings in the 'encode' array from plaintext characters
  // to encypered characters.  The encode array will be indexed by the plaintext char.  To
  // make this a useful 0-26 index for the array, 'A' will be stubtracted from it (yes you
  // can do this in C).  You can see this in the main(){} below.  The values in the array
  // will be the cipher value, in the example at the top A -> H, B -> J, etc.

  // You are implementing a Caesar 1 & 2 combo Cypher as given in handout.
  // Your code here:

  // probably need to declare some stuff here!

//key = fixkey(key);

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

int encodeTranscribeIndex = 0;
char* encodePointer;
for (encodePointer = encode; encodePointer < encode + strlen(finalEncode); encodePointer++) {
  (*encodePointer) = finalEncode[encodeTranscribeIndex++];
}
(*encodePointer) = '\0';

}

int main(int argc, char **argv){
  // format will be: 'program' key {encode|decode}
  // We'll be using stdin and stdout for files to encode and decode.

  // first allocate some space for our translation table.

  char* encode = (char*)malloc(sizeof(char)*26);
  char ch;

  if(argc != 2){
    printf("format is: '%s' key", argv[0]);
    exit(1);
  }

  // Build translation tables, and ensure key is upcased and alpha chars only.

  buildtable(argv[1], encode);

  // write the key to stderr (so it doesn't break our pipes)

  fprintf(stderr,"key: %s - %d\n", encode, strlen(encode));

  // the following code does the translations.  Characters are read
  // one-by-one from stdin, translated and written to stdout.

  ch = fgetc(stdin);
  while (!feof(stdin)) {
    if(isalpha(ch)){        // only encrypt alpha chars
      ch = upcase(ch);      // make it uppercase
      fputc(encode[ch-'A'], stdout);
    }else
    fputc(ch, stdout);
    ch = fgetc(stdin);      // get next char from stdin
  }
}
