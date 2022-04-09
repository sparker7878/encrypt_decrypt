#include <stdio.h> //importing standard function calls
#include <stdlib.h> //importing standard function calls
#include <string.h> //importing standard function calls

void encrypt(int key, FILE *fp1, FILE *fp2) {
  char p; //the plaintext character
  char c; //the cyphertext character
  srandom(key); //seeds the random function

  printf("Encrypting...\n");

  while ((p = fgetc(fp1)) != EOF) { //checks that the file isn't at its end
    int p1;
    int c1;
    int r = random() % 97; //change all displayable characters to range [0...96]

    if (p == '\t') { //beginning of encryption algorithm
      p1 = 0;
    } else if (p == '\n') {
      p1 = 1;
    } else {
      p1 = p - 30;
    }

    c1 = (p1 + r) % 97;

    if (c1 == 0) {
      c = '\t';
    } else if (c1 == 1) {
      c = '\n';
    } else {
      c = c1 + 30;
    } //end of encryption algorithm
    fprintf(fp2, "%c", c); //prints encrypted file to given output file
  }

  printf("Encryption done!\n");
}

void decrypt(int key, FILE *fp1, FILE *fp2) {
  char p; //the plaintext character
  char c; //the cyphertext character
  srandom(key); //seeds the random function

  printf("Decrypting...\n");

  while ((p = fgetc(fp1)) != EOF) { //checks that the file isn't at its end
    int p1;
    int c1;
    int r = random() % 97; //change all displayable characters to range [0...96]

    if (p == '\t') { //beginning of decryption algorithm
      p1 = 0;
    } else if (p == '\n') {
      p1 = 1;
    } else {
      p1 = p - 30;
    }

    c1 = (p1 + 97 - r) % 97;

    if (c1 == 0) {
      c = '\t';
    } else if (c1 == 1) {
      c = '\n';
    } else {
      c = c1 + 30;
    } //end of decryption algorithm

    fprintf(fp2, "%c", c); //prints decrypted file to given output file
  }
  printf("Decryption done!\n");
}

int main(int argc, char *argv[]) {
  if (argc < 5) { //checks if argument count is fewer than five
    printf("Too few inputs. Must have 5 arguments.\n");
    printf("Required: program name, key, mode, input file, output file.\n");
    exit(1);
  } else {
    printf("Number of arguments is %d.\n", argc);
  }

  FILE *infile = NULL; //declares a new input file pointer
  FILE *outfile = NULL; //declares a new output file pointer
  infile = fopen(argv[3], "r"); //opens the input file in read mode
  outfile = fopen(argv[4], "w"); //opens the output file in read mode

  int key = atoi(argv[1]); //converts the key arg from a string to an int
  char mode1[8] = "ENCRYPT"; //sets mode one as ENCRYPT
  char mode2[8] = "DECRYPT"; //sets mode two as DECRYPT

  if (infile == NULL) {  //check to make sure the file opened properly
    printf("Error opening file.\n");
    exit(1);
  } else {
    printf("File 1 opened fine!\n");
  }

  if (outfile == NULL) {  //check to make sure the file opened properly
    printf("Error opening file.\n");
    exit(1);
  } else {
    printf("File 2 opened fine!\n");
  }

  if ((strcmp(argv[2], mode1)) == 0) { //checks string equality
    printf("Mode: ENCRYPT\n");
    encrypt(key, infile, outfile); //send thru encyption method
    fclose(infile); //closes file
    fclose(outfile); //closes file
    exit(0); //closes any remaining files
  } else if ((strcmp(argv[2], mode2)) == 0) { //checks string equality
    printf("Mode: DECRYPT\n");
    decrypt(key, infile, outfile); //send thru decryption method
    fclose(infile); //closes file
    fclose(outfile); //closes file
    exit(0); //closes any remaining files
  } else {
    printf("INVALID MODE.\n");
    exit(1);
  }
}
