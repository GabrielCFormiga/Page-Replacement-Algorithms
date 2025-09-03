#include <iostream>
#include <vector>
#include <fstream>
#include <cstddef>
#include "FIFO.hpp"
#include "LRU.hpp"
#include "OPT.hpp"

using namespace std;

vector<int> input(const string &path, size_t &num_frames) {
    vector<int> pages;
    int page;

    ifstream file(path);
    if (!file) {
        cerr << "Error opening file: " << path << endl;
        exit(1);
    }

    file >> num_frames;
    while (file >> page) {
        pages.push_back(page);
    }

    file.close();
    return pages;
}


int main(int argc, char* argv[]) {
    // num_frames : number of page frames
    size_t num_frames = 0;

    // pages : represents the sequence of arrival of pages
    vector<int> pages = input(argv[1], num_frames); 

    FIFO fifo(num_frames, pages);
    cout << "FIFO " << fifo.get_faults() << endl;

    OPT opt(num_frames, pages);
    cout << "OTM " << opt.get_faults() << endl;

    LRU lru(num_frames, pages);
    cout << "LRU " << lru.get_faults() << endl;

    return 0;
}