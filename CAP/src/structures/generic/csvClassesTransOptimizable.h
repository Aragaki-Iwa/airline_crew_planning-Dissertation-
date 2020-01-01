/* transform input classes to the classes which used in the process of optimization
 * InputClasses corresponding to a optimizable classes named "Opt_InputClassName"
 * optimizable classes only include needed member of input classes
 */

#pragma once
#ifndef CSV_CLASSES_TRANS_OPTIMIZABLE
#define CSV_CLASSES_TRANS_OPTIMIZABLE
#include "../../pch.h"


class CREW;
class CREW_RANK;
class RANK;
class CREW_BASE;
class Segment;
class BASE;
struct csvActivityComposition;
struct csvComposition;

class CREW_RANK;
class CREW_BASE;
class CrewStatus;

typedef std::vector<CREW_RANK*> CrewRankAry;
typedef std::vector<CREW_BASE*> CrewBaseAry;


class Opt_CREW
{
public:
	Opt_CREW(CREW* crew);
	~Opt_CREW() {
		_crew = NULL;
		_rankAry = NULL;
		_baseAry = NULL;

		_skillMap.clear();
		_rankAry->clear();
		_baseAry->clear();

		delete workStatus;		
	}

	void setCrewRankAry(CrewRankAry* rankAry);
	void setCrewBaseAry(CrewBaseAry* baseAry);
	void setCurRank();
	void setCurPosition();	
	
	std::string& getIdCrew() { return _idCrew; }
	std::string& getDivision() { return _division; }
	std::string& getCurRank() { return _curRank; }
	std::string& getCurPosition() { return _curPosition; }
	std::map<std::string, int>& getSkillMap() { return _skillMap; }

	CrewRankAry& getRankAry() { return *_rankAry; }
	CrewBaseAry& getBaseAry() {return *_baseAry;	}

	void setDualPrice(double price) { _dual_price = price; }
	double getDualPrice() const { return _dual_price; }

	void setIndex(int index) { _index = index; }
	int getIndex() const { return _index; }

	CrewStatus* workStatus;

private:	
	CREW* _crew;
	CrewRankAry* _rankAry;
	CrewBaseAry* _baseAry;

	std::string _idCrew;
	std::string _division; //����:����Ա������Ա	
	std::string _curRank;
	std::string _curPosition;
	std::map<std::string, int> _skillMap;//�������ʣ��˴���Ϊ���Է��������
	std::string _gender;
	std::string _nationality;

	double _dual_price;

	int _index; //crew��OptCrewSet�е��±�

};

class Opt_Segment
{
public:
	Opt_Segment(Segment* seg);
	~Opt_Segment() {
		_seg = NULL;
		_fltCompo = NULL;
		_composition = NULL;
	}

	void setDualPrice(double price) { _dual_price = price; }
	double getDualPrice() const { return _dual_price; }

	void setIndex(int index) { _index = index; }
	int getIndex() const { return _index; }

	void setCompositions(csvActivityComposition* fltCompo, csvComposition* composition);
	csvActivityComposition* getFltComposition() const { return _fltCompo; }
	csvComposition* getCompositon()const { return _composition; }
	//! 
	void setRankToNumMap();
	std::map<std::string, int>& getRankToNumMap() { return _rank_to_num; };
	
	bool getAssigned();
	void setAssigned(bool flag);

	Segment& getSegment() const { return *_seg; }

	long long getDBId() const;
	std::string getDate() const;
	std::string getFlightNumber() const;
	std::string getDepStation() const;
	std::string getArrStation() const;
	int getBlkMinutes() const;
	time_t getStartTimeUtcSch() const;
	time_t getStartTimeLocSch() const;
	time_t getEndTimeUtcSch() const;
	time_t getEndTimeLocSch() const;
	std::string getDomIntType() const;
	std::string getFleet() const;
	std::string getTailNum() const;

private:
	Segment* _seg;

	long long _id;	
	std::string _fltDt;//��������date
	std::string	_fltNum;//����ţ�ʵ�ʻ�Ʊ�ϵĺ����
	std::string _depArp;
	std::string _arvArp;	
	int	_schBlkMin;//�ƻ�������У�block��ʱ�䣬��min��
	time_t _schDepDtUtc;
	time_t _schDepDtLoc;
	time_t _schArvDtUtc;
	time_t _schArvDtLoc;	
	std::string _segType;//segment�����ͣ�D-���ڣ�I-���ʣ�R-region�����򣬱���̨�壬��ۡ�������ΪD
	std::string _fleet;
	std::string _tailNumber;//��β��

	csvActivityComposition* _fltCompo;
	csvComposition* _composition;
	std::map<std::string, int> _rank_to_num; //��segment��Ӧrank��Ҫ������

	bool _assigned;

	double _dual_price;
	int _index; //��OptSegSet�е��±�
};


extern class Path;
class CrewStatus
{
public:
	CrewStatus() {};
	~CrewStatus() {
		_creditedDutySet.clear();
		_creditedDutySet.shrink_to_fit();
	}
	//
	void setInitStatus(const time_t initialTime, const std::string& initialStation);	

	bool getDayoff();
	//set _inDayoff to true
	void setDayoff(bool flag);	

	bool getAssigned();
	void setAssigned(bool flag);	
	//after assigned, _CreditedDutySet.push_back(param *duty)
	void addDuty(Path* duty);

	const std::vector<Path*>& getCreditDutySet() const;

	//reset every week
	int accumuFlyMin;
	//reset every day off
	//if it over 5 days, then must day off
	int accumuCreditMin;
	//����day off��ʱ��,[2 days, 3 days]
	int dayoffMin;
	//���һ��dutyִ�����ʱ��
	time_t endDtLoc;
	std::string restStation;

	//��¼7���ڵ��ۼ�flymin
	int sevenDayTotalFlyMint;
	//Ϊ�˼�¼7�����ܷ�ʱ��
	//ÿ7��ˢ��һ��
	time_t dateLocFlyBegining;
	
	//ͳ��ָ��

	//�������ڿ�ʼ����ǰ���ۼƷ���ʱ��
	int wholePlanTotalFlyMint;
	//�������ڿ�ʼִ�ڵ���ǰ���ۼ�ʱ��
	int wholePlanTotalCreditMint;	
	

private:

	bool _assigned;
	//��ǰ����day off״̬	
	bool _inDayoff;
	//���վ����ĵ�����duty����һֱ�ۼ�
	std::vector<Path*> _creditedDutySet;

};

#endif // !CSV_CLASSES_TRANS_OPTIMIZABLE