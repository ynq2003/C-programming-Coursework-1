#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readHistFile(const char filename[],float *bin, float *freq, int *N){
    FILE *fpointer;
    if((fpointer=fopen(filename,"r")) !=NULL){
        while (fscanf(fpointer, "%f\t%f", &bin[*N], &freq[*N]) == 2) { //the programming scan the .hist file every two float nummber and store them in bin[] and freq[] respectively
            (*N)++; //N increment from 0 until the programming cannot scan two float number in one line.
        }fclose(fpointer);
    }
}

void printHist(float *bin, float *freq,int *N){
    for(int i=0;i<*N;i++){
        printf("%.1f\t%.1f\n", bin[i], freq[i]);

    }
}

void plotHorizontalHist(const char filename[], float *bin,float *freq, int *wFreq, int *maxLetter, int *maxLetterFreq){
    FILE *fpointer;
    if((fpointer=fopen(filename,"r")) !=NULL){
        int N=0; //declare N as int
        while (fscanf(fpointer, "%f\t%f", &bin[N], &freq[N]) == 2) { //execute this function when the programming scan every two float numbers
            //Print .hist file for the horizontal histogram
            printf("\n%.1f/%.1f ", bin[N], freq[N]);
                for(int i=0;i<freq[N];i++){
                printf("*");
                }
            printf("\n");
            N++;

    }
        //Print .txt file for the vertical histogram
        for(int i=1;i<*maxLetter+1;i++){ //maxLetter only record as 13, hence need to +1
            int j=0;
            printf("\nwLength:%2d /wFreq[%2d]:%2d : ", i,i,wFreq[i]);
            while(j<wFreq[i]){
                printf("*");
                j++;
            }
        }
        printf("\n"); //divide the horizontal and vertical histogram
    }
}

void plotVerticalHist(const char filename[], float *bin, float *freq, int *wFreq, int *maxLetter, int *maxLetterFreq){
    FILE *fpointer;
    if((fpointer=fopen(filename,"r")) !=NULL){
        int N=0;
        float maxfreq=0;
        printf("\n");
        while (fscanf(fpointer, "%f\t%f", &bin[N], &freq[N]) == 2) {
            if (freq[N] > maxfreq) { //using while loop to set 'float maxfreq' to store the maximum frequency
                maxfreq = freq[N];
            }
            N++;
    }
        // Print .hist file for the vertical histogram
        for (float i = maxfreq; i > 0; i--) { //set a vertical cursor, which start from top to print'*'
            for (int j = 0; j < N; j++) { //set a horizontal cursor, which start from left to print'*'
                if (freq[j]>= i) {
                    printf("* ");
                } else {
                    printf("  ");
                }
            }
            printf("\n");
        }

        // Print bin[] at the bottom
        for (int j = 0; j < N; j++) {
            printf("%.0f ", bin[j]);
        }
        printf("\n");

        //Print .txt file for the vertical histogram
        printf("\n");
        //set a vertical cursor, which start from top to print'*'
        for (int i = *maxLetterFreq; i > 0; i--) {
            //set a horizontal cursor, which start from left to print'*'
            for (int j = 1; j < *maxLetter+1; j++) { //maxLetter only record as 13, hence need to +1
                if (wFreq[j] >= i) {
                    printf("*  ");
                } else {
                    printf("   ");
                }
            }
            printf("\n");
        }

        // Print bin[] at the bottom
        // A bit lengthy, just to make the output more neat
        for (int k=1; k <10; k++) {
            printf("%d  ", k);
        }
        for(int k=10; k<*maxLetter+1; k++){
            printf("%d ",k);
        }
        printf("\n");
        fclose(fpointer);
    }
}


void readTextFile(const char textFilename[], float *bin, float *freq, int *wFreq, int *maxLetter, int *maxLetterFreq){
    FILE *fpointer;
    char word[1000];
        if((fpointer=fopen(textFilename,"r")) !=NULL){
            while (fscanf(fpointer, "%s", word) == 1) { //execute this function when the programming scan one a string of word
                int wLength=0; //clear the word length in every while loop
                int combineWord=0; //clear the status of "combineWord" in every while loop
                for(int i=0; i<strlen(word);i++){
                    //scan the word letter by letter which are in Ascii Format
                    if((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')){ //recognise every alphabets whether in uppercase or lowercase
                    wLength++; //if the alphabet is recognised, word length will +1

                    //eliminate the error when reading word consists of '-'
                    }else if(word[i]=='-'){
                        combineWord=1; //change the status of "combineWord" to execute another function to continue reading the letter
                    }
                }
                //continue reading the letters after recognise '-'
                if(combineWord==1){
                    fscanf(fpointer, "%s", word); //scan the word before '-'
                    for(int i=0; i<strlen(word);i++){
                        if((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')){
                        wLength++;
                        }
                    }
                }
            wFreq[wLength]++;// +1 to the frequency of the word length appeared everytime after couting the word length and store it into the array of wFreq

            if (wLength > *maxLetter) { //using while loop to set *maxLetter to be the biggest word length
                *maxLetter = wLength;
            }

        }
        for(int i=1; i<*maxLetter+1; i++){
            if(wFreq[i]>*maxLetterFreq){ //using for loop to set *maxLetterFreq to be the number of the most frequently counted word length
                *maxLetterFreq=wFreq[i];
            }
        }
    }fclose(fpointer);
}






