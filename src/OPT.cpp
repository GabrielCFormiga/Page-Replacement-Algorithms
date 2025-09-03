#include "OPT.hpp"  
#include <iomanip>
#include <iostream>

OPT::OPT(size_t num_frames, const std::vector<int> &pages) : num_frames(num_frames), pages(pages), page_faults(0) {
    frames.resize(pages.size() + 1, std::vector<int>(num_frames));
    std::fill(frames[0].begin(), frames[0].end(), -1);
    simulate(); 
}

void OPT::simulate() {
    bool fault;
    size_t replace; // index of the frame that will be replaced
    size_t mx_future; // maximum future use

    for (size_t i = 0; i < pages.size(); ++i) {
        fault = true;

        for (size_t j = 0; j < num_frames; ++j) {
            frames[i + 1][j] = frames[i][j];
            if (frames[i][j] == pages[i]) {
                fault = false;
            }
        }

        if (fault) {
            replace = 0;
            mx_future = i;

            for (size_t j = 0; j < num_frames; ++j) {
                int page = frames[i + 1][j];
                
                if (page == -1) {
                    // there is an empty frame
                    replace = j;
                    break;    
                }

                for (size_t k = i + 1; k < pages.size() + 1; ++k) {
                    if (k == pages.size()) {
                        // the page wont be used again
                        replace = j;
                        mx_future = pages.size();
                        break;
                    }

                    if (pages[k] == page) {
                        if (k > mx_future) {
                            mx_future = k;
                            replace = j;
                        }
                        break;
                    }
                }
            }

            frames[i + 1][replace] = pages[i];
            page_faults++;
        }
    }
}

void OPT::print_frames() const {
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