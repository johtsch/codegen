#include "huffman.hpp"

HuffmanCoder::HuffmanCoder(){
    reset();
}

HuffmanCoder::~HuffmanCoder(){
    reset();
}

void HuffmanCoder::reset(){
    _probmap.clear();
    _codemap.clear();
    _probsum = 0.0;
}

bool HuffmanCoder::addElement(char z, prob p){
    /* the sum of all probabilities can't be bigger 1 */
    if (_probsum + p > 1.0)
        return false;

    if(p < 0)
        return false;

    /* the element already exists */
    if(_probmap.find(z) != _probmap.end())
        return false;

    _probmap.insert(std::pair<char, prob>(z, p));
    _probsum+=p;
    _codemap.insert(std::pair<char, std::string>(z, ""));

    return true;
}

void HuffmanCoder::calcProbs(){
    fireup();
}

void HuffmanCoder::fireup(){
    if(_probsum < 1.0)
        alterProbs();

    /* groups the chars, at the beginning each char has its own node */
    std::map<char, int> nodes;

    std::map<char, prob>::iterator it = _probmap.begin();
    int count = 0;
    for(it = _probmap.begin(); it != _probmap.end(); ++it){
        nodes.insert(std::pair<char, int>(it->first, count));
        ++count;
    }

    genCode(nodes);
}

std::string HuffmanCoder::encodeMsg(std::string msg){
    std::string cmsg;   
    for(int i = 0; i < msg.length(); ++i){
        if(gcocStr(msg[i]) != "")
            cmsg+=gcocStr(msg[i]);
        else    
            cmsg+=msg[i];
    }

    return cmsg;
}

void HuffmanCoder::alterProbs(){
    std::map<char, prob>::iterator it;

    for(it = _probmap.begin(); it != _probmap.end(); ++it){
        it->second /= _probsum;
    }
}


void HuffmanCoder::genCode(std::map<char, int> nodes){
    std::map<char, int>::iterator it = nodes.begin();
    int largest = 0;
    /* find the largest nodeidentifier */
    for(it = nodes.begin(); it != nodes.end(); ++it){
        if(it->second > largest)    
            largest = it->second;
    }

    /* escape */
    if(largest == 0)
        return;

    std::vector<double> probs;
    for(int i = 0; i < largest+1; ++i){              /* + 1 because nodeidentifiers start with 0*/
        double nodeprob = 0.0;

        for(it = nodes.begin(); it != nodes.end(); ++it){
            if(it->second == i){
                nodeprob+=_probmap[it->first];
            }
        }

        probs.push_back(nodeprob);
    }

    int sma1 = 0, sma2 = 1;

    /* p(sma1) has to be smaller than p(sma2). if not change the values */
    if(probs[sma1] > probs[sma2]){
        sma1 += sma2;
        sma2 = sma1 - sma2;
        sma1 = sma1 - sma2;
    }

    for(int i = 0; i < probs.size(); ++i){
        if(i != sma1 && probs[i] <= probs[sma1]){
            sma2 = sma1;
            sma1 = i;
        }
        if(i != sma2 && probs[i] <= probs[sma2] && i != sma1)
            sma2 = i;
    }

    /* sma1 has to be smaller than sma2. if not change the values 
        the smaller nodeidentifier should stay */
    if(sma1 > sma2){
        sma1 += sma2;
        sma2 = sma1 - sma2;
        sma1 = sma1 - sma2;
    }

    /* now adapt code and change nodeidentifiers */
    for(it = nodes.begin(); it != nodes.end(); ++it){
        if(it->second == sma1)
            _codemap[it->first] = "1" + _codemap[it->first];
        else if(it->second == sma2){
            _codemap[it->first] = "0" + _codemap[it->first];
            it->second = sma1;              /* entries with the larger nodeidentifier get the smaller of the two node identifiers*/
        }
        else if(it->second > sma2)    
            it->second -= 1;                /* - 1 since there is now exactly 1 node missing */

        //std::cout << "\t[D] nodeid = " << it->second << std::endl;
    }

    //std::cout << "\t[D] next call" << std::endl;

    /* recursion */
    genCode(nodes);
}

std::string HuffmanCoder::gcocStr(char c){
    if(_codemap.find(c) == _codemap.end())
        return "";
    return _codemap[c];
}

/* GETTER */

double HuffmanCoder::gred(){
    return gawl() - gaic();
}


double HuffmanCoder::gawl(){
    std::map<char, std::string>::iterator it;
    double avwl = 0.0;
    for(it = _codemap.begin(); it != _codemap.end(); ++it){
        avwl+=it->second.size() * _probmap[it->first];
    }

    return avwl;
}

double HuffmanCoder::gaic(){
    std::map<char, double>::iterator it;
    double aic = 0.0;
    for(it = _probmap.begin(); it != _probmap.end(); ++it){
        aic += it->second * log(1/it->second)/log(2.0);
    }

    return aic;
}

void HuffmanCoder::showAll(){
    std::map<char, std::string>::iterator it;
    
    for(it = _codemap.begin(); it != _codemap.end(); ++it){
        std::cout << "'" << it->first << "'  ->  '" << it->second << "'  ->  " << _probmap[it->first] << std::endl; 
    }
}

void HuffmanCoder::showAllSorted(){
    double lsp = 0.0;
    char lchr = '\0';
    double csp = 12;           /* current smallest probability */
    char csc = '\0';
    bool found = false;
    std::map<char, double>::iterator it;
    std::string used = "";

    while(true){
        found = false;
        csp=10.0;
        for(it = _probmap.begin(); it != _probmap.end(); ++it){
            if(it->second < csp && it->second >= lsp && used.find(it->first) == std::string::npos){
                csp = it->second;
                found = true;
                csc = it->first;
            }
        }   
        // if no new smaller value has been found break loop
        if(!found)
            break;
        lsp = csp;
        used+=csc;
        std::cout << "'" << csc << "'  ->  '" << _codemap[csc] << "'  ->  " << _probmap[csc] << std::endl; 
    }
}