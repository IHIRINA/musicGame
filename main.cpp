#include<iostream>
#include <graphics.h>
#include "Game.h"

using namespace std;

int main() {
	Game game;
	game.init(1400, 800);

	cout << "ֻ���������û���������ſ��Խ�����ϷŶ" << endl;
	cout << "�������û���: " << endl;
	cin >> game.inputUsername;  // �ӿ���̨�����û���
	cout << "����������: " << endl;
	cin >> game.inputPassword;  // �ӿ���̨��������

	return game.run();
}