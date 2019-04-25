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
	* 選択肢を選んだ時に次に処理されるユニットと登録する.
	* @param string		:選択肢の文字列.
	* @param unitPtr	:処理対象に登録するUnitのポインタ
	* 今のところの問題点はSetChoicesしてからじゃないと機能しない2/10
	*/
	void Unit::SetNextUnit(std::string string,Unit* unitPtr) {
		//選択肢に登録されているか調べてもし登録されていないのであれば処理はしない
		bool strCheck = false;
		for (int i = 0; i < this->string.size(); ++i) {
			if (this->string[i] == string) {
				strCheck = true;
				break;
			}
		}
		//std::map(choices)の方に文字列に対応するunitを登録する.
		if (strCheck) {
			this->Choices.insert(std::make_pair(string,unitPtr));
		}
		else {
			std::cout << "デバッグ不具合:Select::Unit::SetNextUnit:登録されていない選択肢文字列です" << std::endl;
		}
	}

	/*
	* unitに移行した際に一度だけ呼ばれる関数を登録する.
	* @param (*func)()	:実行したい関数のポインタ
	*
	* 正確にはこのunitに処理対象が移行するタイミングで呼ばれる
	* 詳しくはManagaer::Transision()を参照
	*/
	void Unit::SetFuncPtr(void (*func)()) {
		this->funcPtr = func;
	}





	/*
	* コンストラクタ
	*
	*/
	Manager::Manager()
	{
		decision = audio.Prepare(FILENAME_WAV_DECISION);
		cancell = audio.Prepare(FILENAME_WAV_DECISION);
		select = audio.Prepare(FILENAME_WAV_SELECT);
	}

	/*
	* デストラクタ.
	*
	*/
	Manager::~Manager()
	{
		cancell->Stop();
		decision->Stop();
	}

	/*
	* 入力処理.
	*
	*/
	void Manager::ProcessInput() {
		GLFWEW::Window& window = GLFWEW::Window::Instance();	//入力関数をしようするためwindowを参照.
		if (window.GetCommand(GLFWEW::Window::COMMANDLIST_DECISION)) {
			//決定コマンドが押された処理
			this->Transision();
			decision->Stop();
			decision->Play();
		}
		else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_CANCEL)) {
			//キャンセルコマンドが押された時
			this->Back();
			cancell->Stop();
			cancell->Play();
		}
		else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_UP_1ST)) {
			//上が押された時
			AddSelectNum(-1);
			select->Stop();
			select->Play();
		}
		else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_DOWN_1ST)) {
			//下コマンドが押された時
			AddSelectNum(1);
			select->Stop();
			select->Play();
		}
		else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_RIGHT_1ST)) {
			//右コマンドが押された時
		}
		else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_LEFT_1ST)) {
			//左コマンドが押された時
		}

	}
	/*
	* 更新処理.
	*
	*
	*/
	void Manager::Update()
	{

	}

	/*
	* 一番初めに表示する選択肢を登録する.
	*
	* @param entryPoint : 登録する選択肢
	*/
	void Manager::SetEntryPoint(Unit* entryPoint) {
		this->entryPoint = entryPoint;
		this->Trajectory.push_back(entryPoint);
	}

	/*
	* 描画処理.
	*
	*
	*/
	void Manager::Render()
	{
		//fontを取得
		Font& font = Font::Instance();

		for (int i = 0; i < entryPoint->string.size()+1; ++i)
		{
			//一番下にExitを表示する処理.
			if(i==entryPoint->string.size()){
				if (i == this->selectNum) {
					font.AddString("Exit", glm::vec3(layout.space.x*i, i*((-20 * layout.fScale.y) - layout.space.y), 0), glm::vec3(0), layout.fScale * layout.fLarge);

				}
				else {
					font.AddString("Exit", glm::vec3(layout.space.x*i, i*((-20 * layout.fScale.y) - layout.space.y), 0), glm::vec3(0), layout.fScale);

				}
			}
			//上から順番に
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
	* 遷移.次のユニットを使う.その際に.
	* unitが持つ関数を実行.
	*
	*
	*/
	void Manager::Transision() {
		//Exitを選んだ場合の処理(戻る)
		if (this->selectNum == this->entryPoint->string.size()) {
			this->Back();
		}
		else {
			std::string nextUnitStr = this->entryPoint->string[this->selectNum];
			//選択肢マップが存在するか確認.これは後に消したい2/10.
			if (this->entryPoint->Choices.count(nextUnitStr)) {
				if (this->entryPoint->Choices.at(nextUnitStr) != nullptr) {

					//次の選択肢のポインタがnullでなければ処理対象に登録.軌跡にも追加
					this->Trajectory.push_back(this->entryPoint->Choices.at(nextUnitStr));
					this->entryPoint = this->entryPoint->Choices.at(nextUnitStr);

					//番号を0に
					this->selectNum = 0;

					//その際に次の選択肢に登録されている関数があれば実行する.
					if (this->entryPoint->funcPtr != nullptr) {
						this->entryPoint->funcPtr();
					}
				}
			}
			else {
				std::cout << "デバッグ:Select::Manager::Transition:Unitにマップが登録されていない" << std::endl;
			}
		}
	}

	/*
	* 一つ前のUnitに戻る処理
	* Exitとかキャンセルコマンドで発動させてくれ./
	*
	*/
	void Manager::Back() {
		if (Trajectory.size() <= 1) {
			//これ以上戻れない時
			exitFlag = true;
		}
		else {
			//一つ戻した値をentryPointに登録.
			this->entryPoint = this->Trajectory[Trajectory.size() - 2];
			this->Trajectory.pop_back();
			this->selectNum = 0;
		}
	}
}//namespace Select