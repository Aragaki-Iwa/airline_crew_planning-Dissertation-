#pragma once
#ifndef PROBLEM_H
#define PROBLEM_H
#include "../pch.h"
#include "../easylogging/easylogging++.h"


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
/**
 * @brief ��void*ת��Ϊ���������
 **/
class Concretizer {
	friend class ProblemBuilder;
	friend class Problem;
public:
	/*
	 * @brief ת�����弯��
	 * @detail ���弯��ʵ��Ϊvector<vector<void*>>����Ҫ������ÿ��Ԫ��vector<void*>�е�Ԫ��void*ת��Ϊ��Ӧ����
	 * ת����Ķ��󼯺Ϸֱ�������ĳ�Ա������ʵ����ͬһ���������������������棬һ��Ϊvoid*���ͣ�һ��Ϊʵ�ʾ�������
	 *
	 * @param std::map<std::string, std::vector<void*>>& dataSet keyΪ�������ƣ�valueΪ��Ӧ���͵Ķ��󼯺�
	 * @param const std::vector<std::string>& objNameSet Ŀ��ת�����͵����Ƽ���
	 *
	 **/
	void concretizeAll(std::map<std::string, std::vector<void*>>& dataSet,
		const std::vector<std::string>& objNameSet);
	void clear();
	
private:
	void concretizeFlight(const std::vector<void*>& objSet, std::vector<Segment*>* segmentSet);
	void concretizeCrew(const std::vector<void*>& objSet, std::vector<CREW*>* crewSet);
	void concretizeBase(const std::vector<void*>& objSet, std::vector<BASE*>* baseSet);

	void concretizeCrewBase(const std::vector<void*>& objSet, std::vector<CREW_BASE*>* crewBaseSet);
	void concretizeCrewRank(const std::vector<void*>& objSet, std::vector<CREW_RANK*>* crewRankSet);
	void concretizeFlightComposition(const std::vector<void*>& objSet,
		std::vector<csvActivityComposition*>* fltCompositionSet);
	void concretizeComposition(const std::vector<void*>& objSet,
		std::vector<csvComposition*>* compositionSet);

	std::vector<Segment*> _segSet;
	std::vector<BASE*> _baseSet;
	std::vector<CREW*> _crewSet;
	std::vector<CREW_RANK*> _crew_rankSet;
	std::vector<CREW_BASE*> _crew_baseSet;
	std::vector<csvActivityComposition*> _fltCompositionSet;
	std::vector<csvComposition*> _compositionSet;
}; // end of Concretizer

class ProblemBuilder;
class Problem 
{
public:	
	class ProblemBuilder
	{
		friend class Problem;
	public:
		ProblemBuilder(Concretizer concretizer);
		
		~ProblemBuilder() {
			_segSet.clear();
			_crewSet.clear();
			_baseSet.clear();
			_crew_baseSet.clear();
			_crew_rankSet.clear();
			_fltCompositionSet.clear();
			_compositionSet.clear();
			_airportSet.clear();
		}

		/*
		 * @brief ��˳��ִ�г�ʼ��
		 **/
		Problem* build();		

