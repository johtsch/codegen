#include <iostream>
#include <cstdlib>
#include "huffman.hpp"

int main(int argc, char **argv){
    HuffmanCoder hc;

    if(argc < 2){
        std::cout << "[Usage]: " << argv[0] << " <message> " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string msg = argv[1];

    for(int i = 31; i < 127; ++i){
        int count = 0;

        for(int j = 0; j < msg.length(); ++j){
            if(msg[j] == i)
                ++count;
        }

        if(count > 0){
            hc.addElement(i, ((double)count / (double)msg.length()));
        }
    }

    hc.fireup();
    std::cout << "\nsorted: " << std::endl;
    hc.showAllSorted();
    std::cout << "\naverage wordlength : \t\t\t" << hc.gawl() << std::endl;
    std::cout << "average (information) content : \t" << hc.gaic() << std::endl;
    std::cout << "redundance : \t\t\t\t" << hc.gred() << std::endl;
    
    std::cout << "\n\noriginal message: " << std::endl;
    std::cout << msg << std::endl << std::endl;
    std::cout << "encoded message: " << std::endl;
    std::cout << hc.encodeMsg(msg) << std::endl;
}