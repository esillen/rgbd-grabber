/**
 * @file UEyeCapture.cpp
 * @author Yutaka Kondo <yutaka.kondo@youtalk.jp>
 * @date Apr 20, 2014
 */

#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <gflags/gflags.h>
#include "rgbd/camera/UEye.h"
#include "rgbd/camera/DistortionCalibrator.h"
#include "rgbd/camera/ColorCalibrator.h"
#include "rgbd/camera/ColorRotator.h"

using namespace rgbd;

//DEFINE_int32(id, 0, "camera id");
//DEFINE_string(conf, "data/ueye-conf.ini", "camera configuration");
//DEFINE_string(intrinsics, "data/ueye-calib.xml", "camera intrinsic data");

int main(int argc, char *argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);


    std::shared_ptr<UEye> original1;
    std::shared_ptr<UEye> original2;
    std::shared_ptr<UEye> original3;
    std::shared_ptr<UEye> original4;


    cv::Mat raw1;
    cv::Mat raw2;
    cv::Mat raw3;
    cv::Mat raw4;


    bool cam1 = true;
    bool cam2 = true;
    bool cam3 = true;
    bool cam4 = true;

  
    //std::shared_ptr<rgbd::DistortionCalibrator> undistorted(
      //      new rgbd::DistortionCalibrator(original, FLAGS_intrinsics));
    //std::shared_ptr<rgbd::ColorCalibrator> camera(
      //      new rgbd::ColorCalibrator(undistorted));
//    std::shared_ptr<rgbd::ColorRotator> camera(
//            new rgbd::ColorRotator(calibrated, 90));
    if(cam1){
        original1.reset(new UEye(1, "data/ueye-conf.ini"));
        original1->start();
        raw1 = cv::Mat::zeros(original1->colorSize(), CV_8UC1);
        cv::namedWindow("Raw1", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    }

    if(cam2){
        original2(new UEye(2, "data/ueye-conf.ini"));
        original2->start();
        raw2 = cv::Mat::zeros(original2->colorSize(), CV_8UC1);
        cv::namedWindow("Raw2", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    }

    if(cam3){
        original3(new UEye(3, "data/ueye-conf.ini"));
        original3->start();
        raw3 = cv::Mat::zeros(original3->colorSize(), CV_8UC1);
        cv::namedWindow("Raw3", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    }

    if(cam4){
        original4(new UEye(4, "data/ueye-conf.ini"));
        original4->start();
        raw4 = cv::Mat::zeros(original4->colorSize(), CV_8UC1);
        cv::namedWindow("Raw4", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    }
    


    int key = 0;

    while ((key = cv::waitKey(10)) != 0x1b) {
        
        if(cam1) original1->captureColor(raw1);
        if(cam2) original2->captureColor(raw2);
        if(cam3) original3->captureColor(raw3);
        if(cam4) original4->captureColor(raw4);

        
        if(cam1) cv::imshow("Raw1", raw1);
        if(cam2) cv::imshow("Raw2", raw2);
        if(cam3) cv::imshow("Raw3", raw3);
        if(cam4) cv::imshow("Raw4", raw4);
    }

    return 0;
}
