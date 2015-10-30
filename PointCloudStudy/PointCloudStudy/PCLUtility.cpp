#include "PCLUtility.h"

pcl::PointCloud<pcl::PointXYZRGB>::Ptr PCLUtility::createKinectPointCloud(cv::Size depthSize){
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointcloud(new pcl::PointCloud<pcl::PointXYZRGB>());
	pointcloud->width = static_cast<uint32_t>(depthSize.width);
	pointcloud->height = static_cast<uint32_t>(depthSize.height);
	pointcloud->is_dense = false;

	return pointcloud;
}

void PCLUtility::convKinectDataToPointCloudXYZRGB(Kinect2Sensor &kinect, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pointcloud){
	pointcloud->clear();

	//pointcloud->width = 640;
	//pointcloud->height = 480;

	//�J���[�摜�̎擾(�|�C���^)
	cv::Mat test = kinect.getFrame();
	unsigned char *colorImagePointer = test.data;

	//�[�x�摜�S�s�N�Z�����̃��[�v
	for(int y = 0; y < kinect.getDepthSize().height; y++) {
		for(int x = 0; x < kinect.getDepthSize().width; x++) {
			//�_�Q�̒���1�̓_
			pcl::PointXYZRGB point;

			int depth_target = y * kinect.getDepthSize().width + x; //depth�̒��ډ�f
			//**************************************************************************
			//1. �[�x�摜��1�_�̐[�x�l�𓾂�
			//�[�x�l�̎擾
			//**************************************************************************
			unsigned int depth = kinect.getDepthBuffer()[depth_target];

			//**************************************************************************
			//2. �[�x�摜��1�_��3�������W�ł͂ǂ����𓾂�
			//�_��3�����ʒu�𓾂�
			//**************************************************************************
			CameraSpacePoint skeletonPoint = kinect.getCameraBuffer()[depth_target];
			//�[�x�l�̃Z�b�g
			point.x = skeletonPoint.X;
			point.y = skeletonPoint.Y;
			point.z = skeletonPoint.Z;

			//**************************************************************************
			//3. �[�x�摜��1�_���J���[�摜�ł͂ǂ����𓾂�
			//�_�̃J���[���𓾂�
			//**************************************************************************
			cv::Point colorPoint = kinect.getMapper()->getColorUVFromDepthUV(x, y);

			//�[�x�J�����̃s�N�Z�����J���[�摜�͈̔͊O�ɂ��邩������Ȃ�
			if(0 <= colorPoint.x && colorPoint.x < kinect.getColorSize().width && 0 <= colorPoint.y && colorPoint.y < kinect.getColorSize().height) {
				unsigned int index = (colorPoint.y * kinect.getColorSize().width + colorPoint.x) * 3; //ARGB
				//�J���[�l�̃Z�b�g
				point.r = colorImagePointer[index + 2];
				point.g = colorImagePointer[index + 1];
				point.b = colorImagePointer[index + 0];

				//���X�g�Ƀv�b�V�����Ă���
				pointcloud->push_back(point);
			}
		}
	}
}