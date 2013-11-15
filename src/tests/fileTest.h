/*
 * fileTest.h
 *
 *  Created on: Mar 3, 2013
 *      Author: stijn, Serge Demeyer
 */

#ifndef FILETEST_H_
#define FILETEST_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;
namespace tests {
	class FileTest: public testing::Test {
		protected:
			virtual void SetUp() {
			}
			virtual void TearDown() {
			}
		public:
	};
	bool DirectoryExists(const char *dirname) {
		struct stat st;
		return stat(dirname, &st) == 0;
	}

	bool FileCompare(const char *leftFileName, const char *rightFileName) {
		ifstream leftFile;
		ifstream rightFile;
		char leftRead, rightRead;
		bool result;

		// Open the two files.
		leftFile.open(leftFileName);
		if (!leftFile.is_open()) {
			return false;
		};
		rightFile.open(rightFileName);
		if (!rightFile.is_open()) {
			leftFile.close();
			return false;
		};

		result = true; // files exist and are open; assume equality unless a counterexamples shows up.
		while (result && leftFile.good() && rightFile.good()) {
			leftFile.get(leftRead);
			rightFile.get(rightRead);
			result = (leftRead == rightRead);
		};
		if (result) {
			// last read was still equal; are we at the end of both files ?
			result = (!leftFile.good()) && (!rightFile.good());
		};

		leftFile.close();
		rightFile.close();
		return result;
	}

	// Tests the compare files
	TEST_F(FileTest, FileCompare) {
		ASSERT_TRUE(DirectoryExists("testOutput"));
		std::string out1 = "testOutput/file1.txt";
		std::string out2 = "testOutput/file2.txt";
		ofstream myfile;
		myfile.open(out1.c_str());
		myfile.close();
		myfile.open(out2.c_str());
		myfile.close();

		//compare 2 empty files
		// *** Beware: the following does not work with older versions of libstdc++
		// *** It doesn't work with gcc version 4.0.1 (Apple Inc. build 5465)
		// *** It does work with gcc version 4.2.1
		//	EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
		//	EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

		//compare an empty and a non-empty files
		myfile.open(out1.c_str());
		myfile << "xxx" << endl << "yyy";
		myfile.close();
		EXPECT_FALSE(FileCompare(out1.c_str(), out2.c_str()));
		EXPECT_FALSE(FileCompare(out2.c_str(), out1.c_str()));

		//compare two equal files
		myfile.open(out2.c_str());
		myfile << "xxx" << endl << "yyy";
		myfile.close();
		EXPECT_TRUE(FileCompare(out1.c_str(), out2.c_str()));
		EXPECT_TRUE(FileCompare(out2.c_str(), out1.c_str()));

		//compare 2 non-empty files which are off by a character in the middle
		myfile.open(out2.c_str());
		myfile << "xxx" << endl << "xyy";
		myfile.close();
		EXPECT_FALSE(FileCompare(out1.c_str(), out2.c_str()));
		EXPECT_FALSE(FileCompare(out2.c_str(), out1.c_str()));

		//compare 2 non-empty files where one is one character shorter than the other
		myfile.open("testOutput/file2.txt");
		myfile << "xxx" << endl << "yy";
		myfile.close();
		EXPECT_FALSE(FileCompare(out1.c_str(), out2.c_str()));
		EXPECT_FALSE(FileCompare(out2.c_str(), out1.c_str()));

		//compare existig against non existing file
		EXPECT_FALSE( FileCompare(out1.c_str(), "testOutput/nonexisting.txt"));
		EXPECT_FALSE( FileCompare("testOutput/nonexisting.txt", out1.c_str()));
	}
} /*namespace tests*/
#endif /* FILETEST_H_ */
