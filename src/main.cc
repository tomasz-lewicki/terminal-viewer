#include <cstdio>
#include <unistd.h> // STDOUT_FILENO, TIOCGWINSZ
#include <sys/ioctl.h>
#include <opencv2/opencv.hpp>

std::string rgb_to_ascii(cv::Vec3b pixel)
{
  // set color using ANSI escape sequences
  // Excelent explanation here:
  // https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences

  cv::Vec3b p = pixel;
  std::string b = std::to_string(p[0]);
  std::string g = std::to_string(p[1]);
  std::string r = std::to_string(p[2]);
  return "\033[38;2;" + r + ";" + g + ";" + b + "m" + "█" + "\033[0m";
}

void display_image(cv::Mat im)
{
  for(int r = 0; r < im.rows; r++)
  {
    for(int c = 0; c < im.cols; c++)
    {
        cv::Vec3b pixel = im.at<cv::Vec3b>(r, c);
        std::string t;
        std::cout <<  rgb_to_ascii(pixel);
    }
    std::cout << std::endl;
  }
}

int main(int argc, char* argv[])
{
  struct winsize ws;
  ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);

  if(argc == 1) return -1; //no image specified

  cv::Mat image; //stack-allocated matrix
  
  cv::String fname(argv[1]);
  image = cv::imread(fname);

  cv::Mat image_small(ws.ws_row, ws.ws_col, CV_8UC3, cv::Scalar(0, 0, 0));
  
  cv::resize(image, image_small, cv::Size(ws.ws_col, ws.ws_row));
  display_image(image_small);

  return 0;
}