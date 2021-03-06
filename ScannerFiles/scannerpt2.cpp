#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: **
//=====================================================

// --------- HELPER FUNCTIONS ---------------------
// Done By: Ivan Inandan
// Purpose: To simplify vowel / consanant checking

// Checks for vowel
// 'a' 'e' 'i' 'o' 'u' 'E' 'I'
// Done By: Ivan Inandan
bool vowelCheck(char input)
{
  if(input == 'a' || input == 'e' || input == 'i' || input == 'o' || input == 'u' || // Word 1
     input == 'E' || input == 'I') // Word 2
    return true;
  
  else
    return false;
}

// Checks for consonants able to start a consonant pair
// 'b' 'g' 'h' 'k' 'm' 'n' 'p' 'r'
// Done By: Ivan Inandan
bool consonantPairCheck(char input)
{
  if(input == 'b' || input == 'g' || input == 'h' || input == 'k' ||
     input == 'm' || input == 'n' || input == 'p' || input == 'r')
    return true;
  
  else
    return false;
}

// Checks for other consonants not able to start consonant pair
// 'd' 'j' 'w' 'y' 'z'
// Done By: Ivan Inandan
bool consonantCheck(char input)
{
  if(input == 'd' || input == 'j' || input == 'w' ||
     input == 'y' || input == 'z')
    return true;
  
  else
    return false;
}

// --------- STATE REFERENCE ----------------------
// State 0: q0 (starting state)
// State 1: qV (final state)
// State 2: qN (final state)
// State 3: qSA
// State 4: qY
// State 5: qS
// State 6: qC
// State 7: qT

// --------- DFAs ---------------------------------

// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by: Ivan Inandan
// ** RE: (vowel | vowel n | consonant vowel | consonant vowel n |
//         consonant-pair vowel | consonant-pair vowel n) ^+

bool word(string s)
{
  int state = 0;
  int charpos = 0;
  
  while (s[charpos] != '\0')
    {
      if(state == 0 && vowelCheck(s[charpos])) //q0 --> qV (on vowel)
	state == 1; // Final State
      
      else if(state == 0 && consonantCheck(s[charpos])) //q0 --> qSA (on consonant nonpair)
	state == 3;
      
      else if(state == 0 && consonantPairCheck(s[charpos])) //q0 --> qY (on consonant pair)
	state = 4;

      else if(state == 0 && s[charpos] == 's') //q0 --> qS (on 's')
	state = 5;
      
      else if(state == 0 && s[charpos] == 'c') //q0 --> qC (on 'c')
	state = 6;
      
      else if(state == 0 && s[charpos] == 't') //q0 --> qT (on 't')
	state = 7;
      
      else if(state == 1 && vowelCheck(s[charpos])) // qV --> qV (loop on vowel)
	state = 1; // Final State
      
      else if(state == 1 && s[charpos] == 'n') //qV --> qN (on 'n')
	state = 2; // Final state
      
      else if(state == 1 && consonantCheck(s[charpos])) //qV --> qSA (on consonant nonpair)
	state = 3;
      
      else if(state == 1 && consonantPairCheck(s[charpos])) //qV --> qY (on consonant pair)
	state = 4;

      else if(state == 1 && s[charpos] == 's') //qV --> qS (on 's')
	state = 5;
      
      else if(state == 1 && s[charpos] == 'c') //qV --> qC (on 'c')
	state = 6;
      
      else if(state == 1 && s[charpos] == 't') //qV --> qT (on 't')
	state = 7;
      
      else if(state == 2 && vowelCheck(s[charpos])) //qN --> qV (on vowel)
	state = 1; // Final State
      
      else if(state == 2 && s[charpos] == 'n') //qN --> qN (loop on 'n')
	state = 2;
      
      else if(state == 2 && consonantCheck(s[charpos])) //qN --> qSA (on consonant nonpair)
	state = 3;

      else if(state == 2 && consonantPairCheck(s[charpos])) //qN --> qY (on consonant pair)
	state = 4;
      
      else if(state == 2 && s[charpos] == 's') //qN --> qS (on 's')
	state = 5;
      
      else if(state == 2 && s[charpos] == 'c') //qN --> qC (on 'c')
	state = 6;
      
      else if(state == 2 && s[charpos] == 't') //qN --> qT (on 't')
	state = 7;

      else if(state == 3 && vowelCheck(s[charpos])) //qSA --> qV (on vowel)
	state = 1; // Final State
      
      else if(state == 4 && vowelCheck(s[charpos])) //qY --> qV (on owel)
	state = 1; // Final State

      else if(state == 4 && s[charpos] == 'y') //qY --> qSA (on 'y')
	state = 3;
      
      else if(state == 5 && vowelCheck(s[charpos])) //qS --> qV (on vowel)
	state = 1; // Final state
      
      else if(state == 5 && s[charpos] == 'h') //qS --> qSA (on 'h')
	state = 3;
      
      else if(state == 6 && vowelCheck(s[charpos])) //qC --> qV (on vowel)
	state = 1; // Final State
      
      else if(state == 6 && s[charpos] == 'h') //qC --> qSA (on 'h')
	state = 3;
      
      else if(state == 7 && vowelCheck(s[charpos])) //qT --> qV (on vowel)
	state = 1; // Final State

      else if(state == 7 && s[charpos] == 's') //qT --> qSA (on 's')
	state = 3;

      else // Stuck in a state
	return false;

      charpos++;
    }//end of while
  
  // where did I end up????
  if (state == 1 || state == 2) // Final States
    return(true);  // end in a final state
  
  else // Otherwise not in final state
    return(false);
}

