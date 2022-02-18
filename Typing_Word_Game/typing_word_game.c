/* Name: Shatabdi Pal
   Assignment: A1
   Description: To implement a program for a game that tests user's typing speed
   Date: 13th Jan, 2021
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <error.h>

#define MAX_LENGTH 15
#define MAX(a, b) ((a) > (b) ? (a):(b))

void swap(char ** word_1, char ** word_2);
void randomize_array(char * string[], int size);

int main (int argc, char * argv[])
{

    char * word_list[] = { "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"}; 

    char word[MAX_LENGTH];
    int length;
    bool found = false;
    int i;
    char c;

    struct timeval start_time;
    struct timeval end_time; 
    struct timeval total_time;

    length = (int) (sizeof(word_list) / sizeof(word_list[0]));

    randomize_array(word_list, length);                 //to generate permutations of words

    printf("This is a game that tests typing speed\n");

    printf("\nType the following words:\n");
 
    gettimeofday(&start_time, NULL);  /*to keep track of  the beginning
                                      of the user's input*/

    i = 0;

    do
     {
         do
         {
             printf("word #%d is %s: ", (i + 1) , word_list[i]);

             int temp = scanf("%10s", word); 

             if (temp == 0)
             {
                 error(EXIT_FAILURE, 0, "INPUT ERROR");
             }                                
             while((c = getchar()!= '\n') && c != EOF);            //to flush out extra characters 
                                                         

             int compare_len = MAX(strlen(word_list[i]),strlen(word));

             if (strncmp(word_list[i] , word, compare_len) == 0)       //comparison with user's input
                  found = true;                                        //if match found
             else
                  found = false;
             
          }while (found == false);                      /*for wrong input
                                                          user would reenter*/

          i++;

     }while (i < length);
                                                    
     gettimeofday(&end_time, NULL);                       //to track endtime after all correct input

     timersub(&end_time, &start_time, & total_time);      /*time difference
                                                            gives actual typing time*/
                                                      
     printf("You took %ld seconds and %ld microseconds\n",\
            total_time.tv_sec, total_time.tv_usec);

     exit (EXIT_SUCCESS);

}

void swap(char ** word_1, char ** word_2)
{
    char * temp = *word_1;
    *word_1 = *word_2;
    *word_2 = temp;
}

void randomize_array(char * string[], int size)
{
    int i;
    struct timeval system_time;
    gettimeofday(&system_time, NULL);
   
    srand (system_time.tv_usec);            //to seed with usec value

    for (i = size - 1; i > 1; i--)
    {
        int k = rand() % (i + 1);
        swap(&string[i], &string[k]);
    }
} 
     
