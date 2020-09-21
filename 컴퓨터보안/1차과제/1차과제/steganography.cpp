
#include <iostream>
#include <stdio.h>
#include <queue>
#include <stack>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	char option = argv[1][0];
	queue <char> q;
	stack<char> stk;
	static string text = "";
	char ch;
	int offset;
	int* ptr = 0;
	char last_bmp = '*';

	switch (option) {
	case 'e': {
		//read binary mode
		FILE* bmpfile;
		fopen_s(&bmpfile, "origin.bmp", "rb");
		if (bmpfile == NULL) {

			cout << "���� ���� ����";
			return 0;
		}

		//fread�� ���� ��ü�� �о ť�� ����
		while (!feof(bmpfile)) {
			if (!fread(&ch, sizeof(char), 1, bmpfile))
				break;
			q.push(ch);
		}

		//w+b, ������ ����
		FILE* result_file;
		fopen_s(&result_file, "stego.bmp", "w+b");

		//queue���� pop�ؼ� output�� ��
		while (q.size()) {
			fwrite(&q.front(), 1, 1, result_file);
			q.pop();
		}

		//���� ũ��
		int f_size = ftell(result_file);

		getline(cin, text);
		int size = text.length();

		//origin.bmp�� ������ �̵�
		fseek(result_file, f_size, SEEK_SET);

		//���⼭���� text���� ǥ��
		fwrite(&last_bmp, 1, 1, result_file);

		f_size += 1;

		//write text
		for (size_t i = 0; i < text.length(); i++)
		{
			offset = f_size + (i);
			fseek(result_file, offset, SEEK_SET);
			fwrite(&text[i], 1, 1, result_file);
		}

		fclose(bmpfile);
		fclose(result_file);
		break;
	}
	case 'd': {
		char ch;
		FILE* stegano_file;
		fopen_s(&stegano_file, "stego.bmp", "rb");


		if (stegano_file == NULL)
		{
			cout << "���� ���� ����";
			return 0;
		}

		fseek(stegano_file, 0, SEEK_END);


		int i = 1;
		while (1) {
			fseek(stegano_file, -(i), SEEK_END);
			ch = fgetc(stegano_file);
			stk.push(ch);

			if (ch == '*') {
				break;
			}
			i++;
		}

		stk.pop();
		while (!stk.empty()) {
			cout << stk.top();
			stk.pop();
		}

		fclose(stegano_file);
	}

		break;
	}
	return 0;
}
