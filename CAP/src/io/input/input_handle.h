#pragma once
#ifndef INPUT_HANDLE_H
#define INPUT_HANDLE_H
#include "../../pch.h"

class CREW;
class CREW_RANK;
class CREW_BASE;
class Segment;
class BASE;
struct csvActivityComposition;
struct csvComposition;
class CrewRules;

class Opt_CREW;
class Opt_Segment;


class InputHandler
{
public:	
	InputHandler() {}
	~InputHandler() {
		_segSet.clear();
		_baseSet.clear();
		_crewSet.clear();
		_crew_rankSet.clear();
		_crew_baseSet.clear();
		_fltCompositionSet.clear();
		_compositionSet.clear();
		_airportSet.clear();
	}

	/*
	 * @brief ת�����弯��
	 * @detail ���弯��ʵ��Ϊvector<vector<void*>>����Ҫ������ÿ��Ԫ��vector<void*>�е�Ԫ��void*ת��Ϊ��Ӧ����
	 * ת����Ķ��󼯺Ϸֱ�������ĳ�Ա������ʵ����ͬһ���������������������棬һ��Ϊvoid*���ͣ�һ��Ϊʵ�ʾ�������
	 *
	 * @param std::map<std::string, std::vector<void*>>& dataSet keyΪ�������ƣ�valueΪ��Ӧ���͵Ķ��󼯺�
	 * @param const std::vector<std::string>& objNameSet Ŀ��ת�����͵����Ƽ���	 
	 * @attention
	 * @warning
	 * @exception
	 *
	 **/
	void transformInputObjSet(std::map<std::string, std::vector<void*>>& dataSet, 
		const std::vector<std::string>& objNameSet);

	void loadCrewRules(const std::string& rulesFile);
	void loadPenalties(const std::string& penaltiesFile);

	/*
	 * @brief ����ԭʼ���ͣ�Segment�����󴴽������������ͣ�Opt_Segment������
	 * @detail ���ı�ԭʼ���Ͷ��󣬲�����ϵķ�ʽ����ԭʼ���Ͷ�����Ϊ��Ӧ�����Ͷ���ĳ�Ա
	 *
	 * @param std::vector<Opt_Segment*>* optSegSet ԭʼ���Ͷ��󼯺�
	 *
	 * @attention �ж�̬�ڴ����(new Opt_Segment)����
	 * @warning
	 * @exception
	 *
	 **/
	void createOptSegments(/*std::vector<Segment*>& segSet, */std::vector<Opt_Segment*>* optSegSet);
	/*
	 * @brief ����ԭʼ���ͣ�CREW�����󴴽������������ͣ�Opt_CREW������
	 * @detail ���ı�ԭʼ���Ͷ��󣬲�����ϵķ�ʽ����ԭʼ���Ͷ�����Ϊ��Ӧ�����Ͷ���ĳ�Ա
	 *
	 * @param std::vector<Opt_CREW*>* optCrewSet ԭʼ���Ͷ��󼯺�
	 *
	 * @attention �ж�̬�ڴ����(new Opt_CREW)����
	 * @warning
	 * @exception
	 *
	 **/
	void createOptCrews(/*std::vector<CREW*>& crewSet, */std::vector<Opt_CREW*>* optCrewSet);

	/*
	 * @brief ��ֵ��Opt_Segment�����Ҫ��
	 * @detail
	 *
	 * @param std::vector<Opt_Segment*>* optSegSet
	 *
	 * @attention
	 * @warning
	 * @exception
	 *
	 **/
	void matchOptSegmentAndComposition(std::vector<Opt_Segment*>* optSegSet
		/*std::vector<csvActivityComposition*>* fltCompoSet,
		std::vector<csvComposition*>* compoSet*/);
	
	/*
	 * @brief ��ֵ��ÿ��Opt_Segment����Ҫ�ĸ���rank������
	 * @detail
	 *
	 * @param std::vector<Opt_Segment*>* optSegSet
	 *
	 * @attention
	 * @warning
	 * @exception
	 *
	 **/
	void setRankToNumMapOfOptSegment(std::vector<Opt_Segment*>* optSegSet);

