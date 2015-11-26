// PointCloudStudy.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char key = 0;

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	/*pcl::PCDReader reader;
	std::stringstream Filename;
	std::string name = "scene2";

	reader.read<pcl::PointXYZ>("scene2.pcd", *cloud);*/

	//// PCD�t�@�C���`������PLY�t�@�C���`���ɕϊ�
	/*Filename << name << ".ply";
	std::cout << Filename.str() << std::endl;
	pcl::io::savePLYFileBinary(Filename.str(), *cloud);*/

	// PCD�t�@�C���̓ǂݍ���
	//pcl::io::loadPCDFile("table_scene_mug_stereo_textured.pcd", *cloud);
	pcl::io::loadPLYFile("xyzrgb_dragon.ply", *cloud);

	pcl::visualization::CloudViewer viewer("Cloud Viewer");
	while (key != 'q'){
		viewer.showCloud(cloud); //�e���O�������̕\��
		key = cv::waitKey(1); //�E�B���h�E�̍X�V
	}

	return (0);
}

