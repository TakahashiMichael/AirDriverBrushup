#include "SelectManager.h"

#include "GLFWEW.h"
#include "Font.h"
#include <iostream>
#include "FileNameData.h"


namespace Select {
	
	void Unit::SetChoices(std::vector<std::string> string) {
		for (int i = 0; i < string.size(); ++i) {
			this->string.push_back(string[i]);
		}
	}

	/*
	* �I������I�񂾎��Ɏ��ɏ�������郆�j�b�g�Ɠo�^����.
	* @param string		:�I�����̕�����.
	* @param unitPtr	:�����Ώۂɓo�^����Unit�̃|�C���^
	* ���̂Ƃ���̖��_��SetChoices���Ă��炶��Ȃ��Ƌ@�\���Ȃ�2/10
	*/
	void Unit::SetNextUnit(std::string string,Unit* unitPtr) {
		//�I�����ɓo�^����Ă��邩���ׂĂ����o�^����Ă��Ȃ��̂ł���Ώ����͂��Ȃ�
		bool strCheck = false;
		for (int i = 0; i < this->string.size(); ++i) {
			if (this->string[i] == string) {
				strCheck = true;
				break;
			}
		}
		//std::map(choices)�̕��ɕ�����ɑΉ�����unit��o�^����.
		if (strCheck) {
			this->Choices.insert(std::make_pair(string,unitPtr));
		}
		else {
			std::cout << "�f�o�b�O�s�:Select::Unit::SetNextUnit:�o�^����Ă��Ȃ��I����������ł�" << std::endl;
		}
	}

	/*
	* unit�Ɉڍs�����ۂɈ�x�����Ă΂��֐���o�^����.
	* @param (*func)()	:���s�������֐��̃|�C���^
	*
	* ���m�ɂ͂���unit�ɏ����Ώۂ��ڍs����^�C�~���O�ŌĂ΂��
	* �ڂ�����Managaer::Transision()���Q��
	*/
	void Unit::SetFuncPtr(void (*func)()) {
		this->funcPtr = func;
	}





	/*
	* �R���X�g���N�^
	*
	*/
	Manager::Manager()
	{
		decision = audio.Prepare(FILENAME_WAV_DECISION);
		cancell = audio.Prepare(FILENAME_WAV_DECISION);
		select = audio.Prepare(FILENAME_WAV_SELECT);
	}

	/*
	* �f�X�g���N�^.
	*
	*/
	Manager::~Manager()
	{
		cancell->Stop();
		decision->Stop();
	}

	/*
	* ���͏���.
	*
	*/
	void Manager::ProcessInput() {
		GLFWEW::Window& window = GLFWEW::Window::Instance();	//���͊֐������悤���邽��window���Q��.
		if (window.GetCommand(GLFWEW::Window::COMMANDLIST_DECISION)) {
			//����R�}���h�������ꂽ����
			this->Transision();
			decision->Stop();
			decision->Play();
		}
		else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_CANCEL)) {
			//�L�����Z���R�}���h�������ꂽ��
			this->Back();
			cancell->Stop();
			cancell->Play();
		}
		else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_UP_1ST)) {
			//�オ�����ꂽ��
			AddSelectNum(-1);
			select->Stop();
			select->Play();
		}
		else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_DOWN_1ST)) {
			//���R�}���h�������ꂽ��
			AddSelectNum(1);
			select->Stop();
			select->Play();
		}
		else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_RIGHT_1ST)) {
			//�E�R�}���h�������ꂽ��
		}
		else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_LEFT_1ST)) {
			//���R�}���h�������ꂽ��
		}

	}
	/*
	* �X�V����.
	*
	*
	*/
	void Manager::Update()
	{

	}

	/*
	* ��ԏ��߂ɕ\������I������o�^����.
	*
	* @param entryPoint : �o�^����I����
	*/
	void Manager::SetEntryPoint(Unit* entryPoint) {
		this->entryPoint = entryPoint;
		this->Trajectory.push_back(entryPoint);
	}

	/*
	* �`�揈��.
	*
	*
	*/
	void Manager::Render()
	{
		//font���擾
		Font& font = Font::Instance();

		for (int i = 0; i < entryPoint->string.size()+1; ++i)
		{
			//��ԉ���Exit��\�����鏈��.
			if(i==entryPoint->string.size()){
				if (i == this->selectNum) {
					font.AddString("Exit", glm::vec3(layout.space.x*i, i*((-20 * layout.fScale.y) - layout.space.y), 0), glm::vec3(0), layout.fScale * layout.fLarge);

				}
				else {
					font.AddString("Exit", glm::vec3(layout.space.x*i, i*((-20 * layout.fScale.y) - layout.space.y), 0), glm::vec3(0), layout.fScale);

				}
			}
			//�ォ�珇�Ԃ�
			else {
				if(i==this->selectNum){
					font.AddString(this->entryPoint->string[i], glm::vec3(layout.space.x*i, i*((-20 * layout.fScale.y)-layout.space.y), 0), glm::vec3(0), layout.fScale * layout.fLarge);
				}
				else {
					font.AddString(this->entryPoint->string[i], glm::vec3(layout.space.x*i, i*((-20 * layout.fScale.y) - layout.space.y), 0), glm::vec3(0), layout.fScale);
				}
			}

		}



	}



	void Manager::AddSelectNum(int i) {
		this->selectNum += i;
		if (this->selectNum < 0) {
			this->selectNum = this->entryPoint->string.size();
		}
		else if(this->selectNum> this->entryPoint->string.size()) {
			this->selectNum = 0;
		}
	}
	/*
	* �J��.���̃��j�b�g���g��.���̍ۂ�.
	* unit�����֐������s.
	*
	*
	*/
	void Manager::Transision() {
		//Exit��I�񂾏ꍇ�̏���(�߂�)
		if (this->selectNum == this->entryPoint->string.size()) {
			this->Back();
		}
		else {
			std::string nextUnitStr = this->entryPoint->string[this->selectNum];
			//�I�����}�b�v�����݂��邩�m�F.����͌�ɏ�������2/10.
			if (this->entryPoint->Choices.count(nextUnitStr)) {
				if (this->entryPoint->Choices.at(nextUnitStr) != nullptr) {

					//���̑I�����̃|�C���^��null�łȂ���Ώ����Ώۂɓo�^.�O�Ղɂ��ǉ�
					this->Trajectory.push_back(this->entryPoint->Choices.at(nextUnitStr));
					this->entryPoint = this->entryPoint->Choices.at(nextUnitStr);

					//�ԍ���0��
					this->selectNum = 0;

					//���̍ۂɎ��̑I�����ɓo�^����Ă���֐�������Ύ��s����.
					if (this->entryPoint->funcPtr != nullptr) {
						this->entryPoint->funcPtr();
					}
				}
			}
			else {
				std::cout << "�f�o�b�O:Select::Manager::Transition:Unit�Ƀ}�b�v���o�^����Ă��Ȃ�" << std::endl;
			}
		}
	}

	/*
	* ��O��Unit�ɖ߂鏈��
	* Exit�Ƃ��L�����Z���R�}���h�Ŕ��������Ă���./
	*
	*/
	void Manager::Back() {
		if (Trajectory.size() <= 1) {
			//����ȏ�߂�Ȃ���
			exitFlag = true;
		}
		else {
			//��߂����l��entryPoint�ɓo�^.
			this->entryPoint = this->Trajectory[Trajectory.size() - 2];
			this->Trajectory.pop_back();
			this->selectNum = 0;
		}
	}
}//namespace Select