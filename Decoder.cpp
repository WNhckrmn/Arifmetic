#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
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

int main() {
    ifstream read("result.txt", ios::binary);
    unsigned short M;
    read.read((char*)&M, sizeof(M));//>>M;
    //cout<<M<<"M"<<endl;
    unsigned long long words;
    read.read((char*)&words, sizeof(words));//>>words;
    //cout<<words<<"words"<<endl;
    //int M_last = words % M;
    //cout<<M_last<<"M_last"<<endl;
    //words -=M_last;
    //cout<<words<<"words"<<endl;
    unsigned int countt;
    read.read((char*)&countt, sizeof(countt));//>>countt;
    //cout<<countt<<"count"<<endl;
    unsigned char w;
    double nym;
    double st = 0;
    map <unsigned char, segment > table;
    int a = 0;
    while (countt > 0) {
        a++;
        read.read((char*)&(w), sizeof(w));
        read.read((char*)&(nym), sizeof(nym));//>>nym;
        table[w].freq = nym / words;
        table[w].left = st;
        table[w].right = st + table[w].freq;
        st = table[w].right;
        cout << a << ": sym - " << w << ", left - " << table[w].left << ", right - " << table[w].right << endl;
        countt--;
    }
    map< unsigned char, segment>::iterator ii;
    for (ii = table.begin(); ii != table.end(); ++ii) {
        cout << ii->first << endl << "::" << ii->second.freq << "--" << ii->second.left << "--" << ii->second.right << endl;
    }



    ofstream res("decod.txt");

    double num = 0;
    //    while(words > 0){
    //        int count = M;
    //        read>>num;
    //        cout<<num<<endl;
    //        double l = 0;
    //        double h = 1;
    //        while (count > 0) {
    //            for (ii = table.begin(); ii != table.end(); ++ii) {
    //                if (((ii->second.left) <= num) && ((ii->second.right) >= num)){
    //                    res << ii->first;
    //                    count--;
    //                    num = (num - (ii->second.left))/((ii->second.right) - (ii->second.left));
    //                    words--;
    //                }
    ////                double l1 = l + ii->second.left * (h - l);
    ////                double h1 = l + ii->second.right * (h - l);
    ////                l = l1;
    ////                h = h1;
    ////                if((l <= num)&&(h>=num)){
    ////                    char a = ii->first;
    ////                    break;
    ////                }
    //            }
    ////            res<< a;
    ////            count--;
    //        }
    while (words > 0) {
        for (int i = 0; i < 7; ++i) {
            unsigned char buf;
            read.read((char*)&buf, sizeof(buf));
            for (int j = 0; j < 8; ++j) {
                if ((1 << j) & buf) {
                    num += 1 / pow(2, j + (i * 8)+1);
                }
            }
        }
        double l = 0;
        double h = 1;

        for (int i = M; i > 0; --i) {

            for (auto s : table) {
                double l1 = l + s.second.left * (h - l);
                double h1 = l + s.second.right * (h - l);
                if (l1 <= num && num < h1) {
                    words--;
                    
                    l = l1;
                    h = h1;
                    res << s.first;
                    break;
                }
            }
            if (!words) {
                break;
            }

        }
        num = 0;
    }


    //    read>>num;
    //    cout<<num<<endl;
    //    while(M_last > 0){
    //        for (ii = table.begin(); ii != table.end(); ++ii) {
    //            if (((ii->second.left) <= num) && ((ii->second.right) > num)){
    //                res << ii->first;
    //                M_last--;
    //                break;
    //            }
    //        }
    //        num = (num - (ii->second.left))/((ii->second.right) - (ii->second.left));
    //    }

}
