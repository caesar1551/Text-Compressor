# Text-Compressor
A Text Compressor built on C++ using Huffman Technique.

## Efficiency
* Input Text - 334 KB
* Mapper - 2 KB
* Encoded Text - 275 KB
* Compressed file is 80% of the original file.


## How to run?
To compress the text file run the following command on terminal :-

```bash
g++ encode.cpp
./a.out input.txt encodedMessage.txt map.txt
```

To get the original text file run the following command on terminal :-

```bash
g++ decode.cpp
./a.out encodedMessage.txt map.txt output.txt
```

## License
[MIT](https://choosealicense.com/licenses/mit/)
