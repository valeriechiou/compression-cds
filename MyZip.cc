/* 
 * Course: CS 100 Summer Session II 2015
 *
 * First Name: Valerie
 * Last Name: Chiou
 * Username: vchio001
 * email address: vchio001@ucr.edu
 * SID: 861102819
 *
 * AssignmentID: hw2
 * Filename: Chiou_Valerie.tar.gz
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 * I also understand that by cheating, stealing, plagiarism or
 * any other form of academic misconduct defined at
 * http://conduct.ucr.edu/policies/academicintegrity.html,
 * the consequences will be an F in the class, and additional
 * disciplinary sanctions, such as the dismissal from UCR.
 *
*/

//***********************************************************
// MyZip Implementation
//***********************************************************

#include "./MyZip.hh"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <assert.h>

using namespace std;

// MyZip Constructor
MyZip::MyZip()
{}

// MyZip Destructor
MyZip::~MyZip()
{}

//Accessor of BufferSize
int MyZip::GetBufferSize() const 
{
	return m_BufferSize;
}

//Mutator of BufferSize
void MyZip::SetBufferSize(int& value)
{
	m_BufferSize = value;
}

// Method: Compress
//*********************************************
// Purpose: Create .cds with encryption values
//
// Implementation Notes: 
// 
// Pseudocode:
// Open the InputFile
// Find the size of the InputFile
// Read in the InputFile
// Create the blank .cds file that will have the encryption
// 
// Create ifstream to read InputFile
// Create character count and base line variable
// Loop through the file to find character count (if a/A/c/C/g/G/t/T are found)
// Increment character count (N) and base per line count (L) if valid base is found
// 		When read hits first new line, stop baseline variable incrementation
//	If program ever find non-base character, display error message and exit out of program
// 
// Create string to hold encrypted values 
// 		Add \0\0\0\N\0\L
// 
// For-loop to go through buffer that holds the InputFile bases
// 	create string to hold sequence of 4 values, 4 character count
// 	if a base match is found, its corresponding binary value is added to the string sequence
// 	
//	take string sequence, and calculate decimal value.
//	store value in string with encrypted values
//	continue until there are no more bases to be encrypted
//
// convert string of encrypted values to char array
// pass char array into fwrite to write into .cds file
// 
// remove original file
// end Compression
//*********************************************
void MyZip::Compress(string& InputFile) const 
{
	
	FILE * inFile;
	long fileSz;
	char * buffer;
	size_t result;
	
	inFile = fopen(InputFile.c_str(), "rb"); //open inputfile
	if(inFile == NULL){
		fputs("File error", stderr);
		exit(1);
	}
	
	fseek(inFile, 0, SEEK_END);
	fileSz = ftell(inFile);
	rewind (inFile);
	buffer = (char*)malloc(sizeof(char)*fileSz); //get size of inputfile
	
	if(buffer == NULL){
		fputs("Memory error", stderr);
		exit(2);
	}
	result = fread(buffer, sizeof(char), fileSz, inFile); //read in inputfile
	
	if(result != fileSz){
		fputs("Reading error", stderr);
		exit(3);
	}
	
	string OutputFile=InputFile +".cds";
	FILE * outFile = fopen(OutputFile.c_str(), "w"); //create blank file
	
	/*************************************************************/
	
	//COMPRESSION
	fopen(InputFile.c_str(), "r");
	
	//find N and L
	ifstream fin;
	fin.open(InputFile.c_str(), ios::in);
	char currChar;
	int c_Char=0;
	long c_newLine=0;
	int basePerLine=0;
	bool foundfirstnewline=false;
	while(!fin.eof()){
		if(fin.get(currChar)){ 
			if(currChar=='a' || currChar=='A' || currChar=='g' || currChar=='G' || currChar=='c' || currChar=='C' || currChar=='t' || currChar=='T'){ 
				//cout << "c_Char: " << c_Char;
				c_Char++;
			}
			else if(currChar=='\n' && foundfirstnewline==false){
				foundfirstnewline=true;
				assert(foundfirstnewline==true && "foundfirstline still equals false");
				basePerLine=c_Char;
			}
			else if( !(currChar=='a' || currChar=='A' || currChar=='g' || currChar=='G' || currChar=='c' || currChar=='C' || currChar=='t' || currChar=='T') && currChar!='\n'){
				cout << "Error: non-base character found. Please check input file." << endl;
				exit(1);
			}
		}
	}
	fin.close();
	
	//create basic beginning .cds content
	string writeIn="\\0\\0\\0\\";
	stringstream ss;
	ss << writeIn << c_Char << "\\0\\" << basePerLine;
	writeIn=ss.str();
	ss.str(""); 										//clear stringstream
	//should look like \0\0\0\N\0\L right now
	
	string value;
	int baseCount = 0;
	int total = 0;
	for(int pos = 0; pos < fileSz;){	
		if(baseCount < 4){
			if(pos+1 == fileSz){
				if(buffer[pos] == 'a' || buffer[pos] == 'A'){
					value+="00";
					baseCount++;
				}
				else if(buffer[pos] == 'c'|| buffer[pos] == 'C'){
					value+="01";
					baseCount++;	
				}
				else if(buffer[pos] == 'g'|| buffer[pos] == 'G'){
					value+="10";
					baseCount++;
				}
				else if(buffer[pos] == 't'|| buffer[pos] == 'T'){
					value+="11";
					baseCount++;		
				}
				else if(buffer[pos] == '\n'){
					//do nothing
				}
				pos++;
				int power = value.size()-1;
				for(int i = 0; i < value.size(); i++){
					if (value[i] == '0'){} // do nothing 
					else total += pow(2,power);		
					power--;
				}
				string decTotal = to_string(total);
				ss << writeIn << "\\" << decTotal;
				writeIn = ss.str();
				ss.str("");
			}
			else{
				if(buffer[pos] == 'a' || buffer[pos] == 'A'){
					value+="00";
					baseCount++;
				}
				else if(buffer[pos] == 'c'|| buffer[pos] == 'C'){
					value+="01";
					baseCount++;	
				}
				else if(buffer[pos] == 'g'|| buffer[pos] == 'G'){
					value+="10";
					baseCount++;
				}
				else if(buffer[pos] == 't'|| buffer[pos] == 'T'){
					value+="11";
					baseCount++;		
				}
				else if(buffer[pos] == '\n'){
					//do nothing
				}
				pos++;
			}
		}
		else if(baseCount == 4 && (pos < fileSz) ){
			int power = value.size()-1;
			for(int i = 0; i < value.size(); i++){
				if (value[i] == '0'){}
				else total += pow(2,power);		
				
				power--;
			}	
			string decTotal = to_string(total);
			ss << writeIn << "\\" << decTotal;
			writeIn=ss.str();
			
			ss.str("");
			baseCount = 0;
			total = 0;
			value = "";
		}
		else if ((pos+1) == fileSz){
			int power = value.size()-1;
			for(int i = 0; i < value.size();i++){
				if (value[i] == '0'){}
				else total += pow(2,power);		
				
				power--;
			}	
			string decTotal = to_string(total);
			ss << writeIn << "\\" << decTotal;
			writeIn=ss.str();
			
			ss.str("");
			baseCount = 0;
			total = 0;
			value = "";
		}
	}
	
	
	
	assert(!writeIn.empty() && "error: writeIn is empty");
	char str[writeIn.size()];
	strcpy(str, writeIn.c_str()); //copy writeIn to str so it can be fwritten
	fwrite (str, sizeof(char), sizeof(str), outFile); //write into .cds file	
	
	remove(InputFile.c_str());
	
	fclose(outFile);
	fclose(inFile);
	free(buffer);
	cout << "Successful compression." << endl;
	//return 0;
}

