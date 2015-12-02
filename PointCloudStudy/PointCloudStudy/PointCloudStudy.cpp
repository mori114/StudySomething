// PointCloudStudy.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "FileConvert.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char key = 0;

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	FileConvert conv;
	std::string name = "table_scene_mug_stereo_textured";

	conv.convPCD2PLY(name, cloud);
	
	//pcl::io::loadPCDFile(name + ".pcd", *cloud);
	pcl::io::loadPLYFile(name + ".ply", *cloud);

	/*pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZRGB>);

	pcl::PointCloud<pcl::PointNormal> mls_points;

	pcl::MovingLeastSquares<pcl::PointXYZRGB, pcl::PointNormal> mls;

	mls.setComputeNormals(true);

	mls.setInputCloud(cloud);
	mls.setPolynomialFit(true);
	mls.setSearchMethod(tree);
	mls.setSearchRadius(0.03);

	mls.process(mls_points);

	pcl::io::savePLYFileBinary(name + ".ply", mls_points);*/

	pcl::visualization::CloudViewer viewer("Cloud Viewer");

	while (key != 'q'){
		viewer.showCloud(cloud); //�e���O�������̕\��
		key = cv::waitKey(1); //�E�B���h�E�̍X�V
	}

	return 0;
}

