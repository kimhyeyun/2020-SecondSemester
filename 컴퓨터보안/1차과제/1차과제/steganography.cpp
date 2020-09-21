
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

			cout << "파일 열기 실패";
			return 0;
		}

		//fread로 파일 전체를 읽어서 큐에 저장
		while (!feof(bmpfile)) {
			if (!fread(&ch, sizeof(char), 1, bmpfile))
				break;
			q.push(ch);
		}

		//w+b, 없으면 생성
		FILE* result_file;
		fopen_s(&result_file, "stego.bmp", "w+b");

		//queue에서 pop해서 output에 씀
		while (q.size()) {
			fwrite(&q.front(), 1, 1, result_file);
			q.pop();
		}

		//파일 크기
		int f_size = ftell(result_file);

		getline(cin, text);
		int size = text.length();

		//origin.bmp의 끝으로 이동
		fseek(result_file, f_size, SEEK_SET);

		//여기서부터 text임을 표시
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
			cout << "파일 열기 실패";
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
