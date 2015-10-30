#include <fstream>
#include <boost/date_time.hpp>

#include <pcl/io/pcd_io.h>

#include <list>

#include "KinectPointDef.h"
class KinectPointRecorder {
private:

	std::string filename;				//�������ރt�@�C����
	std::ofstream ofs;

	std::list<boost::posix_time::ptime> timeList;		//�L�^��������
	std::list<std::list<struct int_point>> pointList;	//�L�^�����e���O��

	void flush();

	size_t maxBufferSize;	//�ő�o�b�t�@��
	size_t nowBuffer;		//���̃o�b�t�@

	boost::posix_time::ptime lastUpdate;	//�ŏI�X�V����
	double targetFPS;						//fps
public:

	void recordInitialize(std::string filename);

	void setData(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pointcloud);

	void recordClose();

};