	private:
		/*
		 * @brief ��������skill����
		 * @attention TO BE FINISHED����ǰ��������һ����ԭ����"PlateauAirport"
		 **/
		void loadAllSkills();
		/*
		 * @brief ����ԭʼ���ͣ�Segment�����󴴽������������ͣ�Opt_Segment������
		 * @detail ���ı�ԭʼ���Ͷ��󣬲�����ϵķ�ʽ����ԭʼ���Ͷ�����Ϊ��Ӧ�����Ͷ���ĳ�Ա
		 *
		 * @param std::vector<Opt_Segment*>* optSegSet ԭʼ���Ͷ��󼯺�
		 * @attention �ж�̬�ڴ����(new Opt_Segment)����
		 **/
		void createOptSegments();
		/*
		 * @brief ����ԭʼ���ͣ�CREW�����󴴽������������ͣ�Opt_CREW������
		 * @detail ���ı�ԭʼ���Ͷ��󣬲�����ϵķ�ʽ����ԭʼ���Ͷ�����Ϊ��Ӧ�����Ͷ���ĳ�Ա
		 *
		 * @param std::vector<Opt_CREW*>* optCrewSet ԭʼ���Ͷ��󼯺�
		 * @attention �ж�̬�ڴ����(new Opt_CREW)����
		 **/
		void createOptCrews();
		/*
		 * @brief ��ֵ��Opt_Segment�����Ҫ��
		 * @param std::vector<Opt_Segment*>* optSegSet
		 **/
		void matchOptSegmentAndComposition();
		/*
		 * @brief ��ֵ��ÿ��Opt_Segment����Ҫ�ĸ���rank������
		 * @param std::vector<Opt_Segment*>* optSegSet
		**/
		void setRankToNumMapOfOptSegment();
		/*
		 * @brief ����Opt_Crew��rankAry
		 * @param std::vector<Opt_CREW*>* optCrewSet
		 **/
		void matchOptCrewAndRankAry();
		/*
		 * @brief ����Opt_Crew��baseAry
		 * @param std::vector<Opt_CREW*>* optCrewSet
		 **/
		void matchOptCrewAndBaseAry();
		/*
		 * @brief ��ʼ��crew��skillsmap
		 * @detail set crew.skillMap[skill] = 0, foreach skill in skillSet
		 * @param std::vector<Opt_CREW*>* optCrewSet
		 * @attention �ȼ��crew��skillMap�Ƿ�Ϊ��ʼ״̬����Ϊ��
		 *
		 **/
		void initializeCrewSkills();
		/*
		 * @brief ��ֵ��Opt_Crew�ڼ���optCrewSet�е��±�
		 * @detail ȫ�ֵ�optCrewSet������ı䣬�������Opt_Crew��indexҲ����ı䣬���ڲ���
		 **/
		void setIndexOfCrew();
		/*
		 * @brief ��ÿ��crew��rank�����µ�ʱ������
		 **/
		void sortCrewRank();

		void setCrewLatestRankAndPosition();

		/*
		 * @brief ��ֵ������airport�ļ���
		 **/
		void setAirportSet();

		/*���¼��ϴ��void*ת��Ϊ��Ӧ���ͺ�Ķ���
		 * ��������Ϊ��ֱ�������������
		 */

		std::vector<Segment*> _segSet;
		std::vector<BASE*> _baseSet;
		std::vector<CREW*> _crewSet;
		std::vector<CREW_RANK*> _crew_rankSet;
		std::vector<CREW_BASE*> _crew_baseSet;
		std::vector<csvActivityComposition*> _fltCompositionSet;
		std::vector<csvComposition*> _compositionSet;

		/*���¼��ϴ��void*ת��Ϊ��Ӧ���ͺ�Ķ���*/
		std::vector<Opt_CREW*> _optCrewSet;
		std::vector<Opt_Segment*> _optSegSet;


		std::set<std::string> _skillSet; //���е�crew skill
		std::vector<std::string> _airportSet;

	}; // end of ProblemBuilder

	Problem(const ProblemBuilder& builder); 
	
	static el::Logger* logger;	

	const std::vector<Segment*>& getSegmentSet() const { return _segSet; }
	const std::vector<CREW*>& getCrewSet() const { return _crewSet; }
	const std::vector<BASE*>& getBaseSet() const { return _baseSet; }
	const std::vector<CREW_BASE*>& getCrewBaseSet() const { return _crew_baseSet; }
	const std::vector<CREW_RANK*>& getCrewRankSet() const { return _crew_rankSet; }
	
	const std::vector<csvActivityComposition*>& getFltCompositonSet() const { return _fltCompositionSet; }
	const std::vector<csvComposition*>& getCompositionSet() const { return _compositionSet; }

	const std::set<std::string>& getSkillSet() const { return _skillSet; }
	const std::vector<std::string>& getAirptSet() const { return _airportSet; }

	const std::vector<Opt_Segment*>& getOptSegmentSet() const { return _optSegSet; }
	const std::vector<Opt_CREW*>& geOptCrewSet() const { return _optCrewSet; }
	
	
private:
	std::vector<Segment*> _segSet;	
	std::vector<CREW*> _crewSet;
	std::vector<BASE*> _baseSet;
	std::vector<CREW_BASE*> _crew_baseSet;
	std::vector<CREW_RANK*> _crew_rankSet;	
	std::vector<csvActivityComposition*> _fltCompositionSet;
	std::vector<csvComposition*> _compositionSet;

	std::set<std::string> _skillSet; //���е�crew skill
	std::vector<std::string> _airportSet;

	std::vector<Opt_Segment*> _optSegSet;
	std::vector<Opt_CREW*> _optCrewSet;

};


// end Problem





#endif // !PROBLEM_H