// Method: Decompress
//*********************************************
// Purpose: Take .cds file and decompress it
//
// Implementation Notes: it doesn't work with huge files...
//	
// Pseudocode:
// 	Open input file
// 	get size of input file
//	read input file
//	
// find starting position in file to begin decrypting
// extract values
//	 
// 
// for-loop to iterate through buffer (inputfile) at position 13 (where stored encrypted values start) until you reach eof (which is size of the file)
// 	if '\' is found, there is a value to be decrypted
// 		subtract total bases by 4
//			create bitmask to grab current value
// 	else, add to sequence
//	continue for-loop 
//
// reverse decrypted string because it's backwards
// 
// create .tmp file
// write string of decrypted bases into .tmp file
// 	when written bases=base line number, enter a newline character
//
// remove .cds file
// end method
//*********************************************
void MyZip::Decompress(string& InputFile) const{
	FILE * inFile;
	long fileSz;
	char * buffer;
	size_t result;
	
	inFile = fopen(InputFile.c_str(), "r"); //open inputfile
	if(inFile == NULL){
		fputs("File error", stderr);
		exit(1);
	}
	
	fseek(inFile, 0, SEEK_END);
	fileSz = ftell(inFile);
	rewind (inFile);
	buffer = (char*)malloc(sizeof(char)*fileSz); //get size of inputfile
	
	if(buffer == NULL){
		fputs("Memory error",stderr);
		exit(2);
	}
	result = fread(buffer, sizeof(char), fileSz, inFile); //read in inputfile
	
	if(result != fileSz){
		fputs("Reading error",stderr);
		exit(3);
	}
	
	/*************************************************************/
	
	//DECOMPRESSION
	fopen(InputFile.c_str(), "r");
	
	int count = 0;
	int totalBases = 0; 
	int basesPerLine = 0;
	int perLineStart = 0;
	int start = 7;
	while (buffer[start] != '\\'){
		if(count == 0) {	
			totalBases = buffer[start] - '0';
		}
		else {
			totalBases = (totalBases*10) + (buffer[start] - '0');
		}	
		count++;
		start++;
	}
	start += 3;	
	while(buffer[start] != '\\'){	
		if(count == 0) {
			basesPerLine = buffer[start] - '0';
		}
		else {
			basesPerLine = (basesPerLine*10) + (buffer[start] - '0');
		}	
		count++;
		start++;
	}
	start++;
	
	//count = 0;
	int sequence;
	int curr;
	string currSeq = "";
	string totalFinal = "";

	for(int i = start; i < fileSz;)
	{
		if(buffer[i] == '\\')
		{
			totalBases = totalBases - 4;
			count=0;
			curr = sequence;
			
			for(int j = 0; j < 4; ){
				int bitmask = curr&3;
				if(bitmask == 0) {
					currSeq+='A';
					j++;
				}
				else if (bitmask == 1){
					currSeq+='C';
					j++;
				}
				else if (bitmask == 2) {
					currSeq+='G';
					j++;
				}
				else if (bitmask == 3){
					currSeq+='T';	
					j++;
				}
				curr = curr>>2;
			}
			
			for(int j = 3; j >= 0; j--) {
				totalFinal += currSeq[j];
			}
			
			currSeq ="";
	 		sequence=0;
		}	
		else{	
			if(count == 0){
				sequence = buffer[i] - '0';
				count++;
			}
			else{ 
				sequence = ( sequence*10 ) + (buffer[i] - '0');
				count++;
			}
			
		}	
		i++;
	}

	count = 0;		
	curr = sequence;
	for(int j = 0; j < totalBases;){
		int bitmask = curr&3;
		
		if(bitmask == 0){
			currSeq+='A';
			j++;
		}
		else if (bitmask == 1){
			currSeq+='C';
			j++;
		}
		else if (bitmask == 2){
			currSeq+='G';
			j++;
		}
		else if (bitmask == 3){
			currSeq+='T';
			j++;
		}
		
	 	curr = curr>>2;
			 
	}
	
	//reverse
	for(int j = totalBases-1; j >= 0; j--) {
		totalFinal += currSeq[j];
	} 
	
	string OutputFile="";
	for(int i=0; i < InputFile.size()-4;i++) {
		OutputFile+=InputFile[i];
	}

	OutputFile+=".tmp";

	FILE* outFile; 
	outFile = fopen(OutputFile.c_str(), "w");
	char newLineChar[] = {'\n'};
	for(int i = 0; i < totalFinal.size(); i++)
	{
		if (count == basesPerLine)
		{
			fwrite(newLineChar, sizeof(char), sizeof(newLineChar), outFile);
			count=0;
		}
		const char* lastFinal = string(1, totalFinal.at(i)).c_str();
		fwrite(lastFinal, sizeof(char), 1, outFile);
		count++;  
	}
	fwrite(newLineChar, sizeof(char), 1, outFile);
	fclose(outFile);
	remove(InputFile.c_str());
	
	cout << "Successful decompression." << endl;
}
