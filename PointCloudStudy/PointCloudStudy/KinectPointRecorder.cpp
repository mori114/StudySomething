#include "KinectPointRecorder.h"
#include "KinectPointDef.h"

void KinectPointRecorder::recordInitialize(std::string filename){
	this->filename = filename;

	ofs.open(filename, std::ios::out | std::ios::binary);
	if(ofs.fail()) {
		std::cout << "�t�@�C���I�[�v�����s" << std::endl;
		return;
	}

	//������
	nowBuffer = 0;
	lastUpdate = boost::posix_time::microsec_clock::local_time();
	targetFPS = 10;
	//�o�b�t�@�T�C�Y��64MB
	maxBufferSize = 1024 * 1024 * 128;

	//�w�b�_�����񂾂����炱����
}

void KinectPointRecorder::recordClose(){
	std::cout << "���܂�" << std::endl;
	flush();
	ofs.close();
}

void KinectPointRecorder::setData(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pointcloud){
	if(!ofs.is_open()) {
		std::cout << "�����������R��" << std::endl;
		return;
	}
	
	//���̎��Ԃ𓾂�
	boost::posix_time::ptime nowTime = boost::posix_time::microsec_clock::local_time();

	//�ۑ����ׂ��������ǂ����`�F�b�N
	double interval = 1000.0 / targetFPS;
	if((nowTime - lastUpdate).total_milliseconds() < interval) {
		return;
	}
	//�ŏI�X�V�������X�V����
	lastUpdate = nowTime;

	std::list<struct int_point> oneFrame;
	for(auto p : *pointcloud) {
		struct int_point data;
		//�X�P�[�������[�g��->�~�����[�g���ɂ���
		data.x = (int)(p.x * 1000);
		data.y = (int)(p.y * 1000);
		data.z = (int)(p.z * 1000);
		data.r = p.b;		//������������
		data.g = p.g;		//������������
		data.b = p.r;		//������������
		//���X�g�ɓ����
		oneFrame.push_back(data);
	}

	//���X�g�ɓ����
	pointList.push_back(oneFrame);
	timeList.push_back(nowTime);

	//���������ށH
	nowBuffer += oneFrame.size() * sizeof(struct int_point);
	if(nowBuffer >= maxBufferSize) {
		flush();
		nowBuffer = 0;
	}
}

void KinectPointRecorder::flush(){
	//std::cout << "��������m@s";

	std::list<boost::posix_time::ptime>::iterator itrTime = timeList.begin();
	std::list<std::list<struct int_point>>::iterator itrPoint = pointList.begin();

	while(itrPoint != pointList.end()) {
		//�����̏�������
		ofs.write((const char*)&(*itrTime), sizeof(boost::posix_time::ptime));
		//�f�[�^���̏�������
		size_t dataSize = itrPoint->size();
		ofs.write((const char*)&dataSize, sizeof(size_t));
		//�_�Q�̏�������
		for(auto p : (*itrPoint)) {
			ofs.write((const char*)&p, sizeof(struct int_point));
		}

		//���̃f�[�^��
		itrPoint++;
		itrTime++;
	}

	//�f�[�^������
	timeList.clear();
	pointList.clear();

	//std::cout << "�������݂܂���" << std::endl;
}