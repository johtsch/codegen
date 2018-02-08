#ifndef CODELIB_HUFFMAN_HPP
#define CODELIB_HUFFMAN_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <math.h>

typedef double prob;

class HuffmanCoder{
public:
    /* Standard-Konstruktor */
    HuffmanCoder();
    /* Konstruktor mit init-Listen */
    //HuffmanCoder(std::vector<char> lit, std::vector<double> prob);
    /* Konstruktor mit init-Map */
    ~HuffmanCoder();
    /* resets all membervars */
    void reset();

    /* 
        add new Element, z is the char in plaintext, p is the probablity of that char to occur.
        returns false if the new element would cause the sum of the probabilities to be bigger 1 or if the char was already added. in this case the new element is not added.
    */
    bool addElement(char z, prob p);
    /* fire up the engine. Function to call after finishing adding elements */
    void calcProbs();
    void fireup();

    /* GETTER */

    /* get average wordlength */
    double gawl();
    /* get redundancy */
    double gred();
    /* get average (information) content */
    double gaic();
    /* get coding of an char as string */
    std::string gcocStr(char c);
    /* get coding of an char as integer */
    // int gcocInt(char c);

    /* show all encoded chars and their codes */
    void showAll();


private:
    std::map<char, prob>                                _probmap;
    std::map<char, std::string>                         _codemap;

    prob                                                _probsum; // sum of all current probabilities

    /* scales the probabilities in such a way that their sum becomes 1.0 */
    void alterProbs();  
    /* recursive method calculating the codes for each char */
    void genCode(std::map<char, int> nodes);
};

#endif