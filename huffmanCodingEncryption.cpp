#include<bits/stdc++.h>
#define ll long long
using namespace std;

class HuffmanNode {
public:
	char data;
	int freq;
	HuffmanNode *left, *right;
	HuffmanNode() {
		data = '\0';
		freq = 0;
		left = right = nullptr;
	}
	HuffmanNode(char data, int val) {
		this->data = data;
		freq = val;
		left = right = nullptr;
	}
	HuffmanNode(int val, HuffmanNode *first, HuffmanNode *second) {
		data = '\0';
		freq = val;
		left = first;
		right = second;
	}
};

unordered_map<char, int> getFreqTable() {
	ifstream inputFile("input.txt");
	char data;
	unordered_map<char, int> freqTable;
	while (inputFile.get(data)) {
		freqTable[data]++;
	}
	inputFile.close();
	return freqTable;
}

struct cmp {
	bool operator()(const HuffmanNode* a, const HuffmanNode* b) const {
		return a->freq > b->freq;
	}
};

HuffmanNode *createHuffmanTree(const unordered_map<char, int> &freqTable) {
	priority_queue<HuffmanNode*, vector<HuffmanNode*>, cmp> pq;
	for (auto it : freqTable) {
		HuffmanNode *newNode = new HuffmanNode(it.first, it.second);
		pq.push(newNode);
	}
	while (pq.size() != 1) {
		HuffmanNode *first = pq.top(); pq.pop();
		HuffmanNode *second = pq.top(); pq.pop();
		HuffmanNode *newNode = new HuffmanNode(first->freq + second->freq, first, second);
		pq.push(newNode);
	}
	return pq.top();
}

void generateHuffmanCodes(const HuffmanNode *root, const string& code, unordered_map<char, string>& huffmanCodes) {
	if (root->data != '\0') {
		huffmanCodes[root->data] = code;
		return ;
	}
	generateHuffmanCodes(root->left, code + '0', huffmanCodes);
	generateHuffmanCodes(root->right, code + '1', huffmanCodes);
}

string getEncodedData(unordered_map<char, string>& huffmanCodes) {
	string encodedData = "";
	ifstream inputFile("input.txt");
	char data;
	while (inputFile.get(data)) encodedData += huffmanCodes[data];
	inputFile.close();
	return encodedData;
}

void writeCompressedData(const string& encodedData, const unordered_map<char, string> &huffmanCodes) {
	ofstream outputFile("output.bin", ios::binary);
	outputFile.write("HUFFMAN", 7);
	char numSym = static_cast<char>(huffmanCodes.size());
	outputFile.write(&numSym, 1);
	for (const auto& pair : huffmanCodes) {
		char symbol = pair.first;
		char codeLength = static_cast<char>(pair.second.length());
		outputFile.write(&symbol, 1);
		outputFile.write(&codeLength, 1);
		outputFile.write(pair.second.c_str(), codeLength);
	}

	outputFile.write("DATA", 4);
	size_t originalLength = encodedData.length();
	outputFile.write(reinterpret_cast<const char*>(&originalLength), sizeof(size_t));
	for (int i = 0; i < encodedData.length(); i += 8) {
		string byteStr = encodedData.substr(i, 8);
		while (byteStr.length() < 8) {
			byteStr += '0';
		}
		char byte = static_cast<char>(bitset<8>(byteStr).to_ulong());
		outputFile.put(byte);
	}
	outputFile.close();
	cout << "encoded data is stored in  output.bin file\n";
}

int main() {
	unordered_map<char, int> freqTable = getFreqTable();
	HuffmanNode *huffmanTree = createHuffmanTree(freqTable);
	unordered_map<char, string> huffmanCodes;
	generateHuffmanCodes(huffmanTree, "", huffmanCodes);
	string encodedData = getEncodedData(huffmanCodes);
	writeCompressedData(encodedData, huffmanCodes);
	cout << "encryption is done";
}
