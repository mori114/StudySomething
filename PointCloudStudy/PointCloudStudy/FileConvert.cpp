#include "FileConvert.h"

void FileConvert::convPCD2PLY(std::string filename, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud){
	pcl::PCDReader reader;
	std::stringstream FileName;
	
	reader.read<pcl::PointXYZRGB>(filename + ".pcd", *cloud);

	//// PCD�t�@�C���`������PLY�t�@�C���`���ɕϊ�
	FileName << filename << ".ply";
	std::cout << FileName.str() << std::endl;
	pcl::io::savePLYFileBinary(FileName.str(), *cloud);

	return ;
}

void FileConvert::convPLY2PCD(std::string filename, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud){
	pcl::PLYReader reader;
	std::stringstream FileName;
	
	reader.read<pcl::PointXYZRGB>(filename + ".ply", *cloud);

	//// PLY�t�@�C���`������PCD�t�@�C���`���ɕϊ�
	FileName << filename << ".pcd";
	std::cout << FileName.str() << std::endl;
	pcl::io::savePCDFileBinary(FileName.str(), *cloud);

	return ;
}