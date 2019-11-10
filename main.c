#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int randomNumber(){
  int entropyfile = open("/dev/random", O_RDONLY);
  if (errno) {
    printf("Errno number: %d, Error Message: %s\n", errno, strerror(errno));
  }
  int randomNum;
  read(entropyfile, &randomNum, sizeof(int));
  if (errno) {
    printf("Errno number: %d, Error Message: %s\n", errno, strerror(errno));
  }
  close(entropyfile);
  if (errno) {
    printf("Errno number: %d, Error Message: %s\n", errno, strerror(errno));
  }
  return randomNum;
}

int main(){
  int randArray[10];
  int slider = 0;
  printf("Generating Random Numbers:\n");
  while(slider < 10){
    randArray[slider] = randomNumber();
    printf("random %d: %d\n", slider, randArray[slider]);
    slider++;
  }

  int randomfile = open("randomNumbers.txt", O_RDWR|O_CREAT, 0644);
  if (errno) {
    printf("Errno number: %d, Error Message: %s\n", errno, strerror(errno));
  }
  printf("\nWriting numbers to file...\n");
  write(randomfile, randArray, 10 * sizeof(int));
  if (errno) {
    printf("Errno number: %d, Error Message: %s\n", errno, strerror(errno));
  }
  close(randomfile);
  if (errno) {
    printf("Errno number: %d, Error Message: %s\n", errno, strerror(errno));
  }


  int newArray[10];
  int readfile = open("randomNumbers.txt", O_RDONLY);
  if (errno) {
    printf("Errno number: %d, Error Message: %s\n", errno, strerror(errno));
  }
  printf("\nReading numbers from file...\n\n");
  read(readfile, &newArray, 10 * sizeof(int));
  if (errno) {
    printf("Errno number: %d, Error Message: %s\n", errno, strerror(errno));
  }
  close(readfile);
  if (errno) {
    printf("Errno number: %d, Error Message: %s\n", errno, strerror(errno));
  }
  slider = 0;
  printf("Verification that written values were the same:\n");
  while(slider < 10){
    printf("random %d: %d\n", slider, newArray[slider]);
    slider++;
  }

  return 0;
}
