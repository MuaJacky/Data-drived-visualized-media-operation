#include <iostream>
#include <iomanip>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

//定义全局变量
// -- sp 均值迁移的物理空间半径
// -- sr 均值迁移的颜色空间半径
// -- numOp 记录当前的操作
int sp = 15, sr = 50, numOp = -1;

// 所有用到的图片Mat
Mat src, meanShiftDst, meanFilterDst, medianFilterDst;

// 图片的读取路径
String path = "/Users/bytedance/Downloads/ace.jpg";

// 是否已成功读取到图片
bool readImageResult = false;


// 定义main会用到的所有接口
bool printInfo();
void readImage();
void MeanShiftImage();
void MeanFilterImage();
void myMeanFilterImage();
void MedianFilterImage();

int main(int argc, char const *argv[])
{
    while(printInfo())
    {
        cin >> numOp;
        switch(numOp) {
            case 1: {
                readImage();
                break;
            }
            case 2: {
                MeanShiftImage();
                break;
            }
            case 3: {
                MeanFilterImage();
                break;
            }
            case 4: {
                myMeanFilterImage();
                break;
            }
            case 5: {
                MedianFilterImage();
                break;
            }
            case 6: {
                exit(0);
            }
            default: {
                printf("Cannot recognize the number, program exit.\n");
                exit(0);
            }
        }
    }

    return 0;
}

bool printInfo()
{
    // 根据不同的操作系统来保证操作目录的正确显示
    #if defined(__APPLE__) || defined(_linux) || defined(__linux__) || defined(linux)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
        system("cls");
    #elif defined(_WIN64) || defined(__WIN64__) || defined(WIN64)
        system("cls");
    #endif

    printf("*-----------------------------------------------------------------------*\n");
    printf("* Please Enter the operation's number to execute                        *\n");
    printf("*                                                                       *\n");
    printf("*    1.  readImage                                                      *\n");
    printf("*    2.  perform \e[1;31man mean shift\e[0m filter on this image                     *\n");
    printf("*    3.  perform \e[1;31man mean filter\e[0m on this image                           *\n");
    printf("*    4.  perform \e[1;32mmy mean filter\e[0m on this image                           *\n");
    printf("*    5.  perform \e[1;31man median filter\e[0m on this image                         *\n");
    printf("*    6.  exit this program                                              *\n");
    printf("*                                                                       *\n");
    printf("*-----------------------------------------------------------------------*\n");
    printf("*                                                                       *\n");
    printf("*    color \e[1;31mred\e[0m stands for using the standard API                        *\n");
    printf("*    color \e[1;32mgreen\e[0m stands for using the function designed by me           *\n");
    printf("*                                                                       *\n");
    printf("*-----------------------------------------------------------------------*\n");
    printf("*                                                                       *\n");
    if (readImageResult) {
        cout << "*    Current Image:  \e[1;32m"  << path << setw(22) << "\e[0m*" << endl;
    } else {
        printf("*    Current Image:   \e[1;31mYou haven't read image yet\e[0m                        *\n");
    }
    printf("*                                                                       *\n");
    printf("*-----------------------------------------------------------------------*\n");


    return true;
}


// 读取一个String作为图片的路径,读取并且提示用户结果
void readImage() 
{
    printf("Please Enter the path of the image:\n");
    cin >> path;
    src = imread(path);
    if (src.empty()) {
        readImageResult = false;
    }
    else {
        readImageResult = true;
    }

    String res = readImageResult ? " success!" : " failed.";
    cout << "read image " << path << res << endl;
}

// 使用前提：读取到正确的图片
// 进行均值迁移滤波后显示图像
void MeanShiftImage()
{
    if (readImageResult) {
        double time = (double)getTickCount();
        pyrMeanShiftFiltering(src, meanShiftDst, sp, sr);

        time = (double)getTickCount() - time;
        time = (time *1000.) / ((double)getTickFrequency());
 
        cout << "mean shift filter success" << endl;
        cout << "mean shift cost time " << time << " ms. " << endl << std::endl;

        namedWindow("origin image", WINDOW_AUTOSIZE);
        imshow("origin image", src);
        namedWindow("mean shift image", WINDOW_AUTOSIZE);
        imshow("mean shift image", meanShiftDst);

        cout << "select a window and press any button to close them all" << endl;
        waitKey(0);
        destroyAllWindows();

        // destroy之后要waitKey(1)才能正确关闭窗口：Mac系统独有
        waitKey(1);
    } else {
        cout << "you have not read image yet" << endl;
    }
}

// 使用前提：读取到正确的图片
// 进行均值滤波后显示图像
void MeanFilterImage() {
    if (readImageResult) {
        double time = (double)getTickCount();
        blur(src, meanFilterDst, Size(15, 15));

        time = (double)getTickCount() - time;
        time = (time *1000.) / ((double)getTickFrequency());
        cout << "mean filter success" << endl;
        cout << "mean filter cost time " << time << " ms. " << endl << std::endl;

        namedWindow("origin image", WINDOW_AUTOSIZE);
        imshow("origin image", src);
        namedWindow("mean filter image", WINDOW_AUTOSIZE);
        imshow("mean filter image", meanFilterDst);

        cout << "select a window and press any button to close them all" << endl;
        waitKey(0);
        destroyAllWindows();

        // destroy之后要waitKey(1)才能正确关闭窗口：Mac系统独有
        waitKey(1);

    } else {
        cout << "you have not read image yet" << endl;
    }
}


