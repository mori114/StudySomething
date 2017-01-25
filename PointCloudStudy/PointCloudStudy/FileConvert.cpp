#include "FileConvert.h"

void FileConvert::convPCD2PLY(std::string filename, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud){
	pcl::PCDReader reader;
	pcl::PLYWriter writer;
	std::stringstream FileName;
	
	reader.read<pcl::PointXYZ>(filename + ".pcd", *cloud);

	// PCD�t�@�C���`������PLY�t�@�C���`���ɕϊ�
	FileName << filename << ".ply";
	std::cout << FileName.str() << std::endl;
	writer.write<pcl::PointXYZ>(FileName.str(), *cloud, false, false);

	return ;
}

void FileConvert::convPLY2PCD(std::string filename, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud){
	pcl::PLYReader reader;
	pcl::PCDWriter writer;
	std::stringstream FileName;
	
	reader.read<pcl::PointXYZ>(filename + ".ply", *cloud);

	// PLY�t�@�C���`������PCD�t�@�C���`���ɕϊ�
	FileName << filename << ".pcd";
	std::cout << FileName.str() << std::endl;
	writer.write<pcl::PointXYZ>(FileName.str(), *cloud, false);

	return ;
}

// DIND�Ŏ擾����Depth Image��Point CloudXYZ�ɕϊ�����
void FileConvert::convPNG2PointCloud(std::string file_path, cv::Point2d param_fl, cv::Point2d param_pp){
	cv::Mat depthmap = cv::imread(file_path + "depth.png", -1);
	pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointXYZ point;
	pcl::PLYWriter ply_writer;

	auto starttime = boost::posix_time::microsec_clock::local_time();

	// Depth Image����_�Q�𐶐�
	for (int v = 0; v < depthmap.rows; ++v){
		for (int u = 0; u < depthmap.cols; ++u){
			// �~�����[�g�������[�g���ɕϊ�
			point.z = depthmap.at<UINT16>(v, u) / 1000.0;
			point.x = ((double)u - param_pp.x) * point.z / param_fl.x;
			point.y = ((double)v - param_pp.y) * point.z / param_fl.y;

			if (point.z != 0.00) {
				pointcloud->push_back(point);
			}
		}
	}

	filter.Remove_outliers(pointcloud, pointcloud);

	// �J�����̌��_��ǉ�
	point.x = 0.00;
	point.y = 0.00;
	point.z = 0.00;
	pointcloud->push_back(point);

	ply_writer.write<pcl::PointXYZ>(file_path + "pointcloud.ply", *pointcloud, false, false);

	auto endtime = boost::posix_time::microsec_clock::local_time();

	std::cout << "�_�Q��������: " << (endtime - starttime).hours() << "[h] "
		<< (endtime - starttime).minutes() << "[m] "
		<< (endtime - starttime).seconds() << "[s] "
		<< (endtime - starttime).total_milliseconds() << std::endl;

	pointcloud->clear();
	depthmap.release();

	return;
}

// DIND�Ŏ擾����Depth Image��Point CloudRGB�ɕϊ�����
void FileConvert::convPNG2PointCloudColor(std::string file_path, cv::Point2d param_fl, cv::Point2d param_pp){
	cv::Mat colormap = cv::imread(file_path + "_raw_trunc_color.png", -1);
	cv::Mat depthmap = cv::imread(file_path + "_out_depth.png", -1);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointcloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointXYZRGB point;
	pcl::PLYWriter ply_writer;

	auto startTime = boost::posix_time::microsec_clock::local_time();

	// Depth Image����_�Q�𐶐�
	for (int v = 0; v < depthmap.rows; ++v){
		for (int u = 0; u < depthmap.cols; ++u){
			// �~�����[�g�������[�g���ɕϊ�
			point.z = depthmap.at<UINT16>(v, u) / 1000.0;
			point.x = ((double)u - param_pp.x) * point.z / param_fl.x;
			point.y = ((double)v - param_pp.y) * point.z / param_fl.y;

			if (point.z != 0.00) {
				point.r = colormap.at<cv::Vec3b>(v, u)[2];
				point.g = colormap.at<cv::Vec3b>(v, u)[1];
				point.b = colormap.at<cv::Vec3b>(v, u)[0];
				pointcloud->push_back(point);
			}
		}
	}

	// �J�����̌��_��ǉ�
	point.x = 0.00;
	point.y = 0.00;
	point.z = 0.00;
	point.r = 255;
	point.g = 0;
	point.b = 0;
	pointcloud->push_back(point);

	ply_writer.write<pcl::PointXYZRGB>(file_path + "pointcloudrgb.ply", *pointcloud, false, false);

	auto endTime = boost::posix_time::microsec_clock::local_time();

	std::cout << "DepthMap�����ߎ���: " << (endTime - startTime).hours() << "[h] "
		<< (endTime - startTime).minutes() << "[m] "
		<< (endTime - startTime).seconds() << "[s] "
		<< (endTime - startTime).total_milliseconds() << std::endl;

	pointcloud->clear();
	depthmap.release();

	return;
}