	/*
	 * @brief ����Opt_Crew��rankAry
	 * @detail
	 *
	 * @param std::vector<Opt_CREW*>* optCrewSet
	 *	 
	 * @attention
	 * @warning
	 * @exception
	 *
	 **/
	void matchOptCrewAndRank(std::vector<Opt_CREW*>* optCrewSet/*, std::vector<CREW_RANK*>* crewrankSet*/);
	/*
	 * @brief ����Opt_Crew��baseAry
	 * @detail
	 *
	 * @param std::vector<Opt_CREW*>* optCrewSet
	 *
	 * @attention
	 * @warning
	 * @exception
	 *
	 **/
	void matchOptCrewAndBase(std::vector<Opt_CREW*>* optCrewSet/*, std::vector<CREW_BASE*>* crewbaseSet*/);

	/*
	 * @brief ��ֵ��Opt_Crew�ڼ���optCrewSet�е��±�
	 * @detail ȫ�ֵ�optCrewSet������ı䣬�������Opt_Crew��indexҲ����ı䣬���ڲ���
	 *
	 * @param
	 *
	 * @return
	 *     @retval ����ֵ˵��
	 * @attention
	 * @warning
	 * @exception
	 *
	 **/
	void setIndexOfCrew(std::vector<Opt_CREW*>* optCrewSet);

	/*
	 * @brief ��ÿ��crew��rank�����µ�ʱ������
	 * @detail
	 *
	 * @param
	 *
	 * @return
	 *     @retval ����ֵ˵��
	 * @attention
	 * @warning
	 * @exception
	 *
	 **/
	void sortCrewRank(/*std::vector<CREW_RANK*>* crewrankAry*/);

	/*
	 * @brief ��ֵ������airport�ļ���
	 * @detail
	 *
	 * @param
	 *
	 * @attention
	 * @warning
	 * @exception
	 *
	 **/
	void setAirportSet(/*const std::vector<Segment*>& fltSet*/);
	
	std::vector<BASE*>& getBaseSet() { return _baseSet; }
	
	/***TODO �ⲿ��Ӧ���Ƴ���������InputHandler�Ĺ���*******************/
	//�ȿ��Ƿ���Ա
	std::vector<Opt_CREW*>* getPilotSet(const std::vector<Opt_CREW*>& optCrewSet);
	std::vector<std::string>& createSpecialArpSet();
	void randomSetCrewSkills(std::vector<Opt_CREW*>* optCrewSet, double percent = 0.3);
	void setRankCombination(CrewRules* rules);
	//! ����ȼ�¼��Ӧ�ĺ�λ���䣬����ϵ�һ������������������
	void setRankCombination_OnePermutation(CrewRules* rules);
	
private:

	/*
	 * @brief ��void*ת��Ϊ��������
	 * @detail
	 *
	 * @param std::vector<void*>& objSet void*���󼯺�
	 * @param const std::string& objName Ŀ��ת������
	 * @param void* outObjSet ���������ת�����Ŀ�����Ͷ��󼯺�
	 *	 	 
	 * @attention
	 * @warning
	 * @exception
	 *
	 **/
	void typeTrans(std::vector<void*>& objSet, const std::string& objName, void* outObjSet);

	std::vector<Segment*> _segSet;
	std::vector<BASE*> _baseSet;
	std::vector<CREW*> _crewSet;
	std::vector<CREW_RANK*> _crew_rankSet;
	std::vector<CREW_BASE*> _crew_baseSet;
	std::vector<csvActivityComposition*> _fltCompositionSet;
	std::vector<csvComposition*> _compositionSet;

	//CrewRules* _rules;

	std::vector<std::string> _airportSet;
	std::vector<std::string> _special_airportSet;
};

#endif // !INPUT_HANDLE_H
