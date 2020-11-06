#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

typedef struct {
	int x;
	int y;
	char direcao;
}MOVIMENTO;

typedef struct {
	int n;
	int m;
	int** tabuleiro;
}RESTAUM;

RESTAUM& getSave() {
	ifstream file("save.txt");
	RESTAUM ru;
	int num;

	file >> ru.n;
	file >> ru.m;
	
	ru.tabuleiro = new int*[ru.n];
	for (int i = 0; i < ru.n; i++) {
		ru.tabuleiro[i] = new int[ru.m];
	}

	for (int i = 0; i < ru.n; i++) {
		for (int j = 0; j < ru.m; j++) {
			file >> ru.tabuleiro[i][j];

		}
	}

	return ru;
}

void printGame(RESTAUM& ru) {
	for (int i = 0; i < ru.n; i++) {
		for (int j = 0; j < ru.m; j++) {
			char symbol = '&';
			if (ru.tabuleiro[i][j] == -1) symbol = '#';
			else if (ru.tabuleiro[i][j] == 1) symbol = 'X';
			else if (ru.tabuleiro[i][j] == 0) symbol = 'O';
			cout << " | " << symbol;
		}
		cout << endl;
	}
}

int countPieces(RESTAUM& ru) {
	int count = 0;
	for (int i = 0; i < ru.n; i++) {
		for (int j = 0; j < ru.m; j++) {
			if (ru.tabuleiro[i][j] == 1) count++;
		}
	}
	return count;
}

int verifyMove(RESTAUM& ru, MOVIMENTO& movimento) {
	if (movimento.x >= 0 && movimento.x < ru.n && movimento.y >= 0 && movimento.y < ru.m) {
		switch (movimento.direcao) {
		case 'c':
			if (movimento.x - 2 >= 0 && ru.tabuleiro[movimento.x][movimento.y] == 1 && ru.tabuleiro[movimento.x - 1][movimento.y] == 1 && ru.tabuleiro[movimento.x - 2][movimento.y] == 0) {
				return 1;
			}
			else {
				return 0;
			}

			break;
		case 'b':
			if (movimento.x + 2 < ru.n && ru.tabuleiro[movimento.x][movimento.y] == 1 && ru.tabuleiro[movimento.x + 1][movimento.y] == 1 && ru.tabuleiro[movimento.x + 2][movimento.y] == 0) {
				return 1;
			}
			else {
				return 0;
			}
			break;
		case 'e':
			if (movimento.y - 2 >= 0 && ru.tabuleiro[movimento.x][movimento.y] == 1 && ru.tabuleiro[movimento.x][movimento.y - 1] == 1 && ru.tabuleiro[movimento.x][movimento.y - 2] == 0) {
				return 1;
			}
			else {
				return 0;
			}
			break;
		case 'd':
			if (movimento.y + 2 < ru.m && ru.tabuleiro[movimento.x][movimento.y] == 1 && ru.tabuleiro[movimento.x][movimento.y + 1] == 1 && ru.tabuleiro[movimento.x][movimento.y + 2] == 0) {
				return 1;
			}
			else {
				return 0;
			}
			break;
		}
	}
}

vector<MOVIMENTO> getValidMoves(RESTAUM& ru) {
	vector<MOVIMENTO> movimentos_validos;
	for (int i = 0; i < ru.n; i++) {
		for (int j = 0; j < ru.m; j++) {
			for (int k = 0; k < 4; k++) {
				MOVIMENTO mov;
				mov.x = i;
				mov.y = j;
				if (k == 0) mov.direcao = 'c';
				if (k == 1) mov.direcao = 'b';
				if (k == 2) mov.direcao = 'e';
				if (k == 3) mov.direcao = 'd';
				if (verifyMove(ru, mov)) {
					movimentos_validos.push_back(mov);
				}
			}
		}
	}
	return movimentos_validos;
}

void makeMove(RESTAUM& ru, MOVIMENTO& movimento) {
	switch (movimento.direcao) {
		case 'c':
			ru.tabuleiro[movimento.x][movimento.y] = 0;
			ru.tabuleiro[movimento.x - 1][movimento.y] = 0;
			ru.tabuleiro[movimento.x - 2][movimento.y] = 1;
			break;
		case 'b':
			ru.tabuleiro[movimento.x][movimento.y] = 0;
			ru.tabuleiro[movimento.x + 1][movimento.y] = 0;
			ru.tabuleiro[movimento.x + 2][movimento.y] = 1;
			break;
		case 'e':
			ru.tabuleiro[movimento.x][movimento.y] = 0;
			ru.tabuleiro[movimento.x][movimento.y - 1] = 0;
			ru.tabuleiro[movimento.x][movimento.y - 2] = 1;
			break;
		case 'd':
			ru.tabuleiro[movimento.x][movimento.y] = 0;
			ru.tabuleiro[movimento.x][movimento.y + 1] = 0;
			ru.tabuleiro[movimento.x][movimento.y + 2] = 1;
			break;
	}
}

