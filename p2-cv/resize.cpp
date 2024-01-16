// Project UID af1f95f547e44c8ea88730dfb185559d
#include <iostream>
#include "processing.h"
#include <fstream>
using namespace std;

int main(int argc, char **argv){

    // Error Checking: Arguments
    if (argc < 4 || argc > 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n";
        exit(1);
    }

    ifstream fin;
    fin.open(argv[1]);

    if(!fin.is_open()) {
        cout << "Error opening file: " << argv[1] << endl;
        exit(1);
    }

    Image *img = new Image;
    Image_init(img, fin);

    ofstream fout;
    fout.open(argv[2]);
    if(!fout.is_open()) {
        cout << "Error opening file: " << argv[2] << endl;
        exit(1);
    }

    int expected_w = atoi(argv[3]);
    int expected_h = 0;
    // For optional argument:  desired height
    if (argc == 5) {
        expected_h = atoi(argv[4]);
    } else if (argc == 4) {
        expected_h = Image_height(img);
    }
    
    // Error Checking: Width & Height
    if (0 >= expected_w || expected_w > Image_width(img)) {
        cout << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        exit(1);
    }
    if (0 >= expected_h || expected_h > Image_height(img)) {
        cout << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        exit(1);
    }

    seam_carve(img, expected_w, expected_h);

    Image_print(img, fout);

    fin.close();
    fout.close();
    delete img;
}