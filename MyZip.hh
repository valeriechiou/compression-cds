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

#ifndef MyZip_hh
#define MyZip_hh

//***********************************************************
//Class Name: MyZip
//
//Design:
//
//Usage/Limitations: Is unable to decrypt correctly with really large files/file examples
//
//***********************************************************

#include <string>

class MyZip
{
	public:
	MyZip();
	~MyZip();

	//Accessor/Mutator of m_BufferSize
	int GetBufferSize() const;
	void SetBufferSize(int& value);

	// Method: Compress
	// Output: void
	// Input: InputFile to be compressed
	void Compress(std::string& InputFile) const;
	
	// Method: Decompress
	// Output: void
	// Input: InputFile.cds to be decompressed
	void Decompress(std::string& InputFile) const;
	
	private:
	int m_BufferSize;


};

#endif

