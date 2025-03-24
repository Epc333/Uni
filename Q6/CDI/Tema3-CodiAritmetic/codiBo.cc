#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <numeric>
using namespace std;

/**
 * Funció que llegeix un nombre binari i el converteix a decimal    
 * Rep un string amb el nombre binari
 * Retorna el nombre en decimal
 */
int BinToInt(const string& binary) {
    return stoi(binary, nullptr, 2);
}

/**
 * Funció que transforma un numero enter a número binari
 * Rep un enter i en quants bits el vols representar
 * Retorna un string amb el enter codificat en binari utilitzant tants bits com pasats com a parametre
 */
string IntToBin(int num, int totalBitToRead){
    string binary = "";
    for (int i = totalBitToRead - 1; i >= 0; i--){
        if (num & (1 << i)){
            binary.push_back('1');
        }
        else {
            binary.push_back('0');
        }
    }
    return binary;
}

vector<int> inicialitzar_intervals (vector<int>& freq, int totalFreq, int maxNum){
    vector<int> initialIntervals (freq.size() + 1);
    double aux = 0;


    for (int i = 0; i < freq.size(); i++){
        double aux2 = double(freq[i]) / totalFreq * maxNum;
        double valor= aux + 0.000000001;  //Per evitar errors d'arrodoniment
        initialIntervals[i] = valor;
        aux += aux2;
    }
    initialIntervals[freq.size()] = maxNum;
    return initialIntervals;
}

vector<int> actualitzar_intervals (int& num, pair<int, int>& interval, int& totalFreq, vector<int>& freq, int& maxNum, string& codi){
    while (((interval.second <= maxNum/2 or interval.first >= maxNum/2 or (interval.first >= maxNum/4 and interval.second <= 3*maxNum/4))) and not codi.empty()){
        if ( interval.second <= maxNum/2){
            /*
            cout << "Reescalat E_1: " << interval.first << " <= " << num << " < " << interval.second << endl;
            cout << codi << endl;
            cout << interval.first << " <= " << num << " < " << interval.second << "------>";
            */
            interval.first *= 2;
            interval.second *= 2;
            num *= 2;
            if (codi.front() == '1'){
                num += 1;
            }
            codi.erase(0, 1);
            //cout << interval.first << " <= " << num << " < " << interval.second << endl << endl;
        }
        else if (interval.first >= maxNum/2){
            /*
            cout << "Reescalat E_2: " << interval.first << " <= " << num << " < " << interval.second << endl;
            cout << codi << endl;
            cout << interval.first << " <= " << num << " < " << interval.second << "------>";
            */
            interval.first = 2 * interval.first - maxNum;
            interval.second = 2 * interval.second - maxNum;
            num = 2 * num - maxNum;
            if (codi.front() == '1'){
                num += 1;
            }
            codi.erase(0, 1);
            //cout << interval.first << " <= " << num << " < " << interval.second << endl << endl;
        }
        else {
            /*
            cout << "Reescalat E_3: " << interval.first << " <= " << num << " < " << interval.second << endl;
            cout << codi << endl;
            cout << interval.first << " <= " << num << " < " << interval.second << "------>";
            */
            interval.first = 2 * interval.first - maxNum/2;
            interval.second = 2 * interval.second - maxNum/2;
            num = 2 * num - maxNum/2;
            if (codi.front() == '1'){
                num += 1;
            }
            codi.erase(0, 1);
            //cout << interval.first << " <= " << num << " < " << interval.second << endl << endl;
        }
    }
    vector<int> newIntervals (freq.size() + 1);
    double aux = 0;
    for (int i = 0; i < freq.size(); i++){
        double aux2 = double(freq[i]) / totalFreq * (interval.second-interval.first);
        double valor = interval.first + aux + 0.000000001;
        newIntervals[i] = valor;
        aux += aux2;
    }
    newIntervals[freq.size()] = interval.second;
    /*
    cout << "Intervals: [";
    for (int i = 0; i < newIntervals.size(); i++){
        cout << newIntervals[i] << ", ";
    }
    cout << "]" << endl;
    cout << "Num: " << num << endl;
    */

    return newIntervals;

}

string decode (vector<int>& intervals, int& num, vector<char>& symbols, int& totalFreq, int& maxNum, vector<int>& freq, int longitudMissatge, string& codi){
    string missatge = "";
    while (codi.size() > 0 and missatge.size() < longitudMissatge){
        pair<int, int> interval;
        int idx = -1;
        for (int i = 1; i < intervals.size(); i++){
            if (num < intervals[i]){
                interval = {intervals[i - 1], intervals[i]};
                idx = i - 1;
                /*
                cout << "Simbol: " << symbols[idx] << endl;
                cout << "Interval: " << interval.first << " " << interval.second << endl;
                cout << "Missatge: " << missatge << endl;
                cout << endl;
                */
                missatge.push_back(symbols[idx]);
                intervals = actualitzar_intervals(num, interval, totalFreq, freq, maxNum, codi);
                break;
            }

        }
    }
    
    return missatge;
}

int bits_acul = 0;

