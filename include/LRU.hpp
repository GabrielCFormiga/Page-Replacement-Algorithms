#ifndef LRU_HPP
#define LRU_HPP

#include <vector>
#include <unordered_map>
#include <list>
#include <iostream>
#include <iomanip>

class LRU {
private:
    size_t num_frames;
    
    std::vector<int> pages;
    
    size_t page_faults;

    // frames[i + 1] : the state of frames after processing the i-th page request
    // frames[0] : its a clear frame representing that no requests have been processed yet
    // if frames[i][j] = -1, then the j-th page in the i-th frame is empty
    std::vector<std::vector<int>> frames;
public:
    LRU(size_t num_frames, const std::vector<int> &pages);

    void simulate();
    void print_frames() const;
    
    int get_faults() const { return page_faults; }
};

#endif