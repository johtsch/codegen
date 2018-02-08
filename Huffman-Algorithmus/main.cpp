#include <iostream>
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

    /*
    hc.addElement('c', 0.1638);
    hc.addElement('v', 0.0454);
    hc.addElement('w', 0.0871);
    hc.addElement('u', 0.1957);
    hc.addElement('r', 0.4209);
    hc.addElement('z', 0.0871);

    hc.fireup();

    std::cout << "c: "<< hc.gcocStr('c') << std::endl;
    std::cout << "v: "<< hc.gcocStr('v') << std::endl;
    std::cout << "w: "<< hc.gcocStr('w') << std::endl;
    std::cout << "u: "<< hc.gcocStr('u') << std::endl;
    std::cout << "r: "<< hc.gcocStr('r') << std::endl;
    std::cout << "z: "<< hc.gcocStr('z') << std::endl;*/

    hc.showAll();
    std::cout << "average wordlength : \t\t\t" << hc.gawl() << std::endl;
    std::cout << "average (information) content : \t" << hc.gaic() << std::endl;
    std::cout << "redundance : \t\t\t\t" << hc.gred() << std::endl;
    
    
}