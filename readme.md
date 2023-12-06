# Huffman Coding Encryption and Decryption

## Overview

This project implements Huffman coding for data compression, including encryption and decryption functionalities. Huffman coding is a widely used algorithm for lossless data compression. The encryption process converts the input text into a compressed binary format, and the decryption process reverses this operation to recover the original text.

## Usage

### Prerequisites

Ensure you have a C++ compiler installed on your system.

### Input and Output

- Input text for encryption is read from `input.txt`.
- Encoded binary data is stored in `output.bin`.
- Decrypted text is written to `output.txt`.

### Compilation

Compile the programs using the following commands:

For Encryption:
```bash
g++ huffmanCodingEncryption.cpp -o encrypt
```

For Decryption:
```bash
g++ huffmanCodingDecryption.cpp -o decrypt
```

### Encryption

To encrypt a text file, run the following command:

```bash
./encrypt
```

This will read the text from `input.txt`, perform Huffman coding encryption, and write the encoded binary data to `output.bin`.

### Decryption

To decrypt the binary file and obtain the original text, run the following command:

```bash
./decrypt
```

This will read the encoded binary data from `output.bin`, perform Huffman coding decryption, and write the original text to `output.txt`.

## File Structure

- [`huffmanCodingEncryption.cpp`](huffmanCodingEncryption.cpp): C++ program for Huffman coding encryption.
- [`huffmanCodingDecryption.cpp`](huffmanCodingDecryption.cpp): C++ program for Huffman coding decryption.

## Example

Assuming you have a file named `input.txt` with the following content:

```
Hello, Huffman Coding!
```

After encryption, the binary data will be stored in `output.bin`. Running the decryption process on `output.bin` will produce a file named `output.txt` with the original text.

## Acknowledgments

- The Huffman coding algorithm used in this project is based on the classic Huffman coding algorithm.

Feel free to modify the code and customize it according to your needs. If you encounter any issues or have suggestions for improvement, please open an issue on the GitHub repository.
