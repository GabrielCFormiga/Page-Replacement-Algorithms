#include "LRU.hpp"
#include <iomanip>
#include <iostream>

LRU::LRU(size_t num_frames, const std::vector<int> &pages) : num_frames(num_frames), pages(pages), page_faults(0) {
    frames.resize(pages.size() + 1, std::vector<int>(num_frames));
    std::fill(frames[0].begin(), frames[0].end(), -1);
    simulate(); 
}

void LRU::simulate() {
    // priority : keeps the index in the frame of the pages that must be replaced by priority
    // priority[0] : least recently used page
    // priority[num_frames - 1] : most recently used page
    std::vector<int> priority(num_frames); 

    for (size_t j = 0; j < num_frames; ++j) {
        priority[j] = j;
    }

    bool fault;
    
    for (size_t i = 0; i < pages.size(); ++i) {
        fault = true;
        
        for (size_t j = 0; j < num_frames; ++j) {
            frames[i + 1][j] = frames[i][j];
            if (frames[i][j] == pages[i]) {
                fault = false;
            }
        }

        if (fault) {
            size_t aux = priority[0];
            frames[i + 1][priority[0]] = pages[i];

            for (size_t j = 0; j + 1 < num_frames; ++j) {
                priority[j] = priority[j + 1];
            }
            priority[num_frames - 1] = aux;

            page_faults++;
        } else {
            size_t ind;
            size_t aux;
            size_t j = 0;

            for (size_t j = 0; j < num_frames; ++j) {
                if (frames[i + 1][priority[j]] == pages[i]) {
                    ind = j;
                    aux = priority[j];
                    break;
                }
            }

            for (size_t j = ind; j + 1 < num_frames; ++j) {
                priority[j] = priority[j + 1];
            }
            priority[num_frames - 1] = aux;
        }
    }
}

void LRU::print_frames() const {
    std::cout << std::left << std::setw(15) << "Pages Sequence:";

    for (size_t i = 0; i < pages.size(); ++i) {
        std::cout << std::right << std::setw(4) << pages[i];
    }

    std::cout << std::endl;

    for (size_t j = 0; j < num_frames; j++) {
        std::cout << std::left << std::setw(15) << (j == 0 ? "Frames State:" : " ");

        for (size_t i = 1; i < frames.size(); ++i) {
            std::cout << std::right << std::setw(4) << (frames[i][j] == -1 ? "x" : std::to_string(frames[i][j]));
        }
        std::cout << std::endl;
    }
}