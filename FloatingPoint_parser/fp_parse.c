/* Name: Shatabdi Pal
   Assignment: A3
   Description: To implement an IEEE floating point parser 
   Date: 15th Feb, 2021
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <error.h>

void input_validation(int frac_bits, int exp_bits, unsigned int hex_number, 
                       char hex_string[5]);
float normalized_number(int k, int n, int exp, int frac, int sign_bit);
float denormalized_number(int k, int n, int exp, int frac,int sign_bit);
 
int main (int argc, char * argv[])
{
    int frac_bits, exp_bits,sign_bit;
    int arg1_read = 0;
    int arg2_read = 0;
    int arg3_read = 0;
    unsigned int hex_number;
   
    float V;

    if (argc < 2)
    {
       printf("Usage: fp_parse < 0 of frac_bits > < 0 of exp_bits >\n");
       exit(0);                                          //program abort for no arguments
    }
    else
    {
         
        arg1_read = sscanf(argv[1], "%d", &frac_bits);
        arg2_read = sscanf(argv[2], "%d", &exp_bits);
        arg3_read = sscanf(argv[3], "%x", &hex_number);

        if (arg1_read == 0 || arg2_read == 0 || arg3_read == 0)   //error checking for sscanf
        {
            error(EXIT_FAILURE, 0, "INPUT ERROR"); 

        }
        
        input_validation(frac_bits, exp_bits, hex_number, argv[3]);
    }
     
     unsigned int exp = (((1 << exp_bits) - 1) & (hex_number >> exp_bits));    // to isolate exponent bits
     unsigned int frac = (((1 << exp_bits) - 1) & hex_number);                 // to isolate fraction bits 
     sign_bit = (((1 << exp_bits) - 1) & (hex_number >> (exp_bits + frac_bits)));        //to isolate sign bits

     if ((exp >  0) && (exp < (pow (2, exp_bits) - 1)))            //for normalized number;
     {

         V = normalized_number(exp_bits, frac_bits, exp, frac, sign_bit); 
         printf("%.6f\n", V); 

     } 

     if (exp == 0)                                              //for denormalized number
     {
 
         V = denormalized_number(exp_bits, frac_bits, exp, frac,sign_bit);
         printf("%.6f\n", V); 

     } 

      if ((frac == 0)&& (exp == (pow (2, exp_bits) - 1)))          //to calculate infinite number
      {
          if (sign_bit == 0)
          {

              printf("+inf\n");

          }
          else
          {
    
              printf ("-inf\n");

          }
     }

     if ((frac != 0) && (exp == (pow (2, exp_bits) - 1)))             //to calculate NAN
     {
  
         printf("NaN\n");

     }
     
               
     exit(EXIT_SUCCESS);
}

void input_validation(int frac_bits, int exp_bits, unsigned int  hex_number, char  hex_string[5])
{

    int idx = 0;
    unsigned int bit_count = 0;

    if ((frac_bits >= 2) && (frac_bits <= 10));                 //range checking for fraction bits

    else
    {
        printf("Invalid number of fraction bits (%d)", frac_bits);
        printf(". Should be between 2 and 10\n");
        exit(0);

     }

     if ((exp_bits >= 3) && (exp_bits <= 5));                  //range checking for exponent bits

     else
     {
       
         printf("Invalid number of exponent bits (%d)", exp_bits);
         printf(". Should be between 3 and 5\n");
         exit(0);

      }
      do
      {
          if (isxdigit(hex_string[idx]) != 0)                 //to check hexadecimal number
          {

              idx++;

          }
          else
          {
              printf("Argument 3 is not a hexadecimal number (%s) .\n", hex_string);
              exit(0);

          }

       }  while (hex_string[idx] != '\0'); 

       while (hex_number)  
       {

           bit_count++;                                   //to count bits in hexdecimal number
           hex_number >>= 1;
       
       }
 
       if (bit_count <= (frac_bits + exp_bits + 1));            //to check limit of bits in hexadecimal number

       else
       {
                        
            printf("Number %s exceeds maximum number of bits. ",hex_string);
            printf("Only 7 allowed here. \n");
            exit(0);   
   
       }
  
        return; 
        
}

float normalized_number(int n, int k,int exp, int frac, int sign_bit)
{
    int bias, E,S;                    
    float f, M, V, pow_2e;

    bias = pow(2,(k - 1))- 1;                        
    E = exp - bias;                   // E exponent
    f = frac / pow (2 ,n);          
    M = 1 + f;                        //M significand
    pow_2e = pow(2, E);

    if (sign_bit == 0)
    {
        S = pow(-1,0);
       
        V = S * M * pow_2e;          //floating point output
    }
    else
    {
         
        S = pow(-1,1);
       
        V = S * M * pow_2e;
    } 

    return V; 
     
}
float denormalized_number(int k, int n, int exp, int frac, int sign_bit)
{

    int bias, E, S;
    float f, M, V, pow_2e;

    bias = pow(2, (k - 1))- 1;       
    E = 1 - bias;
    f = frac / pow (2 ,n);
    M = f;
    pow_2e = pow(2, E);
    
    if (sign_bit == 0)
    {
        S = pow(-1,0);
       
        V = S * M * pow_2e;
    }

    else
    {
         
        S = pow(-1,1);
       
        V = S * M * pow_2e;
    } 

     return V;
}
