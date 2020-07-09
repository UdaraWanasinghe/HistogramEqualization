#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

struct Histogram {
    int columns[256] = {0};
    int width = 512;
    int height = 256;
};

void get_histogram(Mat image, Histogram *histogram);

void show_histogram(string window, Histogram *histogram);

void get_equalize_arr(Histogram *inputHistogram, int total, int *arr);

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Image path is required" << endl;
        return 128;
    }
    string path = argv[1];
    Mat image = imread(path, IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Invalid image: " << argv[1] << endl;
        return 128;
    }
    imshow("Input_Image", image);

    struct Histogram histogram1;
    get_histogram(image, &histogram1);
    show_histogram("Input_Histogram", &histogram1);
    int arr[256];
    int total = image.cols * image.rows;
    get_equalize_arr(&histogram1, total, arr);
    Mat outputImage = image.clone();
    for (int i = 0; i < outputImage.rows; i++) {
        for (int j = 0; j < outputImage.cols; ++j) {
            int v = (int) outputImage.at<uchar>(i, j);
            outputImage.at<uchar>(i, j) = arr[v];
        }
    }
    imshow("Output_Image", outputImage);
    Histogram outputHistogram;
    get_histogram(outputImage, &outputHistogram);
    show_histogram("Output_Histogram", &outputHistogram);
    waitKey(0);
    image.release();
    outputImage.release();
    return 0;
}

void get_histogram(Mat image, Histogram *histogram) {
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.rows; j++) {
            int v = (int) image.at<uchar>(i, j);
            histogram->columns[v]++;
        }
    }
}

void show_histogram(string window, Histogram *histogram) {
    Mat image(histogram->height, histogram->width, CV_8UC1, Scalar(255));
    int thickness = histogram->width / 256;
    int max = 0;
    for (int i = 0; i < 256; i++) {
        if (max < histogram->columns[i]) {
            max = histogram->columns[i];
        }
    }
    for (int i = 0; i < 256; i++) {
        int colH = histogram->columns[i] * histogram->height / max;
        Point start = Point(i * thickness, histogram->height);
        Point end = Point(i * thickness, histogram->height - colH);
        line(image,
             start,
             end,
             Scalar(0),
             1);
    }
    imshow(window, image);
}

void get_equalize_arr(Histogram *inputHistogram, int total, int *arr) {
    int sum = 0;
    for (int i = 0; i < 256; i++) {
        sum += inputHistogram->columns[i];
        arr[i] = sum * 256 / total;
    }
}