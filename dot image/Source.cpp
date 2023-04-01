#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <windows.h>
#include <thread>

using namespace cv;

std::string checker(int value)
{
    if (value <= 25) return " ";
    else if (value <= 50) return ".";
    else if (value <= 75) return ":";
    else if (value <= 100) return ";";
    else if (value <= 125) return "-";
    else if (value <= 150) return "+";
    else if (value <= 175) return "*";
    else if (value <= 200) return "@";
    else if (value <= 225) return "%";
    else return " ";
}

void processFrame(Mat frame, std::string &output)
{

    for (int x = 0; x < frame.size().height; x++)
    {
        for (int y = 0; y < frame.size().width; y++)
        {
            int value = static_cast<int>(frame.at<uchar>(x, y));
            output.append(checker(value));
        }
        output.append("\n");
    }
}

int main()
{
    system("MODE CON COLS=200 LINES=80");
    std::string image_path = samples::findFile("C:\\Users\\likim\\Downloads\\test4.mp4");
    VideoCapture cap(image_path);

    while (1) {

        Mat frame;
        cap >> frame;

        if (frame.empty())
            break;

        imshow("Frame", frame);

        cvtColor(frame, frame, COLOR_BGR2GRAY, 0);

        resize(frame, frame, Size(200, 80));

        std::string text = "";

        std::thread t(processFrame, std::cref(frame), std::ref(text));
        t.join();
        std::cout << text;

        std::chrono::milliseconds duration(1);
        std::this_thread::sleep_for(duration);

        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }

    cap.release();

    destroyAllWindows();
    return 0;
}