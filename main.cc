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

#include <iostream> 
#include "./MyZip.hh"

using namespace std;

int main(int argc, char** argv)
{
	MyZip* zip;
	zip = new MyZip;
	int bufferSize =100;
	zip->SetBufferSize(bufferSize);
	string InputFile(argv[1]);
	
	FILE* fin;
	long fileSz=0;
	char* buffer;
	size_t result;
	
	fin=fopen(InputFile.c_str(),"r");
	if(fin == NULL){
		fputs("File error", stderr);
		exit(1);
	}
	
	fseek(fin, 0, SEEK_END);
	fileSz=ftell(fin);
	rewind(fin);
	buffer=(char*)malloc(sizeof(char)*fileSz);
	
	if(buffer == NULL){
		fputs("Memory error",stderr);
		exit(2);
	}
	
	result=fread(buffer, sizeof(char), 1, fin);
	
	//if content is genomic file data (check if first is '\')
	if(buffer[0] != '\\'){
		zip->Compress(InputFile);
	}
	else{
		zip->Decompress(InputFile);
	}
		
	delete zip; //free space
	zip = NULL;
	
	
	return 0;
}

