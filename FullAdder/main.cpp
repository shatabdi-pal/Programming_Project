/* 
NAME: Shatabdi Pal
ASSIGNMENT: Lab 2
SOURCES: None
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>


using namespace std;


struct adderStruct{
       bool sum;
       bool carry;
 };

bool notFunc(bool p);
bool andFunc(bool p, bool q);
bool orFunc(bool p, bool q);
bool xorFunc(bool p, bool q);
char fullAdder(bool, bool, bool&);
string formattedOutput(string str);
string stringValidity(char * num);
adderStruct halfAdderFunc(bool, bool);

int main(int argc, char **argv)
{   

    bool     P, Q;
    int      count      = 0;
    string   output     = "";
    string   reverseOut = "";
    string   space      = " ";
    bool     carryIn    = false;
    char     numOne[9]  = "00000000";
    char     numTwo[9]  = "00000000";
    
   cout << "Name: Shatabdi Pal\n" << endl;

   while (count < 4){
 
   cout << "Please enter first string: ";
   cin.getline(numOne, 9);
   string operandOne = stringValidity(numOne);
   
    
   cout << "Please enter second string: ";
   cin.getline(numTwo, 9);
   string operandTwo = stringValidity(numTwo);
  

   string firstValue  = operandOne;
   string secondValue = operandTwo;    
  
   cout << "The numbers to be added are  " << formattedOutput(firstValue)
         << " and " << formattedOutput(secondValue) << endl;
  
   for (int i = operandOne.length() - 1, j = operandTwo.length() - 1; i >=0, j >=0; i--, j--)
   {
            if (operandOne[i] == '0')
            {
                P  = false;     
            }
            else
            {
                P = true;
            }
            
            if (operandTwo[j] == '0')
            {
                Q  = false;     
            }
            else
            {
               Q = true;
            }
            
            output += fullAdder(P, Q, carryIn);    
            
   }
    int k = 0;
    for (k = output.length() - 1; k >= 0; k--)
    {
        reverseOut += output[k];
    }
    if (carryIn == true)
    {
        cout << "The answer is " <<  "1" + formattedOutput(reverseOut) << endl;
    }
    else
    {
          cout << "The answer is " <<  formattedOutput(reverseOut) << endl;
    }

    reverseOut = "";
    output = "";
    carryIn = false;
    
    count++; 

   }
  
    return 0;
}
// For checking if input consists of char other than 1 or 0
string stringValidity(char *  num)
{
   for(int i = 0; i < strlen(num); i++)
   {
      if (num[i] != '0' && num[i] != '1')
      {
         cout << "Invalid string! Please enter valid string: ";
         cin.getline(num, 9);      
               
       }
   }
   return num;
}

bool andFunc(bool p, bool q)
{
    bool andOut = false;

    andOut = p && q ;

    return andOut;
}

bool orFunc(bool p, bool q)
{
    bool andOut = false;

    andOut = p || q ;

    return andOut;
}

bool notFunc(bool p)
{
    bool notOut = false;

    notOut = !p;

    return notOut;
}

bool xorFunc(bool p, bool q)
{
    bool xorOut = false;

    xorOut = andFunc(orFunc(p ,q) , notFunc(andFunc(p, q)));

    return xorOut;
}

adderStruct halfAdderFunc(bool p, bool q)
{
   adderStruct ad;
   ad.sum   =  xorFunc(p, q);
   ad.carry = andFunc(p, q);
      
    return ad;
}     

char fullAdder(bool p, bool q, bool &cIn)
{
   adderStruct r1, r2; 
   bool cOut     = false;
   
   
   r1   = halfAdderFunc(p, q);
   r2   = halfAdderFunc(r1.sum, cIn);
   cOut = orFunc(r1.carry, r2.carry);
  

   cout << "The bits are " << p << " and " <<  q << "."  << setw(20) 
          << "The carry in is " << cIn << "." << setw(20) << " The sum is "
          << r2.sum << setw(20) << " The carry out is " << cOut << "."
          << endl;

   cIn = cOut;

   return ((r2.sum == 1) ? '1' : '0');  
    
}

string formattedOutput(string str)   // For adding space in every 4 bits
{
    string newStr;
    int length = 0;
    length = str.length ();
    if (length == 8)
    {    
        newStr= str.substr(0,4)+ " " + str.substr(4,4);        
    }
    else if (length < 8  && length > 4)
    {
       
       newStr= str.substr(0,(length - 4))+ " " + str.substr((length -4),4);
    }
    else 
    {
        newStr = str;  
    }

    return newStr;
}   
