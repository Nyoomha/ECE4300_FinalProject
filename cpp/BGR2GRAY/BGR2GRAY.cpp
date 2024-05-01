#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>

namespace fs = std::filesystem;
using namespace std::chrono;

int main() {
    std::string input_folder = "/home/saladbot/eceproject/ECE4300_FinalProject/Images/";
    std::string output_folder = "/home/saladbot/eceproject/ECE4300_FinalProject/Images/BGR2GrayDone"; 
    fs::create_directories(output_folder);

    auto start_time = high_resolution_clock::now();

    for (const auto& entry : fs::directory_iterator(input_folder)) {
        std::string filename = entry.path().filename();

        if (filename.size() >= 4 &&
            (filename.compare(filename.size() - 4, 4, ".jpg") == 0 || filename.compare(filename.size() - 5, 5, ".jpeg") == 0)) {

            std::string image_path = entry.path();
            cv::Mat image = cv::imread(image_path);

            if (!image.empty()) {
                cv::Mat converted_image;
                cv::cvtColor(image, converted_image, cv::COLOR_BGR2GRAY); 

                std::string output_path = output_folder + "/" + filename;
                cv::imwrite(output_path, converted_image);
                std::cout << "Image converted, new image saved: " << output_path << std::endl;
            }
        }
    }

    auto end_time = high_resolution_clock::now();
    duration<double> execution_time = duration_cast<duration<double>>(end_time - start_time);

    std::cout << "Execution Time: " << execution_time.count() << " seconds" << std::endl;

    return 0;
}