// Checks to see if word ends in vowel lower case                                                                                                                                 // Done By: Ivan Inandan                                                                                                                                                          
/*bool checkWord1(string s)
{
  if(word(s))
    {
      char lastCharacter = s[s.length() - 1];

      if(lastCharacter == 'a' || lastCharacter == 'e' || lastCharacter == 'i' ||
         lastCharacter == 'o' || lastCharacter == 'u')
        return true;

      else
        return false;
    }
}
*/
// Checks to see if word ends in 'E' or 'I'                                                                                                                                       // Done By: Ivan Inandan                                                                                                                                                          
/*bool checkWord2(string s)
{
  if(word(s))
    {
      char lastCharacter = s[s.length() - 1];

      if(lastCharacter == 'E' || lastCharacter == 'I')
        return true;

      else
        return false;
    }
}
*/

// ** Add the PERIOD DFA here
// ** Done by: Ivan Inandan
bool periodtoken(string s)
{
  if(s == ".")
    return true;
  
  else
    return false;
}

// -----  Tables -------------------------------------

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, EOFM, PERIOD, WORD1, WORD2, VERB, VERBNEG, VERBPAST, VERBPASTNEG,
                IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR};

string tokenName[30] = {"ERROR", "EOFM", "PERIOD", "WORD1", "WORD2",
			"VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG",
			"IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR"};
//for the display names oftokens - must be in the same order as the tokentype.

// ** Need the reservedwords table to be set up here.
struct rt
{
  const char* string;
  tokentype token;
}

// ** Do not require any file input for this.
// ** a.out should work without any additional files
  
//rt = reserved table
// has strings from file and tokent types
  rt[] = {
    //Verb Markers
    {"masu", VERB}, 
    {"masen", VERBNEG}, 
    {"mashita", VERBPAST}, 
    {"masendshita", VERBPASTNEG},
    {"desu", IS}, 
    {"deshita", WAS}, 
    //Particles 
    {"o", OBJECT}, 
    {"wa", SUBJECT}, 
    {"ni", DESTINATION},
    //Pronouns
    {"watashi", PRONOUN}, //(I/me)
    {"anata", PRONOUN}, //(you)
    {"kare", PRONOUN}, //(he/him)
    {"kanojo", PRONOUN},//(she/her)
    {"sore", PRONOUN}, //(it)
    //Connectors
    {"mata", CONNECTOR}, //(Also)
    {"soshite", CONNECTOR}, //(Ho)
    {"shikashi", CONNECTOR},//(However)
    {"dakara", CONNECTOR} //(Therefore)
  };

// ------------ Scaner and Driver -----------------------

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by:
int scanner(tokentype& a, string& w)
{

  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.
  fin >> w;
  /*
  2. Call the token functions one after another (if-then-else)
     And generate a lexical error message if both DFAs failed.
     Let the token_type be ERROR in that case.

  3. Then, make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.

  4. Return the token type & string  (pass by reference)
  */
  int rowcounter = sizeof rt/ sizeof rt[0];
  //call token function
  if(word(w))
    {
      for (int i = 0; i < rowcounter; i++)
        {
          if (w == rt[i].string)
            {
              a = rt[i].token;
              return 0;
            }
        }
      //find it token has a capital E or I
      char endofstring = ' '; endofstring = w[(w.length())-1];

      //checking for tokent type word1 and word2
      if(endofstring == 'I' || endofstring == 'E')
        {
          a = WORD2;
        }
      else if(endofstring == 'a' || endofstring == 'e' || endofstring == 'i' ||
	      endofstring == 'o' || endofstring == 'u')
        {
          a = WORD1;
        }
    }
  
  //check period token
  else if (periodtoken(w))
    {
      a = PERIOD;
    }
  
  else if (w == "eofm")
    {
    }
  
  else //check if lexical error
    {
      cout << "LEXICAL ERROR: " << w << "is not a valid token \n";
      a = ERROR;
    }

  return 0;


}//the end of scanner

// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by:  Rika
int main()
{
  tokentype thetype;
  string theword;
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
  while (true)
    {
      scanner(thetype, theword);  // call the scanner
      if (theword == "eofm") break;  // stop now

      cout << "Type is:" << tokenName[thetype] << endl;
      cout << "Word is:" << theword << endl;
    }

  cout << "End of file is encountered." << endl;
  fin.close();

}// end
