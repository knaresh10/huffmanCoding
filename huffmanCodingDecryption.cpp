#include<bits/stdc++.h>
#define ll long long
using namespace std;

class HuffmanNode {
public:
	char data;
	HuffmanNode *left, *right;
	HuffmanNode() {
		data = '\0';
		left = right = nullptr;
	}
};

unordered_map<char, string> getHuffmanCodes(ifstream& inputFile) {
	unordered_map<char, string> huffmanCodes;
	char marker[7];
	inputFile.read(marker, 7);
	char numSym;
	inputFile.read(&numSym, 1);
	for (int i = 0; i < numSym; i++) {
		char symbol;
		char codeLength;
		inputFile.read(&symbol, 1);
		inputFile.read(&codeLength, 1);
		string huffmanCode;
		for (int j = 0; j < codeLength; j++) {
			char bit;
			inputFile.read(&bit, 1);
			huffmanCode += bit;
		}
		huffmanCodes[symbol] = huffmanCode;
	}
	return huffmanCodes;
}

HuffmanNode *buildHuffmanTree(const unordered_map<char, string> &huffmanCodes) {
	HuffmanNode *tree = new HuffmanNode();
	HuffmanNode *currNode = tree;
	for (auto pair : huffmanCodes) {
		char symbol = pair.first;
		string code = pair.second;
		for (char bit : code) {
			if (bit == '0') {
				if (currNode->left == nullptr) currNode->left = new HuffmanNode();
				currNode = currNode->left;
			} else {
				if (currNode->right == nullptr) currNode->right = new HuffmanNode();
				currNode = currNode->right;
			}
		}
		currNode->data = symbol;
		currNode = tree;
	}
	return tree;
}

string getEncodedData(ifstream& inputFile) {
	char separator[4];
	inputFile.read(separator, 4);
	size_t encodedDataLength;
	inputFile.read(reinterpret_cast<char*>(&encodedDataLength), sizeof(size_t));
	string encodedData;
	char byte;
	while (inputFile.get(byte)) {
		encodedData += bitset<8>(byte).to_string();
	}
	encodedData.resize(encodedDataLength);
	return encodedData;

}

void decompress(string& encodedData, HuffmanNode *root) {
	string decodedData = "";
	HuffmanNode* currNode = root;
	for (char bit : encodedData) {
		if (bit == '0') {
			currNode = currNode->left;
		} else {
			currNode = currNode->right;
		}

		if (currNode->left == NULL && currNode->right == NULL) {
			decodedData += currNode->data;
			currNode = root;
		}
	}
	ofstream decodedFile("output.txt");
	decodedFile << decodedData;
	decodedFile.close();
	cout << "decoded data is stored in output.txt file\n";
}

int main() {
	ifstream inputFile("output.bin", ios:: binary);
	unordered_map<char, string> huffmanCodes = getHuffmanCodes(inputFile);
	HuffmanNode *huffmanTree = buildHuffmanTree(huffmanCodes);
	string encodedData = getEncodedData(inputFile);
	inputFile.close();
	decompress(encodedData, huffmanTree);
	cout << "decryption is done";
}
