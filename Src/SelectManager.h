//@file SelectManager.h


#ifndef SELECTMANAGER_H_INCLUDED
#define SELECTMANAGER_H_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "Audio.h"


/*
* �^�C�g�����ł悭���郂�[�h�I���Ȃǂ������K�w����ꍇ�Ɏg�����Ƃ�z�肵���N���X.
* �����K������Ȃ������string�^�� 1_
*
*
*
*
*/
namespace Select {


	/*
	* �\������I������1��,
	* �I���̏����������Ă���.
	*
	*
	*/
	class Manager;
	class Unit{
	public:
		friend class Manager;
		void SetChoices(std::vector<std::string>);							//
		void SetNextUnit(std::string,Unit*);
		void SetFuncPtr(void(*func)());
	private:
		std::vector<std::string> string;			//�\�����镶����_�j
		std::map<std::string, Unit*> Choices;		//���̏���������΂܂��o�^
		void(*funcPtr)() = nullptr;					//�I�����ꂽ���ɉ��������������ꍇ�͊֐���o�^����;

		unsigned int Hierarcht;						//�y�[�W�̊K�w.
	};

	/*
	* Unit�𓝊�����class
	*
	*
	*
	*
	*
	*/
	class Manager {
	public:
		Manager();
		~Manager();

		void SetEntryPoint(Unit*);					//�͂��߂ɕ\������G���g���[�|�C���g��o�^
		void ProcessInput();						//���͏���.
		void Update();								//�X�V����.
		void Render();								//�`�揈��.
		bool GetExit() const { return exitFlag; }	//�Q�b�^�[

		struct Layout {								//������`�悷�郌�C�A�E�g(�Ƃ肠������]�͏Ȃ���)
			glm::vec3 fTransform=glm::vec3(0);					//������̈ʒu
			glm::vec3 fScale = glm::vec3(2);						//�����̑傫��
			float fLarge = 1.2f;										//��剻�̕����̊g�嗦
			glm::vec2 space=glm::vec2(30,30);						//�t�H���g�ƃt�H���g�̊Ԋu
		};

		Layout layout;								//��������public
		void Back();								//��߂�.
	private:
		Unit* entryPoint;							//�͂��߂ɕ\������unit

		std::vector<Unit*> Trajectory;				//�߂�(Exit)�ɑΉ����邽�� Tranjectory/�O��
		int selectNum = 0;
		void AddSelectNum(int);						//Num�𑫂�����.
		void Transision();							//�J��

		bool exitFlag = false;								//����ȏ�߂�Ȃ���
		//��
		Audio::EngineRef audio = Audio::Engine::Instance();
		Audio::SoundPtr decision;
		Audio::SoundPtr cancell;
		Audio::SoundPtr select;

	};

}//namespace Select


#endif // !SELECTMANAGER_H_INCLUDED
