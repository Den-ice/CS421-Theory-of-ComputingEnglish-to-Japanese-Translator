#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;

// INSTRUCTION:  Complete all ** parts.
// You may use any method to connect this file to scanner.cpp
// that you had written.  
// You can copy scanner.cpp here by cp ../ScannerFiles/scanner.cpp . and do 
// cat scanner.cpp parser.cpp > myparser.cpp
// -----------------------------------------------------

//=================================================
// File parser.cpp written by Group Number: 12
//=================================================

// ----- Utility and Globals -----------------------------------

token_type token_received;
string word;
bool token_here = false;

//story
void s();
void after_subject();

void after_noun();
void after_Object();
void noun();

void verb();
void be();
void tense();


// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by: 
//exit(1) is for halting

//Done by: Denice Hickethier
void syntax_error1(token_type correct, string word)
{
  cout << "SYNTAX ERROR: expected " << tokenName[correct] << ", yet found " << word << endl;
  exit (1);
}

//Done by: Denice Hickethier
void syntax_error2(string word, string pfunction)
{
  cout << "SYNTAX ERROR: unecpected " << word << " located in " << pfunction << endl;
  exit(1);
}

// ** Need the updated match and next_token (with 2 global vars)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by: Ivan Inandan


// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// i.e. Grammar: 
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

/*
Grammar: <story> ::= <s>{<s>}
Done by: Denice Hickethier
*/

void story()
{
  cout << "Processing: <story> \n";
  s();
  while((true) && (word != "eofm"))
    {
      s();
    }
  cout << "\nStory was successfully parsed!\n";
}

/*
Grammar: <s> ::= [CONNECTOR] 
Done by: Denice Hickethier
*/

void s()
{
  next_token();
  if(word != "eofm")
    {
      cout << "Processing: <s> \n";

      if(next_token() == CONNECTOR)
	{
	  match(CONNECTOR);
	}
      noun();
      match(SUBJECT);
      after_subject();
    } 
  else
    {
      cout << "\nDid not get through!\n";
    }
}

/*
Grammar: <after subject> ::= <verb> <tense> PEROD | <noun> <after noun>
Done by: Denice Hickethier
*/

void after_subject()
{
  cout << "Processing: <after_subject> \n";
  switch(next_token())  // Grab next token                                         
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    case WORD1:
      noun();
      afterNoun();
      break;
    case PRONOUN:
      noun();
      afterNoun();
      break;
    default:
      syntax_error2(word, "after subject");    
    }
}

/*
Grammar: <after noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD| OBJECT <after object>
Done by: Denice Hicekthier
*/

void after_noun()
{
  cout << "Processing: <after_noun> \n";
  
  switch(next_token())  // Grab next token       
    {
    case IS:
      be();
      match(PERIOD);
      break;
    case WAS:
      be();
      match(PERIOD);
      break;
    case DESTINATION:
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    case OBJECT:
      match(OBJECT);
      afterObject();
      break;
    default:
      syntax_error2(word, "after noun");          
    }
  
}

/*
Grammar: <after object> ::= <verb> <tense> PERIOD |<noun> DESTINATION <verb> <tense> PERIOD
Done by: Denice Hickethier
*/

void after_object()
{
  cout<<"Processing: <after_object> \n";
  
  switch(next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    case WORD1:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    case PRONOUN:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    default:
      syntax_error2(word, "after object");      
    }
}

/*
Grammar: <noun> ::= WORD1 | PRONOUN 
Done by: Denice Hickethier
*/

void noun()
{
  cout << "Processing: <noun> \n";
  switch(next_token())  // Grabnext token                                   
    {
    case  WORD1:
      match(WORD1);
      break;
    case  PRONOUN:
      match(PRONOUN);
      break;
    default:
      syntax_error2(saved_lexeme, "noun"); 
    }
}

/*
Grammar: <verb> ::= WORD2
Done by:Ivan Inandan
*/

void verb()
{
  cout << "Processing: <verb>" << endl;

  switch(next_token())// Grab next token
    {
    case WORD2:
      match(WORD2);
      break;
      
    default:
      syntax_error2(word, "verb");
    }
}

/*
Grammar: <be> ::= IS | WAS
Done by: Ivan Inandan
*/

void be()
{
  cout << "Processing: <be>" << endl;

  switch(next_token())// Grab Next Token
    {
    case IS:
      match(IS);
      break;

    case WAS:
      match(WAS);
      break;
      
    default:
      syntax_error2(word, "be");
    }
}

/*
Grammar: <tense> ::= VERB | VERBPAST | VERBNEG | VERBPASTNEG
Done by:Ivan Inandan
*/
void tense()
{
  cout << "Processing: <tense>" << endl;

  switch(next_token())// Grab Next Token
    {
    case VERB:
      match(VERB);
      break;

    case VERBPAST:
      match(VERBPAST);
      break;

    case VERBNEG:
      match(VERBNEG);
      break;

    case VERBPASTNEG:
      match(VERBPASTNEG);
      break;
      
    default:
      syntax_error2(word, "tense");
    }
}


//---------------------------------------

// The new test driver to start the parser
// Done by:  Denice Hickethier
int main()
{
  // string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  // story();

  //** closes the input file 
  // fin.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.text of messages