// 使用前提：读取到正确的图片
// 进行中值滤波后显示图像
void MedianFilterImage() {
    if (readImageResult) {
        double time = (double)getTickCount();
        medianBlur(src, medianFilterDst, 15);

        time = (double)getTickCount() - time;
        time = (time *1000.) / ((double)getTickFrequency());
        cout << "median filter success" << endl;
        cout << "median filter cost time " << time << " ms. " << endl << std::endl;

        namedWindow("origin image", WINDOW_AUTOSIZE);
        imshow("origin image", src);
        namedWindow("median filter image", WINDOW_AUTOSIZE);
        imshow("median filter image", medianFilterDst);

        cout << "select a window and press any button to close them all" << endl;
        waitKey(0);
        destroyAllWindows();

        // destroy之后要waitKey(1)才能正确关闭窗口：Mac系统独有
        waitKey(1);
    } else {
        cout << "you have not read image yet" << endl;
    }
}


// 优化前获取积分图的方法
//对于W*H图像：3*(W-1)*(H-1)次加减法
void Im_integral(Mat& src, Mat& dst){
    dst = cv::Mat::zeros(src.rows + 1, src.cols + 1, CV_64F);
    int rows = dst.rows, cols = dst.cols;
    for (int i = 1; i < rows; ++i){
        for (int j = 1; j < cols; ++j){
            double top_left = dst.at<double>(i - 1, j - 1);
            double top_right = dst.at<double>(i - 1, j);
            double buttom_left = dst.at<double>(i, j - 1);
            int buttom_right = src.at<uchar>(i-1, j-1);
            dst.at<double>(i, j) = top_right + buttom_right + buttom_left  - top_left;
        }
    }
}

// 优化后获取积分图方法
// 由普通积分图at(i, j)加上当前行的和即可
// 对于W*H图像：2*(W-1)*(H-1)次加减法
// 是比普通积分图更优的方法
void Integral(Mat& src, Mat& dst){
    int sum_r = 0;
    dst = Mat::zeros(src.rows + 1, src.cols + 1, CV_64F);
    int rows = dst.rows, cols = dst.cols;
    for (int i = 1; i < rows; ++i){  
        for (int j = 1, sum_r = 0; j < cols; ++j) {
            // 行累加，因为积分图相当于在原图上方加一行，左边加一列，所以积分图的(1,1)对应原图(0,0),(i,j)对应(i-1,j-1)
            sum_r = src.at<uchar>(i-1 , j-1) + sum_r; 
            dst.at<double>(i, j) = dst.at<double>(i-1, j) + sum_r;
        }
    }
}

// 利用积分图进行快速的均值滤波
void myMeanFilter(Mat& originSrc, Mat& dst, Size wsize){
    Mat src, newSrc, integralMat;
    int height = (wsize.height - 1) / 2, width = (wsize.width - 1) / 2;

    if (originSrc.channels() > 1)
        cvtColor(originSrc, src, COLOR_RGB2GRAY);
    else src = originSrc;

    //图像边界扩充
    if (wsize.height % 2 == 0 || wsize.width % 2 == 0){
        fprintf(stderr, "window size must be odd");
        exit(-1);
    }
    
    // 官方API，生成边界以防止获取积分图时越界
    copyMakeBorder(src, newSrc, height, height, width, width, BORDER_REFLECT_101);//以边缘为轴，对称
    dst = Mat::zeros(src.size(), src.type());
    
    // 计算积分图
    Integral(newSrc, integralMat);
 
    // 利用积分图计算均值滤波
    double mean = 0;
    for (int i = height+1; i < src.rows + height + 1;++i){  //积分图图像比原图（边界扩充后的）多一行和一列 
        for (int j = width+1; j < src.cols + width + 1; ++j){
            int top = i - height - 1, left = j - width -1,
                bottom = i + height, right = j + width;
            double top_left = integralMat.at<double>(top, left);
            double top_right = integralMat.at<double>(top, right);
            double buttom_left = integralMat.at<double>(bottom, left);
            double buttom_right = integralMat.at<double>(bottom, right);
            mean = (buttom_right - top_right - buttom_left + top_left) / wsize.area();
            
            mean = std::max(std::min(mean, 255.), 0.);
            dst.at<uchar>(top, left) = static_cast<uchar> (mean);
        }
    }
}

void myMeanFilterImage() {
    if (readImageResult) {
        double time = (double)getTickCount();
        myMeanFilter(src, meanFilterDst, Size(15, 15));

        time = (double)getTickCount() - time;
        time = (time *1000.) / ((double)getTickFrequency());
        cout << "my mean filter success" << endl;
        cout << "my mean filter cost time " << time << " ms. " << endl << std::endl;


        namedWindow("origin image", WINDOW_AUTOSIZE);
        imshow("origin image", src);
        namedWindow("mean filter image", WINDOW_AUTOSIZE);
        imshow("my mean filter image", meanFilterDst);

        cout << "select a window and press any button to close them all" << endl;
        waitKey(0);
        destroyAllWindows();

        // destroy之后要waitKey(1)才能正确关闭窗口：Mac系统独有
        waitKey(1);

    } else {
        cout << "you have not read image yet" << endl;
    }
}