void reverseMove(RESTAUM& ru, MOVIMENTO& movimento) {
	switch (movimento.direcao) {
		case 'c':
			ru.tabuleiro[movimento.x][movimento.y] = 1;
			ru.tabuleiro[movimento.x - 1][movimento.y] = 1;
			ru.tabuleiro[movimento.x - 2][movimento.y] = 0;
			break;
		case 'b':
			ru.tabuleiro[movimento.x][movimento.y] = 1;
			ru.tabuleiro[movimento.x + 1][movimento.y] = 1;
			ru.tabuleiro[movimento.x + 2][movimento.y] = 0;
			break;
		case 'e':
			ru.tabuleiro[movimento.x][movimento.y] = 1;
			ru.tabuleiro[movimento.x][movimento.y - 1] = 1;
			ru.tabuleiro[movimento.x][movimento.y - 2] = 0;
			break;
		case 'd':
			ru.tabuleiro[movimento.x][movimento.y] = 1;
			ru.tabuleiro[movimento.x][movimento.y + 1] = 1;
			ru.tabuleiro[movimento.x][movimento.y + 2] = 0;
			break;
		}
}

int verifySmallestString(vector<int>& vector_one, vector<int>& vector_two) {
	for (int i = 0; i < vector_one.size(); i++) {
		if (vector_one[i] != vector_two[i]) {
			if (vector_one[i] == 1) return 0;
			else return 1;
		}
	}
}

vector<int> getBoardsVariations(RESTAUM& ru, vector<vector<int>>& tabuleiros_verificados) {
	vector<int> matrix_to_vector[8];

	for (int i = 0; i < ru.n; i++) {
		for (int j = 0; j < ru.m; j++) {
			if (ru.tabuleiro[i][j] != -1) matrix_to_vector[0].push_back(ru.tabuleiro[i][j]);
			if (ru.tabuleiro[ru.n - i - 1][j] != -1) matrix_to_vector[1].push_back(ru.tabuleiro[ru.n - i - 1][j]);
			if (ru.tabuleiro[i][ru.m - j - 1] != -1) matrix_to_vector[2].push_back(ru.tabuleiro[i][ru.m - j - 1]);
			if (ru.tabuleiro[ru.n - i - 1][ru.m - j - 1] != -1) matrix_to_vector[3].push_back(ru.tabuleiro[ru.n - i - 1][ru.m - j - 1]);
			if (ru.tabuleiro[j][i] != -1) matrix_to_vector[4].push_back(ru.tabuleiro[j][i]);
			if (ru.tabuleiro[j][ru.n - i - 1] != -1) matrix_to_vector[5].push_back(ru.tabuleiro[j][ru.n - i - 1]);
			if (ru.tabuleiro[ru.m - j - 1][i] != -1) matrix_to_vector[6].push_back(ru.tabuleiro[ru.m - j - 1][i]);
			if (ru.tabuleiro[ru.m - j - 1][ru.n - i - 1] != -1) matrix_to_vector[7].push_back(ru.tabuleiro[ru.m - j - 1][ru.n - i - 1]);
		}
	}

	vector<int> menor_vector = matrix_to_vector[0];

	for (int i = 1; i < 8; i++) {
		if (verifySmallestString(menor_vector, matrix_to_vector[i])) {
			menor_vector = matrix_to_vector[i];
		}
	}

	return menor_vector;
}

int verifyBoardsVerified(RESTAUM& ru, vector<vector<int>>& tabuleiros_verificados) {

	vector<int> matrix_to_vector = getBoardsVariations(ru,tabuleiros_verificados);

	for (int i = 0; i < tabuleiros_verificados.size(); i++) {
		if (tabuleiros_verificados[i] == matrix_to_vector) {
			return 0;
		}
	}
	
	return 1;
}

int solve(RESTAUM& ru, vector<MOVIMENTO>& solucao, vector<vector<int>>& tabuleiros_verificados, int& nodes) {
	nodes++;
	if (countPieces(ru) == 1) {
		return 1;
	}else {
		if (verifyBoardsVerified(ru, tabuleiros_verificados)) {
			vector<MOVIMENTO> movimentos_possiveis = getValidMoves(ru);
			if (movimentos_possiveis.size()) {
				for (int i = 0; i < movimentos_possiveis.size(); i++) {
					makeMove(ru, movimentos_possiveis[i]);
					int result = solve(ru, solucao, tabuleiros_verificados, nodes);
					if (result) {
						solucao.push_back(movimentos_possiveis[i]);
						return 1;
					}else {
						vector<int> vector = getBoardsVariations(ru,tabuleiros_verificados);
						tabuleiros_verificados.push_back(vector);
						reverseMove(ru, movimentos_possiveis[i]);	
					}
				}
				return 0;
			}else {
				return 0;
			}
		}else {
			return 0;
		}
	}
}

int main() {
	auto t1 = chrono::high_resolution_clock::now();
	int nodes = 0;
	RESTAUM ru;
	vector<MOVIMENTO> solucao;
	vector<vector<int>> tabuleiros_verificados;
	ru = getSave();
	
	cout << "ENCONTRANDO SOLUCAO: \n" << endl;
	printGame(ru);

	int result = solve(ru,solucao,tabuleiros_verificados,nodes);

	if (result) {
		cout << "SOLUCAO: \n" << endl;
		for (int i = 0; i < solucao.size(); i++) {
			cout << " " << solucao[i].x << " " << solucao[i].y << " " << solucao[i].direcao << endl;
		}
		cout << endl;
		printGame(ru);
		cout << "\nNUMERO DE NODES: " << nodes << endl;
		cout << "\nNUMERO DE JOGADAS: " << solucao.size() << endl;
	}
	else {
		cout << "SOLUCAO NAO ENCONTRADA " << endl;
	}

	for (int i = 0; i < ru.n; i++) {
		delete[] ru.tabuleiro[i];
	}
	delete[] ru.tabuleiro;

	auto t2 = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
	cout << duration << endl;
	

	return 0;
}