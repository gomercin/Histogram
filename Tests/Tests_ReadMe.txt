"make tests" command will build TestMain.cpp.
TestMain.cpp will traverse the folders here (under Tests directory) and use each folder as a Test Harness.
Test directories should be named with numbers starting from 1 and increasing by 1 to be run automatically.
Tests with hardcoded paths will not require this limitation

A valid test directory must include following items:
	expected_errors.txt
	expected_output.txt
Output of the application will be compared to these files.

Input files in automatic folders must be named input.txt

Test descriptions for each test folder will be written in a file named description.txt