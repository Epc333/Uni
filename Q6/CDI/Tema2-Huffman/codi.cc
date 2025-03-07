#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
using namespace std;

/**
 * Funció per calcular la freqüencia dels símbols.
 * Rep per paràmetre el missatge i el diccionari
 * Al acabar l'execució el diccionari pren per valor els caracters que hi ha, i la seva freqüencia
 */
void calcSymbolsFreq(string &message, map<char, float> &mapFreq){
    multiset<char> total; // Serveix per separar el text en simbols
    total.insert(message.begin(), message.end());
    float lengthText = message.length();

    for (char i : total){
        mapFreq[i] = total.count(i) / lengthText;
    }
}

/**
 * Funció per calcular la longitud de cada símbol
 * Rep per paràmetre el diccionari dels simbols i la seva freqüencia
 * Retorna un diccionari amb els simbols i la seva longitud
 */
map<char, int> calcLength(map<char, float> &mapFreq){
    map<char, int> simbolLength;
    priority_queue<pair<float, string>, vector<pair<float, string>>, greater<pair<float, string>>> Q;
    for (auto [c, f] : mapFreq){
        string s = "";
        s += c;
        Q.push({f, s});
    };

    while (Q.size() > 1){
        pair<float, string> a = Q.top();
        Q.pop();
        pair<float, string> b = Q.top();
        Q.pop();
        string s = a.second + b.second;
        Q.push({a.first + b.first, s});
        for (char i : s){
            ++simbolLength[i];
        }
    }

    return simbolLength;
}

int main(){
    string message = "The Invisible Man, by H. G. Wells. [...] At that he returned to his bedroom, armed himself with the most obvious weapon, the poker, and descended the staircase as noiselessly as possible. Mrs. Bunting came out on the landing. The hour was about four, and the ultimate darkness of the night was past. There was a faint shimmer of light in the hall, but the study doorway yawned impenetrably black. Everything was still except the faint creaking of the stairs under Mr. Bunting's tread, and the slight movements in the study. Then something snapped, the drawer was opened, and there was a rustle of papers. Then came an imprecation, and a match was struck and the study was flooded with yellow light. Mr. Bunting was now in the hall, and through the crack of the door he could see the desk and the open drawer and a candle burning on the desk. But the robber he could not see. He stood there in the hall undecided what to do, and Mrs. Bunting, her face white and intent, crept slowly downstairs after him. One thing kept Mr. Bunting's courage; the persuasion that this burglar was a resident in the village.";

    map<char, float> mapFreq; // Char = symbol int = freq;

    calcSymbolsFreq(message, mapFreq);

    //map<char, float> mapFreqEx2 = {{'a',5./38}, {'b', 7./38}, {'c', 1./19}, {'d', 13./38}, {'e',11./38}};

    map<char, int> freq = calcLength(mapFreq);

    float longitutMitjana = 0;
    for (auto [c, f] : mapFreq){
        longitutMitjana += float(f) * float(freq[c]);
    }
    cout << "Longitud Mitjana del codi de Huffman: " << longitutMitjana << endl;

    cout << "Caracter Freqüencia Longitud" << endl;
    for (auto [c, f] : mapFreq){
        cout << " '" << c << "'\t\t" << f << "\t\t" << freq[c] << endl;
    }
}

/**
 * Per fer l'exercici 1 i 5, només fa falta canviar el missatge i mirar l'output de la longitud mitjana
 * Per l'exercici 2, nomes cal descomentar linia 64, i canviar mapFreq per mapFreqEx2 (liniea 66, 69, 75)
 * Per l'exercici 3, s'ha de mirar la taula del output i mirar si la mida de bits es la mateixa que la longitud
 * Per l'exercici 4, l'he fet a ull, basicament les codificacions amb més freqüencia tenen menys bits
 */