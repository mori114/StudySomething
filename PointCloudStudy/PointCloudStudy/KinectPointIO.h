/*
�_�Q�ۑ�������
�ۑ������_�Q�ǂݍ��񂾂�
PCL�Ƒ��ݕϊ������肵����
*/

#pragma once
#include "../../Kinect2Wrapper/Kinect2Wrapper/Kinect2.h"

#include <fstream>
#include <iostream>

#include <boost/date_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>

#include <pcl/io/pcd_io.h>

#include "KinectPointDef.h"


class KinectPointIO {
private:
	std::string computerName;

public:


private:
	cv::Point3i getPixel(cv::Mat &frame, ColorSpacePoint *colorCoordinates, int depthIndex);

public:

	KinectPointIO();

	//�o�C�i���ŏ�������
	template<typename T_n>
	void saveBinary(std::vector<T_n>& pointsList);
	template<typename T_n>
	void saveBinary(std::string filepath, std::vector<T_n>& pointsList);

	//�o�C�i���œǂݍ���
	void loadBinary(std::string filepath, std::vector<struct float_point>& pointsList);

	//�|�C���g���X�g�ɕϊ�����
	std::vector<struct float_point> convCamera2Points(Kinect2Sensor &kinect);

	//�|�C���g���X�g����PCL�ɕϊ�����
	void convPoints2PCL(std::vector<struct float_point> points, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pointcloud);

	//�_�Q��ۑ�����
	void savePoints(Kinect2Sensor &kinect);
	void savePoints(std::string filepath, Kinect2Sensor &kinect);

};