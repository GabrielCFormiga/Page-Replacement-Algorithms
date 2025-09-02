#include "FIFO.hpp"
#include <iostream>
#include <iomanip>

FIFO::FIFO(size_t num_frames, const std::vector<int> &pages) : num_frames(num_frames), pages(pages), page_faults(0) {
    frames.resize(pages.size() + 1, std::vector<int>(num_frames));
    std::fill(frames[0].begin(), frames[0].end(), -1);
    simulate(); 
}

void FIFO::simulate() {
    bool fault;
    size_t replace = 0; // index of the frame that will be replaced
    
    for (size_t i = 0; i < pages.size(); ++i) {
        fault = true;

        for (size_t j = 0; j < num_frames; ++j) {
            frames[i + 1][j] = frames[i][j];
            if (frames[i][j] == pages[i]) {
                fault = false;
            }
        }

        if (fault) {
            frames[i + 1][replace] = pages[i];
            replace = (replace + 1) % num_frames;
            page_faults++;
        }
    }
}

void FIFO::print_frames() const {
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