#include "QInt.h"


int main(int argc, char** argv)
{
	//xu ly tham so truyen vao
	string input_path;
	string output_path;
	if (argc < 2)
	{
		//Chua co duong dan den input va output
		input_path = "input.txt";
		output_path = "output.txt";
		Out_File(input_path, output_path);
	}
	else
	{
		input_path = argv[1];
		output_path = argv[2];
		Out_File(input_path, output_path);
	}

		return 0;
}

