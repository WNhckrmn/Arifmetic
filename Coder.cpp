#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;
class segment {
public:
    double left;
    double right;
    double freq;
    segment() {
        left = 0;
        right = 0;
        freq = 0;
    }
    segment(double l, double r, double f) {
        left = l;
        right = r;
        freq = f;
    }
};

double min_mantis(double l, double r) {
    double count = 0;
    int a = floor(l * 10 * count);
    int b = floor(r * 10 * count);
    while (b == a) {
        a = floor(l * 10 * count);
        b = floor(r * 10 * count);
        count++;
    }
    return count;
}
int main() {
    unsigned short M = 8;
    map <unsigned char, double > v;
    unsigned char cc;
    unsigned long long words = 0;
    ifstream fail;
    fail.open("text.txt");
    if (!(fail.is_open())) // если файл не открыт
        cout << "file can't open\n"; // сообщить об этом
    else {
        while ((cc = fail.get()) && !(fail.eof())) {
            v[cc]++;
            words++;
        }
    }
    fail.close();

    map < unsigned char, double> ::iterator ii;
    map <unsigned char, segment > table;
    double st = 0;
    unsigned int countt = 0;
    for (ii = v.begin(); ii != v.end(); ++ii) {
        countt++;
        table[ii->first].freq = (ii->second) / words;
        table[ii->first].left = st;
        table[ii->first].right = st + table[ii->first].freq;
        st = table[ii->first].right;
    }
    map <unsigned char, segment > ::iterator iip;
    for (iip = table.begin(); iip != table.end(); ++iip) {
        cout << iip->first << "--" << table[iip->first].left << "--" << table[iip->first].right << "::" << table[iip->first].freq << endl;
    }

    double l = 0;
    double r = 1;

    ifstream file;
    char c;
    int x = 0;
    int count = 0;
    file.open("text.txt");
    ofstream res("result.txt", ios::binary);
    if (!(file.is_open())) // если файл не открыт
        cout << "file can't open\n"; // сообщить об этом
    else if (!(res.is_open()))
        cout << "file can't open\n";
    else {
        res.write((char*)&M, sizeof(M));
        //int M_last = words % 15;
//        res<<" ";
        res.write((char*)&words, sizeof(words));//<<words;
//        res<<" ";
        res.write((char*)&countt, sizeof(countt));//<<countt;
        map<unsigned char, double> ::iterator iii;

        for (iii = v.begin(); iii != v.end(); ++iii) {
            unsigned char a = iii->first;
            double numer = iii->second;
            res.write((char*)&(a), sizeof(a));//<<iii->first;
            res.write(reinterpret_cast<char*>(&numer),sizeof(numer));//<<iii->second;
            //res<<" ";
        }
        while (file.peek()!=EOF) {

            unsigned char c = file.get();
            double l1 = l + table[c].left * (r - l);
            double r1 = l + table[c].right * (r - l);
            l = l1;
            r = r1;
            count++;
            if (count % M == 0) {
                double element = 0;
                uint64_t result = 0;
                int i = 0;
                while (!((l <= element ) && (element < r))) {
                    i++;
                    if ((1 / pow(2, i) + element) < r) {
                        element += 1 / pow(2, i);
                        result |= (uint64_t(1) << (i-1));
                    }
                  
                }                
                
                for (int i = 0; i < 7; ++i) {
                    unsigned char per = 255 & (result >> (i * 8));
                    res.write((char*)&per, sizeof(per));
                    //cout << per;
                }
                l = 0;
                r = 1;
                i = 0;
            }
            //            if (count == M) {
            //                stringstream str1,str2;
            //                str1<<setprecision(100)<<l;
            //                str2<<setprecision(100)<<r;
            //                count = 0;
            //                if(str1.str()!=str2.str()){
            //                    for (int i = 0; i < 100; ++i) {
            //                       if(str1.str()[i]!=str2.str()[i]){
            //                           char ress[100];
            //                           int len = str1.str().copy(ress,i+1,0);
            //                           ress[len - 1]++;
            //                           ress[len]='\0';
            //                           res<<ress;
            //                           break;
            //                       }
            //                    }
            //                }
            //                else{
            //                    res <<setprecision(100)<< l;
            //                }
            //                cout<<l<<endl;
            //                cout<<r<<endl;
            //                int el = min_mantis(l,r);
            //                double plus = 1 / pow(10,el) ;
                            //l+=plus;
        }
        //        if (count!=0){
        //            res<<l;
        //        }
    }
    if (count % M) {
        double element = 0;
        uint64_t result = 0;
        int i = 0;
        while (!((l <= element) && (element < r))) {
            i++;
            if ((1 / pow(2, i) + element) < r) {
                element += 1 / pow(2, i);
                result |= (uint64_t(1) << (i - 1));
            }

        }

        for (int i = 0; i < 7; ++i) {
            unsigned char per = 0 | (result >> (i * 8));
            res.write((char*)&per, sizeof(per));
            //cout << per;
        }
        l = 0;
        r = 1;
        i = 0;
    }
    file.close();
    res.close();
}

