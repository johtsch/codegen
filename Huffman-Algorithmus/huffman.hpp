#ifndef CODELIB_HUFFMAN_HPP
#define CODELIB_HUFFMAN_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>

class HuffmanCoder{
public:
    /* Standard-Konstruktor */
    HuffmanCoder();
    /* Konstruktor mit init-Listen */
    //HuffmanCoder(std::vector<char> lit, std::vector<double> prob);
    /* Konstruktor mit init-Map */
    ~HuffmanCoder();
    /* leert alle Maps */
    void newCode();
    /* add new Element, z is the char in plaintext, p ist the probablity of that char to occur */
    void addElement(char z, double p);

private:
    std::map<std::string, double> _probmap;
    std::map<std::string, std::string> _codemap;
};

#endif