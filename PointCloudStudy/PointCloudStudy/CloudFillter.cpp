#include "CloudFillter.h"

pcl::PointCloud<pcl::PointXYZRGB> Remove_outliers(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud)
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> sor;
	sor.setInputCloud(cloud);//�O��l����������_�Q�����
	sor.setMeanK(50);//MeanK��ݒ�
	sor.setStddevMulThresh(0.1);
	sor.setNegative(false);//�O��l���o�͂���ꍇ��true�ɂ���
	sor.filter(*cloud_filtered);//�o��

	return *cloud_filtered;
}