vector<int> actualitzar_intervals_encode(pair<int, int> interval, int totalFreq, vector<int>& freq, int maxNum, string& codi){
    
    while((interval.second <= maxNum/2 or interval.first >= maxNum/2 or (interval.first >= maxNum/4 and interval.second <= 3*maxNum/4))){
        if (interval.second <= maxNum/2){
            //cout << "Reescalat E_1: ";// << interval.first << " <= " << interval.second << endl;
            //cout << codi << endl;
            //cout << interval.first << " <= " << interval.second << "------>";
            codi.push_back('0');
            if (bits_acul > 0){
                for (int i = 0; i < bits_acul; i++){
                    codi.push_back('1');
                }
                bits_acul = 0;
            }
            interval.first *= 2;
            interval.second *= 2;
            //cout << interval.first << " <= " << interval.second << endl << endl;
        }
        else if (interval.first >= maxNum/2){
            //cout << "Reescalat E_2: ";// << interval.first << " <= " << interval.second << endl;
            //cout << codi << endl;
            //cout << interval.first << " <= " << interval.second << "------>";
            codi.push_back('1');
            if (bits_acul > 0){
                for (int i = 0; i < bits_acul; i++){
                    codi.push_back('0');
                }
                bits_acul = 0;
            }
            interval.first = 2 * interval.first - maxNum;
            interval.second = 2 * interval.second - maxNum;
            //cout << interval.first << " <= " << interval.second << endl << endl;
        }
        else {
            //cout << "Reescalat E_3: "; //<< interval.first << " <= " << interval.second << endl;
            //cout << codi << endl;
            //cout << interval.first << " <= " << interval.second << "------>";
            bits_acul++;
            interval.first = 2 * interval.first - maxNum/2;
            interval.second = 2 * interval.second - maxNum/2;
            //cout << interval.first << " <= " << interval.second << endl << endl;
        }
    }
    
    
    vector<int> newIntervals (freq.size() + 1);
    double aux = 0;
    for (int i = 0; i < freq.size(); i++){
        double aux2 = double(freq[i]) / totalFreq * (interval.second-interval.first);
        double valor = double(interval.first) + aux + 0.000000001;  //Per evitar errors d'arrodoniment
        newIntervals[i] = valor;
        aux += aux2;
    }
    newIntervals[freq.size()] = interval.second;

    /*cout << "Intervals: [";
    for (int i = 0; i < newIntervals.size(); i++){
        cout << newIntervals[i] << ", ";
    }
    cout << "]" << endl;
    */
    return newIntervals;

}

string encode(vector<int>& intervals, vector<char>& symbols, int& totalFreq, int& maxNum, vector<int>& freq, string& codi){
    string missatge = ""; 
    while (not codi.empty()){
        char simbol = codi.front();
        codi.erase(0, 1);
        int idx = -1;
        for (int i = 0; i < symbols.size(); i++){
            if (symbols[i] == simbol){
                idx = i;
                break;
            }
        }
        pair<int, int> interval = {intervals[idx], intervals[idx + 1]};

        //cout << "Simbol: " << simbol << endl;
        //cout << "Interval: " << interval.first << " " << interval.second << endl;

        string codificacio = "";
        intervals = actualitzar_intervals_encode(interval, totalFreq, freq, maxNum, codificacio);
        missatge += codificacio;
        //cout << missatge << endl;
    }

    pair<int, int> interval = make_pair(intervals[0], intervals[freq.size()]);
    if (interval.first <= maxNum / 4) {
        missatge.push_back('0');
        for (int i = 0; i < bits_acul + 1; ++i) {
            missatge.push_back('1');
        }
    } else {
        missatge.push_back('1');
        for (int i = 0; i < bits_acul + 1; ++i) {
            missatge.push_back('0');
        }
    }

    missatge += IntToBin(interval.first, ceil(log2(maxNum)));
    cout << "Missatge final " << missatge << endl;
    return missatge;
}

int main(){
    string codi = "The Island of Doctor Moreau, by H. G. Wells. [...] But the laws we feel our way towards--Why, even on this earth, even among living things, what pain is there? As he spoke he drew a little penknife from his pocket, opened the smaller blade, and moved his chair so that I could see his thigh. Then, choosing the place deliberately, he drove the blade into his leg and withdrew it.";
    vector<char> symbols =  {' ', ',', '-', '.', '?', 'A', 'B', 'D', 'G', 'H', 'I', 'M', 'T', 'W', '[', ']', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'v', 'w', 'y'};
    vector<int> freq =  {70, 8, 2, 8, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 19, 4, 6, 13, 42, 4, 6, 25, 19, 3, 17, 4, 16, 19, 6, 13, 17, 22, 4, 5, 8, 4};
    int longitudMissatge = 379;


    int totalFreq = accumulate(freq.begin(), freq.end(), 0);


    int totalBitToRead = ceil(log2(4 * totalFreq));


    int maxNum = pow(2, totalBitToRead);

    /*
    //To decode
    int initialNum = BinToInt(codi.substr(0, totalBitToRead));
    codi.erase(0, totalBitToRead);
    */

    vector<int> initialIntervals = inicialitzar_intervals(freq, totalFreq, maxNum);
   
    /*cout << "Intervals: [";
    for (int i = 0; i < initialIntervals.size(); i++){
        cout << initialIntervals[i] << ", ";
    }
    cout << "]" << endl;*/

    //string decoded = decode(initialIntervals, initialNum, symbols, totalFreq, maxNum, freq, longitudMissatge, codi);
    //cout << decoded << endl;

    string encoded = encode(initialIntervals, symbols, totalFreq, maxNum, freq, codi);
    cout << endl << "Missatge retallat a 1000 bits: " << endl << encoded.substr(0, 1000) << endl << endl;
    //cout << endl << encoded << endl;

    int initialNum = BinToInt(encoded.substr(0, totalBitToRead));
    encoded.erase (0, totalBitToRead);
    initialIntervals = inicialitzar_intervals(freq, totalFreq, maxNum);
    string decoded = decode(initialIntervals, initialNum, symbols, totalFreq, maxNum, freq, longitudMissatge, encoded);
    cout << decoded << endl;

}   
