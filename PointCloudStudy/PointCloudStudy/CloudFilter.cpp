#include "CloudFilter.h"

void CloudFilter::Remove_outliers(pcl::PointCloud<pcl::PointXYZ>::Ptr in_cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr out_cloud)
{
	pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
	sor.setInputCloud(in_cloud);  // �O��l����������_�Q�����
	sor.setMeanK(25);  // MeanK��ݒ�
	sor.setStddevMulThresh(1.0);  // �ɗ̓m�C�Y�ȊO�̓_�͎c�������c
	sor.setNegative(false);  // �O��l���o�͂���ꍇ��true�ɂ���
	sor.filter(*out_cloud);  // �o��

	return ;
}