#include <vector>
#include <string>
#include <time.h>
#include "csv_impl.h"
//"..\csvReader\csv\csv_impl.h"
#ifndef SEGMENT_MINE_H
#define SEGMENT_MINE_H

class Segment
{
public:
	void setDBId(long long id);
	void setDate(std::string fltDt);
	void setFlightNumber(std::string fltNum);
	void setDepStation(std::string depArp);
	void setArrStation(std::string arvArp);
	void setBlkMinute(int schBlkMin);
	void setStartTimeUtcSch(time_t schDepDtUtc);
	void setStartTimeLocSch(time_t schDepDtLoc);
	void setEndTimeUtcSch(time_t schArvDtUtc);
	void setEndTimeLocSch(time_t schArvDtLoc);
	void setDomIntType(std::string segType);
	void setFleetCD(std::string fleetCD);
	void setTailNum(std::string tailNumber);

	long long getDBId();
	std::string getDate();
	std::string getFlightNumber();
	std::string getDepStation();
	std::string getArrStation();
	int getBlkMinutes();
	time_t getStartTimeUtcSch();
	time_t getStartTimeLocSch();
	time_t getEndTimeUtcSch();
	time_t getEndTimeLocSch();
	std::string getDomIntType();
	std::string getFleetCD();
	std::string getTailNum();
	

	/*csvActivityComposition* fltCompo;
	csvComposition* composition;
	bool assigned = false;*/

private:
	/*ֻ�����Ż��ƻ���ص�����*/	
	long long _id;
	//int schId;//�����о���ͬ	
	std::string _fltDt;//��������date
	std::string	_fltNum;//����ţ�ʵ�ʻ�Ʊ�ϵĺ����
	std::string _depArp;
	std::string _arvArp;
	//int	airline;//��˾//�����о���ͬ	
	int	_schBlkMin;//�ƻ�������У�block��ʱ�䣬��min��
	time_t _schDepDtUtc;
	time_t _schDepDtLoc;
	time_t _schArvDtUtc;
	time_t _schArvDtLoc;

	//int	actBlkMin;//ʵ�ʺ�����У�block��ʱ�䣬��min��
	//string segSeq;//һ�˺����segment�����У���Ϊ������ܾ�ͣ��������Ϊ1
	std::string _segType;//segment�����ͣ�D-���ڣ�I-���ʣ�R-region�����򣬱���̨�壬��ۡ�������ΪD

	string _fleetCD;
	//string _aircraft;//��fleet������Ч��һ����fleetΪ׼������עtailNumer����
	std::string _tailNumber;//��β��
	
	//string setFltType;//�ͻ�����������PO���ù�ע
	//string actAln;//ʵ�ʵ�airline�����ù�ע
	//string actDepDtUtc;
	//string actDepDtLoc;
	//string actArvDtUtc;
	//string actArvDtLoc;
	//string actFltNum;//ʵ�ʺ���ţ����ù�ע
	//string actDepArp;
	//string actArvArp;
	//string flightStatus;
	//string onwardFlt;
	//string acConfig;
	//string actTakeOffLoc;
	//string actTouchDownUtc;
	//string actTouchDownLoc;
	//string actTakeOffUtc;
	//int ver;//�仯���������ù�ע
	//string serviceType;
	//string interfaceFltId;	
};

class Duty
{
public:	
	void setDutyId(long long id);
	void setPairingId(long long pairingId);
	void setDutySeq(int seq);
	void setTypeByStr(std::string type);
	void setDepStation(std::string startAirport);
	void setArrStation(std::string endAirport);
	void setRegion(std::string region);
	void setMinRest(int minRestMinutes);
	void setFlyMin(int fltMinutes);
	void setDutyMin(int dutyMinutes);
	void setStartTimeUtcSch(time_t schStartDtUtc);
	void setStartTimeLocSch(time_t schStartDtLoc);
	void setEndTimeUtcSch(time_t schEndDtUtc);
	void setEndTimeLocSch(time_t schEndDtLoc);

	long long getDutyId();
	long long getPairingId();
	int getDutySeq();
	std::string getTypeStr();
	std::string getDepStation();
	std::string getArrStation();
	std::string getRegion();
	int getMinRest();
	int getFlyMin();
	int getDutyMin();
	time_t getStartTimeUtcSch();
	time_t getStartTimeLocSch();
	time_t getEndTimeUtcSch();
	time_t getEndTimeLocSch();
private:
	long long _id;
	long long _pairingId;
	int _dutySeq;
	std::string _dutyType;
	/*int pickupMin;
	int dropoffMin;*/
	std::string _startArp;
	std::string _endArp;
	std::string _region;
	int _minRestMin;
	int _fltMin;
	int _dutyMin;
	//int creditedMin;

	time_t _schStartDtUtc;
	time_t _schStartDtLoc;
	time_t _schEndDtUtc;
	time_t _schEndDtLoc;

};
class DBAirport
{
public:
	int id;
	std::string airport;
	std::string airportName;
	std::string airportNativeName;
	std::string airportICAO;
	std::string airportABBR;
	std::string city;
	std::string cityName;
	std::string cityNativeName;
	std::string category;
	std::string dir;
	std::string zoneId;
	int utcOffset;
	std::string dstGrp;
	std::string country;
	std::string plateauType;
	std::string rnp;
	std::string cats;
};

class BASE
{
public:
	BASE() {};
	BASE(int id, std::string base, std::string name) :baseId(id), base(base), name(name) {};
	int baseId;
	std::string airline;
	std::string base;
	std::string name;
	int displayOrder;
	std::string isPrimeDisplayBase;
};

//class Pairing 
//{
//public:
//	Pairing()
//	{
//		fltVec_ptr = new std::vector<Segment*>();
//	}
//	~Pairing()
//	{
//		delete fltVec_ptr;
//		delete coverArrayFlts;
//	}
//
//	string toCsv();
//	void setValues();//TODO������pairing��duty��������������
//	string outFlts();
//	string id;
//	string base;
//	string endArp;
//	std::vector<Segment*>* fltVec_ptr;
//	/*props*/
//	int durationInDays = -1;//���ڼ��
//	int durationInHours;
//	int blockMint;
//	int flyMint;
//	//int duty
//	string schStartDtUtc;
//	string schEndDtUtc;
//	string schStartDtLoc;		
//	string schEndDtLoc;
//	/*for model*/
//	int* coverArrayFlts;	
//	//int fixedCost;//��ʱ��durationInDays��ʾ
//private:
//	int _calDurationInDays();
//
//};

#endif // !SEGMENT_MINE_H
