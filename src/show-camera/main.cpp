#include <iostream>
#include <sstream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
     if (argc < 2) {
          cout << "Usage: " << argv[0] << " <input source>" << endl;
          return -1;
     }

     int cam_id;
     std::istringstream convert(argv[1]);
     if (!(convert >> cam_id)) {
          cam_id = 0;
     }
     
     cv::VideoCapture cap(cam_id);
     if (!cap.isOpened()) {
          return -1;
     }

     cv::Mat original;
     for (;;) {
          cap >> original;
          cv::imshow("Cam", original);
          if (cv::waitKey(1) == 'q') {
               break;
          }
     }

          return 0;
     }
